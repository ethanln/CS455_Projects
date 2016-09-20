#include "stdafx.h"
#include "matrix4.h"

using namespace std;

matrix4::matrix4() 
{
	this->loadIdentity();
}

matrix4::matrix4(array<array<float, matrix4::DIM>, matrix4::DIM> _matrix)
{
	this->matrix = _matrix;
}

matrix4::~matrix4()
{

}

glm::vec4 matrix4::transform(glm::vec4 coordinate)
{
	float coor_vec[matrix4::DIM] = { coordinate.x, coordinate.y, coordinate.z, coordinate.w };
	float new_vec[matrix4::DIM] = { 0.0f, 0.0f, 0.0f, 0.0f };

	for (unsigned int i = 0; i < matrix4::DIM; i++)
	{
		for (unsigned int j = 0; j < matrix4::DIM; j++)
		{
			new_vec[i] += coor_vec[j] * this->matrix[i][j];
		}
	}

	glm::vec4 transformed_coor(new_vec[0], new_vec[1], new_vec[2], new_vec[3]);
	return transformed_coor;
}

array<array<float, 4>, 4> matrix4::getMatrix()
{
	return this->matrix;
}

void matrix4::setMatrix(array<array<float, matrix4::DIM>, matrix4::DIM> _matrix)
{
	this->matrix = _matrix;
}

void matrix4::loadIdentity()
{
	this->matrix[0] = { 1.0f, 0.0f, 0.0f, 0.0f };
	this->matrix[1] = { 0.0f, 1.0f, 0.0f, 0.0f };
	this->matrix[2] = { 0.0f, 0.0f, 1.0f, 0.0f };
	this->matrix[3] = { 0.0f, 0.0f, 0.0f, 1.0f };
}

void matrix4::multiplyMatrix(matrix4 matrix_right)
{
	array<array<float, matrix4::DIM>, matrix4::DIM> new_matrix;
	new_matrix[0] = { 0.0f, 0.0f, 0.0f, 0.0f };
	new_matrix[1] = { 0.0f, 0.0f, 0.0f, 0.0f };
	new_matrix[2] = { 0.0f, 0.0f, 0.0f, 0.0f };
	new_matrix[3] = { 0.0f, 0.0f, 0.0f, 0.0f };

	for (unsigned int i = 0; i < matrix4::DIM; i++) {
		for (unsigned int j = 0; j < matrix4::DIM; j++) {
			for (unsigned int k = 0; k < matrix4::DIM; k++) {
				new_matrix[i][j] += this->matrix[i][k] * matrix_right.getMatrix()[k][j];
			}
		}
	}
	this->matrix = new_matrix;
}