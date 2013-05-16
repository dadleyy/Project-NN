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
	int		LonOff;			//DIR	: POINT : SPOT
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
Texture2D bumpMap;

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
	float3 worldTangent :TEXCOORD2;
	float3 worldBiTangent: TEXCOORD3;
	float2 UV : TEXCOORD4;	
};

float4 AmbientLight(Light light)
{
	return light.Lintensity * light.Lcolor;
}

float4 DirectionalLight(Light light, float3 normal)
{
	return max(0,light.Lintensity * dot(light.Ldirection.xyz, normal) * light.Lcolor);
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
	float angleDot = dot(-L, normalize(light.Ldirection.xyz));
	float angleCos = cos(light.Langle);

	if(angleCos < angleDot)
	{
		float intensity;

		if(light.Lradius == 0)
		{
			//no falloff
			if(light.Lfalloff == 0)
			{
				diffuseColor = light.Lcolor.xyz * max(0, dot(L, normal));
				specularColor = float3(1,1,1) * pow( max(0, dot(R, L)), 25 );
			}
			//linear falloff
			else if(light.Lfalloff == 1)
			{
				float k = 1/(sqrt(distSq));
				diffuseColor = light.Lcolor.xyz * max(0, dot(L, normal)) * k;
				specularColor = light.Lcolor.xyz * pow( max(0, dot(R, L)), 25 ) * k;
			}

			//quadratic falloff
			else if(light.Lfalloff == 2)
			{
				float k = 1/distSq;
				diffuseColor = light.Lcolor.xyz * max(0, dot(L, normal)) * k;
				specularColor = light.Lcolor.xyz * pow( max(0, dot(R, L)), 25 ) * k;
			}
		}

		if(light.Lradius > 0)
		{
			//no falloff
			if(light.Lfalloff == 0)
			{
				diffuseColor = light.Lcolor.xyz * max(0, dot(L, normal));
				specularColor = float3(1,1,1) * pow( max(0, dot(R, L)), 25 );
			}
			//linear falloff
			else if(light.Lfalloff == 1)
			{
				float k = 1-(sqrt(distSq)/light.Lradius);
				diffuseColor = light.Lcolor.xyz * max(0, dot(L, normal)) * k;
				specularColor = light.Lcolor.xyz * pow( max(0, dot(R, L)), 25 ) * k;
			}

			//quadratic falloff
			else if(light.Lfalloff == 2)
			{
				float k = max(0,1-(distSq/radiusSq));
				diffuseColor = light.Lcolor.xyz * max(0, dot(L, normal)) * k;
				specularColor = light.Lcolor.xyz * pow( max(0, dot(R, L)), 25 ) * k;
			}
		}

		//penumbra
		float anglePercent = acos(angleDot)/acos(angleCos);
		if(anglePercent > .95)
		{
			diffuseColor  *= (.05-(anglePercent - .95))/.05;
			specularColor *= (.05-(anglePercent - .95))/.05;
		}
	}
	specularColor.x = max(0, specularColor.x);
	specularColor.y = max(0, specularColor.y);
	specularColor.z = max(0, specularColor.z);

	diffuseColor.x = max(0, diffuseColor.x);
	diffuseColor.y = max(0, diffuseColor.y);
	diffuseColor.z = max(0, diffuseColor.z);

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
	output.worldNormal   = mul(normalTransform, float4(input.Norm, 1.0)).xyz;

	float3 temp1 = cross(output.worldNormal, float3(1,0,0));
	float3 temp2 = cross(output.worldNormal, float3(0,1,0));

	if(length(temp1) > length(temp2))
		output.worldTangent = temp1;
	else
		output.worldTangent = temp2;

	output.worldBiTangent = cross(output.worldNormal, output.worldTangent);


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
	float4 bumpNormal = bumpMap.Sample(samAnisotropic, input.UV);
	bumpNormal.xy = (bumpNormal.xy-.5)*2;
	float3 bump = input.worldTangent*bumpNormal.x + input.worldBiTangent*bumpNormal.y + input.worldNormal*bumpNormal.z;

	for(int i = 0; i < numLights; i++)
	{
		if(lights[i].LonOff != 0)
		{
			if(lights[i].Ltype == 0)
				finalColor += texColor * AmbientLight(lights[i]);
			if(lights[i].Ltype == 1)
				finalColor += texColor*DirectionalLight(lights[i], bump);
			if(lights[i].Ltype == 2)
				finalColor += texColor*PointLight(lights[i], input.worldPosition, bump, cameraPosition);
			if(lights[i].Ltype == 3)
				finalColor += texColor*SpotLight(lights[i], input.worldPosition, bump, cameraPosition);
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