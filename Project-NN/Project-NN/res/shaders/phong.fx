cbuffer cbPerObject 
{
	float4x4 world;
	float4x4 ViewProj; 
	float4x4 normalTransform;
};

cbuffer sceneAttributes
{
	float3 cameraPosition;
	float pad;
};

SamplerState samAnisotropic
{
	Filter = ANISOTROPIC;
	MaxAnisotropy = 4;

	AddressU = WRAP;
	AddressV = WRAP;
};

Texture2D diffuseMap;

struct VERTEX
{   
	float4 Pos : POSITION;    
	float3 Norm : NORMAL;
	float2 Tex: TEXCOORD;
};

struct PIXEL
{	
	float4 Pos  :   SV_POSITION; 
	float3 N	:	TEXCOORD0;
	float3 L	:	TEXCOORD1;
	float3 H	:	TEXCOORD2;
	float3 V	:	TEXCOORD3;
	float2 Tex	:	TEXCOORD4;
};

//*********************************
// Vertex Shader
//*********************************
PIXEL VS( VERTEX input )
{
    PIXEL output = (PIXEL)0;
	float3 lightPosition = float3(0, 0, 0);

	float4 worldCoord = mul(input.Pos, world);
	float3 pos = worldCoord.xyz;
	output.Pos = mul( worldCoord, ViewProj );

	output.N = normalize(input.Norm);
	output.L = normalize(lightPosition - pos);
	output.V = normalize(cameraPosition - pos);
	output.H = normalize(output.V+output.L);

	output.Tex = input.Tex;

	return output;
}



//*********************************
// Pixel Shader
//*********************************
float4 PS( PIXEL input ) : SV_Target
{
	float4 ObjectColor = diffuseMap.Sample(samAnisotropic, input.Tex);
	//float4 ObjectColor =  float4( 0.3f, 0.3f, 0.8f, 1.0f );
	float4 finalColor = float4(0,0,0,1.0);
	float4 white = float4(1.0,1.0,1.0,0.0);

	//reflect the View vector over the normal:: The halfway vector wasn't interpolating correctly for some reason
	float3 R = normalize(reflect(-input.V, input.N));
	
	//get the diffuse shading
	finalColor = ObjectColor*max(0, dot(input.N, input.L));
	//get the specular highlight
	finalColor = finalColor + white*pow( max(0,dot(R, input.L)), 25 );
	finalColor = finalColor + ObjectColor*float4(.2,.2,.2,0.0);

	return finalColor;
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