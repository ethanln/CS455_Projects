#include "stdafx.h"
#include "camera.h"

using namespace std;

camera::camera(float _orientation_x, float _orientation_y, float _orientation_z, float _cam_x, float _cam_y, float _cam_z)
{
	this->orientation_x = _orientation_x;
	this->orientation_y = _orientation_y;
	this->orientation_z = _orientation_z;

	this->cam_x = _cam_x;
	this->cam_y = _cam_y;
	this->cam_z = _cam_z;
}

camera::~camera()
{

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

float camera::getOrientationX()
{
	return this->orientation_x;
}

float camera::getOrientationY()
{
	return this->orientation_y;
}

float camera::getOrientationZ()
{
	return this->orientation_z;
}

void camera::setOrientation(float _orientation_x, float _orientation_y, float _orientation_z)
{
	this->orientation_x = _orientation_x;
	this->orientation_y = _orientation_y;
	this->orientation_z = _orientation_z;
}

void camera::setOrientationX(float _orientation_x)
{
	this->orientation_x = _orientation_x;
}

void camera::setOrientationY(float _orientation_y)
{
	this->orientation_y = _orientation_y;
}

void camera::setOrientationZ(float _orientation_z)
{
	this->orientation_z = _orientation_z;
}