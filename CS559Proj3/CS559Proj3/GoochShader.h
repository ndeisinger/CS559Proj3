//A subclass for a special kind of shader.
//The intention here is that we not provide any extra public functions;
//Instead, use the sub{X} functions to provide special functionality.

#pragma once
#include "shader.h"
typedef Shader super;
class GoochShader :
	public Shader
{
public:
	GoochShader(void);
	~GoochShader(void);
	void subSetup(void * arg1, void * arg2, void * arg3, void * arg4);
	void subInit(void); //To be overridden
	void subTakeDown(void);
protected:
	void GoochShader::subInval(void);
	GLuint warm_color_handle;
	GLuint cool_color_handle;
	GLuint diffuse_warm_handle;
	GLuint diffuse_cool_handle;
};

