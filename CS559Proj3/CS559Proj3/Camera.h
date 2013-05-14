#include "glutInclude.h"
#pragma once
class Camera
{
public:
	Camera();
	~Camera();
	glm::mat4 proj;
	glm::mat4 modelview;
	glm::vec3 loc; //Location of the cmaera
	glm::vec3 point; //Where we're looking at in our eyeLoc.
	float fov; //our FOV
};
