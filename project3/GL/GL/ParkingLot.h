#pragma once
#include "stdafx.h"
#include "GraphicObject.h"

using namespace std;

class ParkingLot : public GraphicObject
{
	public:
		ParkingLot(string _object_uri, float _orientation, float _x_pos, float _y_pos, float _z_pos, float _scale_x, float _scale_y, float _scale_z, GraphicObjectType _type);

		~ParkingLot();
};