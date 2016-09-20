#include "stdafx.h"
#include "camera.h"

using namespace std;

camera::camera(float _orientation, float _cam_x, float _cam_y, float _cam_z)
{
	this->orientation = _orientation;
	this->cam_x = _cam_x;
	this->cam_y = _cam_y;
	this->cam_z = _cam_z;
}

camera::~camera()
{

}

float camera::getOrientation()
{
	return this->orientation;
}

float camera::getCamX()
{
	return this->cam_x;
}

float camera::getCamY()
{
	return this->cam_y;
}

float camera::getCamZ()
{
	return this->cam_z;
}

void camera::setCam(float _cam_x, float _cam_y, float _cam_z)
{
	this->cam_x = _cam_x;
	this->cam_y = _cam_y;
	this->cam_z = _cam_z;
}

void camera::setCamX(float _cam_x)
{
	this->cam_x = _cam_x;
}

void camera::setCamY(float _cam_y)
{
	this->cam_y = _cam_y;
}

void camera::setCamZ(float _cam_z)
{
	this->cam_z = _cam_z;
}

void camera::setOrientation(float _orientation)
{
	this->orientation = _orientation;
}