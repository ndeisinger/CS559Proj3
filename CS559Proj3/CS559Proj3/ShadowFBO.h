#pragma once
#include "framebufferobject.h"
#define SHADOW_BUFFER_RES 1024
class ShadowFBO :
	public FrameBufferObject
{
public:
	ShadowFBO(void);
	~ShadowFBO(void);
	void initialize(void);
};

