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
				orientation_new = orientation_new > 205.0f ? 205.0f : orientation_new;
				orientation_new = orientation_new < 155.0f ? 155.0f : orientation_new;
				this->objects.at(i)->set_orientation(orientation_new);
			}

			if (wheel->get_wheel_type() == WheelType::FRONT_RIGHT)
			{
				orientation_new = orientation_new > 25.0f ? 25.0f : orientation_new;
				orientation_new = orientation_new < -25.0f ? -25.0f : orientation_new;
				this->objects.at(i)->set_orientation(orientation_new);
			}
			
		}
	}
}

void Car::moveCar(float rate)
{
	/* ROTATE CARE AND WHEELS*/
	Wheel* wheel_right = nullptr;
	Wheel* wheel_left = nullptr;

	for (unsigned int i = 0; i < this->objects.size(); i++)
	{
		if (this->objects.at(i)->getType() == GraphicObjectType::WHEEL)
		{
			Wheel* wheel = (Wheel*)this->objects.at(i);

			if (wheel->get_wheel_type() == WheelType::FRONT_RIGHT)
			{
				wheel_right = wheel;
			}

			if (wheel->get_wheel_type() == WheelType::FRONT_LEFT)
			{
				wheel_left = wheel;
			}
		}
	}

	float wheel_orientation = wheel_right->get_orientation();

	if (wheel_orientation < 0.0f)
	{
		rate = (wheel_orientation + rate) >= 0.0f ? rate + wheel_orientation : rate;
		this->orientation = this->orientation - rate;
		wheel_right->set_orientation(wheel_right->get_orientation() + rate);
		wheel_left->set_orientation(wheel_left->get_orientation() + rate);
	}
	else if (wheel_orientation > 0.0f)
	{
		rate = (wheel_orientation - rate) <= 0.0f ? rate - wheel_orientation : rate;
		this->orientation = this->orientation + rate;
		wheel_right->set_orientation(wheel_right->get_orientation() - rate);
		wheel_left->set_orientation(wheel_left->get_orientation() - rate);
	}

	/*MOVE CAR*/
	rate = 0.1f;
	float camMovementXComponent = 0.0f;
	float camMovementYComponent = 0.0f;
	float camMovementZComponent = 0.0f;
	// Control X-Axis movement
	float pitchFactor = cos(math_ext::toRads(0.0f));
	camMovementXComponent += (rate * float(sin(math_ext::toRads(this->orientation))) * -1.0f) * pitchFactor;

	// Control Y-Axis movement
	camMovementYComponent += rate * float(sin(math_ext::toRads(0.0f)));

	// Control Z-Axis movement
	float yawFactor = float(cos(math_ext::toRads(0.0f)));
	camMovementZComponent += (rate * float(cos(math_ext::toRads(this->orientation)))) * yawFactor;


	float carXSpeed = camMovementXComponent;
	float carYSpeed = camMovementYComponent;
	float carZSpeed = camMovementZComponent;

	// Cap the speeds to our movementSpeedFactor (otherwise going forward and strafing at an angle is twice as fast as just going forward!)
	// X Speed cap
	if (carXSpeed > rate)
	{
		//cout << "high capping X speed to: " << movementSpeedFactor << endl;
		carXSpeed = rate;
	}
	if (carXSpeed < -rate)
	{
		//cout << "low capping X speed to: " << movementSpeedFactor << endl;
		carXSpeed = -rate;
	}

	// Y Speed cap
	if (carYSpeed > rate)
	{
		//cout << "low capping Y speed to: " << movementSpeedFactor << endl;
		carYSpeed = rate;
	}
	if (carYSpeed < -rate)
	{
		//cout << "high capping Y speed to: " << movementSpeedFactor << endl;
		carYSpeed = -rate;
	}

	// Z Speed cap
	if (carZSpeed > rate)
	{
		//cout << "high capping Z speed to: " << movementSpeedFactor << endl;
		carZSpeed = rate;
	}
	if (carZSpeed < -rate)
	{
		//cout << "low capping Z speed to: " << movementSpeedFactor << endl;
		carZSpeed = -rate;
	}

	this->x_pos = this->x_pos + carXSpeed;
	this->y_pos = this->y_pos + carYSpeed;
	this->z_pos = this->z_pos + carZSpeed;
}