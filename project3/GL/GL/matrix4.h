#pragma once

#include <glm/vec4.hpp>
#include <array>

using namespace std;

class matrix4 {
	
	public:
		static const int DIM = 4;

		matrix4();

		matrix4(array<array<float, matrix4::DIM>, matrix4::DIM> _matrix);

		~matrix4();

		glm::vec4 transform(glm::vec4 coordinate);

		array<array<float, matrix4::DIM>, matrix4::DIM> getMatrix();

		void setMatrix(array<array<float, matrix4::DIM>, matrix4::DIM> _matrix);

		void loadIdentity();

		void multiplyMatrix(matrix4 matrix_right);

	private:

		array<array<float, matrix4::DIM>, matrix4::DIM> matrix;

};