//Amb = 0; Dir = 1; Point = 2; Spot = 3
//noFalloff = 0; linear = 1; quadratic = 2
struct Light
{   
	float4	Lposition;		//      : POINT : SPOT
	float4	Lcolor;			//DIR	: POINT : SPOT : AMBIENT
	float4	Ldirection;		//DIR	:       : SPOT
	float	Lradius;		//		: POINT	: SPOT
	float	Langle;			//		:		: SPOT
	float	Lintensity;		//DIR	: POINT : SPOT : AMBIENT
	int		Lfalloff;		//		: POINT : SPOT
	int		LonOff;			//DIR	: POINT : SPOT
	int		Ltype;			//DIR	: POINT : SPOT
	float2	Lpad;
};


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

cbuffer LightsBuffer
{
	Light lights[10];
	int numLights;
	float3 pad;
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
	float2 UV: TEXCOORD;
};

struct PIXEL
{	
	float4 Pos : SV_POSITION; 
	float4 Col : COLOR0;
	float3 worldPosition : TEXCOORD0;
	float3 worldNormal : TEXCOORD1;
	float2 UV : TEXCOORD2;	
};

float4 AmbientLight(Light light)
{
	return light.Lintensity * light.Lcolor;
}

float4 DirectionalLight(Light light, float3 normal)
{
	return light.Lintensity * dot(light.Ldirection.xyz, normal) * light.Lcolor;
}

float4 PointLight(Light light, float3 shadePoint, float3 normal, float3 eyePosition)
{
	float3 L = light.Lposition.xyz - shadePoint;
	float3 V = -normalize(eyePosition - shadePoint);
	float3 R = normalize(reflect(V, normal));
	float radiusSq = light.Lradius*light.Lradius;
	float distSq = dot(L, L);
	L = normalize(L);

	float3 diffuseColor = 0;
	float3 specularColor = 0;
	if(radiusSq > distSq || radiusSq == 0)
	{
		float intensity;

		//no falloff
		if(light.Lfalloff == 0 || radiusSq == 0)
		{
			diffuseColor = light.Lcolor.xyz * max(0, dot(L, normal));
			specularColor = float3(1,1,1) * pow( max(0, dot(R, L)), 25 );
		}

		//linear falloff
		else if(light.Lfalloff == 1)
		{
			float k = (1-sqrt(distSq)/light.Lradius);
			diffuseColor = light.Lcolor.xyz * max(0, dot(L, normal)) * k;
			specularColor = light.Lcolor.xyz * pow( max(0, dot(R, L)), 25 ) * k;
		}

		//quadratic falloff
		else if(light.Lfalloff == 2)
		{
			float k = (1-distSq/radiusSq);
			diffuseColor = light.Lcolor.xyz * max(0, dot(L, normal)) * k;
			specularColor = light.Lcolor.xyz * pow( max(0, dot(R, L)), 25 ) * k;
		}
	}

	return float4((specularColor+diffuseColor)*light.Lintensity, 1.0);
}


float4 SpotLight(Light light, float3 shadePoint, float3 normal, float3 eyePosition)
{
	float3 L = light.Lposition.xyz - shadePoint;
	float3 V = -normalize(eyePosition - shadePoint);
	float3 R = normalize(reflect(V, normal));
	float radiusSq = light.Lradius*light.Lradius;
	float distSq = dot(L, L);
	L = normalize(L);

	float3 diffuseColor = 0;
	float3 specularColor = 0;
	if(cos(light.Langle) < dot(-L, normalize(light.Ldirection)))
	{
		float intensity;

		//no falloff
		if(light.Lfalloff == 0)
		{
			diffuseColor = light.Lcolor.xyz * max(0, dot(L, normal));
			specularColor = float3(1,1,1) * pow( max(0, dot(R, L)), 25 );
		}

		//linear falloff
		else if(light.Lfalloff == 1)
		{
			float k = (1-sqrt(distSq)/light.Lradius);
			diffuseColor = light.Lcolor.xyz * max(0, dot(L, normal)) * k;
			specularColor = light.Lcolor.xyz * pow( max(0, dot(R, L)), 25 ) * k;
		}

		//quadratic falloff
		else if(light.Lfalloff == 2)
		{
			float k = (1-distSq/radiusSq);
			diffuseColor = light.Lcolor.xyz * max(0, dot(L, normal)) * k;
			specularColor = light.Lcolor.xyz * pow( max(0, dot(R, L)), 25 ) * k;
		}
	}

	return float4((specularColor+diffuseColor)*light.Lintensity, 1.0);
}

//*********************************
// Vertex Shader
//*********************************
PIXEL VS( VERTEX input )
{
    PIXEL output = (PIXEL)0;

	float4 i = mul(worldMatrix, input.Pos);
	float4 worldPos = i;
	i =		   mul(viewMatrix, i);
	i =        mul(fovScaling, i);

	output.Pos = i;
	output.Col = 1;
	output.worldPosition = worldPos.xyz;
	output.worldNormal   = input.Norm;

	output.UV = input.UV;

	return output;
}



//*********************************
// Pixel Shader
//*********************************
float4 PS( PIXEL input ) : SV_Target
{
	float4 finalColor = 0;
	float4 texColor = diffuseMap.Sample(samAnisotropic, input.UV);

	for(int i = 0; i < numLights; i++)
	{
		if(lights[i].LonOff != 0)
		{
			if(lights[i].Ltype == 0)
				finalColor += texColor * AmbientLight(lights[i]);
			if(lights[i].Ltype == 1)
				finalColor += texColor*DirectionalLight(lights[i], input.worldNormal);
			if(lights[i].Ltype == 2)
				finalColor += texColor*PointLight(lights[i], input.worldPosition, input.worldNormal, cameraPosition);
			if(lights[i].Ltype == 3)
				finalColor += texColor*SpotLight(lights[i], input.worldPosition, input.worldNormal, cameraPosition);
		}
	}

	return finalColor;
}


technique11 Render
{
    pass P0
    {
        SetVertexShader( CompileShader( vs_4_0, VS() ) );
        SetGeometryShader( NULL );
        SetPixelShader( CompileShader( ps_4_0, PS() ) );
    }
}