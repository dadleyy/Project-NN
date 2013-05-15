//
//
cbuffer perObject
{
	float4x4 worldMatrix;
};

Texture2D buttonTexture;

SamplerState linearSample
{
	Filter = MIN_MAG_MIP_LINEAR;
};

cbuffer CameraBuffer
{
	float4x4 viewMatrix;
	float4x4 fovScaling;
	float3 cameraPosition;
	float Cpad;
};

struct VERTEX
{   
	float2 Pos : POSITION;    
	float Width : WIDTH;  
	float Height : HEIGHT;
};

struct PIXEL
{	
	float4 Pos : SV_POSITION; 
	float4 Col : COLOR0;
	float2 UV : TEXCOORD2;	
};

VERTEX VS( VERTEX input )
{
	return input;
}

[maxvertexcount(6)]
void GS( point VERTEX v[1], inout TriangleStream<PIXEL> output )
{
	PIXEL p;
	float height = v[0].Height;
	float width = v[0].Width;
	float2 pos = v[0].Pos;
	
	float hh = height * 0.5f;
	float hw = width * 0.5f;
	
	float4 positions[4];
	positions[0] = float4( (pos.x - hw), (pos.y - hh), 1.0f, 1.0f );
	positions[1] = float4( (pos.x - hw), (pos.y + hh), 1.0f, 1.0f );
	positions[2] = float4( (pos.x + hw), (pos.y + hh), 1.0f, 1.0f );
	positions[3] = float4( (pos.x + hw), (pos.y - hh), 1.0f, 1.0f );
	
	// texture co-ordinate mapping
	float2 tc[4];
	tc[1] = float2(0.0f, 0.0f); //the origin
	tc[0] = float2(0.0f, 1.0f); //bottom left
	tc[2] = float2(1.0f, 0.0f); //top right
	tc[3] = float2(1.0f, 1.0f); //borrom right

	

	p.Pos = mul( fovScaling, mul( viewMatrix, mul( worldMatrix, positions[0] ) ) );
	p.Col = float4( 1.0f, 1.0f, 1.0f, 1.0f );
	p.UV = tc[0];
	output.Append( p );
	
	p.Pos = mul( fovScaling, mul( viewMatrix, mul( worldMatrix, positions[1] ) ) );
	p.Col = float4( 1.0f, 1.0f, 1.0f, 1.0f );
	p.UV = tc[1];
	output.Append( p );
	
	p.Pos = mul( fovScaling, mul( viewMatrix, mul( worldMatrix, positions[2] ) ) );
	p.Col = float4( 1.0f, 1.0f, 1.0f, 1.0f );
	p.UV = tc[2];
	output.Append( p );
	
	output.RestartStrip( );
	
	p.Pos = mul( fovScaling, mul( viewMatrix, mul( worldMatrix, positions[0] ) ) );
	p.Col = float4( 1.0f, 1.0f, 1.0f, 1.0f );
	p.UV = tc[0];
	output.Append( p );
	
	p.Pos = mul( fovScaling, mul( viewMatrix, mul( worldMatrix, positions[2] ) ) );
	p.Col = float4( 1.0f, 1.0f, 1.0f, 1.0f );
	p.UV = tc[2];
	output.Append( p );
	
	p.Pos = mul( fovScaling, mul( viewMatrix, mul( worldMatrix, positions[3] ) ) );
	p.Col = float4( 1.0f, 0.0f, 1.0f, 1.0f );
	p.UV = tc[3];
	output.Append( p );
	
}

float4 PS( PIXEL input ) : SV_Target
{
	
	float4 finalColor = buttonTexture.Sample(linearSample, input.UV);
	return finalColor;
}

technique11 Render
{
    pass P0
    {
        SetVertexShader( CompileShader( vs_5_0, VS( ) ) );
        SetGeometryShader( CompileShader( gs_5_0, GS( ) ) );
        SetPixelShader( CompileShader( ps_5_0, PS( ) ) );
    }
}