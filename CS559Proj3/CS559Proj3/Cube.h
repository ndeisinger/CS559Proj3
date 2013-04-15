#pragma once
#include "drawobject.h"
typedef DrawObject super;
class Cube :
	public DrawObject
{
public:
	Cube(void);
	~Cube(void);
	bool init (float w, float h, float d);
	bool draw(const glm::mat4 & proj, glm::mat4 mv, const glm::ivec2 & size, const float time, lightInfo * & l, materialInfo * & m);
protected:
	void subInit(VertexAttPCN b_l, VertexAttPCN u_l, VertexAttPCN b_r, VertexAttPCN u_r, glm::vec3 norm);
};

