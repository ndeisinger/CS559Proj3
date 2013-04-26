#pragma once
#include "Box2D\Box2D.h"
#include "DrawObject.h"
#include "glutInclude.h"
typedef DrawObject super;

class Sphere :
	public DrawObject
{
public:
	Sphere(void);
	~Sphere(void);
	bool draw(const glm::mat4 & proj, glm::mat4 mv, const glm::ivec2 & size, const float time, lightInfo * & l, materialInfo * & m);
	bool initialize(float radius, int slices, int stacks);
	void initPhysics(b2World * world); //Set up our Box2D object
	void updatePos();
	inline b2Body * getBody() { return circleBody; }
	inline float getRadius() { return own_radius; }
	inline void setColor(glm::vec4 new_colors[2]) { colors[0] = new_colors[0]; colors[1] = new_colors[1]; custom_colors = true; }

private:
	float own_radius; //Allow this to be variable in case we want to adjust spheres
	glm::vec4 colors[2];
	bool solidColor;
	void BuildNormalVisualizationGeometry();

	bool custom_colors; //Are we using unusal colors?
	b2BodyDef circleDef; // Stores position for hitbox; THIS SHOULD BE IN SYNC WITH DRAWOBJECT'S POS VALUE
	b2Body* circleBody;  // Body for the circle that represents the sphere for collision detection
	b2CircleShape circleShape; //Represent the circle's hitbox
	b2FixtureDef circleFixtureDef; //Fixture definition for the circle
	//struct sphere_data data; //Stores timer/activated bool
};

