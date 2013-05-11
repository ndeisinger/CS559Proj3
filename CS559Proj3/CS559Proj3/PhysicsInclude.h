#pragma once
#include "Box2D\Box2D.h"
#include "glm\glm.hpp"

extern float max_time;
extern int num_spheres;
extern float elapsed_time;
extern b2Vec2 player_pos;
static float prev_time = 0.0f;
static bool is_paused = false;

inline float feetToMeters(float feet) { return (feet * 0.3048f); }
inline float metersToFeet(float meters) { return (meters * 3.28084f); }
inline glm::vec2 boxToGlm (b2Vec2 in) { return glm::vec2(in.x, in.y); }

static const float SPHERE_RADIUS = feetToMeters(50.0f);
static const float WALL_HEIGHT = 2 * SPHERE_RADIUS;
static const float WALL_LENGTH = feetToMeters(2640.0f);
typedef struct _sphere_data
{
	float time_left;
	bool active;
	bool isPlayer;
} sphere_data;