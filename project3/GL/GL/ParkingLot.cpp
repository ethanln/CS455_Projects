#include "stdafx.h"
#include "ParkingLot.h"

using namespace std;

ParkingLot::ParkingLot(string _object_uri, float _orientation, float _x_pos, float _y_pos, float _z_pos, float _scale_x, float _scale_y, float _scale_z, GraphicObjectType _type)
	: GraphicObject(_object_uri, _orientation, _x_pos, _y_pos, _z_pos, _scale_x, _scale_y, _scale_z, _type)
{

}

ParkingLot::~ParkingLot() {}