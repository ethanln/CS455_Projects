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
#include "camera.h"

using namespace std;

/*
	Graphic object definitions
*/
enum GraphicObjectType
{
	WHEEL,
	CAR,
	PARKING_LOT,
	CRAYON_BOX,
	CRAYON,
	CREATURE
};

class GraphicObject
{
	protected:
		/*
			Object polygons
		*/
		vector<face> faces;

		/*
			texture id of the object texture.
		*/
		GLuint texId;

		/*
			Object type.
		*/
		GraphicObjectType type;

		/*
			Object orientation.
		*/
		float orientation;

		/*
			Object translation coordinates.
		*/
		float x_pos;
		float y_pos;
		float z_pos;

		/*
			Scaling factors of object.
		*/
		float scale_x;
		float scale_y;
		float scale_z;

		/*
			Nested objects within current object space.
		*/
		vector<GraphicObject*> objects;

		/*
			Object vertex information, including uv coordinate information
		*/
		vector<glm::vec3> out_vertices;
		vector<glm::vec2> out_uvs;
		vector<glm::vec3> out_normals;

		/*
			composes modelview matrix from a new space
		*/
		void setup_object_transformation();

		/*
			composes modelview matrix back from the previous space
		*/
		void inverse_object_transformation();

	public:
		GraphicObject(string _object_uri, float _orientation, float _x_pos, float _y_pos, float _z_pos, float _scale_x, float _scale_y, float _scale_z, GraphicObjectType _type);

		~GraphicObject();

		/*
			returns all polygons of graphic object.
		*/
		vector<face> getObjectFaces();

		/*
			Loads texture for this graphic object instance.
		*/
		bool loadTexture(string _texture_uri);

		/*
			Draw this object instance along with its nested objects that are rendered within it's space.
		*/
		virtual void display(camera cam);

		/*
			Adds a pointer graphic object to the current graphic instance nested graphic objects.
		*/
		void add_object(GraphicObject* obj);

		/*
			Set orientation of object.
		*/
		void set_orientation(float _orientation);

		/*
			Set x position of object.
		*/
		void set_x_pos(float _x_pos);

		/*
			Set y position of object.
		*/
		void set_y_pos(float _y_pos);
		
		/*
			Set z position of object.
		*/
		void set_z_pos(float _z_pos);

		/*
			Get orientation of object.
		*/
		float get_orientation();

		/*
			Get x position of object.
		*/
		float get_x_pos();

		/*
			Get y position of object.
		*/
		float get_y_pos();

		/*
			Get z position of object.
		*/
		float get_z_pos();

		/*
			Set x scale of object.
		*/
		void set_scale_x(float _scale_x);

		/*
			Set y scale of object.
		*/
		void set_scale_y(float _scale_y);

		/*
			Set z scale of object.
		*/
		void set_scale_z(float _scale_z);

		/*
			Get x scale of object.
		*/
		float get_scale_x();

		/*
			Get y scale of object.
		*/
		float get_scale_y();

		/*
			Get z scale of object.
		*/
		float get_scale_z();

		/*
			Get object type.
		*/
		GraphicObjectType getType();
};

#endif