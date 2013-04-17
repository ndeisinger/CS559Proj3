#include "glutInclude.h"
#include <vector>
#include <random>
#include "DrawObject.h"
#include "Camera.h"
#include "Player.h"
#include "Sphere.h"
#include "Stadium.h"
#include "MaterialInfo.h"
#include "Box2D\Box2D.h"

class World
{
public:
	World(void);
	~World(void);
	bool init(int spheres); //Should we specify stacks/slices?
	//void draw(glm::mat4 mv, glm::mat4 perspective); //Actually, this should be void - we handle mv/persp inside
	void draw(void);
	void switchCam(void); //Switch from overhead view to first-person view

private:
	vector<Sphere> spheres; // Keeps track of all our spheres in the world
	std::vector<Sphere>::iterator sphereIt; //Lets us move through the spheres and draw them
	Camera * currCam; // Points to the camera we're using
	Camera birdsEye; // Camera situated above the world
	Stadium stadium; // Our playing field
	glm::mat4 baseMv; // Base modelview for our world
	lightInfo l; //Light for our world
	materialInfo m;
	// The camera for the player is in the Player class

	//BOX2D INFO
	b2World * world; //Our world; have as pointer because there's no default constructor
};