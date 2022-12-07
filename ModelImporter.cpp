#include "ModelImporter.h"
#include <fstream>
#include <glm\glm.hpp>
#include <sstream>
#include <iostream>
using namespace std;

ModelImporter::ModelImporter(){}

void ModelImporter::parseOBJ(const char* filePath) {

	cout << "Object File path: " << filePath << endl;

	float x, y, z;
	string content;
	ifstream fileStream(filePath, ios::in);

	string line = "";
	while (!fileStream.eof()) {
		getline(fileStream, line);
		if (line.compare(0, 2, "v ") == 0) {
			cout << "vertex found" << endl;
			stringstream ss(line.erase(0, 2));
			ss >> x;
			ss >> y;
			ss >> z;
			vertVals.push_back(x);
			vertVals.push_back(y);
			vertVals.push_back(z);
		}

		if (line.compare(0, 2, "vt") == 0) {
			cout << "texture coordinate found" << endl;
			stringstream ss(line.erase(0, 2));
			ss >> x;
			ss >> y;
			stVals.push_back(x);
			stVals.push_back(y);
		}

		if (line.compare(0, 2, "vn") == 0) {
			cout << "normals found" << endl;
			stringstream ss(line.erase(0, 2));
			ss >> x;
			ss >> y;
			ss >> z;
			normVals.push_back(x);
			normVals.push_back(y);
			normVals.push_back(z);
		}

		if (line.compare(0, 2, "f ") == 0) {
			cout << "faces found" << endl;
			string oneCorner, v, t, n;
			stringstream ss(line.erase(0, 2));
			for (int i = 0; i < 3; i++) {
				// extract triangle face references 
				getline(ss, oneCorner, ' ');
				stringstream oneCornerSS(oneCorner);
				getline(oneCornerSS, v, '/');
				getline(oneCornerSS, t, '/');
				getline(oneCornerSS, n, '/');

				// "stoi" converts string to integer
				int vertRef = (stoi(v) - 1) * 3;
				int tcRef = (stoi(t) - 1) * 2;
				int normRef = (stoi(n) - 1) * 3;

				// build vector of vertices
				triangleVerts.push_back(vertVals[vertRef]);
				triangleVerts.push_back(vertVals[vertRef + 1]);
				triangleVerts.push_back(vertVals[vertRef + 2]);

				// build a vector of texture coordinates
				textureCoords.push_back(stVals[tcRef]);
				textureCoords.push_back(stVals[tcRef + 1]);

				// build a vector of normals 
				normals.push_back(normVals[normRef]);
				normals.push_back(normVals[normRef + 1]);
				normals.push_back(normVals[normRef + 2]);
			}
		}

	}
}

// Accessors
int ModelImporter::getNumVertices() {
	return (triangleVerts.size()/3);
}

std::vector<float> ModelImporter::getVertices() {
	return triangleVerts;
}

std::vector<float> ModelImporter::getTextureCoordinates() {
	return textureCoords;
}

std::vector<float> ModelImporter::getNormals() {
	return normals;
}





