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
	super::inval();
}

void ShaderWithShadows::subTakeDown(void)
{
	//Do any special cleanup here
	subInval();
	super::TakeDown();
}

void ShaderWithShadows::subInit(void)
{
	//Do any special initialization code here
	this->shad_mat_handle = glGetUniformLocation(this->program_id, "shadow_map");

	//Set up subroutine
}

//ARG1 = Shadow matrix (GLfloat *)
//ARG2 = Are we collecting depth? (bool *)
//ARG3 = N/A
//ARG4 = N/A
void ShaderWithShadows::subSetup(void * arg1, void * arg2, void * arg3, void * arg4)
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
}
