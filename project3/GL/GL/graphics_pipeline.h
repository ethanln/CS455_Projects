#pragma once
#include "matrix4.h"
#include "glm/vec3.hpp"
#include "glm/vec4.hpp"

using namespace std;

enum matrix_mode {
	PROJECTION_GL,
	MODELVIEW_GL
};

class graphics_pipeline
{
	private:
		matrix4* modelview;
		matrix4* projection;
		matrix4* current_matrix;

		static graphics_pipeline *inst;

		static graphics_pipeline* instance();

		graphics_pipeline();

		~graphics_pipeline();

		void _mode(matrix_mode mode);

		void _pushMatrix(matrix4 matrix);

		void _loadIdentityMatrix();

		void _rotate(float orientation, float x, float y, float z);

		void _translate(float x, float y, float z);

		void _scale(float scale_x, float scale_y, float scale_z);

		void _gluPerspective(float fov, float aspect, float near, float far);

		void _combinePipeline();

		matrix4 _glhFrustumf(float left, float right, float bottom, float top, float znear, float zfar);

		matrix4 _getPipeline();

		matrix4 _getModelViewMatrix();

		matrix4 _getProjectionMatrix();

		glm::vec4 _transform(glm::vec4 coordinates);

		glm::vec3 _to_screen(glm::vec4 transformed_coordinates);

	public:
		
		static void mode(matrix_mode mode);

		static void pushMatrix(matrix4 matrix);

		static void loadIdentityMatrix();

		static void rotate(float orientation, float x, float y, float z);

		static void translate(float x, float y, float z);

		static void scale(float scale_x, float scale_y, float scale_z);

		static void gluPerspective(float fov, float aspect, float near, float far);

		static void combinePipeline();

		static matrix4 getPipeline();

		static matrix4 getModelViewMatrix();

		static matrix4 getProjectionMatrix();

		static glm::vec4 transform(glm::vec4 coordinates);
		
		static glm::vec3 to_screen(glm::vec4 transformed_coordinates);
};