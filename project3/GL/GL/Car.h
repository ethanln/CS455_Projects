#pragma once
#include "stdafx.h"
#include "GraphicObject.h"
#include "Wheel.h"

using namespace std;

class Car : public GraphicObject {
	public:
		Car(string _object_uri, float _orientation, float _x_pos, float _y_pos, float _z_pos, float _scale_x, float _scale_y, float _scale_z, GraphicObjectType _type);

		~Car();

		void turnCar(float _orientation);

		void moveCar(float rate);
		//virtual void display(camera cam) override;
};