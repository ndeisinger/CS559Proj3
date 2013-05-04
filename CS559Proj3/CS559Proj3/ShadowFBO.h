#pragma once
#include "framebufferobject.h"
class ShadowFBO :
	public FrameBufferObject
{
public:
	ShadowFBO(void);
	~ShadowFBO(void);
	void initialize(void);
};

