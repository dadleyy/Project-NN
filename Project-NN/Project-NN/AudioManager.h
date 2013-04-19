#pragma once

#include <Windows.h>
#include <vector>
#include <unordered_map>
#include <iostream>
#include "framework\d3dUtil.h"
#include <XAudio2.h>
#include "framework\SDKwavefile.h"

using namespace std;

enum AUDIOTYPE {
	BACKGROUND,
	EFFECT
};

struct Sound {
	IXAudio2SourceVoice* voice;
	AUDIOTYPE type;
	XAUDIO2_BUFFER buffer;
	unsigned char* data;
	char* name;
};

class AudioManager {

public:
	AudioManager( );
	~AudioManager( );

	int Initialize( );
	int LoadSound( LPWSTR fname, char* name, AUDIOTYPE type );
	int PlaySound( char* name );

	void Volume( float v );
	float Volume( void );

private:

	int RestartSound( char* name );
	int DesroySound( Sound* s );

	bool ready;

	IXAudio2* engine;
	IXAudio2MasteringVoice* masterVoice;

	unordered_map< char*, Sound> sounds;

};