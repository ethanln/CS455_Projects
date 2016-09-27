#include "stdafx.h"
#include "graphics_pipeline.h"

using namespace std;

graphics_pipeline* graphics_pipeline::inst = nullptr;


static const float M_PI = 3.141592653589793238463;

/******************************************************/
/*			    singleton instance method			  */
/******************************************************/
graphics_pipeline* graphics_pipeline::instance()
{
	if (!graphics_pipeline::inst) 
	{
		graphics_pipeline::inst = new graphics_pipeline();
	}

	return graphics_pipeline::inst;
}


/******************************************************/
/*			  singleton private constructor			  */
/******************************************************/
graphics_pipeline::graphics_pipeline()
{
	this->projection = new matrix4();
	this->modelview = new matrix4();
	this->current_matrix = NULL;
}

graphics_pipeline::~graphics_pipeline()
{
	delete this->projection;
	delete this->modelview;
	delete this->current_matrix;
}

/******************************************************/
/*			    singleton private methods			  */
/******************************************************/

void graphics_pipeline::_mode(matrix_mode mode)
{
	// TODO: TEST
	if (mode == matrix_mode::PROJECTION_GL)
	{
		this->current_matrix = this->projection;
	}
	else if (mode == matrix_mode::MODELVIEW_GL)
	{
		this->current_matrix = this->modelview;
	}
	else
	{
		this->current_matrix = nullptr;
	}
}

void graphics_pipeline::_pushMatrix(matrix4 matrix)
{
	// TODO: TEST
	this->current_matrix->multiplyMatrix(matrix);
}

void graphics_pipeline::_loadIdentityMatrix()
{
	// TODO: TEST
	this->current_matrix->loadIdentity();
}

void graphics_pipeline::_rotate(float orientation, float x, float y, float z)
{
	// X ROTATION MATRIX
	if (x == 1.0f)
	{
		array<array<float, matrix4::DIM>, matrix4::DIM> rotation_matrix_x;
		rotation_matrix_x[0] = { 1.0f,  0.0f,					 0.0f,						0.0f };
		rotation_matrix_x[1] = { 0.0f,	(float)cos(orientation), (float)-sin(orientation),	0.0f };
		rotation_matrix_x[2] = { 0.0f,  (float)sin(orientation), (float)cos(orientation),	0.0f };
		rotation_matrix_x[3] = { 0.0f,	0.0f,					 0.0f,						1.0f };
		this->current_matrix->multiplyMatrix(rotation_matrix_x);
	}

	// Y ROTATION MATRIX
	if (y == 1.0f)
	{
		array<array<float, matrix4::DIM>, matrix4::DIM> rotation_matrix_y;
		rotation_matrix_y[0] = { (float)cos(orientation),  0.0f, (float)sin(orientation), 0.0f };
		rotation_matrix_y[1] = { 0.0f,					   1.0f, 0.0f,					  0.0f };
		rotation_matrix_y[2] = { (float)-sin(orientation), 0.0f, (float)cos(orientation), 0.0f };
		rotation_matrix_y[3] = { 0.0f,					   0.0f, 0.0f,					  1.0f };
		this->current_matrix->multiplyMatrix(rotation_matrix_y);
	}

	// Z ROTATION MATRIX
	if (z == 1.0f)
	{
		array<array<float, matrix4::DIM>, matrix4::DIM> rotation_matrix_x;
		rotation_matrix_x[0] = { (float)cos(orientation),   (float)-sin(orientation),	0.0f,	0.0f };
		rotation_matrix_x[1] = { (float)sin(orientation),	(float)cos(orientation),	0.0f,	0.0f };
		rotation_matrix_x[2] = { 0.0f,						0.0f,						1.0f,	0.0f };
		rotation_matrix_x[3] = { 0.0f,						0.0f,						0.0f,	1.0f };
		this->current_matrix->multiplyMatrix(rotation_matrix_x);
	}
}

void graphics_pipeline::_translate(float x, float y, float z)
{
	array<array<float, matrix4::DIM>, matrix4::DIM> translated_matrix;
	translated_matrix[0] = { 1.0f, 0.0f, 0.0f, x	};
	translated_matrix[1] = { 0.0f, 1.0f, 0.0f, y	};
	translated_matrix[2] = { 0.0f, 0.0f, 1.0f, z	};
	translated_matrix[3] = { 0.0f, 0.0f, 0.0f, 1.0f };
	matrix4 mat(translated_matrix);

	this->current_matrix->multiplyMatrix(mat);
}

void graphics_pipeline::_scale(float scale_x, float scale_y, float scale_z)
{
	array<array<float, matrix4::DIM>, matrix4::DIM> scale_matrix;
	scale_matrix[0] = { scale_x, 0.0f,	 0.0f,		0.0f };
	scale_matrix[1] = { 0.0f,	scale_y, 0.0f,		0.0f };
	scale_matrix[2] = { 0.0f,	0.0f,	 scale_z,	0.0f };
	scale_matrix[3] = { 0.0f,	0.0f,	 0.0f,		1.0f };
	matrix4 mat(scale_matrix);

	this->current_matrix->multiplyMatrix(mat);
}

void graphics_pipeline::_gluPerspective(float fov, float aspect, float near, float far)
{
	float ymax, xmax;
	ymax = near * tanf((fov / 2.0f) * M_PI / 360.0f);
	xmax = ymax * aspect;

	this->current_matrix->multiplyMatrix(this->_glhFrustumf(-xmax, xmax, -ymax, ymax, near, far));

	/*array<array<float, matrix4::DIM>, matrix4::DIM> clip_matrix;
	clip_matrix[0] = { 1000.0f / 2.0f,	0.0f,				0.0f,							4.0f + (1000.0f / 2.0f) };
	clip_matrix[1] = { 0.0f,		   1000.0f / 2.0f,		0.0f,							4.0f + (1000.0f / 2.0f) };
	clip_matrix[2] = { 0.0f,			0.0f,				far - near,						near };
	clip_matrix[3] = { 0.0f,			0.0f,				0.0f,							1.0f };
	matrix4 clip(clip_matrix);

	//this->current_matrix->multiplyMatrix(clip);*/

	/*
	float f = 1.0f / tan(((fov / 2.0f) * M_PI) / 360.0f);
	array<array<float, matrix4::DIM>, matrix4::DIM> clip_matrix;
	clip_matrix[0] = { f / aspect, 0.0f,	0.0f,							0.0f							};
	clip_matrix[1] = { 0.0f,	   f,		0.0f,							0.0f							};
	clip_matrix[2] = { 0.0f,	   0.0f,	(far + near) / (near - far),	(2 * far * near) / (near - far) };
	clip_matrix[3] = { 0.0f,	   0.0f,	-1.0f,							0.0f							};

	array<array<float, matrix4::DIM>, matrix4::DIM> pers_matrix;
	pers_matrix[0] = { 1.0f, 0.0f,	0.0f,		0.0f };
	pers_matrix[1] = { 0.0f, 1.0f,	0.0f,		0.0f };
	pers_matrix[2] = { 0.0f, 0.0f,	0.0f,		0.0f };
	pers_matrix[3] = { 0.0f, 0.0f, -1.0f / 1.0f, 1.0f };

	float x = 1.0f * tan((((fov / 2.0f) * M_PI) / 360.0f));

	array<array<float, matrix4::DIM>, matrix4::DIM> trans_matrix;
	trans_matrix[0] = { 1.0f, 0.0f,	0.0f, x };
	trans_matrix[1] = { 0.0f, 1.0f,	0.0f, x };
	trans_matrix[2] = { 0.0f, 0.0f,	1.0f, 0.0f };
	trans_matrix[3] = { 0.0f, 0.0f,  0.0f, 1.0f };

	float sX = 0.1f / (2.0f * x);
	float sY = 0.1f / (2.0f * x);

	array<array<float, matrix4::DIM>, matrix4::DIM> scale_matrix;
	scale_matrix[0] = { sX,	 0.0f,	0.0f, 0.0f };
	scale_matrix[1] = { 0.0f, sY,	0.0f, 0.0f };
	scale_matrix[2] = { 0.0f, 0.0f,	1.0f, 0.0f };
	scale_matrix[3] = { 0.0f, 0.0f,  0.0f, 1.0f };

	array<array<float, matrix4::DIM>, matrix4::DIM> origin_matrix;
	origin_matrix[0] = { 1.0f, 0.0f,	0.0f, 0.0f };
	origin_matrix[1] = { 0.0f, 1.0f,	0.0f, 0.0f };
	origin_matrix[2] = { 0.0f, 0.0f,	1.0f, 0.0f };
	origin_matrix[3] = { 0.0f, 0.0f,	0.0f, 1.0f };

	matrix4 mat(origin_matrix);
	//mat.multiplyMatrix(scale_matrix);
	//mat.multiplyMatrix(trans_matrix);
	//mat.multiplyMatrix(pers_matrix);
	mat.multiplyMatrix(clip_matrix);

	this->current_matrix->multiplyMatrix(mat);*/

	//
	//
	// TODO: TEST
	/*float zoomx = 1.0f / tan(((fov * M_PI) / 180.0f) / 2.0f);
	float zoomy = 1.0f / tan(((fov * M_PI) / 180.0f) / 2.0f);

	float clip1 = ((far + near) / (far - near));
	float clip2 = ((-2.0f * near * far) / (far - near));

	array<array<float, matrix4::DIM>, matrix4::DIM> clip_matrix;
	clip_matrix[0] = { zoomx, 0.0f,  0.0f,  0.0f };
	clip_matrix[1] = { 0.0f,  zoomy, 0.0f,  0.0f };
	clip_matrix[2] = { 0.0f,  0.0f,  clip1, clip2 };
	clip_matrix[3] = { 0.0f,  0.0f,  1.0f,  0.0f };

	matrix4 mat(clip_matrix);

	this->current_matrix->multiplyMatrix(mat);*/
}

// MAY WANT TO DELETE THIS SECTION OF CODE
matrix4 graphics_pipeline::_glhFrustumf(float left, float right, float bottom, float top, float znear, float zfar)
{
	float temp, temp2, temp3, temp4;
	temp = 2.0 * znear;
	temp2 = right - left;
	temp3 = top - bottom;
	temp4 = zfar - znear;

	array<array<float, matrix4::DIM>, matrix4::DIM> clip_matrix;
	clip_matrix[0] = { temp / temp2,			0.0f,					(right + left) / temp2,							0.0f				   };
	clip_matrix[1] = { 0.0f,					temp / temp3,			(top + bottom) / temp3,							0.0f				   };
	clip_matrix[2] = { 0.0f,					0.0f,					(-zfar - znear) / temp4,						(-temp * zfar) / temp4 };
	clip_matrix[3] = { 0.0f,					0.0f,					-1.0f,											0.0f				   };

	matrix4 mat(clip_matrix);
	return mat;
}

matrix4 graphics_pipeline::_getPipeline()
{
	// TODO: TEST
	matrix4 pipeline = *this->projection;
	pipeline.multiplyMatrix(*this->modelview);
	//matrix4 s(pipeline.getMatrix());
	return pipeline;
}

matrix4 graphics_pipeline::_getModelViewMatrix()
{
	// TODO: TEST
	return *this->modelview;
}

matrix4 graphics_pipeline::_getProjectionMatrix() 
{
	// TODO: TEST
	return *this->projection;
}

glm::vec4 graphics_pipeline::_transform(glm::vec4 coordinates)
{
	// I THINK I JUST WANT TO RETURN A VEC 4 VALUE, OR CONVERT IT TO SCREEN ON THIS METHODS
	matrix4 pipeline = this->_getPipeline();
	return pipeline.transform(coordinates);
}

glm::vec3 graphics_pipeline::_to_screen(glm::vec4 transformed_coordinates)
{
	//array<array<float, 3>, 3> screen_matrix;
	//screen_matrix[0] = { 1000.0f / 2.0f,	 0.0f,			    1000.0f / 2.0f };
	//screen_matrix[1] = { 0.0f,				1000.0f / 2.0f,		1000.0f / 2.0f };
	//screen_matrix[2] = { 0.0f,				0.0f,				1.0f        };

	float w = transformed_coordinates.w;
	float transformed_coor_vec[3] = { transformed_coordinates.x / w, transformed_coordinates.y / w, 1.0f};
	

	//float new_vector[3] = {0.0f, 0.0f, 0.0f};
	//for (int i = 0; i < 3; i++) {
	//	for (int j = 0; j < 3; j++) {
	//		new_vector[i] += transformed_coor_vec[j] * screen_matrix[i][j];
	//	}
	//}

	//glm::vec3 screen_vec(new_vector[0], new_vector[1], new_vector[2]);
	glm::vec3 screen_vec(transformed_coor_vec[0], transformed_coor_vec[1], transformed_coor_vec[2]);
	return screen_vec;
}

/******************************************************/
/*			    singleton methods public			  */
/******************************************************/

void graphics_pipeline::mode(matrix_mode mode)
{
	graphics_pipeline::instance()->_mode(mode);
}

void graphics_pipeline::pushMatrix(matrix4 matrix)
{
	graphics_pipeline::instance()->_pushMatrix(matrix);
}

void graphics_pipeline::loadIdentityMatrix()
{
	graphics_pipeline::instance()->_loadIdentityMatrix();
}

void graphics_pipeline::rotate(float orientation, float x, float y, float z)
{
	graphics_pipeline::instance()->_rotate(orientation, x, y, z);
}

void graphics_pipeline::translate(float x, float y, float z)
{
	graphics_pipeline::instance()->_translate(x, y, z);
}

void graphics_pipeline::scale(float scale_x, float scale_y, float scale_z)
{
	graphics_pipeline::instance()->_scale(scale_x, scale_y, scale_z);
}

void graphics_pipeline::gluPerspective(float fov, float aspect, float near, float far)
{
	graphics_pipeline::instance()->_gluPerspective(fov, aspect, near, far);
}

matrix4 graphics_pipeline::getPipeline()
{
	return graphics_pipeline::instance()->_getPipeline();
}

matrix4 graphics_pipeline::getModelViewMatrix()
{
	return graphics_pipeline::instance()->_getModelViewMatrix();
}

matrix4 graphics_pipeline::getProjectionMatrix()
{
	return graphics_pipeline::instance()->_getProjectionMatrix();
}

glm::vec4 graphics_pipeline::transform(glm::vec4 coordinates)
{
	return graphics_pipeline::instance()->_transform(coordinates);
}

glm::vec3 graphics_pipeline::to_screen(glm::vec4 transformed_coordinates)
{
	return graphics_pipeline::instance()->_to_screen(transformed_coordinates);
}