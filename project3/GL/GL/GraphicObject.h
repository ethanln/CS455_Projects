#pragma once

#ifndef GRAPHICOBJECT_H
#define GRAPHICOBJECT_H

#include <string>
#include <Windows.h>
#include <vector>
#include <glm/vec2.hpp> // glm::vec3
#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <GL/glew.h>
#include <GL/glut.h>
#include <GLFW\glfw3.h>
#include "ObjectParser.h"
#include "SOIL.h"

using namespace std;

class GraphicObject
{
	private:
		vector<face> faces;
		GLuint texId;

	public:
		GraphicObject(string _object_uri);

		~GraphicObject();

		vector<face> getObjectFaces();

		bool loadTexture(string _texture_uri);

		void display();
};

#endif