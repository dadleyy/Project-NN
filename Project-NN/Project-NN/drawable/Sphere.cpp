#include "Sphere.h"


Sphere::Sphere(void)
{
}

Sphere::Sphere(ID3D11Device* device, ID3D11DeviceContext* immediateContext) : Drawable(device, immediateContext)
{
	
}

Sphere::~Sphere(void)
{
}

//****************************************************************
//Creates all buffers needed for the object (vertex, index, etc.)
//and compiles the shaders to be used for this object
// **We need to add the index buffer code still**
//****************************************************************
void Sphere::createBuffer()
{
	HRESULT hr;
	//create the vertex shader
	ID3DBlob* pVSBlob = NULL;
    hr = CompileShaderFromFile( L"DrawSphere.fx", "VS", "vs_4_0", &pVSBlob ); 
	hr = pD3DDevice->CreateVertexShader( pVSBlob->GetBufferPointer(), pVSBlob->GetBufferSize(), NULL, &vertexShader );

	//create the pixel shader
	ID3DBlob* pPSBlob = NULL;
    hr = CompileShaderFromFile( L"DrawSphere.fx", "PS", "ps_4_0", &pPSBlob );
	hr = pD3DDevice->CreatePixelShader( pPSBlob->GetBufferPointer(), pPSBlob->GetBufferSize(), NULL, &pixelShader );

	//describe the input layout
	D3D11_INPUT_ELEMENT_DESC layout[] = {"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0};

	hr = pD3DDevice->CreateInputLayout(layout,
				1,
				pVSBlob->GetBufferPointer(),
				pVSBlob->GetBufferSize(),
				&pVertexLayout);

	XMFLOAT3 *x = getVerts(.3, 50);

	D3D11_BUFFER_DESC bufferDescription;
	bufferDescription.Usage = D3D11_USAGE_IMMUTABLE; //the data will not change
	bufferDescription.ByteWidth = sizeof(float) * 3 * numVerts; //total number of bytes for all verticies
	bufferDescription.BindFlags = D3D11_BIND_VERTEX_BUFFER; //binds the buffer to the correct type
	bufferDescription.CPUAccessFlags = 0;	//0 means the cpu does not have access to the buffer
	bufferDescription.MiscFlags = 0;	//only one D3D device
	
	//add the data for the buffer
	D3D11_SUBRESOURCE_DATA InitData;
	InitData.pSysMem = x;


	//Set the size of a single vertex
	vertexStride = sizeof(float)*3;

	//create the vertex buffer
	hr = pD3DDevice->CreateBuffer(&bufferDescription, &InitData, &pVertexBuffer);
}

//********************************************************
//Gets the verticies for the sphere
//divions: the number of time the sphere will be tesselated
//********************************************************
XMFLOAT3* Sphere::getVerts(float radius, int divisions)
{
	// minimum sides is 6
    if( divisions < 6 ) {
        divisions = 6;
    }
	
	float trigDelta = (360.0/divisions) * (3.1415926536/180);
	numVerts = divisions*ceil(divisions/2.0)*6;
	XMFLOAT3* verts = new XMFLOAT3[numVerts];
	int counter = 0;
	for(int k = 0; k < divisions; k++)
	{
		for(int i = 0; i < divisions/2; i++)
		{
			float angle1 = trigDelta * k;
			float angle2 = trigDelta * i;

			float X1 = radius*sin(angle2)*cos(angle1) - .5;
			float X2 = radius*cos(angle1+trigDelta)*sin(angle2)- .5;
			float X3 = radius*sin(angle2+trigDelta)*cos(angle1)- .5;
			float X4 = radius*cos(angle1+trigDelta)*sin(angle2+trigDelta)- .5;

			float Y1 = radius*sin(angle1)*sin(angle2);
			float Y2 = radius*sin(angle2+trigDelta)*sin(angle1);
			float Y3 = radius*sin(angle1+trigDelta)*sin(angle2);
			float Y4 = radius*sin(angle2+trigDelta)*sin(angle1+trigDelta);

			float Z1 = radius*cos(angle2)+radius;
			float Z2 = radius*cos(angle2+trigDelta)+radius;

			XMFLOAT3 p1(X1, Y1, Z1);
			XMFLOAT3 p2(X2, Y3, Z1);
			XMFLOAT3 p3(X3, Y2, Z2);
			XMFLOAT3 p4(X4, Y4, Z2);

			verts[counter] = p2;	counter++;
			verts[counter] = p3;	counter++;
			verts[counter] = p1;	counter++;
			verts[counter] = p4;	counter++;
			verts[counter] = p3;	counter++;
			verts[counter] = p2;	counter++;
			//addTriangle(p2, p3, p1);
			//addTriangle(p4, p3, p2);
		}
	}

	return verts;
}