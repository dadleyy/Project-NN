#include "AudioManager.h"

AudioManager::AudioManager( ) : engine(0), ready(false), masterVoice(0)
{ }

void AudioManager::Volume( float v ){ masterVoice->SetVolume(v); }
float AudioManager::Volume( void ) { float f; masterVoice->GetVolume( &f ); return f; }

int AudioManager::Initialize( ) 
{
	HRESULT hr;

	hr = CoInitializeEx( 0, COINIT_MULTITHREADED );
	if( hr != S_OK )
		return 0;

	hr = XAudio2Create( &engine, 0, XAUDIO2_DEFAULT_PROCESSOR );
	if( FAILED(hr) )
		return 0;

	hr = engine->CreateMasteringVoice( &masterVoice );
	if( FAILED(hr) )
		return 0;


	masterVoice->SetVolume( 0.25f );

	ready = true;
	return 1;
}

int AudioManager::DesroySound( Sound* s )
{	
	if( s->voice != 0 )
		s->voice->DestroyVoice( );
	
	free( s->data );
	return 1;
}

int AudioManager::LoadSound( LPWSTR fname, char* name, AUDIOTYPE type )
{
	if( ready == false )
		return -1;

	Sound s;
	s.voice = 0;
	s.data = (unsigned char*) calloc( 0, 0 );

	IXAudio2SourceVoice* src;
	CWaveFile wav;
	HRESULT status;

	status = wav.Open( fname, 0, WAVEFILE_READ );
	if( status != S_OK )
		return status;
	
	WAVEFORMATEX* format = wav.GetFormat( );
	unsigned long size = wav.GetSize( );
	unsigned char* data = new unsigned char[size];
	status = wav.Read( data, size, &size );
	s.data = data;

	if( status != S_OK )
		return DesroySound( &s );	

	status = engine->CreateSourceVoice( &src, format, 0, XAUDIO2_DEFAULT_FREQ_RATIO, 0, 0, 0 );
	s.voice = src;
	if( status != S_OK )
		return DesroySound( &s );
	

	int loops = 0;
	switch( type )
	{
	case BACKGROUND:
		loops = XAUDIO2_LOOP_INFINITE;
		break;
	case EFFECT:
		loops = 0;
		break;
	default:
		loops = 0;
		break;
	}

	XAUDIO2_BUFFER buffer = { 0 };
	buffer.pAudioData = data;
	buffer.Flags = XAUDIO2_END_OF_STREAM;
	buffer.AudioBytes = size;
	buffer.LoopCount = loops;

	status = src->SubmitSourceBuffer( &buffer );
	s.buffer = buffer;

	if( status != S_OK )
		return DesroySound( &s );

	// by now, we should be good to go
	s.type = type;
	s.name = name;

	sounds.insert( make_pair<char*, Sound> (name, s) );

	return 1;
}

int AudioManager::RestartSound( char* name )
{
	Sound s;
	try {
		s = sounds[ name ];
	} catch( out_of_range e ) { return -1; }

	HRESULT status;

	status = s.voice->Stop(0);
	if( status != S_OK )
		return status;

	status = s.voice->FlushSourceBuffers( );
	if( status != S_OK )
		return status;

	status = s.voice->SubmitSourceBuffer( &s.buffer );
	if(status != S_OK)
		return status;

	return status;
}

int AudioManager::PlaySound( char* name )
{
	Sound s;
	try {
		s = sounds[ name ];
	} catch( out_of_range e ) { return -1; }

	IXAudio2SourceVoice* v = s.voice;
	AUDIOTYPE t = s.type;

	XAUDIO2_VOICE_STATE state;
	v->GetState( &state );

	// if the 
	if( t == EFFECT && state.BuffersQueued == 0 )
		RestartSound( name );

	return v->Start( );
}

AudioManager::~AudioManager( ) 
{
	int count, i;

	count = sounds.size( );
	if( count > 0 ){
		for( auto it = sounds.begin(); it != sounds.end(); ++it ){
			it->second.voice->DestroyVoice( );
			delete it->second.data;
		}
	}

	if( masterVoice != 0 )
		masterVoice->DestroyVoice( );

	if( engine != 0 )
		engine->Release( );

	CoUninitialize( );
}