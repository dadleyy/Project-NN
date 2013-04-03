#include "Sphere.h"


extern ResourceManager* drawAtts;

Sphere::Sphere(ID3D11Device* device, ID3D11DeviceContext* immediateContext) : Drawable(device, immediateContext)
{
}

Sphere::~Sphere()
{
}


void Sphere::createBuffer(char* mesh)
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

	//VERTEX BUFFER
	//describe the input layout
	D3D11_INPUT_ELEMENT_DESC layout[] = {"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0};
	
	//get required vertex information from a shader technique
	D3DX11_PASS_DESC passDesc;
    technique->GetPassByIndex(0)->GetDesc(&passDesc);

	hr = pD3DDevice->CreateInputLayout(layout,
				1,
				passDesc.pIAInputSignature,
				passDesc.IAInputSignatureSize,
				&pVertexLayout);


	pVertexBuffer = drawAtts->meshes.at("testSphere")->verticies;
	indexBuffer = drawAtts->meshes.at("testSphere")->indicies;

	vertexStride = drawAtts->meshes.at("testSphere")->vertexStride;
	vertexOffset = drawAtts->meshes.at("testSphere")->vertexOffset;

	numVerts = drawAtts->meshes.at("testSphere")->numVerts;
	numIndicies = drawAtts->meshes.at("testSphere")->numIndicies;
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
			verts[counter] = p3;	counter++;
			verts[counter] = p2;	counter++;
			verts[counter] = p1;	counter++;
			verts[counter] = p3;	counter++;
			verts[counter] = p4;	counter++;
			verts[counter] = p2;	counter++;
			//addTriangle(p2, p3, p1);
			//addTriangle(p4, p3, p2);
		}
	}

	return verts;
}

UINT* Sphere::getIndicies()
{
	numIndicies = numVerts;
	UINT* indicies = new UINT[numIndicies];

	int counter = 0;
	for(int k = 0; k < numIndicies; k++)
	{
		indicies[k] = k;
	}

	return indicies;
}
