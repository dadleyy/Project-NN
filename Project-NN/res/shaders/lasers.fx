

cbuffer CameraBuffer
{
	float4x4 viewMatrix;
	float4x4 fovScaling;
	float3 cameraPosition;
	float Cpad;
};


float4 color = float4(0,1,0,1);

struct VERTEX
{   
	float4 Pos : POSITION;    
};

struct PIXEL
{	
	float4 Pos : SV_POSITION; 
};


//*********************************
// Vertex Shader
//*********************************
PIXEL VS( VERTEX input )
{
    PIXEL output = (PIXEL)0;

	float4 i = input.Pos;
	i =		   mul(viewMatrix, i);
	i =        mul(fovScaling, i);

	output.Pos = i;

	return output;
}



//*********************************
// Pixel Shader
//*********************************
float4 PS( PIXEL input ) : SV_Target
{
	return color;
}


technique11 RenderLasers
{
    pass P0
    {
        SetVertexShader( CompileShader( vs_4_0, VS() ) );
        SetGeometryShader( NULL );
        SetPixelShader( CompileShader( ps_4_0, PS() ) );
    }
}