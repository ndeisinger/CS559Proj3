#pragma once
#include "Box2D\Box2D.h"

static float max_time;
static int num_spheres;

inline float feetToMeters(float feet) { return (feet * 0.3048f); }
inline float metersToFeet(float meters) { return (meters * 3.28084f); }

static const float SPHERE_RADIUS = feetToMeters(50.0f);
static const float WALL_HEIGHT = 2 * SPHERE_RADIUS;
static const float WALL_LENGTH = feetToMeters(2640.0f);

typedef struct _sphere_data
{
	float time_left;
	bool active;
} sphere_data;