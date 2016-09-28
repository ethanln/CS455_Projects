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
				orientation_new = orientation_new > 225.0f ? 225.0f : orientation_new;
				orientation_new = orientation_new < 135.0f ? 135.0f : orientation_new;
				this->objects.at(i)->set_orientation(orientation_new);
			}

			if (wheel->get_wheel_type() == WheelType::FRONT_RIGHT)
			{
				orientation_new = orientation_new > 45.0f ? 45.0f : orientation_new;
				orientation_new = orientation_new < -45.0f ? -45.0f : orientation_new;
				this->objects.at(i)->set_orientation(orientation_new);
			}
			
		}
	}
}

void Car::moveCar(float rate)
{
	// IMPLEMENT FOR PROJECT 4
}

/*
void Car::display(camera cam)
{
	this->setup_object_transformation();

	glBindTexture(GL_TEXTURE_2D, this->texId);

	for (unsigned int i = 0; i < this->out_vertices.size(); i += 3)
	{
		glBegin(GL_TRIANGLES);

		for (unsigned int j = 0; j < 3; j++)
		{
			glm::vec4 vec(this->out_vertices.at(i + j).x, this->out_vertices.at(i + j).y, this->out_vertices.at(i + j).z, 1.0f);
			glm::vec4 transformed_vec = graphics_pipeline::transform(vec);
			glm::vec3 screen_vec = graphics_pipeline::to_screen(transformed_vec);

			glTexCoord2f(this->out_uvs.at(i + j).x, this->out_uvs.at(i + j).y);
			glVertex2f(screen_vec.x, screen_vec.y);
		}

		glEnd();
	}

	for (unsigned int i = 0; i < this->objects.size(); i++)
	{
		this->objects.at(i)->display(cam);
	}

	this->inverse_object_transformation();						// inverse object transformation.
}*/