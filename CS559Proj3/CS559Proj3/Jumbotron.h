#pragma once
#include "Cube.h"
class Jumbotron
{
public:
	Jumbotron(void);
	~Jumbotron(void);
	void init(glm::vec3 pos, bool flipped); //Do the bool because it's cheaper to init it flipped than do an extra matrix rotation
	bool draw(const glm::mat4 & proj, glm::mat4 mv, const glm::ivec2 & size, const float time, lightInfo * & l, materialInfo * & m);
	void TakeDown(void);
protected:
	Cube stand;
	Cube screen;
	glm::vec3 pos;
};

