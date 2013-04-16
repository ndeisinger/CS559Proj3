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

Camera * Player::getCam(void)
{
	return &playCam;
}
