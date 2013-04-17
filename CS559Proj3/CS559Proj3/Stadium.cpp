#include "Stadium.h"


Stadium::Stadium(void)
{
}

#define WALL_HEIGHT 200.0f
#define FLOOR_DEPTH -50.0f
void Stadium::init(void)
{
	wall_one.init(1.0f, WALL_HEIGHT, 5280.0f);
	wall_one.setPos(glm::vec3(2640.f, FLOOR_DEPTH, -2640.0f));
	wall_two.init(1.0f, WALL_HEIGHT, 5280.0f);
	wall_two.setPos(glm::vec3(-2640.f, FLOOR_DEPTH, -2640.0f));
	wall_three.init(5280.0f, WALL_HEIGHT, 1.0f);
	wall_three.setPos(glm::vec3(-2640.0f, FLOOR_DEPTH, 2640.0f));
	wall_four.init(5280.0f, WALL_HEIGHT, 1.0f);
	wall_four.setPos(glm::vec3(-2640.0f, FLOOR_DEPTH, -2640.0f));
	floor.init(5280.0f, 1.0f, 5280.0f);
	floor.setPos(glm::vec3(-2640.0f, FLOOR_DEPTH, -2640.0f));
}

void Stadium::initPhysics(b2World * world) //Set up our Box2D object
{
	wall_one.initPhysics(5280.0f, glm::vec2(2640.0f, 0.0f), 0.0f, world);
	wall_two.initPhysics(5280.0f, glm::vec2(-2640.0f, 0.0f), 0.0f, world);
	wall_three.initPhysics(5280.0f, glm::vec2(0.0f, 2640.0f), 0.0f, world);
	wall_four.initPhysics(5280.0f, glm::vec2(0.0f, -2640.0f), 0.0f, world);
}

Stadium::~Stadium(void)
{
}

void Stadium::draw(const glm::mat4 & proj, glm::mat4 mv, const glm::ivec2 & size, const float time, lightInfo * & l, materialInfo * & m)
{
	wall_one.draw(proj, mv, size, time, l, m);
	wall_two.draw(proj, mv, size, time, l, m);
	wall_three.draw(proj, mv, size, time, l, m);
	wall_four.draw(proj, mv, size, time, l, m);
	floor.draw(proj, mv, size, time, l, m);
}