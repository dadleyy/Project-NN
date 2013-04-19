
//generic post process that draws the texture exactly as it appears
Texture2D tex;



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
float4 PS( PIXEL input ) : SV_Target
{
	return float4(0, 1,0,0)*tex.Sample(textureSampler, input.UV);
}


technique11 Render
{
    pass P0
    {
        SetVertexShader( CompileShader( vs_5_0, VS() ) );
        SetGeometryShader( NULL );
        SetPixelShader( CompileShader( ps_5_0, PS() ) );
    }
}