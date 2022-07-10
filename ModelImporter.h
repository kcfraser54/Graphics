#pragma once
#include <vector>
#include <iostream>
#include "glm\glm.hpp"
using namespace std;

class ModelImporter
{
public:
	ModelImporter();
	void parseOBJ(const char* filePath);
	int getNumVertices();
	std::vector<float> getVertices();
	std::vector<float> getTextureCoordinates();
	std::vector<float> getNormals();

private:
	// values as read in from OBJ file
	std::vector<float> vertVals;
	std::vector<float> stVals;
	std::vector<float> normVals;

	// values stored for later use as vertex attributes 
	std::vector<float> triangleVerts;
	std::vector<float> textureCoords;
	std::vector<float> normals;
};

