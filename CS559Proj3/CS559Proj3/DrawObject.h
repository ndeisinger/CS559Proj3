#pragma once
#include "glutInclude.h"
#include "VertexAtt.h"
#include <algorithm>
#include "Shader.h"

using namespace std;
class DrawObject
{
public:
	DrawObject(void);
	~DrawObject(void);
	bool initialize(void);
	bool bindArray(GLuint * arr_handle, GLuint * coor_handle, GLsizeiptr size, const GLvoid * data);
	void UseTexture();
	void recolor(glm::vec3 color);
	void switchShader(SHADER_TYPE t);
	void TakeDown(void);
	
	static Shader norm_shader; // All objects will use the same norm shader.  Hopefully this doesn't catastrophically break anything.  If it does we can bump it down to the protected/non-static.
							   // Nope, all good.  But this begs the question: could we make the actual shader static as well?
							   // Would obviously limit us to one shader for all objects... but that's what we do now anyways.  
	static bool draw_norms;    // If we're showing normals, may as well show them all, since we can't much switch between objects.
	static Shader common_shader;
	static bool draw_axes;
	static DrawObject * a;
	static bool axes_init;
protected:

	//bool GLReturnedError(char * s);
	bool initNorms();
	void drawNorms();
	bool norms_init;
	glm::vec3 color;
	bool useTex;
	bool customShader;
	int draw_type; //eg. GL_TRIANGLES, GL_LINES
	bool s_draw(const glm::mat4 & proj, glm::mat4 & mv, const glm::ivec2 & size, const float & time, lightInfo * & l, materialInfo * & m); //Does the actual heavy lifting for draw

	glm::vec3 position; //Overall position in the world

	GLuint vertex_arr_handle;
	GLuint vertex_coor_handle;
	GLuint normal_arr_handle;
	GLuint normal_coor_handle;
	GLuint tex_arr_handle;
	GLuint tex_coor_handle;
	GLuint tex_handle;

	vector<GLuint> vertex_indices;
	vector<VertexAttPCN> atts_pcn;
	vector<VertexAttPCNT> atts_pcnt;
	vector<VertexAttPCN> norm_vertices;
	vector<GLuint> norm_indices;

	Shader shader;
};

