//Oh god what is this I don't even

#include <Box2D/Box2D.h>
#include "glutInclude.h"
#include <math.h>
#include "DrawObject.h"
#include "World.h"
#include "Camera.h"
#include "Cube.h"

#ifdef _DEBUG
	#define CRTDBG_MAP_ALLOC //Used to help find leaks.
	#include <stdlib.h>
	#include <crtdbg.h>
#endif

bool wireframe = false; // Determine if we want wireframe.
float fov = 50.0f; // Our FOV.
//float radius = 5.0f; // Distance away from our eye.
int animFrame = 0; // Used to make it rain.
//bool doRain = FALSE; // Are we making it rain?
bool drawGrid = FALSE; // Are we showing the grid?

Shader DrawObject::norm_shader; // Shared shader for normals.
DrawObject * DrawObject::a; // Shared object used to draw axes.

bool DrawObject::draw_norms; // Boolean to declare if we want to draw normals.
bool DrawObject::draw_axes; // Boolean to declare if we want to draw local axes.
bool DrawObject::axes_init; // Boolean to determine if the shared Axes object is initialized.
Shader DrawObject::common_shader;

int Shader::bind_point = 2; // Bindings for our lighting/materials.

int mouseX = -1; //Lets us smoothly adjust our view.
int mouseY = -1;

GLint Shader::light_index = GLuint(-1);
GLuint Shader::light_handle = GLuint(-1); // Used in our lighting calcs

GLuint tex; //Used for texturing

World draw_world;

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
} window; //TODO: Make this class a little cleaner for possibility of multiple windows.


// This function taken from DevIL documentation.
// http://openil.sourceforge.net/tuts/tut_3/index.htm
void getDevILErr()
{
	ILenum Error;
	while ((Error = ilGetError()) != IL_NO_ERROR) {
		printf("%d: %s/n", Error, iluErrorString(Error));
	} 
}

void DisplayFunc()
{
	float current_time = float(glutGet(GLUT_ELAPSED_TIME));
	//printf("In drawFunc\n");
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE); //Not only saves us computation, it also makes sure we're winding correctly.  How nice!
	glClearColor(0.4f, 0.4f, 0.4f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glViewport(0, 0, window.width, window.height);
	if (wireframe) 
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}
	else
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}
	draw_world.draw();
	glFlush();
}

void timerFunc(int value)
{
	if (window.handle!= -1)
	{
		animFrame++;
		if (animFrame > 200) animFrame = 0;
		glutTimerFunc(window.interval, timerFunc, value);
		glutPostRedisplay();
	}
}


int main (int argc, char * argv[])
{

#ifdef _DEBUG
	_CrtSetDbgFlag ( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
#endif

	B2_NOT_USED(argc);
	B2_NOT_USED(argv);
	
	glutInit(&argc, argv);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(800, 600);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH);

	window.width = 800;
	window.height = 600;
	window.aspect = (float) 800/ (float)600;
	window.handle = glutCreateWindow("A Treatise on why These Projects Need to be Started Sooner, or: Stools 102");
//	window.cam.loc = glm::vec3(-4.0, 1.0, 0.0);
	/*
	glutDisplayFunc(drawFunc);
	glutSpecialFunc(specialFunc);
	glutKeyboardFunc(keyboardFunc);
	glutReshapeFunc(reshapeFunc);
	glutCloseFunc(closeFunc);
	glutTimerFunc(window.interval, timerFunc, 0);
	glutSpecialFunc(specialFunc);
	glutMouseFunc(mouseFunc);
	glutPassiveMotionFunc(PassiveMotionFunc);*/

	GLenum err = glewInit();

	if ( err != GLEW_OK )
	{
		fprintf(stderr, "Failed to initialize GLEW: %s\n", glewGetErrorString(err));
		exit(1);
	}

	GLEW_IS_INIT = true;

	ilInit();
	iluInit();
	ilutRenderer(ILUT_OPENGL);

	ilGenImages(1, &tex); // Set up texture handle.
	ilBindImage(tex);
	
	//Below code is also taken from the DevIL documentation.
	//I'd love to know why I had to jump through these hoops,
	//But in any event the normal load function was failing.
	//My guess? Wrong DLL (non-Unicode v. unicode).
	ILubyte *Lump;
	ILuint Size;
	FILE *File;

	fopen_s(&File, "dirt.jpg", "rb");
	fseek(File, 0, SEEK_END);
	Size = ftell(File);

	Lump = (ILubyte*)malloc(Size);
	fseek(File, 0, SEEK_SET);
	fread(Lump, 1, Size, File);
	fclose(File);

	if (!ilLoadL(IL_JPG, Lump, Size)) { getDevILErr(); exit(1); }
	free(Lump);

	glActiveTexture(GL_TEXTURE0);
	GLuint tid;
	glGenTextures(1, &tid);
	glBindTexture(GL_TEXTURE_2D, tid);
	int w = ilGetInteger(IL_IMAGE_WIDTH);
	int h = ilGetInteger(IL_IMAGE_HEIGHT);
	void * data = ilGetData();
	ilutGLBindTexImage();

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	window.width = 800;
	window.height = 600;

	draw_world.init(40);

	glutDisplayFunc(DisplayFunc);
	glutTimerFunc(window.interval, timerFunc, 0);
	glutMainLoop();

	wireframe = true;

	return 0;
}