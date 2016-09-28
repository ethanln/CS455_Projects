#pragma once
#include "stdafx.h"
#include "GraphicObject.h"

using namespace std;

enum WheelType
{
	FRONT_RIGHT,
	FRONT_LEFT,
	BACK_RIGHT,
	BACK_LEFT,
	NONE
};
class Wheel : public GraphicObject {
	private:
		WheelType wheel_type;

	public:
		Wheel(string _object_uri, float _orientation, float _x_pos, float _y_pos, float _z_pos, float _scale_x, float _scale_y, float _scale_z, GraphicObjectType _type, WheelType _wheel_type);

		~Wheel();

		void rotate_wheels(float _orientation);

		WheelType get_wheel_type();

};