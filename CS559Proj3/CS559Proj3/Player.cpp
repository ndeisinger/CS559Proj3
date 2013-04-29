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

//Need to apply impulse to the player body
//And also adjust angle.
//Probably... adjust angle by adding to it depending on mouse location,
//Then always apply a certain forward motion.

void Player::rotate(float angle)
{
	//float curr_angle = this->sphere.getBody()->GetAngle();
	//curr_angle += angle;
	this->ang_force = angle;
}

void Player::update(void)
{
	sphere.updatePos();
	glm::vec3 center = this->sphere.getPos();
	b2Body * body = this->sphere.getBody();
	body->SetAngularVelocity(0);

	//Calculate GLM look_at as radius away from center at the angle pointed to
	float rot_angle = body->GetAngle(); //Radians
	float x = center.x + (sphere.getRadius() * sin(rot_angle));
	float z = center.z + (sphere.getRadius() * cos(rot_angle));
	float x_force = 20.0f * sin(rot_angle);
	float z_force = 20.0f * cos(rot_angle);
	printf("Angle: %f, x: %f, z: %f, radius: %f, rot_angle: %f, x_force: %f, z_force: %f\n", rot_angle, x, z, sphere.getRadius(), rot_angle, x_force, z_force);
	playCam.modelview = glm::lookAt(glm::vec3(x, 0.0, z), glm::vec3(x + (sphere.getRadius() * sin(rot_angle)), 0.0, z + (sphere.getRadius() * cos(rot_angle))), glm::vec3(0.0f, 1.0f, 0.0f));
	playCam.proj = glm::perspective(playCam.fov, (float) 800/600, 1.0f, 2000.0f);
	this->sphere.getBody()->ApplyAngularImpulse(ang_force);
	body->ApplyLinearImpulse(b2Vec2(x_force, z_force), body->GetWorldCenter());

	//Note: at present we don't get proper behavior.  The direction in which we move and the angle we're looking in don't sync up.

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
