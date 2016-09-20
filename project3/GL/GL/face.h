#pragma once

#include <glm/vec2.hpp> // glm::vec3
#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <vector>

using namespace std;

class material {
	public:
		glm::vec3 vertex;
		glm::vec2 uv;
		glm::vec3 normal;
};

class face {

	public:
		
		face();

		~face();

		void addFaceMaterial(glm::vec3 _vertex, glm::vec2 _uv, glm::vec3 _normal);

		vector<material> getFaceMaterial();

		int getFaceSize();

	private:
		
		vector<material> faceMaterial;
	
};
