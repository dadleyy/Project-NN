#pragma once

#include <vector>
#include <fstream>

using std::vector;
using std::fstream;
using std::ifstream;

class OBJLoader
{
public:
	OBJLoader(void);
	~OBJLoader(void);

	int numVerts;
	int numIndex;
	ifstream file;

	vector<float> points;
	vector<float> normals;
	vector<float> textureCoord;
	vector<float> verticies;
	vector<unsigned int> indicies;

	void readFile(char* fileName);
	float* getVerticies();
	unsigned int* getIndicies();
	unsigned int getNumVerts();
	unsigned int getNumInds();
	bool breakLine(char* a, char* b, char divider); //breaks a line at the first occurence of a character

	void destroy(); //deletes all data and closes the file


};

