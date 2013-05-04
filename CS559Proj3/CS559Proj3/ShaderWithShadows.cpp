#include "ShaderWithShadows.h"


ShaderWithShadows::ShaderWithShadows(void)
{
	subInval();
}

ShaderWithShadows::~ShaderWithShadows(void)
{
}

void ShaderWithShadows::subInval(void)
{
	//Invalidate any special data here
	shad_mat_handle = BAD_GL_VALUE;
	Shader::inval();
}

void ShaderWithShadows::subTakeDown(void)
{
	//Do any special cleanup here
	subInval();
	Shader::TakeDown();
}

void ShaderWithShadows::subInit(void)
{
	//Do any special initialization code here
	this->shad_mat_handle = glGetUniformLocation(this->program_id, "shadow_matrix");
	this->shad_buf_handle = glGetUniformLocation(this->program_id, "shadow_map");
}

//ARG1 = Shadow matrix (GLfloat *)
//ARG2 = Are we collecting depth? (bool *)
//ARG3 = N/A
//ARG4 = N/A
void ShaderWithShadows::subSetup(void * arg1, void * arg2, void * arg3, void * arg4)
{
	glUniformMatrix4fv(shad_mat_handle, 1, GL_FALSE, (GLfloat *) arg1);
	glUniform1i(this->shad_buf_handle, int(SHADOW_BUF));
	bool depth_pass = *((bool *)arg2);
	//Set up any extra uniforms/other data here
	GLuint main_index = glGetSubroutineIndex(this->program_id, GL_FRAGMENT_SHADER, "shade");
	GLuint record_index = glGetSubroutineIndex(this->program_id, GL_FRAGMENT_SHADER, "recordDepth");

	if (depth_pass)
	{
		glUniformSubroutinesuiv(GL_FRAGMENT_SHADER, 1, &record_index);
	}
	else
	{
		glUniformSubroutinesuiv(GL_FRAGMENT_SHADER, 1, &main_index);
	}
	GLReturnedError("ShaderWithShadows - subSetup on exit\n");
}