#include "World.h"
#include "Cube.h"
//ASSUMPTION: THE WORLD IS 5280 x 5280 UNITS
//NOTE: That's feet.  Box2D uses meters-kilograms-seconds.  

World::World(void)
{
	return;
}

World::~World(void)
{
	//Probably want some TakeDown methods here
	return;
}

bool World::init(int spheres)
{
	birdsEye.proj = glm::perspective(birdsEye.fov, (float) 800/600, 1.0f, 500.0f); //TODO: Need to move data from window to world
	birdsEye.modelview = glm::lookAt(glm::vec3(0.0f, 200.0f, 0.0f), glm::vec3(0.01f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	for (int i = 0; i < spheres; i++)
	{
		Sphere new_s;
		new_s.initialize(50, 10, 10);
		new_s.setPos(glm::vec3(rand() % 1000, 0.0f, rand() % 1000));
		this->spheres.push_back(new_s);
//		this->spheres.push_back(new DrawObject()); //TODO: But for serious need to get a good distribution
	}
	this->currCam = &birdsEye;
	l.amb = glm::vec3(0.5, 0.5, 0.5);
	l.diff = glm::vec3(0.5, 0.5, 0.5);
	l.spec = glm::vec3(0.5, 0.5, 0.5);
	l.position = glm::vec4(0.0, 5.0, 0.0, 1.0);
	return true;
}

void World::draw()
{
	//INSERT BOX2D SIMULATION HERE
	lightInfo * new_l = &l;
	materialInfo * new_m = &m;
	Cube c;
	c.init(3.0f, 3.0f, 3.0f);
	c.setPos(glm::vec3(0.0f, 0.0f, 10.0f));
	DrawObject::common_shader.init(DEBUG_POS);
	for (sphereIt = spheres.begin(); sphereIt < spheres.end(); sphereIt++)
	{
		sphereIt->draw(currCam->proj, currCam->modelview, glm::ivec2(1.0, 1.0), 0.0f, new_l, new_m);
	}
	c.draw(currCam->proj, currCam->modelview, glm::ivec2(1.0, 1.0), 0.0f, new_l, new_m);
}