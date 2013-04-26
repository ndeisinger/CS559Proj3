#include "Player.h"

Player::Player(void)
{
}

Player::~Player(void)
{
}

bool Player::init(void)
{
	//Initialization code
	return false;
}

void Player::orientCamera(void)
{
	//could be void
	glm::vec3 center = this->sphere.getPos();
	b2Body * body = this->sphere.getBody();
}

bool Player::draw(const glm::mat4 & proj, glm::mat4 mv, const glm::ivec2 & size, const float time, lightInfo * & l, materialInfo * & m)
{
	return this->sphere.draw(proj, mv, size, time, l, m);
}

Camera * Player::getCam(void)
{
	return &playCam;
}
