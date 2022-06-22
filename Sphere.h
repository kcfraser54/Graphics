#pragma once

#include <cmath>
#include <vector>
#include "glm\glm.hpp"

class Sphere
{

public:
	// constructors
	Sphere();
	Sphere(int prec);
	
	// accessors
	int getNumVertices();
	int getNumIndices();
	std::vector<int> getIndices();
	std::vector<glm::vec3> getVertices();
	std::vector<glm::vec2> getTexCoords();
	std::vector<glm::vec3> getNormals();

private:
	int numVertices;
	int numIndices;
	std::vector<int> indices;
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec2> texCoords;
	std::vector<glm::vec3> normals;
	float toRadians(float degrees);
	void init(int prec);
};

