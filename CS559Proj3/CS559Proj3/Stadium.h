//The base area for our game.
//COMPRISED OF:
//A floor (for now a cube, later we will make it special)
//Four walls
//Two pillars with screens

//The position of the stadium is fixed at 0,0.
//We translate our cubes, then scale them appopriately.
//The danger here is ensuring hitboxes are translated and scaled properly as well.
#include "glutInclude.h"
#include "Cube.h"

#pragma once
class Stadium
{
public:
	Stadium(void);
	~Stadium(void);
	void init();
	bool draw(const glm::mat4 & proj, glm::mat4 mv, const glm::ivec2 & size, const float time, lightInfo * & l, materialInfo * & m);
	void initPhysics(b2World * world); //Set up our Box2D object
protected:
	Cube wall_one;
	Cube wall_two;
	Cube wall_three;
	Cube wall_four; //NOTE: We must be able to simulate bumping against these.
	Cube floor;
	b2Body* ground;
};

