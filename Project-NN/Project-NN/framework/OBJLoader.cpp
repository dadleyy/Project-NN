#include "OBJLoader.h"


OBJLoader::OBJLoader(void)
{
	
}


OBJLoader::~OBJLoader(void)
{
}

void OBJLoader::readFile(char* fileName)
{
	numVerts = 0;
	numIndex = 0;

	file.open(fileName);

	//vector<unsigned int> inds;
	char data[128];
	char dataElement[128];
	int counter = 0;
	vector<float>* currentVector; 

	//loop through every line
	while(1)
	{
		file.getline(data, 128);
		
		if( file.eof() )
			break;


		breakLine( data, dataElement, ' ' );
		
		//gets the indicies of the verticies from each of the vectors
		if( !strcmp( dataElement, "f" ) )
		{
			int p;
			int n;
			int t;
			int goOn = 1;
			while(goOn)
			{
				breakLine( data, dataElement, '/' );
				p = atoi( dataElement );

				breakLine( data, dataElement, '/' );
				t = atoi(dataElement);

				if( breakLine( data, dataElement, ' ' ) )
					n = atoi( dataElement );
				else
				{
					n = atoi( data );
					goOn = 0;
				}

				verticies.push_back( points[ (p-1)*3     ] );
				verticies.push_back( points[ (p-1)*3 + 1 ] );
				verticies.push_back( points[ (p-1)*3 + 2 ] );

				verticies.push_back( normals[ (n-1)*3     ] );
				verticies.push_back( normals[ (n-1)*3 + 1 ] );
				verticies.push_back( normals[ (n-1)*3 + 2 ] );

				verticies.push_back( textureCoord[ (t-1)*2     ] );
				verticies.push_back( textureCoord[ (t-1)*2 + 1 ] );
				
				numIndex++;
				numVerts++;
				//inds.push_back(p-1);
				indicies.push_back(p-1);
			}
			
		}

		else if( !strcmp(dataElement, "v") )
		{
			currentVector = &points;
			
		}
		else if( !strcmp( dataElement, "vn" ) )
			currentVector = &normals;
		else if( !strcmp( dataElement, "vt" ) )
			currentVector = &textureCoord;
		else
			continue;
		//enters the vertex data into individual places
		while( true )
		{
			if( breakLine( data, dataElement, ' ' ) )
			{
				float value = strtod(dataElement, '\0');
				(*currentVector).push_back(value);
			}
			else
			{
				float value = strtod(data, '\0');
				(*currentVector).push_back(value);
				break;
			}
		}

	}

	//counter = 0;
	//for(int i = inds.size()-1; i >= 0; i--)
		//indicies.push_back( inds[i] );

}


bool OBJLoader::breakLine(char* a, char* b, char divider)
{
	int counter = 0;
	while(true)
	{
		if(a[counter] == divider)
			break;
		if(a[counter] == '\0')
			return 0; //divider was not encountered
		counter++;
	}

	strncpy(b, a, counter+1);
	b[counter] = '\0'; //replace the space with a null terminator

	//move everything in 'a' forward
	int offset = counter + 1;
	
	do
	{
		counter++;
		a[counter-offset] = a[counter];
	}while(a[counter] != '\0');

	return 1;
}

float* OBJLoader::getVerticies()
{
	return &verticies[0];
}

unsigned int* OBJLoader::getIndicies()
{
	return &indicies[0];
}


unsigned int OBJLoader::getNumVerts()
{
	return numVerts;
}

unsigned int OBJLoader::getNumInds()
{
	return numIndex;
}