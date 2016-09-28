#include "stdafx.h"
#include "Car.h"

using namespace std;

Car::Car(string _object_uri, float _orientation, float _x_pos, float _y_pos, float _z_pos, float _scale_x, float _scale_y, float _scale_z, GraphicObjectType _type) 
	: GraphicObject(_object_uri, _orientation, _x_pos,  _y_pos, _z_pos, _scale_x, _scale_y, _scale_z, _type)
{

}

Car::~Car() {}

void Car::turnCar(float _orientation)
{
	for (unsigned int i = 0; i < this->objects.size(); i++)
	{
		if (this->objects.at(i)->getType() == GraphicObjectType::WHEEL)
		{
			Wheel* wheel = (Wheel*)this->objects.at(i);
			float orientation_new = this->objects.at(i)->get_orientation() + _orientation;

			if (wheel->get_wheel_type() == WheelType::FRONT_LEFT)
			{
				orientation_new = orientation_new > 215.0f ? 215.0f : orientation_new;
				orientation_new = orientation_new < 145.0f ? 145.0f : orientation_new;
				this->objects.at(i)->set_orientation(orientation_new);
			}

			if (wheel->get_wheel_type() == WheelType::FRONT_RIGHT)
			{
				orientation_new = orientation_new > 35.0f ? 35.0f : orientation_new;
				orientation_new = orientation_new < -35.0f ? -35.0f : orientation_new;
				this->objects.at(i)->set_orientation(orientation_new);
			}
			
		}
	}
}

void Car::moveCar(float rate)
{
	// IMPLEMENT FOR PROJECT 4
}