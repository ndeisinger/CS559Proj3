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
	//Set up subroutine
}

//ARG1 = Shadow matrix (GLfloat *)
//ARG2 = Are we collecting depth? (bool *)
//ARG3 = N/A
//ARG4 = N/A
