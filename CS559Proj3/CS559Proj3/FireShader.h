#pragma once
#include "shader.h"
//typedef Shader super;
class FireShader :
	public Shader
{
public:
	FireShader(void);
	~FireShader(void);
	void subSetup(void * arg1, void * arg2, void * arg3, void * arg4);

	void subInit(void); //To be overridden
	void subTakeDown(void);
protected:
	void subInval(void);
	GLuint noiseHandle;
	GLuint activeHandle;
};

