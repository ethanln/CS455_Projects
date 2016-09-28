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
#include "math_ext.h"
#include "ObjectFactory.h"

using namespace std;

vector<GraphicObject*> objects;

static const float M_PIs = 3.141592653589793238463;

camera* cam;

int windowWidth = 1000;                    // Width of our window
int windowHeight = 1000;                    // Heightof our window

int midWindowX = windowWidth / 2;         // Middle of the window horizontally
int midWindowY = windowHeight / 2;         // Middle of the window vertically

GLfloat movementSpeedFactor = 1.00f;

Car* car;


/********************************/
/*	     DECLARED METHODS		*/
/********************************/

void buildScene();
void init(int argc, char** argv);
void updateView();

void setupWindow(int argc, char** argv,																																					/* setup display window. */															
	int _window_width, int _window_height,
	int _window_origin_x, int _window_origin_y,
	string title);

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

	// BUILD SCENE
	buildScene();

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
/*			BUILD SCENE			*/
/********************************/
void buildScene()
{
	car = (Car*)ObjectFactory::make_object(60.0f, -2.5f, 0.0f, -7.50f, 1.0f, 1.0f, 1.0f, GraphicObjectType::CAR);
	car->add_object(ObjectFactory::make_wheel_object(0.0f, 0.4f, 0.15f, 0.47f, 0.25f, 0.25f, 0.25f, WheelType::BACK_RIGHT));
	car->add_object(ObjectFactory::make_wheel_object(0.0f, 0.4f, 0.15f, -0.54f, 0.25f, 0.25f, 0.25f, WheelType::FRONT_RIGHT));

	car->add_object(ObjectFactory::make_wheel_object(180.0f, -0.4f, 0.15f, 0.47f, 0.25f, 0.25f, 0.25f, WheelType::BACK_LEFT));
	car->add_object(ObjectFactory::make_wheel_object(180.0f, -0.4f, 0.15f, -0.54f, 0.25f, 0.25f, 0.25f, WheelType::FRONT_LEFT));
	car->add_object(ObjectFactory::make_object(90.0f, 0.0f, 0.55f, 0.0f, 0.1f, 0.1f, 0.1f, GraphicObjectType::CREATURE));

	GraphicObject* parking_lot = ObjectFactory::make_object(0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, GraphicObjectType::PARKING_LOT);

	parking_lot->add_object(car);
	objects.push_back(parking_lot);
}

/********************************/
/*			   INIT				*/		
/********************************/
void init(int argc, char** argv)
{

	setupWindow(argc, argv, windowWidth, windowHeight, 0, 0, "Ethans mad world");

	// INIT:
	glClearColor(0.0, 0.0, 0.0, 0.0);

	/*  initialize viewing values */
	cam = new camera(0.0999973565f, 30.7999935f, 0.0f, 7.20559216f, -0.653922081f, -0.283143580f); // BACK SIDE

	/* BEGIN MY PIPELINE */
	graphics_pipeline::mode(matrix_mode::PROJECTION_GL);
	graphics_pipeline::loadIdentityMatrix();
	graphics_pipeline::gluPerspective(45.0f, 1280.0f / 960.0f, 0.01f, 1000.0f);
	/* END MY PIPELINE */

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
	/* BEGIN MY PIPELINE */
	graphics_pipeline::mode(matrix_mode::MODELVIEW_GL);
	graphics_pipeline::loadIdentityMatrix();
	graphics_pipeline::rotate(((cam->getOrientationX() * M_PIs) / 180.0f), 1.0f, 0.0f, 0.0f);
	graphics_pipeline::rotate(((cam->getOrientationY() * M_PIs) / 180.0f), 0.0f, 1.0f, 0.0f);
	graphics_pipeline::rotate(((cam->getOrientationZ() * M_PIs) / 180.0f), 0.0f, 0.0f, 1.0f);
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
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);

	glutInitWindowSize(_window_width, _window_height);
	glutInitWindowPosition(_window_origin_x, _window_origin_y);
	glutCreateWindow(title.c_str());
}

/********************************/
/*	     DRAWS ALL OBJECTS		*/
/********************************/
void draw() 
{
	graphics_pipeline::combinePipeline();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_BLEND);
	glEnable(GL_TEXTURE_2D);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glCullFace(GL_BACK);
	glEnable(GL_CULL_FACE);

	for (unsigned int i = 0; i < objects.size(); i++)
	{
		objects.at(i)->display(*cam);														/*Draw object*/
	}

	glFlush();

	glDisable(GL_TEXTURE_2D);
	glutSwapBuffers();
}


/********************************/
/*	  ----EVENT HANLDERS----	*/
/********************************/


void GLKeyDowns(unsigned char key, int x, int y)
{
	// Break up our movement into components along the X, Y and Z axis
	float camMovementXComponent = 0.0f;
	float camMovementYComponent = 0.0f;
	float camMovementZComponent = 0.0f;

	if (key == 's')
	{
		// Control X-Axis movement
		float pitchFactor = cos(math_ext::toRads(cam->getOrientationX()));
		camMovementXComponent += (movementSpeedFactor * float(sin(math_ext::toRads(cam->getOrientationY())))) * pitchFactor;

		// Control Y-Axis movement
		camMovementYComponent += movementSpeedFactor * float(sin(math_ext::toRads(cam->getOrientationX()))) * -1.0f;

		// Control Z-Axis movement
		float yawFactor = float(cos(math_ext::toRads(cam->getOrientationX())));
		camMovementZComponent += (movementSpeedFactor * float(cos(math_ext::toRads(cam->getOrientationY()))) * -1.0f) * yawFactor;
	}

	if (key == 'w')
	{
		// Control X-Axis movement
		float pitchFactor = cos(math_ext::toRads(cam->getOrientationX()));
		camMovementXComponent += (movementSpeedFactor * float(sin(math_ext::toRads(cam->getOrientationY()))) * -1.0f) * pitchFactor;

		// Control Y-Axis movement
		camMovementYComponent += movementSpeedFactor * float(sin(math_ext::toRads(cam->getOrientationX())));

		// Control Z-Axis movement
		float yawFactor = float(cos(math_ext::toRads(cam->getOrientationX())));
		camMovementZComponent += (movementSpeedFactor * float(cos(math_ext::toRads(cam->getOrientationY())))) * yawFactor;
	}

	if (key == 'd')
	{
		// Calculate our Y-Axis rotation in radians once here because we use it twice
		float yRotRad = math_ext::toRads(cam->getOrientationY());

		camMovementXComponent += -movementSpeedFactor * float(cos(yRotRad));
		camMovementZComponent += -movementSpeedFactor * float(sin(yRotRad));
	}

	if (key == 'a')
	{
		// Calculate our Y-Axis rotation in radians once here because we use it twice
		float yRotRad = math_ext::toRads(cam->getOrientationY());

		camMovementXComponent += movementSpeedFactor * float(cos(yRotRad));
		camMovementZComponent += movementSpeedFactor * float(sin(yRotRad));
	}

	// After combining our movements for any & all keys pressed, assign them to our camera speed along the given axis
	float camXSpeed = camMovementXComponent;
	float camYSpeed = camMovementYComponent;
	float camZSpeed = camMovementZComponent;

	// Cap the speeds to our movementSpeedFactor (otherwise going forward and strafing at an angle is twice as fast as just going forward!)
	// X Speed cap
	if (camXSpeed > movementSpeedFactor)
	{
		//cout << "high capping X speed to: " << movementSpeedFactor << endl;
		camXSpeed = movementSpeedFactor;
	}
	if (camXSpeed < -movementSpeedFactor)
	{
		//cout << "low capping X speed to: " << movementSpeedFactor << endl;
		camXSpeed = -movementSpeedFactor;
	}

	// Y Speed cap
	if (camYSpeed > movementSpeedFactor)
	{
		//cout << "low capping Y speed to: " << movementSpeedFactor << endl;
		camYSpeed = movementSpeedFactor;
	}
	if (camYSpeed < -movementSpeedFactor)
	{
		//cout << "high capping Y speed to: " << movementSpeedFactor << endl;
		camYSpeed = -movementSpeedFactor;
	}

	// Z Speed cap
	if (camZSpeed > movementSpeedFactor)
	{
		//cout << "high capping Z speed to: " << movementSpeedFactor << endl;
		camZSpeed = movementSpeedFactor;
	}
	if (camZSpeed < -movementSpeedFactor)
	{
		//cout << "low capping Z speed to: " << movementSpeedFactor << endl;
		camZSpeed = -movementSpeedFactor;
	}

	cam->setCamX(cam->getCamX() + camXSpeed);
	cam->setCamY(cam->getCamY() + camYSpeed);
	cam->setCamZ(cam->getCamZ() + camZSpeed);

	//TURN WHEEL LEFT
	if (key == 'q')
	{
		car->turnCar(10.0f);
	}
	// TURN WHEEL RIGHT
	if (key == 'e')
	{
		car->turnCar(-10.0f);
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
	GLfloat vertMouseSensitivity = 10.0f;
	GLfloat horizMouseSensitivity = 10.0f;

	//cout << "Mouse cursor is at position (" << mouseX << ", " << mouseY << endl;

	int horizMovement = x - midWindowX;
	int vertMovement = y - midWindowY;

	cam->setOrientationX(cam->getOrientationX() + (vertMovement / vertMouseSensitivity));
	cam->setOrientationY(cam->getOrientationY() + (horizMovement / horizMouseSensitivity));

	// Control looking up and down with the mouse forward/back movement
	// Limit loking up to vertically up
	if (cam->getOrientationX() < -90.0f)
	{
		cam->setOrientationX(-90.0f);
	}

	// Limit looking down to vertically down
	if (cam->getOrientationX() > 90.0f)
	{
		cam->setOrientationX(90.0f);
	}

	// Looking left and right. Keep the angles in the range -180.0f (anticlockwise turn looking behind) to 180.0f (clockwise turn looking behind)
	if (cam->getOrientationY() < -180.0f)
	{
		cam->setOrientationY(cam->getOrientationY() + 360.0f);
	}

	if (cam->getOrientationY() > 180.0f)
	{
		cam->setOrientationY(cam->getOrientationY() - 360.0f);
	}

	// Reset the mouse position to the centre of the window each frame
	glutWarpPointer(midWindowX, midWindowY);
	updateView();
	draw();
}




