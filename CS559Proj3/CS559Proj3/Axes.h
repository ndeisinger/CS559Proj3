#pragma once
#include "DrawObject.h"
class Axes :
	public DrawObject
{
public:
	Axes(void);
	~Axes(void);
	bool draw(const glm::mat4 & proj, glm::mat4 mv, const glm::ivec2 & size, const float time, lightInfo * & l); //TODO: Move this to the DrawObject header/class?
	bool init(void);
};

