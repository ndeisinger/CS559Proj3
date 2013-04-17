#include "World.h"
#include "Cube.h"
//ASSUMPTION: THE WORLD IS 5280 x 5280 UNITS
//NOTE: That's feet.  Box2D uses meters-kilograms-seconds.  
//NOTE: We let (x,y) in box2d translate to (x, 0.0, y) in 3d.

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
	this->world = new b2World(b2Vec2(000.0f, 1445.9f));
	birdsEye.proj = glm::perspective(birdsEye.fov, (float) 800/600, 1.0f, 50000.0f); //TODO: Need to move data from window to world
	birdsEye.modelview = glm::lookAt(glm::vec3(1000.0f, 2000.0f, 1000.0f), glm::vec3(2000.01f, 0.0f, 2000.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	/*
	for (int i = 0; i < spheres; i++)
	{
		Sphere new_s;
		new_s.initialize(50, 10, 10);
		new_s.setPos(glm::vec3(rand() % 1000, 0.0f, rand() % 1000));
		new_s.initPhysics(world); //Since this uses the inital position, must call after setPos
		this->spheres.push_back(new_s);
		//TODO: Initialize Box2d info for each sphere as well.  Maybe abstract that into the init method?
//		this->spheres.push_back(new DrawObject()); //TODO: But for serious need to get a good distribution
	}*/
	//DEBUG

	for (int j = 0; j < 5; j++)
	{
		Sphere new_s;
		new_s.initialize(50, 10, 10);
		new_s.setPos(glm::vec3(2000 + 110.0f * j, 0.0f, 2000 + 110.0f * j));
		new_s.initPhysics(world); //Since this uses the inital position, must call after setPos
		this->spheres.push_back(new_s);
//		this->spheres.push_back(new DrawObject()); //TODO: But for serious need to get a good distribution
	}
	this->currCam = &birdsEye;

	l.amb = glm::vec3(0.5, 0.5, 0.5);
	l.diff = glm::vec3(0.5, 0.5, 0.5);
	l.spec = glm::vec3(0.5, 0.5, 0.5);
	l.position = glm::vec4(0.0, 5.0, 0.0, 1.0);
	m.kA = glm::vec3(0.9f, 0.9f, 0.9f);
	m.kD = glm::vec3(0.5f, 0.5f, 0.5f);
	m.kS = glm::vec3(0.6f, 0.6f, 0.6f);
	m.shininess = 0.6f;

	stadium.init();
	stadium.initPhysics(world);

	DrawObject::common_shader.init(PHONG);
	return true;
}

void World::draw()
{
	lightInfo * new_l = &l;
	materialInfo * new_m = &m;
	world->Step(0.01667f, 500, 500); //TODO: Match this w/ draw rate
	for (sphereIt = spheres.begin(); sphereIt < spheres.end(); sphereIt++)
	{
		sphereIt->updatePos(); //Update sphere's location with physics-based one
		sphereIt->draw(currCam->proj, currCam->modelview, glm::ivec2(1.0, 1.0), 0.0f, new_l, new_m);
	}
	stadium.draw(currCam->proj, currCam->modelview, glm::ivec2(1.0, 1.0), 0.0f, new_l, new_m);
}