#pragma once
#include "stdafx.h"
#include "GraphicObject.h"
#include "Wheel.h"
#include "Car.h"
#include "ParkingLot.h"
#include <map>

using namespace std;

class ObjectFactory
{
	private:

		static ObjectFactory* inst;

		map<GraphicObjectType, string> obj_files;
		map<GraphicObjectType, string> bmp_files;

		ObjectFactory();

		static ObjectFactory* instance();

		GraphicObject* _make_object(float _orientation, float _x_pos, float _y_pos, float _z_pos, float _scale_x, float _scale_y, float _scale_z, GraphicObjectType _type);

		GraphicObject* _make_wheel_object(float _orientation, float _x_pos, float _y_pos, float _z_pos, float _scale_x, float _scale_y, float _scale_z, WheelType _wheel_type);
		

	public:

		static GraphicObject* make_object(float _orientation, float _x_pos, float _y_pos, float _z_pos, float _scale_x, float _scale_y, float _scale_z, GraphicObjectType _type);

		static GraphicObject* make_wheel_object(float _orientation, float _x_pos, float _y_pos, float _z_pos, float _scale_x, float _scale_y, float _scale_z, WheelType _wheel_type);

};