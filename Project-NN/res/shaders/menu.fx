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

[maxvertexcount(6)]
void GS( point VERTEX v[1], inout TriangleStream<PIXEL> output )
{
	PIXEL p;
	float height = 0.25f;
	float width = 0.25f;
	
	/*
	v[0] = float4((ppos.x - hWidth), (ppos.y - hHeight), 1.0f, 1.0f);
	v[1] = float4((ppos.x - hWidth), (ppos.y + hHeight), 1.0f, 1.0f);
	v[2] = float4((ppos.x + hWidth), (ppos.y + hHeight), 1.0f, 1.0f);
	v[3] = float4((ppos.x + hWidth), (ppos.y - hHeight), 1.0f, 1.0f);
	*/
	
	float4 positions[4];
	positions[0] = float4( -width, -height, 1.0f, 1.0f );
	positions[1] = float4( -width, height, 1.0f, 1.0f );
	positions[2] = float4( width, height, 1.0f, 1.0f );
	positions[3] = float4( width, -height, 1.0f, 1.0f );
	

	p.Pos = positions[0];
	p.Col = float4( 1.0f, 1.0f, 1.0f, 1.0f );
	p.UV = float2( 1.0f, 1.0f );
	output.Append( p );
	
	p.Pos = positions[1];
	p.Col = float4( 1.0f, 1.0f, 1.0f, 1.0f );
	p.UV = float2( 1.0f, 1.0f );
	output.Append( p );
	
	p.Pos = positions[2];
	p.Col = float4( 1.0f, 1.0f, 1.0f, 1.0f );
	p.UV = float2( 1.0f, 1.0f );
	output.Append( p );
	
	output.RestartStrip( );
	
	p.Pos = positions[0];
	p.Col = float4( 1.0f, 1.0f, 1.0f, 1.0f );
	p.UV = float2( 1.0f, 1.0f );
	output.Append( p );
	
	p.Pos = positions[2];
	p.Col = float4( 1.0f, 1.0f, 1.0f, 1.0f );
	p.UV = float2( 1.0f, 1.0f );
	output.Append( p );
	
	p.Pos = positions[3];
	p.Col = float4( 1.0f, 0.0f, 1.0f, 1.0f );
	p.UV = float2( 1.0f, 1.0f );
	output.Append( p );
	
}

float4 PS( PIXEL input ) : SV_Target
{
	float4 finalColor = float4( 1.0f, 1.0f, 1.0f, 1.0f );
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