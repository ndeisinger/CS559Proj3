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
};

