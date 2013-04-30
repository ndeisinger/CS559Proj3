//Because I really don't feel like putting all of these in every file.

#pragma once
#include <vector>
#include <gl/glew.h>
#include <gl/freeglut.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <IL\il.h>
#include <IL\ilu.h>
#include <IL\ilut.h>
#include <IL\ilut_config.h>
#include <math.h>


//#pragma comment(lib, "glew32.lib") //wat

#define PI_D 3.14159265
#define PI_F 3.14159265f
static bool GLEW_IS_INIT = false;

inline double degToRad(double degree) { return (degree/180) * PI_D; }
inline float degToRad(float degree) { return (degree/180) * PI_F; }

inline double radToDeg(double rad) { return (rad * 180) / PI_D; }
inline float radToDeg(float rad) { return (rad * 180) / PI_F; }

static bool GLReturnedError(char * s) 
{
	if (!GLEW_IS_INIT) return false;
	GLenum GLerr;
	bool hitErr = false;

	while ((GLerr = glGetError()) && GLerr != GL_NO_ERROR)
	{
		fprintf(stderr, "%s %s\n", s, gluErrorString(GLerr));
		hitErr = true;
	}

	return hitErr;
}
