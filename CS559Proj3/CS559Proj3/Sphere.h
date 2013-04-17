#pragma once
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

private:
	glm::vec4 colors[2];
	bool solidColor;
	void BuildNormalVisualizationGeometry();
};

