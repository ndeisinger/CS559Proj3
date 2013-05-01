//Oh god what is this I don't even

#include "physicsInclude.h"
#include <sstream>
#include <string>
#include "glutInclude.h"
#include <math.h>
#include "DrawObject.h"
#include "World.h"
#include "Camera.h"
#include "Cube.h"
#include "Textures.h"

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

GLuint tex[NUM_TEXTS]; //Used for setting up texturing

World draw_world; //Where we actually draw/simulate everything
Player * game_player; //Our player in the world

int num_spheres; //Number of spheres in the world
float max_time; //Total time

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

void PassiveMotionFunc(int x, int y)
{
	if (is_paused) return;
	else
	{
		float ratio = (x - (float)window.width/2)/((float)window.width/2);
		game_player->rotate(90.0f * ratio);
		printf("ratio: %f\n", ratio);
	}
}


void DisplayFunc()
{
	if (is_paused) return;
	char stringbuf[80];
	sprintf_s(stringbuf, "Time elapsed: %f,\n targets left: %i\n", elapsed_time, num_spheres);
	printf("Time elapsed: %f,\n targets left: %i\n", elapsed_time, num_spheres);
	
	float current_time = float(glutGet(GLUT_ELAPSED_TIME));
	//printf("In drawFunc\n");
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE); //Not only saves us computation, it also makes sure we're winding correctly.  How nice!
	glClearColor(0.4f, 0.4f, 0.4f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	wireframe = false;
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
	glRasterPos2i(0, 0);
	glPushMatrix();
	glutBitmapString(GLUT_BITMAP_HELVETICA_18, (unsigned char *) stringbuf);
	glPopMatrix();
	glFlush();
}

void timerFunc(int value)
{
	if (window.handle!= -1)
	{
		glutTimerFunc(window.interval, timerFunc, value);
		if (!is_paused)
		{
			animFrame++;
			if (animFrame > 200) animFrame = 0;
			elapsed_time += window.interval;
			glutPostRedisplay();
		}
	}
}

void KeyboardFunc(unsigned char c, int x, int y)
{
	if (c == 'c')
	{
		draw_world.switchCam();
	}
	if (c == 'p')
	{
		//Need to pause/unpause
		if (is_paused)
		{
			is_paused = false;
			glutPassiveMotionFunc(PassiveMotionFunc);
		}
		else
		{
			is_paused = true;
			glutPassiveMotionFunc(NULL);
		}
	}
}

void initTextures()
{
	GLuint tid[NUM_TEXTS];
	for (int i = 0; i < NUM_TEXTS; i++)
	{
		if (texts[i] == NULL) { break; }
		ilGenImages(1, &tex[i]); // Set up texture handle.
		ilBindImage(tex[i]);
	
		//Below code is also taken from the DevIL documentation.
		//I'd love to know why I had to jump through these hoops,
		//But in any event the normal load function was failing.
		//My guess? Wrong DLL (non-Unicode v. unicode).
		ILubyte *Lump;
		ILuint Size;
		FILE *File;

		int err = fopen_s(&File, texts[i], "rb");
		if (err)
		{
			fprintf(stderr, "Error: Could not open texture %s", texts[i]);
			exit(-1);
		}
		fseek(File, 0, SEEK_END);
		Size = ftell(File);

		Lump = (ILubyte*)malloc(Size);
		fseek(File, 0, SEEK_SET);
		fread(Lump, 1, Size, File);
		fclose(File);

		if (!ilLoadL(IL_JPG, Lump, Size)) { getDevILErr(); exit(1); }
		free(Lump);

		glActiveTexture((GL_TEXTURE0 + i));
		glGenTextures(1, &tid[i]);
		glBindTexture(GL_TEXTURE_2D, tid[i]);
		int w = ilGetInteger(IL_IMAGE_WIDTH);
		int h = ilGetInteger(IL_IMAGE_HEIGHT);
		void * data = ilGetData();
		ilutGLBindTexImage();

		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	}
}

int main (int argc, char * argv[])
{

#ifdef _DEBUG
	_CrtSetDbgFlag ( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
#endif

	B2_NOT_USED(argc);
	B2_NOT_USED(argv);
	
	int rand_seed;

	if (argc <= 1)
	{
		num_spheres = 30;
		rand_seed = 0;
	}
	else if (argc == 2)
	{
		num_spheres = atoi(argv[1]);
		rand_seed = 0;
	}
	else if (argc == 3)
	{
		num_spheres = atoi(argv[1]);
		rand_seed = atoi(argv[2]);
	}
	else
	{
		fprintf(stderr, "Usage: 559Proj3 numspheres randseed\n");
		exit(1);
	}
	srand(rand_seed);
	max_time = (float)(30 + num_spheres * 2);
	
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

	initTextures();

	window.width = 800;
	window.height = 600;

	draw_world.init(num_spheres);
	game_player = draw_world.getPlayer();

	glutDisplayFunc(DisplayFunc);
	glutTimerFunc(window.interval, timerFunc, 0);
	glutKeyboardFunc(KeyboardFunc);
	glutPassiveMotionFunc(PassiveMotionFunc);
	glutMainLoop();

	wireframe = true;

	return 0;
}