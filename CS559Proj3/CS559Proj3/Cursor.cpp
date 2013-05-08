#include "Cursor.h"


Cursor::Cursor(void)
{
}


Cursor::~Cursor(void)
{
}

#define SCREEN_LENGTH 600.0f
#define SCREEN_HEIGHT 300.0f

void Cursor::init(glm::vec3 pos, bool flipped)
{
	glutSetCursor(GLUT_CURSOR_NONE);//Mute the cursor so the texture works.

	//if (!flipped)
	//{
	//	stand.init(20.0f, 100.0f, 20.0f);
	//	stand.setPos(pos);
	//	stand.setTexture(CONCRETE);

	//	screen.init(0.5f, SCREEN_HEIGHT, SCREEN_LENGTH);
	//	screen.setPos(glm::vec3(pos.x - 20.0f, pos.y + 80, pos.z - SCREEN_LENGTH/2));
	//	screen.setTexture(FRAME_BUF);
	//}
	//else
	//{
	//	stand.init(20.0f, 100.0f, 20.0f);
	//	stand.setPos(pos);
	//	stand.setTexture(CONCRETE);

	//	screen.init(-0.5f, SCREEN_HEIGHT, SCREEN_LENGTH);
	//	screen.setPos(glm::vec3(pos.x + 20.0f, pos.y + 80, pos.z - SCREEN_LENGTH/2));
	//	screen.setTexture(FRAME_BUF);
	//}
}

void Cursor::TakeDown(void)
{
	stand.TakeDown();
	screen.TakeDown();
}

bool Cursor::draw(const glm::mat4 & proj, glm::mat4 mv, const glm::ivec2 & size, const float time, lightInfo * & l, materialInfo * & m)
{
	if (GLReturnedError("Jumbotron draw - on entry")) return false;
	stand.draw(proj, mv, size, time, l, m);
	screen.draw(proj, mv, size, time, l, m);
	if (GLReturnedError("Jumbotron draw - on exit")) return false;
	return true;
}