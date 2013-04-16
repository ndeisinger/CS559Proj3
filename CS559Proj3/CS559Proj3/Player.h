// Class used to represent a player in the world.
// Has an associated sphere object and position.
// NOTE: The camera for the player is placed on the outer radius of the sphere,
// NOT the center.

#include "glutInclude.h"
#include "Camera.h"

#pragma once
class Player
{
public:
	Player(void);
	~Player(void);
	Camera * getCam(void);
	bool init(void);
private:
	Camera playCam;
	//Sphere sphere;
};

