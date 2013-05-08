#pragma once
#include "MaterialInfo.h"
enum TEXTURE_TYPE {DIRT, CONCRETE, SKY, NIGHT_SKY, FRAME_BUF, SHADOW_BUF, FIRE_NOISE, TEX_ERR};
static const int NUM_TEXTS = 4; //Number of textures we load from external sources
//"dirt.jpg", "concrete.jpg" from http://seamless-pixels.blogspot.com/
//"nightsky.jpg" from http://loadpaper.com
//"sky.jpg" from http:://texturez.com
static const char * texts[NUM_TEXTS] = {"dirt.jpg", "concrete.jpg", "sky.jpg", "nightsky.jpg"};

struct skyboxInfo
{
	lightInfo l;
	TEXTURE_TYPE tex;
};