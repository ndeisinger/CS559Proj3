#pragma once
#include "glutInclude.h"
#include <assert.h>
#include <sstream>
#include "MaterialInfo.h"

//Class for our various shaders.
enum SHADER_TYPE {NONE, FLAT, GOURAUD, PHONG, DEBUG_POS, MAX, NORM, DEBUG_NORM, TEX}; //max val used to help us cycle
class Shader
{
public:
	Shader(void);
	~Shader(void);
	//bool init(char * vertex_shader_file, char * fragment_shader_file);
	//TODO: Reboot function X
	bool init(SHADER_TYPE t);
	void setup(const float time, const GLint * size, const GLfloat * proj, const GLfloat * mv, const GLfloat * mvp, const GLfloat * norm);
	void use(void);
	void lightSetup(lightInfo & l);
	void materialSetup(materialInfo & m);
	void texSetup(void);
	void TakeDown(void); //TODO: Different protection? X Nah, we want to be able to call it from main.
	void reload(SHADER_TYPE t);
	std::stringstream GetShaderLog(GLuint shader_id);
	SHADER_TYPE type;

	static GLint light_index;
	static GLuint light_handle;

protected:
	void inval(void);
	//bool GLReturnedError(char * s);
	bool load(char * file, GLuint handle);
	static int bind_point; // Binding locations for our uniform buffers.

	GLint time_handle;
	GLint size_handle; 

	// Matrix handles.
	GLint mv_mat_handle;
	GLint p_mat_handle;
	GLint mvp_mat_handle;
	GLint n_mat_handle; 

	GLint material_index; // Material uniform index location.
	GLuint material_handle; // Material buffer handle.

	GLint tex_handle; // Texture handle.
	
	GLuint program_id; // Program handle.
	GLuint vertex_s_id; // Vertex shader handle.
	GLuint frag_s_id; // Fragment shader handle.

	GLubyte * lightBuffer; // Space for lighting info.
	GLubyte * matBuffer; // Space for material info.

};

