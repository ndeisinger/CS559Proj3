#pragma once
#include "glutInclude.h"
#include <assert.h>
#include <sstream>
#include "MaterialInfo.h"
#include "Textures.h"

#define BAD_GL_VALUE GLuint(-1)

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
	virtual void subInit(void); //To be overridden
	void setup(const float time, const GLint * size, const GLfloat * proj, const GLfloat * mv, const GLfloat * mvp, const GLfloat * norm);
	virtual void subSetup(void * arg1, void * arg2, void * arg3, void * arg4); //To be overridden
	void use(void);
	void lightSetup(lightInfo & l);
	void materialSetup(materialInfo & m);
	void texSetup(TEXTURE_TYPE type);
	void TakeDown(void); //TODO: Different protection? X Nah, we want to be able to call it from main.
	virtual void subTakeDown(void); //
	void reload(SHADER_TYPE t);
	std::stringstream GetShaderLog(GLuint shader_id);
	SHADER_TYPE type;

	static GLint light_index;
	static GLuint light_handle;

protected:
	void inval(void);
	virtual void subInval(void);
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

	GLint position_handle; // Light position
	GLint color_handle; // Light color modifier
	GLint amb_handle; // Light ambient component
	GLint diff_handle; // Light diffuse component
	GLint spec_handle; // Light specular component
	
	GLint ka_handle; // Material ambient component
	GLint kd_handle; // Material diffuse component
	GLint ks_handle; // Material specular component
	GLint shininess_handle; // Material specular exponent

	GLubyte * lightBuffer; // Space for lighting info.
	GLubyte * matBuffer; // Space for material info.

};

