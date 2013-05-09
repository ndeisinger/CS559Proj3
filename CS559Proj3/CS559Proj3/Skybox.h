#pragma once
#include "DrawObject.h"
#include "glutInclude.h"


typedef DrawObject super;

class Skybox :
	public DrawObject
{
public:
	Skybox(void);
	~Skybox(void);
	bool draw(const glm::mat4 & proj, glm::mat4 mv, const glm::ivec2 & size, const float time, lightInfo * & l, materialInfo * & m);
	bool initialize(float radius, int slices, int stacks);

	//void makeSkydome(void);

	inline float getRadius() { return own_radius; }
	inline void setColor(glm::vec4 new_colors[2]) { colors[0] = new_colors[0]; colors[1] = new_colors[1]; custom_colors = true; }


private:
	
	float own_radius; //Allow this to be variable in case we want to adjust spheres
	glm::vec4 colors[2];
	bool solidColor;
	void BuildNormalVisualizationGeometry();

	bool custom_colors; //Are we using unusal colors?

};
