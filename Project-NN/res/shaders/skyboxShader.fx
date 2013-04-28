
//generic post process that draws the texture exactly as it appears
TextureCube texCube;


cbuffer perObject
{
	float4x4 worldMatrix;
	float4x4 normalTransform;
};

cbuffer CameraBuffer
{
	float4x4 viewMatrix;
	float4x4 fovScaling;
	float3 cameraPosition;
	float Cpad;
};

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
	float3 cubeVector : TEXCOORD2;
};



//*********************************
// Vertex Shader
//*********************************
PIXEL VS( VERTEX input )
{
    PIXEL output = (PIXEL)0;

	output.Pos = mul(fovScaling, mul(viewMatrix, mul(worldMatrix, input.Pos))).xyww;
	output.Pos.z *= .9999995;
	output.cubeVector = input.Pos.xyz;
	return output;
}

//*********************************
// Pixel Shader
//*********************************
float4 PS( PIXEL input ) : SV_Target
{
	return texCube.Sample(textureSampler, input.cubeVector);
	//return float4(1,0,1,1);
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