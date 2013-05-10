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
#include <noise\noise.h>
#include <math.h>

class Window
{
public:
	Window()
	{
		this->height = 0;
		this->width = 0;
		this->handle = 0;
		this->interval = 1000/120;
	}
	~Window()
	{

	}
	GLint height;
	GLint width;
	GLfloat aspect;
	int handle;
	int interval;
	//vector<string> textbuf;
};


//#pragma comment(lib, "glew32.lib") //wat
enum RENDER_TARGET {RENDER_FULL, RENDER_FBO, RENDER_SFBO, RENDER_GOOCH};
enum RENDER_SHADER {TEX_SHADER, GOOCH_SHADER, FIRE_SHADER};

#define PI_D 3.14159265
#define PI_F 3.14159265f
static bool GLEW_IS_INIT = false;
static bool WON_GAME = false;
extern bool useShadows;
extern RENDER_TARGET render_target;
extern RENDER_SHADER render_shader;
extern Window window;

//For dynamic shadows
extern glm::mat4 light_matrix; //Light's POV, used in dynamic shadows
extern glm::mat4 bp_matrix; //Bias times light's projection matrix

inline double degToRad(double degree) { return (degree/180) * PI_D; }
inline float degToRad(float degree) { return (degree/180) * PI_F; }

inline double radToDeg(double rad) { return (rad * 180) / PI_D; }
inline float radToDeg(float rad) { return (rad * 180) / PI_F; }

static const glm::mat4 bias_matrix = glm::mat4(0.5f, 0.0f, 0.0f, 0.0f,
											   0.0f, 0.5f, 0.0f, 0.0f,
											   0.0f, 0.0f, 0.5f, 0.0f,
											   0.5f, 0.5f, 0.5f, 1.0f);


//The following two functions are taken from Perry Kivolowitz's code.


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

static const char * FramebufferCompletenessError(GLint error_code)
{
	switch (error_code)
	{
	case GL_FRAMEBUFFER_UNDEFINED:
		return "GL_FRAMEBUFFER_UNDEFINED";

	case GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT:
		return "GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT";

	case GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT:
		return "GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT";

	case GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER:
		return "GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER";

	case GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER:
		return "GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER";

	case GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE:
		return "GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE";

	case GL_FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS:
		return "GL_FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS";

	case GL_FRAMEBUFFER_COMPLETE:
		return "GL_FRAMEBUFFER_COMPLETE";

	case GL_FRAMEBUFFER_UNSUPPORTED:
		return "GL_FRAMEBUFFER_UNSUPPORTED";

	default:
		return "Unknown frame buffer error";
	}
}