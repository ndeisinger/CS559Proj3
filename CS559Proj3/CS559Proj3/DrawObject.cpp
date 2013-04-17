#include "DrawObject.h"
//General-purpose class for any objects/geometry we will need to draw.
//Includes things like the vectors of vertices, etc.

#define BAD_GLU_VAL GLuint(-1)

DrawObject::DrawObject(void)
{
	initialize();
}

DrawObject::~DrawObject(void)
{
	// Deletion could occur after leaving our GL context, so don't call TakeDown.
}

void DrawObject::UseTexture()
{
	this->useTex = true;
}

void DrawObject::switchShader(SHADER_TYPE t)
{
	if (customShader) shader.reload(t);
	else DrawObject::common_shader.reload(t);
}

void DrawObject::setPos(glm::vec3 pos)
{
	this->position = pos;
}

void DrawObject::TakeDown(void)
{
	if (GLReturnedError("DrawObject TakeDown - on entry\n")) return;
	shader.TakeDown();
	this->atts_pcn.clear();
	this->atts_pcnt.clear();
	this->vertex_indices.clear();

	if(this->normal_arr_handle != BAD_GLU_VAL)
	{
		glDeleteVertexArrays(1, &this->normal_arr_handle);
	}
	if(this->normal_coor_handle != BAD_GLU_VAL)
	{
		glDeleteVertexArrays(1, &this->normal_coor_handle);
	}
	if(this->vertex_arr_handle != BAD_GLU_VAL)
	{
		glDeleteVertexArrays(1, &this->vertex_arr_handle);
	}
	if(this->vertex_coor_handle != BAD_GLU_VAL)
	{
		glDeleteVertexArrays(1, &this->vertex_coor_handle);
	}
	initialize();
	if (GLReturnedError("DrawObject TakeDown - on exit\n")) return;
}

bool DrawObject::initialize(void)
{
	if (GLReturnedError("DrawObject initialize - on entry\n")) return false;
	this->normal_arr_handle = this->normal_coor_handle = BAD_GLU_VAL;
	this->vertex_arr_handle = this->vertex_coor_handle = BAD_GLU_VAL;
	this->draw_type = GL_TRIANGLES;
	this->useTex = false;
	this->norms_init = false;
	this->customShader = false;
	color = glm::vec3(0.0f, 0.0f, 0.0f);
	position = glm::vec3(0.0f, 0.0f, 0.0f);
	if (GLReturnedError("DrawObject initialize - on exit\n")) return false;
	return true;
}

bool DrawObject::bindArray(GLuint * arr_handle, GLuint * coor_handle, GLsizeiptr size, const GLvoid * data)
{
	if (GLReturnedError("DrawObject bindArray - on entry\n")) return false;
	glGenVertexArrays(1, arr_handle);
	glBindVertexArray(*arr_handle);
	glGenBuffers(1, coor_handle);
	glBindBuffer(GL_ARRAY_BUFFER, *coor_handle);
	glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW); //TODO: Why GL_STATIC_DRAW? X
	if (GLReturnedError("DrawObject bindArray - on exit\n")) return false;
	return true;
}

using namespace glm;
bool DrawObject::s_draw(const glm::mat4 & proj, glm::mat4 & mv, const glm::ivec2 & size, const float & time, lightInfo * & l, materialInfo * & m)
{
#ifdef _DEBUG
	//printf("Drawing an object!\n");
#endif
	glEnable(GL_DEPTH_TEST);
	mat4 trans_mv = translate(mv, position);
	mat4 mvp = proj * trans_mv;
	mat3 nm = inverse(transpose(mat3(trans_mv))); //TODO: dat math X
	if (customShader)
	{
		this->shader.use();
		this->shader.setup(time, value_ptr(size), value_ptr(proj), value_ptr(trans_mv), value_ptr(mvp), value_ptr(nm));
		if (l != NULL)
		{
			shader.lightSetup(*l); //TODO: Is this safe? X
		}
		if (m != NULL)
		{
			shader.materialSetup(*m);
		}
	}
	else
	{
		common_shader.use();
		common_shader.setup(time, value_ptr(size), value_ptr(proj), value_ptr(trans_mv), value_ptr(mvp), value_ptr(nm));
		if (l != NULL)
		{
			common_shader.lightSetup(*l); //TODO: Is this safe? X
		}
		if (m != NULL)
		{
			common_shader.materialSetup(*m);
		}
	}
	glBindVertexArray(this->vertex_arr_handle);
	glDrawElements(this->draw_type, this->vertex_indices.size(), GL_UNSIGNED_INT, &this->vertex_indices[0]);
	glBindVertexArray(0);
	glUseProgram(0);

	//The following two code blocks let us draw norms/axes, but only if we're not ourself an Axes object.

	if (DrawObject::draw_norms && (this != DrawObject::a))
	{
		if(!norms_init)
		{
			norms_init = initNorms();
		}
		if (!norms_init)
		{
			return false;
		}
		norm_shader.use();
		norm_shader.setup(time, value_ptr(size), value_ptr(proj), value_ptr(trans_mv), value_ptr(mvp), value_ptr(nm)); //TODO: I get the feeling this is going to get screwy since it's static. X: Nope.
		glBindVertexArray(this->normal_arr_handle);
		glDrawElements(GL_LINES, this->norm_indices.size(), GL_UNSIGNED_INT, &this->norm_indices[0]);
		glBindVertexArray(0);
		glUseProgram(0);
	}
	
	if (DrawObject::draw_axes && (this != DrawObject::a))
	{
		if(DrawObject::axes_init == false) return false;
		DrawObject::a->s_draw(proj, trans_mv, size, time, l, m); //TODO: Will this work? X: Yup.
	}

	return true;
}
/*
bool DrawObject::GLReturnedError(char * s)
{
	GLenum GLerr;
	bool hitErr = false;

	while ((GLerr = glGetError()) && GLerr != GL_NO_ERROR)
	{
		fprintf(stderr, "%s %s\n", s, gluErrorString(GLerr));
		hitErr = true;
	}

	return hitErr;
}*/

//ASSUMPTION: This is only called after init has been called.
bool DrawObject::initNorms()
{
	if (GLReturnedError("DrawObject initNorms - on entry\n")) return false;
	assert(this->vertex_arr_handle != -1);
	if (useTex)
	{
		//TODO: Handle textured case
		//Update: Unnecessary, as we curently only texture the ground.
	}
	else
	{
		for (int i = 0; i < (int) this->atts_pcn.size(); i++)
		{
			VertexAttPCN temp = this->atts_pcn.at(i);
			this->norm_vertices.push_back(VertexAttP(temp.pos));
			this->norm_vertices.push_back(VertexAttP(temp.pos + temp.norm));
			this->norm_indices.push_back(this->norm_vertices.size() - 2);
			this->norm_indices.push_back(this->norm_vertices.size() - 1);
		}
		if (!this->bindArray(&this->normal_arr_handle, &this->normal_coor_handle, this->norm_vertices.size() * sizeof(VertexAttPCN), &this->norm_vertices[0])) return false;
	}
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexAttP), 0); //position
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0); 
	if (GLReturnedError("DrawObject initNorms - on exit\n")) return false;
	return true;
}

void DrawObject::drawNorms()
{
	this->draw_norms = true;
}

struct recolor_help
{
	glm::vec3 * color;
	void operator() (VertexAttPCN & i)
	{
		i.color = *color; //TODO: is this a proper copy? X.  Yep.
	}
} r;

void DrawObject::recolor(glm::vec3 color)
{
	this->color = color;
	r.color = &this->color;
	for_each(this->atts_pcn.begin(), this->atts_pcn.end(), r);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(VertexAttPCN), (GLvoid *) (0 + sizeof(glm::vec3) * 1));
	glEnableVertexAttribArray(1);
	GLReturnedError("Recolor - on exit\n");
}