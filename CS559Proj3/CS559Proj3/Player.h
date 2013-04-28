// Class used to represent a player in the world.
// Has an associated sphere object and position.
// NOTE: The camera for the player is placed on the outer radius of the sphere,
// NOT the center.

#include "glutInclude.h"
#include "Camera.h"
#include "Sphere.h"

#pragma once
class Player
{
public:
	Player(void);
	~Player(void);
	Camera * getCam(void);
	bool init(float radius, int slices, int stacks, float x, float z);
	void initPhysics(b2World * world);
	void rotate(float angle);
	void update(void);
	bool draw(const glm::mat4 & proj, glm::mat4 mv, const glm::ivec2 & size, const float time, lightInfo * & l, materialInfo * & m);
private:
	Camera playCam;
	Sphere sphere; //The sphere the player's bouncing around on; we don't draw this in first-person.
	float ang_force;
};

