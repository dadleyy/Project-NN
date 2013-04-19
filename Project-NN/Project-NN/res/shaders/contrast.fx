
//generic post process that draws the texture exactly as it appears
Texture2D tex;
float threshold = 0;
float brightness = 1;

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
	float4 texColor = tex.Sample(textureSampler, input.UV);
	texColor *= brightness;

	if(texColor.x < threshold) texColor.x = 0;
	else if(texColor.x > 1 - threshold) texColor.x = 1;
	else
	{
		float range = 1 - threshold*2;
		texColor.x = (texColor.x - threshold)/range;
	}

	if(texColor.y < threshold) texColor.y = 0;
	else if(texColor.y > 1 - threshold) texColor.y = 1;
	else
	{
		float range = 1 - threshold*2;
		texColor.y = (texColor.y - threshold)/range;
	}

	if(texColor.z < threshold) texColor.z = 0;
	else if(texColor.z > 1 - threshold) texColor.z = 1;
	else
	{
		float range = 1 - threshold*2;
		texColor.z = (texColor.z - threshold)/range;
	}

	return texColor;
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