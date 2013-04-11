//Oh god what is this I don't even

#include <Box2D/Box2D.h>
#include <vector>
#include <gl/glew.h>
#include <gl/freeglut.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <math.h>

int main (int argc, char * argv[])
{
	B2_NOT_USED(argc);
	B2_NOT_USED(argv);

	b2Vec2 gravity(0.0f, -10.0f);
	b2World world(gravity);

	//Define the ground

	b2BodyDef groundBodyDef;
	groundBodyDef.position.Set(0.0f, -10.0f);

	b2Body * groundBody = world.CreateBody(&groundBodyDef);

	//Our ground is a box, 100 x 20

	b2PolygonShape groundBox;

	groundBox.SetAsBox(50.0f, 10.0f);

	groundBody->CreateFixture(&groundBox, 0.0f); //TODO: Why is this 0.0f for density?

	//Now we have a dynamic body factory.  Best name ever.

	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(0.0f, 4.0f);
	b2Body * body = world.CreateBody(&bodyDef);

	//Define our dynamic body shape to be a box

	b2PolygonShape dynamicBox;
	dynamicBox.SetAsBox(2.0, 2.0);

	//Fix it to the dynamic body

	b2FixtureDef dynDef;
	dynDef.shape = &dynamicBox;
	dynDef.density = 1.0f;
	dynDef.friction = 0.3f;

	body->CreateFixture(&dynDef);

	//Everything after this is straight copy-and-pasted from the hello world

	// Prepare for simulation. Typically we use a time step of 1/60 of a
	// second (60Hz) and 10 iterations. This provides a high quality simulation
	// in most game scenarios.
	float32 timeStep = 1.0f / 60.0f;
	int32 velocityIterations = 6;
	int32 positionIterations = 2;

	// This is our little game loop.
	for (int32 i = 0; i < 60; ++i)
	{
		// Instruct the world to perform a single step of simulation.
		// It is generally best to keep the time step and iterations fixed.
		world.Step(timeStep, velocityIterations, positionIterations);

		// Now print the position and angle of the body.
		b2Vec2 position = body->GetPosition();
		float32 angle = body->GetAngle();

		printf("%4.2f %4.2f %4.2f\n", position.x, position.y, angle);
		wait(1);
	}

	// When the world destructor is called, all bodies and joints are freed. This can
	// create orphaned pointers, so be careful about your world management.

	return 0;
}