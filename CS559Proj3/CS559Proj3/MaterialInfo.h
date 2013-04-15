//Used to define structs for material and lighting information.
#pragma once
#include <glm/glm.hpp>

typedef struct _lightInfo {
	glm::vec4 position; //come to think of it, should this be vec3?
	glm::vec3 color; // TODO: This is redundant.
	glm::vec3 amb;
	glm::vec3 diff;
	glm::vec3 spec;
	GLint spec_exp; //TODO: Have this here or in other location?
	// Ultimately it made more sense to deal with it w/ shininess, but no time to remove.
} lightInfo;

typedef struct _materialInfo {
	glm::vec3 kA;
	glm::vec3 kD;
	glm::vec3 kS;
	float shininess;
} materialInfo;
