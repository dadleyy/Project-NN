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

SamplerState samAnisotropic
{
	Filter = ANISOTROPIC;
	MaxAnisotropy = 4;

	AddressU = WRAP;
	AddressV = WRAP;
};

SamplerState nearestPixel
{
	Filter = MIN_MAG_MIP_POINT;

	AddressU = CLAMP;
	AddressV = CLAMP;
};

Texture2D depth;
Texture2D glowTex;
float2 texDimensions;
float4 color = float4(1,0,0,1);
int colorMode = 1; //0 to use color, 1 to use texture, 2 to use texture*color

struct VERTEX
{   
	float4 Pos : POSITION;    
	float3 Norm : NORMAL;
	float2 UV: TEXCOORD;
};

struct PIXEL
{	
	float4 Pos : SV_POSITION; 
	float4 Col : COLOR0;
	float2 UV : TEXCOORD2;	
};


//*********************************
// Vertex Shader
//*********************************
PIXEL VS( VERTEX input )
{
    PIXEL output = (PIXEL)0;

	float4 i = mul(worldMatrix, input.Pos);
	i =		   mul(viewMatrix, i);
	i =        mul(fovScaling, i);

	output.Pos = i;
	output.Col = 1;

	output.UV = input.UV;

	return output;
}



//*********************************
// Pixel Shader
//*********************************
float4 PS( PIXEL input ) : SV_Target
{
	float4 finalColor = 0;
	float4 d = depth.Sample(nearestPixel, float2(input.Pos.x/texDimensions.x, input.Pos.y/texDimensions.y));

	if(abs(input.Pos.z) <= d.x +.000001 && input.Pos.z >= 0)
	{
		if(colorMode == 1)
		{
			finalColor = glowTex.Sample(samAnisotropic, input.UV);;
		}
		else if(colorMode == 2)
		{
			finalColor = color*glowTex.Sample(samAnisotropic, input.UV);;
		}
		else
		{
			finalColor = color;
		}
	}
	else
		discard;

	return finalColor;
}


technique11 RenderGlowy
{
    pass P0
    {
        SetVertexShader( CompileShader( vs_4_0, VS() ) );
        SetGeometryShader( NULL );
        SetPixelShader( CompileShader( ps_4_0, PS() ) );
    }
}