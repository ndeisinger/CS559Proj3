#include "ShaderWithShadows.h"


ShaderWithShadows::ShaderWithShadows(void)
{
	this->inval();
}

ShaderWithShadows::~ShaderWithShadows(void)
{
}

void super::inval(void)
{
	//Invalidate any special data here
	super::inval();
}

void super::TakeDown(void)
{
	//Do any special cleanup here
	super::TakeDown();
}

void super::subInit(void)
{
	//Do any special initialization code here
}

//ARG1 =
//ARG2 =
//ARG3 =
//ARG4 =
void super::subSetup(void * arg1, void * arg2, void * arg3, void * arg4)
{
	//Set up any extra uniforms/other data here
}