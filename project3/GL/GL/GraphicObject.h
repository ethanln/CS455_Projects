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

		float orientation;
		float x_pos;
		float y_pos;
		float z_pos;

		float scale_x;
		float scale_y;
		float scale_z;

		vector<GraphicObject> objects;

		void setup_object_transformation();

		void inverse_object_transformation();

	public:
		GraphicObject(string _object_uri, float _orientation, float _x_pos, float _y_pos, float _z_pos, float _scale_x, float _scale_y, float _scale_z);

		~GraphicObject();

		vector<face> getObjectFaces();

		bool loadTexture(string _texture_uri);

		void display();

		void add_object(GraphicObject obj);

		void set_orientation(float _orientation);

		void set_x_pos(float _x_pos);

		void set_y_pos(float _y_pos);
		
		void set_z_pos(float _z_pos);

		float get_orientation();

		float get_x_pos();

		float get_y_pos();

		float get_z_pos();

		void set_scale_x(float _scale_x);

		void set_scale_y(float _scale_y);

		void set_scale_z(float _scale_z);

		float get_scale_x();

		float get_scale_y();

		float get_scale_z();
};

#endif