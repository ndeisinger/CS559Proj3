#include "World.h"
//ASSUMPTION: THE WORLD IS 5280 x 5280 UNITS
//NOTE: That's feet.  Box2D uses meters-kilograms-seconds.  

World::World()
{
	return;
}

World::~World()
{
	//Probably want some TakeDown methods here
	return;
}

bool World::init(int spheres)
{
	birdsEye.proj = glm::perspective(birdsEye.fov, (float) 800/600, 1.0f, 500.0f); //TODO: Need to move data from window to world
	birdsEye.modelview = glm::lookAt(glm::vec3(0.0f, 20.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	for (int i = 0; i < spheres; i++)
	{
		this->spheres.push_back(new DrawObject()); //TODO: But for serious need to get a good distribution
	}
	return true;
}

void World::draw()
{
	//INSERT BOX2D SIMULATION HERE
	for (sphereIt = spheres.begin(); sphereIt < spheres.end(); sphereIt++)
	{
		*sphereIt->draw(currCam->modelview, currCam->proj, glm::vec2(1.0, 1.0), l, m);
	}
}