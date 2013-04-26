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

void World::switchCam(void)
{
	if (this->currCam == &this->birdsEye)
	{
		this->currCam = this->player.getCam();
	}
	else
	{
		this->currCam = &this->birdsEye;
	}
}

bool World::init(int sphere_count)
{
	if (GLReturnedError("World init - on entry")) return true;
	b2Vec2 gravity;
	gravity.Set(1.0f, 0.0f);
	bool doSleep = true;
	this->world = new b2World(gravity);
	world->SetAllowSleeping(doSleep);
	//world->SetContinuousPhysics(true); //For testing only
	birdsEye.proj = glm::perspective(birdsEye.fov, (float) 800/600, 1.0f, 50000.0f); //TODO: Need to move data from window to world
	birdsEye.modelview = glm::lookAt(glm::vec3(0.0f, 2000.0f, 0.0f), glm::vec3(-000.01f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	
	for (int i = 0; i < sphere_count; i++)
	{
#ifndef BOX2D_DEBUG
		Sphere * new_s = new Sphere();
		new_s->initialize(SPHERE_RADIUS, 10, 10);
		new_s->setPos(glm::vec3(-WALL_LENGTH + rand() % (int) (2 * WALL_LENGTH), 0.0f, -WALL_LENGTH + rand() % (int) (2 * WALL_LENGTH)));
		new_s->initPhysics(world); //Since this uses the inital position, must call after setPos
		this->spheres.push_back(new_s);
#endif
		//TODO: Initialize Box2d info for each sphere as well.  Maybe abstract that into the init method?
//		this->spheres.push_back(new DrawObject()); //TODO: But for serious need to get a good distribution
	}

	//DEBUG
	/*
	for (int j = -50; j < 50; j++)
	{
		Sphere new_s;
		new_s.initialize(50, 10, 10);
		new_s.setPos(glm::vec3(110.0f * j, 0.0f, 110.0f * j));
		new_s.initPhysics(world); //Since this uses the inital position, must call after setPos
		this->spheres.push_back(new_s);
//		this->spheres.push_back(new DrawObject()); //TODO: But for serious need to get a good distribution
	}*/
	this->currCam = &birdsEye;

	player.init(SPHERE_RADIUS, 10, 10, 0.0f, 0.0f);
	player.initPhysics(world);
	player.update();

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

#ifdef BOX2D_DEBUG

	circleDef.type = b2_dynamicBody;
	circleDef.position.Set(50.0f, 50.0f);
	circleDef.bullet = true;
	circleBody = world->CreateBody(&circleDef);
	circleShape.m_p.Set(50.0f, 50.0f);
	circleShape.m_radius = 5.0f;
	circleFixtureDef.shape = &circleShape;
	circleFixtureDef.density = 1.0f;
	circleFixtureDef.friction = 0.1001f;

	circleDef2.type = b2_dynamicBody;
	circleDef2.position.Set(150.0f, 150.0f);
	circleDef2.bullet = true;
	circleBody2 = world->CreateBody(&circleDef);
	circleShape2.m_p.Set(50.0f, 50.0f);
	circleShape2.m_radius = 5.0f;
	circleFixtureDef2.shape = &circleShape;
	circleFixtureDef2.density = 1.0f;
	circleFixtureDef2.friction = 0.1001f;
	
	circleBody->CreateFixture(&circleFixtureDef);
	circleBody2->CreateFixture(&circleFixtureDef2);

#endif

	DrawObject::common_shader.init(PHONG);
	if (GLReturnedError("World init - on exit")) return false;
	return true;
}

int debug_counter = 0;

void World::draw()
{
	if (GLReturnedError("World draw - on entry")) return;
	lightInfo * new_l = &l;
	materialInfo * new_m = &m;
	world->Step(0.016667f, 10, 10); //TODO: Match this w/ draw rate
	for (sphereIt = spheres.begin(); sphereIt < spheres.end(); sphereIt++)
	{
		(*sphereIt)->updatePos(); //Update sphere's location with physics-based one
		(*sphereIt)->draw(currCam->proj, currCam->modelview, glm::ivec2(1.0, 1.0), 0.0f, new_l, new_m);
	}
	player.update();
	if (this->currCam == &this->birdsEye)
	{
		//Drawing from above, need to show player
		player.draw(currCam->proj, currCam->modelview, glm::ivec2(1.0, 1.0), 0.0f, new_l, new_m);
	}
#ifdef BOX2D_DEBUG
		printf("x: %f, y: %f, q: %f\n", circleBody->GetPosition().x, circleBody->GetPosition().y, circleBody->GetAngle());
		printf("x: %f, y: %f, q: %f\n\n", circleBody2->GetPosition().x, circleBody2->GetPosition().y, circleBody->GetAngle());
#endif
	debug_counter++;
	if (debug_counter % 10000 == 0)
	{
		printf("Stop! 10000 passed.\n");
		world->Dump();
	}
	stadium.draw(currCam->proj, currCam->modelview, glm::ivec2(1.0, 1.0), 0.0f, new_l, new_m);
	if (GLReturnedError("World draw - on exit")) return;
}