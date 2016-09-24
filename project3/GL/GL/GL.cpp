#include "stdafx.h"
#include <GL/glew.h>

#include <GL/glut.h>
#include "ObjectParser.h"
#include <vector>
#include <glm/vec2.hpp> // glm::vec3
#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4

#include <stdlib.h>
#include <iostream>
#include <cstdio>
#include <array>
#include "GraphicObject.h"
#include "matrix4.h"
#include "graphics_pipeline.h"
#include "camera.h"

using namespace std;

vector<GraphicObject> objects;

static const float M_PIs = 3.141592653589793238463;

camera* cam;


/********************************/
/*	     DECLARED METHODS		*/
/********************************/

void init(int argc, char** argv);
void updateView();

void setupWindow(int argc, char** argv,																																					/* setup display window. */															
	int _window_width, int _window_height,
	int _window_origin_x, int _window_origin_y,
	string title);

GraphicObject createObject(string _object_uri, string _texture_file, float orientation, float x_pos, float y_pos, float z_pos, float scale_x, float scale_y, float scale_z);			/* Instantiate new graphics object. */
void draw();																																											/* Draw all objects. */
void GLKeyDowns(unsigned char key, int x, int y);																																		/* Keyboard event handler. */
void GLMouseMovements(int x, int y);																																					/* Mouse movement event handler*/


/********************************/
/*			  MAIN				*/
/********************************/
int main(int argc, char **argv)
{

	// SET UP:
	init(argc, argv);

	// SET UP OBJECTS:
    //objects.push_back(createObject("objects/crayonbox-color-green.obj", "objects/greenCrayon.bmp", 20.0f, 10.0f, 0.0f, 0.0f));
	GraphicObject car = createObject("objects/car.obj", "objects/car.bmp", -20.0f, 0.0f, -0.5f, 0.0f, 1.0f, 1.0f, 1.0f);
	car.add_object(createObject("objects/tire.obj", "objects/tire.bmp", 0.0f, 0.4f, 0.15f, 0.47f, 0.25f, 0.25f, 0.25f));
	car.add_object(createObject("objects/tire.obj", "objects/tire.bmp", 0.0f, 0.4f, 0.15f, -0.54f, 0.25f, 0.25f, 0.25f));

	car.add_object(createObject("objects/tire.obj", "objects/tire.bmp", 180.0f, -0.4f, 0.15f, 0.47f, 0.25f, 0.25f, 0.25f));
	car.add_object(createObject("objects/tire.obj", "objects/tire.bmp", 180.0f, -0.4f, 0.15f, -0.54f, 0.25f, 0.25f, 0.25f));

	//createObject("objects/ParkingLot.obj", "objects/ParkingLot.bmp");
	//createObject("objects/crayonbox.obj", "objects/CrayonBox2.bmp");
	//createObject("objects/crayonbox-different.obj", "objects/CrayonBox2.bmp");

	objects.push_back(car);

	// SET UP EVENT HANDLERS:
	glutKeyboardFunc(GLKeyDowns);
	glutMotionFunc(GLMouseMovements);

	// INITIATE DRAW:
	draw();

	// BEGIN LOOP:
	glutMainLoop();

	return 0;
}

/********************************/
/*			   INIT				*/		
/********************************/
void init(int argc, char** argv)
{

	setupWindow(argc, argv, 1000, 1000, 0, 0, "Ethans mad world");

	// INIT:
	glClearColor(0.0, 0.0, 0.0, 0.0);

	/*  initialize viewing values */
	//cam = new camera(-114.0f, -6.98902798f, 0.0f, 3.35688090f); // FRONT
	cam = new camera(-69.0f, -5.29914522f, 0.0f, -2.22203946f); // LEFT SIDE
	//cam = new camera(-253.0f, 4.76900959f, 0.0f, 1.87358809f); // RIGHT SIDE

	/* BEGIN MY PIPELINE */
	graphics_pipeline::mode(matrix_mode::PROJECTION_GL);
	graphics_pipeline::loadIdentityMatrix();
	graphics_pipeline::gluPerspective(45.0f, 1280.0f / 960.0f, 0.01f, 1000.0f);
	/* END MY PIPELINE */

	//glMatrixMode(GL_PROJECTION);
	//glLoadIdentity();
	//gluPerspective(45.0f, 1280.0f / 960.0f, 0.000001f, 1000.0f);

	updateView();

	glEnable(GL_TEXTURE_2D);
	glEnable(GL_CULL_FACE);
	glEnable(GL_COLOR_MATERIAL);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
}


/********************************/
/*	     UPDATE MODEL VIEW		*/
/********************************/
void updateView()
{
	/* intialize camera view*/
	//glMatrixMode(GL_MODELVIEW);
	//glLoadIdentity();
	//glRotatef(((cam->getOrientation() * M_PIs) / 180), 0.0f, 1.0f, 0.0f);
	//glTranslated(cam->getCamX(), cam->getCamY(), cam->getCamZ());

	/* BEGIN MY PIPELINE */
	graphics_pipeline::mode(matrix_mode::MODELVIEW_GL);
	graphics_pipeline::loadIdentityMatrix();
	graphics_pipeline::rotate(((cam->getOrientation() * M_PIs) / 180.0f), 0.0f, 1.0f, 0.0f);
	graphics_pipeline::translate(cam->getCamX(), cam->getCamY(), cam->getCamZ());
	/* END MY PIPELINE */
}

/********************************/
/*	     SETUP WINDOW VIEW		*/
/********************************/
void setupWindow(int argc, char** argv, 
				int _window_width, int _window_height, 
				int _window_origin_x, int _window_origin_y,
				string title)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_SINGLE | GLUT_RGBA);

	glutInitWindowSize(_window_width, _window_height);
	glutInitWindowPosition(_window_origin_x, _window_origin_y);
	glutCreateWindow(title.c_str());
}

/********************************/
/*	   INSTANTIATES OBJECTS		*/
/********************************/
GraphicObject createObject(string _object_uri, string _texture_file, float orientation, float x_pos, float y_pos, float z_pos, float scale_x, float scale_y, float scale_z)
{
	GraphicObject o (_object_uri, orientation, x_pos, y_pos, z_pos, scale_x, scale_y, scale_z);
	o.loadTexture(_texture_file);
	return o;
}

/********************************/
/*	     DRAWS ALL OBJECTS		*/
/********************************/
void draw() 
{
	/*  clear all pixels  */
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	for (unsigned int i = 0; i < objects.size(); i++)
	{
		objects.at(i).display();														/*Draw object*/
	}
}


/********************************/
/*	  ----EVENT HANLDERS----	*/
/********************************/



/********************************/
/*	    KEYBOARD HANDLER		*/
/********************************/
void GLKeyDowns(unsigned char key, int x, int y)
{

	if (key == 'w') {
		//camZ += 0.4f;
		cam->setCamZ(cam->getCamZ() + 1.8f * sin((((cam->getOrientation() + 90.0f) * M_PIs) / 180.0f)));
		cam->setCamX(cam->getCamX() + 1.8f * cos((((cam->getOrientation() + 90.0f) * M_PIs) / 180.0f)));
		///camZs += 0.5 * sin(((0 * M_PIs) / 180));
	}
	else if (key == 's') {
		//camZ -= 0.4f;
		cam->setCamZ(cam->getCamZ() - 1.8f * sin((((cam->getOrientation() + 90.0f) * M_PIs) / 180.0f)));
		cam->setCamX(cam->getCamX() - 1.8f * cos((((cam->getOrientation() + 90.0f) * M_PIs) / 180.0f)));
		///camZs -= 0.5 * sin(((0 * M_PIs) / 180));
	}
	else if (key == 'a') {
		//camX += 0.4f;
		cam->setCamZ(cam->getCamZ() + 0.5f * sin(((cam->getOrientation() * M_PIs) / 180.0f)));
		cam->setCamX(cam->getCamX() + 0.5f * cos(((cam->getOrientation() * M_PIs) / 180.0f)));
	}
	else if (key == 'd') {
		//camX -= 0.4f;
		cam->setCamZ(cam->getCamZ() - 0.5f * sin(((cam->getOrientation() * M_PIs) / 180.0f)));
		cam->setCamX(cam->getCamX() - 0.5f * cos(((cam->getOrientation() * M_PIs) / 180.0f)));
	}

	updateView();
	draw();
}

float lastxs = 0.0;
float lastys = 0.0;

/********************************/
/*	     MOUSE HANDLER			*/
/********************************/
void GLMouseMovements(int x, int y)
{

	if (x < lastxs)
	{
		cam->setOrientation(cam->getOrientation() - 1.0f);
	}
	else
	{
		cam->setOrientation(cam->getOrientation() + 1.0f);
	}

	updateView();
	draw();

	lastxs = (float)x;
}




