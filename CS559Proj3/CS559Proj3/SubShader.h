//A subclass for a special kind of shader.
//The intention here is that we not provide any extra public functions;
//Instead, use the sub{X} functions to provide special functionality.

#pragma once
#include "shader.h"
typedef Shader super;
class SubShader :
	public Shader
{
public:
	SubShader(void);
	~SubShader(void);
	void subSetup(void * arg1, void * arg2, void * arg3, void * arg4);
	void subInit(void); //To be overridden
	void subTakeDown(void);
protected:
	void SubShader::subInval(void);
};

