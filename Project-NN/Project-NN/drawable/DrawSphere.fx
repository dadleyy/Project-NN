//--------------------------------------------------------------------------------------
// File: Tutorial02.fx
//
// Copyright (c) Microsoft Corporation. All rights reserved.
//--------------------------------------------------------------------------------------

struct VERTEX
{   float4 Pos : POSITION;    };

struct PIXEL
{	float4 Pos : SV_POSITION; float depth : DEPTH;};



//*********************************
// Vertex Shader
//*********************************
PIXEL VS( VERTEX input )
{
    PIXEL output = (PIXEL)0;

	float4 i = input.Pos;
	i.z = .5;

	output.Pos = i;
	output.depth = input.Pos.z;

	return output;
}


//*********************************
// Pixel Shader 2
//*********************************
float4 PS( PIXEL input ) : SV_Target
{
	float4 final =  float4( 1.0f, 1.0f, 1.0f, 1.0f );
	final = final - (1-input.depth);
	return final;
}