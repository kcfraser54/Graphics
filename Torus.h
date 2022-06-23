#pragma once

#include <cmath>
#include <vector>
#include "glm\glm.hpp"

class Torus
{
public:
	// constructors
	Torus();
	Torus(float innerRadius, float outerRadius, int prec);

	// accessors
	int getNumVertices();
	int getNumIndices();
	std::vector<int> getIndices();
	std::vector<glm::vec3> getVertices();
	std::vector<glm::vec2> getTexCoords();
	std::vector<glm::vec3> getNormals();
	std::vector<glm::vec3> getStangents();
	std::vector<glm::vec3> getTtangents();

private:
	int numVertices;
	int numIndices;
	int prec;
	float inner;
	float outer;
	std::vector<int> indices;
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec2> texCoords;
	std::vector<glm::vec3> normals;
	std::vector<glm::vec3> sTangents;
	std::vector<glm::vec3> tTangents;
	float toRadians(float degrees);
	void init();
};

