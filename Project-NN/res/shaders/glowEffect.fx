
//generic post process that draws the texture exactly as it appears
Texture2D blurredTex1;
Texture2D blurredTex2;

float offsets[3] = {0.0, 1.3846153846, 3.2307692308};
float weights[3] = {0.2270270270, 0.3162162162,  0.0702702703};
float2 texDimensions;
float intensity = 1;
SamplerState textureSampler
{
	Filter = MIN_MAG_MIP_LINEAR;

	AddressU = CLAMP;
	AddressV = CLAMP;
};

struct VERTEX
{   
	float4 Pos : POSITION;    
	float3 Norm : NORMAL;
	float2 UV: TEXCOORD;
};

struct PIXEL
{	
	float4 Pos : SV_POSITION;
	float2 UV : TEXCOORD2;
};



//*********************************
// Vertex Shader
//*********************************
PIXEL VS( VERTEX input )
{
    PIXEL output = (PIXEL)0;

	output.Pos = input.Pos;
	output.UV = float2(input.UV.x, 1-input.UV.y);

	return output;
}

//*********************************
// Pixel Shader
//*********************************
float4 HorizontalBlur( PIXEL input ) : SV_Target
{
	float4 color = float4(0,0,0,0);
	int i;

	for(i = 0; i < 3; i++)
	{
		//samlelevel, becuase fuck everything at this point
		color += blurredTex1.SampleLevel(textureSampler, input.UV + float2(offsets[i]/texDimensions.x,0.0),0) * weights[i];
		color += blurredTex1.SampleLevel(textureSampler, input.UV + float2(-offsets[i]/texDimensions.x,0.0),0) * weights[i];
	}


	return color*intensity;
}

float4 VerticalBlur( PIXEL input ) : SV_Target
{
	float4 color = float4(0,0,0,0);
	int i;

	for(i = 0; i < 3; i++)
	{
		//samplelevel, becuase fuck everything at this point
		color += blurredTex1.SampleLevel(textureSampler, input.UV + float2(0.0, offsets[i]/texDimensions.y),0) * weights[i];
		color += blurredTex1.SampleLevel(textureSampler, input.UV + float2(0.0, -offsets[i]/texDimensions.y),0) * weights[i];
	}


	return color*intensity;
}

float4 addTex( PIXEL input ) : SV_Target
{
	float4 texColor = blurredTex1.Sample(textureSampler, input.UV) + blurredTex2.Sample(textureSampler, input.UV);
	texColor.w = 1;
	return texColor;
}

technique11 Horz
{
    pass P0
    {
        SetVertexShader( CompileShader( vs_5_0, VS() ) );
        SetGeometryShader( NULL );
        SetPixelShader( CompileShader( ps_5_0, HorizontalBlur() ) );
    }
}

technique11 Vert
{
    pass P0
    {
        SetVertexShader( CompileShader( vs_5_0, VS() ) );
        SetGeometryShader( NULL );
        SetPixelShader( CompileShader( ps_5_0, VerticalBlur() ) );
    }
}

technique11 Add
{
    pass P0
    {
        SetVertexShader( CompileShader( vs_5_0, VS() ) );
        SetGeometryShader( NULL );
        SetPixelShader( CompileShader( ps_5_0, addTex() ) );
    }
}