#pragma once

#include <Windows.h>
#include <iostream>
#include <string>
#include <stdlib.h>
#include <stdio.h>
#include <fstream>
#include <sstream>
#include <vector>
#include <GL/glut.h>
#include <string.h>
#include "face.h"
#include "graphics_pipeline.h"

#include <glm/vec2.hpp> // glm::vec3
#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4


using namespace std;

class ObjectParser
{
private:

	vector<unsigned int> vertexIndices;
	vector<unsigned int> uvIndices;
	vector<unsigned int> normalIndices;

	vector<glm::vec3> temp_vertices;
	vector<glm::vec2> temp_uvs;
	vector<glm::vec3> temp_normals;

public:

	ObjectParser() {}

	~ObjectParser() {}

	bool parse(string file_path,
		vector<glm::vec3> &out_vertices,
		vector<glm::vec2> &out_uvs,
		vector<glm::vec3> &out_normals);

	bool parse(string file_path, vector<face> &faces);

	void print_info(std::ostream &out);

};