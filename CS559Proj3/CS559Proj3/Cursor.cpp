#include "Cursor.h"


Cursor::Cursor(void)
{
}


Cursor::~Cursor(void)
{
}

void Cursor::init(glm::vec3 pos)
{
	glutSetCursor(GLUT_CURSOR_FULL_CROSSHAIR);
	
	//Kept for potential future implementation of unique cursor as defined by texture
	//glutSetCursor(GLUT_CURSOR_NONE);//Mute the cursor so the texture works.
	//textureCursor.init(10.0f, 10.0f, 1.0f);
	//textureCursor.setPos(pos);
	//textureCursor.setTexture(DIRT);
}

void Cursor::TakeDown(void)
{
	textureCursor.TakeDown();
}

bool Cursor::draw(const glm::mat4 & proj, glm::mat4 mv, const glm::ivec2 & size, const float time, lightInfo * & l, materialInfo * & m)
{
	if (GLReturnedError("Jumbotron draw - on entry")) return false;
	textureCursor.draw(proj, mv, size, time, l, m);
	if (GLReturnedError("Jumbotron draw - on exit")) return false;
	return true;
}