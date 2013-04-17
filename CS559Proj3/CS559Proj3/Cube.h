#pragma once
#include "drawobject.h"
#include "Box2D\Box2D.h"
typedef DrawObject super;
class Cube :
	public DrawObject
{
public:
	Cube(void);
	~Cube(void);
	bool init (float w, float h, float d);
	bool draw(const glm::mat4 & proj, glm::mat4 mv, const glm::ivec2 & size, const float time, lightInfo * & l, materialInfo * & m);
	void initPhysics(float size, glm::vec2 center, float angle, b2World * world); //Set up our Box2D object
protected:
	void subInit(VertexAttPCN b_l, VertexAttPCN u_l, VertexAttPCN b_r, VertexAttPCN u_r, glm::vec3 norm);
	
	b2BodyDef boxDef; // Stores position for hitbox; THIS SHOULD BE IN SYNC WITH DRAWOBJECT'S POS VALUE
	b2Body* boxBody;  // Body for the circle that represents the sphere for collision detection
	b2PolygonShape boxShape; //Represent the circle's hitbox
	b2FixtureDef boxFixtureDef; //Fixture definition for the circle
};

