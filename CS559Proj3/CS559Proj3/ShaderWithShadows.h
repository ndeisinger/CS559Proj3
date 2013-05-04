#pragma once
#include "shader.h"
typedef Shader super;
class ShaderWithShadows :
	public Shader
{
public:
	ShaderWithShadows(void);
	~ShaderWithShadows(void);
	void subSetup(void * arg1, void * arg2, void * arg3, void * arg4);
	void subInit(void); //To be overridden
	void subTakeDown(void);
protected:
	void subInval(void);
	GLuint shad_mat_handle;
};

