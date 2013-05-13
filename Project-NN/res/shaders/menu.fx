//
//

struct VERTEX
{   
	float4 Pos : POSITION;    
	float Width : WIDTH;  
	float Height : HEIGHT;
};

struct PIXEL
{	
	float4 Pos : SV_POSITION; 
	float4 Col : COLOR0;
	float2 UV : TEXCOORD2;	
};

VERTEX VS( VERTEX input )
{
    VERTEX output = input;
	return output;
}

[maxvertexcount(4)]
void GS( point VERTEX v[1], inout TriangleStream<PIXEL> output )
{
	PIXEL p;
	for(int i = 0; i < 4; i++)
	{
		p.Pos = float4( 0.0f, 0.0f, 0.0f, 0.0f );
		p.Col = float4( 1.0f, 1.0f, 1.0f, 1.0f );
		p.UV = float2( 1.0f, 1.0f );
		output.Append( p );
	}
}

float4 PS( PIXEL input ) : SV_Target
{
	float4 finalColor = 0;
	return finalColor;
}

technique11 Render
{
    pass P0
    {
        SetVertexShader( CompileShader( vs_5_0, VS( ) ) );
        SetGeometryShader( CompileShader( gs_5_0, GS( ) ) );
        SetPixelShader( CompileShader( ps_5_0, PS( ) ) );
    }
}