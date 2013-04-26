#include "Player.h"

Player::Player(void)
{
}

Player::~Player(void)
{
}

bool Player::init(float radius, int slices, int stacks, float x, float z)
{
	//Initialization code
	glm::vec4 colors[2] = {glm::vec4(0.0f, 0.0f, 1.0f, 1.0f), glm::vec4(0.0f, 0.0f, 1.0f, 1.0f)};
	sphere.setColor(colors);
	this->sphere.initialize(SPHERE_RADIUS, slices, stacks);
	return false;
}

void Player::update(void)
{
	sphere.updatePos();
	glm::vec3 center = this->sphere.getPos();
	b2Body * body = this->sphere.getBody();
	
	//Calculate GLM look_at as radius away from center at the angle pointed to
	float rot_angle = body->GetAngle(); //Radians
	float x = center.x + (sphere.getRadius() * sin(rot_angle));
	float z = center.z + (sphere.getRadius() * cos(rot_angle));
	printf("Angle: %f, x: %f, z: %f, radius: %f, rot_angle: %f\n", rot_angle, x, z, sphere.getRadius(), rot_angle);
	playCam.modelview = glm::lookAt(glm::vec3(x, 0.0, z), glm::vec3(2 * x, 0.0, 2 * z), glm::vec3(0.0f, 1.0f, 0.0f));
	playCam.proj = glm::perspective(playCam.fov, (float) 800/600, 1.0f, 2000.0f);
}

void Player::initPhysics(b2World * world)
{
	sphere.initPhysics(world);
}

bool Player::draw(const glm::mat4 & proj, glm::mat4 mv, const glm::ivec2 & size, const float time, lightInfo * & l, materialInfo * & m)
{
	return this->sphere.draw(proj, mv, size, time, l, m);
}

Camera * Player::getCam(void)
{
	return &playCam;
}
