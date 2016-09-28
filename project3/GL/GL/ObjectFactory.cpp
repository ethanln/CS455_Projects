#include "stdafx.h"
#include "ObjectFactory.h"

using namespace std;

ObjectFactory* ObjectFactory::inst = nullptr;

ObjectFactory::ObjectFactory()
{
	this->obj_files[GraphicObjectType::CAR] = "objects/car.obj";
	this->obj_files[GraphicObjectType::WHEEL] = "objects/tire.obj";
	this->obj_files[GraphicObjectType::PARKING_LOT] = "objects/ParkingLot.obj";
	this->obj_files[GraphicObjectType::CRAYON_BOX] = "objects/crayonbox-different.obj";
	this->obj_files[GraphicObjectType::CRAYON] = "objects/crayonbox-color-green.obj";
	this->obj_files[GraphicObjectType::CREATURE] = "objects/creature.obj";


	this->bmp_files[GraphicObjectType::CAR] = "objects/car.bmp";
	this->bmp_files[GraphicObjectType::WHEEL] = "objects/tire.bmp";
	this->bmp_files[GraphicObjectType::PARKING_LOT] = "objects/ParkingLot.bmp";
	this->bmp_files[GraphicObjectType::CRAYON_BOX] = "objects/CrayonBox2.bmp";
	this->bmp_files[GraphicObjectType::CRAYON] = "objects/greenCrayon.bmp";
	this->bmp_files[GraphicObjectType::CREATURE] = "objects/creature.bmp";
}

ObjectFactory* ObjectFactory::instance()
{
	if (!ObjectFactory::inst)
	{
		ObjectFactory::inst = new ObjectFactory();
	}

	return ObjectFactory::inst;
}

GraphicObject* ObjectFactory::_make_object(float _orientation, float _x_pos, float _y_pos, float _z_pos, float _scale_x, float _scale_y, float _scale_z, GraphicObjectType _type)
{
	GraphicObject* obj = NULL;

	switch (_type) 
	{
		case GraphicObjectType::CAR:
			obj = new Car(this->obj_files[_type], _orientation, _x_pos, _y_pos, _z_pos, _scale_x, _scale_y, _scale_z, _type);
			break;
		case GraphicObjectType::PARKING_LOT:
			obj = new ParkingLot(this->obj_files[_type], _orientation, _x_pos, _y_pos, _z_pos, _scale_x, _scale_y, _scale_z, _type);
			break;
		case GraphicObjectType::CRAYON_BOX:
			obj = new GraphicObject(this->obj_files[_type], _orientation, _x_pos, _y_pos, _z_pos, _scale_x, _scale_y, _scale_z, _type);
			break;
		case GraphicObjectType::CRAYON:
			obj = new GraphicObject(this->obj_files[_type], _orientation, _x_pos, _y_pos, _z_pos, _scale_x, _scale_y, _scale_z, _type);
			break;
		case GraphicObjectType::CREATURE:
			obj = new GraphicObject(this->obj_files[_type], _orientation, _x_pos, _y_pos, _z_pos, _scale_x, _scale_y, _scale_z, _type);
			break;
		default:
			break;
	}

	if (obj != NULL)
	{
		obj->loadTexture(bmp_files[_type]);
	}
		
	return obj;
}

GraphicObject* ObjectFactory::_make_wheel_object(float _orientation, float _x_pos, float _y_pos, float _z_pos, float _scale_x, float _scale_y, float _scale_z, WheelType _wheel_type)
{
	GraphicObject* wheel = new Wheel(this->obj_files[GraphicObjectType::WHEEL], _orientation, _x_pos, _y_pos, _z_pos, _scale_x, _scale_y, _scale_z, GraphicObjectType::WHEEL, _wheel_type);
	wheel->loadTexture(bmp_files[GraphicObjectType::WHEEL]);
	return wheel;
}

GraphicObject* ObjectFactory::make_object(float _orientation, float _x_pos, float _y_pos, float _z_pos, float _scale_x, float _scale_y, float _scale_z, GraphicObjectType _type)
{
	return ObjectFactory::instance()->_make_object(_orientation, _x_pos, _y_pos, _z_pos, _scale_x, _scale_y, _scale_z, _type);
}

GraphicObject* ObjectFactory::make_wheel_object(float _orientation, float _x_pos, float _y_pos, float _z_pos, float _scale_x, float _scale_y, float _scale_z, WheelType _wheel_type)
{
	return ObjectFactory::instance()->_make_wheel_object(_orientation, _x_pos, _y_pos, _z_pos, _scale_x, _scale_y, _scale_z, _wheel_type);
}