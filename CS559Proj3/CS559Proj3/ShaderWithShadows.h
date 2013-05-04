#pragma once
#include "shader.h"
//typedef Shader super;
class ShaderWithShadows :
	public Shader
{
public:
	ShaderWithShadows(void);
	~ShaderWithShadows(void);
	virtual void subSetup(void * arg1, void * arg2, void * arg3, void * arg4)
	{
		glUniformMatrix4fv(shad_mat_handle, 1, GL_FALSE, (GLfloat *) arg1);
		bool depth_pass = *((bool *)arg2);
		//Set up any extra uniforms/other data here
		GLuint main_index = glGetSubroutineIndex(this->program_id, GL_FRAGMENT_SHADER, "main");
		GLuint record_index = glGetSubroutineIndex(this->program_id, GL_FRAGMENT_SHADER, "recordDepth");

		if (depth_pass)
		{
			glUniformSubroutinesuiv(GL_FRAGMENT_SHADER, 1, &record_index);
		}
		else
		{
			glUniformSubroutinesuiv(GL_FRAGMENT_SHADER, 1, &main_index);
		}
		glUniform1i(this->shad_buf_handle, int(SHADOW_BUF));
	}

	void subInit(void); //To be overridden
	void subTakeDown(void);
protected:
	void subInval(void);
	GLuint shad_mat_handle;
	GLuint shad_buf_handle;
};

