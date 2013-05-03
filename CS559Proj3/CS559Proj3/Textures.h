#pragma once
enum TEXTURE_TYPE {DIRT, CONCRETE, SKY, FRAME_BUF, FIRE_NOISE, TEX_ERR};
static const int NUM_TEXTS = 3; //Number of textures we load from external sources
//"dirt.jpg", "concrete.jpg" from http://seamless-pixels.blogspot.com/
static const char * texts[NUM_TEXTS] = {"dirt.jpg", "concrete.jpg", "sky.jpg"};