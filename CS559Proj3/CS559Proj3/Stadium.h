//The base area for our game.
//COMPRISED OF:
//A floor (for now a cube, later we will make it special)
//Four walls
//Two pillars with screens
#include "glutInclude.h"
#include "Cube.h"

#pragma once
class Stadium
{
public:
	Stadium(void);
	~Stadium(void);
	void init();
	void draw(const glm::mat4 & proj, glm::mat4 mv, const glm::ivec2 & size, const float time, lightInfo * & l, materialInfo * & m);
protected:
	Cube wall_one;
	Cube wall_two;
	Cube wall_three;
	Cube wall_four; //NOTE: We must be able to simulate bumping against these.
	Cube floor;

};

