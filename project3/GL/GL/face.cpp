#include "stdafx.h"
#include "face.h"

using namespace std;

face::face() {}

face::~face() {}

void face::addFaceMaterial(glm::vec3 _vertex, glm::vec2 _uv, glm::vec3 _normal)
{
	material newMat;
	newMat.vertex = _vertex;
	newMat.uv = _uv;
	newMat.normal = _normal;
	this->faceMaterial.push_back(newMat);
}

vector<material> face::getFaceMaterial()
{
	return this->faceMaterial;
}

int face::getFaceSize()
{
	return this->faceMaterial.size();
}
