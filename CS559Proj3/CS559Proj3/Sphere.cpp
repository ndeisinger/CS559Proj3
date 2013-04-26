/*	
	Chelsey Denton

	Code based upon code provided by Perry Kivolowitz, some code it directly copied
*/

#include <iostream>
#include "Sphere.h"

using namespace std;
using namespace glm;

Sphere::Sphere()
{
	this->draw_type = GL_TRIANGLES;
	super();
	vec4 lighter_color(MakeColor(255, 69, 0, 1.0f));
	vec4 darker_color = vec4(vec3(lighter_color) * 2.0f / 3.0f, 1.0f);
	this->colors[0] = darker_color;
	this->colors[1] = lighter_color;
	color = vec3(colors[0]);
	solidColor = true;
}

Sphere::~Sphere()
{
	//Should call TakeDown, not this!
}

inline int ColorIndex(int i, int slices)
{
	return (i / (slices / 4)) % 2;
}

inline int PreviousSlice(int i, int slices)
{
	return (i == 0) ? slices - 1 : i - 1;
}

void Sphere::BuildNormalVisualizationGeometry()
{
		//We do normals in DrawObject
	/*
	const float normal_scalar = 0.125f;
	for (int j = 1; j <= 3; ++j)
	{
		this->norm_vertices.push_back(VertexAttP(this->atts_pcn[this->atts_pcn.size() - j].position));
		this->norm_vertices.push_back(VertexAttP(this->atts_pcn[this->atts_pcn.size() - j].position + this->atts_pcn[this->atts_pcn.size() - j].normal * normal_scalar));
		this->norm_indices.push_back(this->norm_vertices.size() - 2);
		this->norm_indices.push_back(this->norm_vertices.size() - 1);
	}
	*/
}

bool Sphere::initialize(float radius, int slices, int stacks)
{
	if (GLReturnedError("Sphere::Initialize - on entry"))
		return false;

	if (!super::initialize())
		return false;

	if (slices < 0)
		slices = 1;

	slices *= 4;
	own_radius = radius;

	float theta = 360.0f/slices;
	float delta = 180.0f/stacks;
	const vec3 y_axis(0.0f, 1.0f, 0.0f);
	const vec3 z_axis(0.0f, 0.0f, 1.0f);
	const vec4 r_vec(radius, 0.0f, 0.0f, 1.0f);
	vec3 n2;
	vec4 n;
	mat4 tmpM2;
	
	mat4 m, m_nxt, m2, m2_nxt;
	for( int j=0; j<slices; j++)
	{
		m_nxt = rotate(m, theta, y_axis);
		m2 = mat4();	
		m2_nxt = rotate(mat4(), -90.0f, z_axis);
		for(int i=0; i<stacks; i++)
		{
			m2 = m2_nxt;
			m2_nxt = rotate(m2, delta, z_axis);

			VertexAttPCN cur_vertex_top, cur_vertex_bottom , nxt_vertex_top,nxt_vertex_bottom;
			cur_vertex_top.pos = vec3((m*m2)*r_vec);	
			cur_vertex_top.norm = normalize(cur_vertex_top.pos);
			nxt_vertex_top.pos = vec3((m_nxt*m2)*r_vec);	
			nxt_vertex_top.norm = normalize(nxt_vertex_top.pos);

			cur_vertex_bottom.pos = vec3((m*m2_nxt)*r_vec);	
			cur_vertex_bottom.norm = normalize(cur_vertex_bottom.pos);
			nxt_vertex_bottom.pos = vec3((m_nxt*m2_nxt)*r_vec);	
			nxt_vertex_bottom.norm = normalize(nxt_vertex_bottom.pos);


			if(solidColor)
			{
				cur_vertex_bottom.color = color;
				cur_vertex_top.color = color;
				nxt_vertex_bottom.color = color;
				nxt_vertex_top.color = color;
			}
			else
			{
				cur_vertex_bottom.color = vec3(this->colors[ColorIndex(j, slices)]);
				cur_vertex_top.color = vec3(this->colors[ColorIndex(j, slices)]);
				nxt_vertex_bottom.color = vec3(this->colors[ColorIndex(j, slices)]);
				nxt_vertex_top.color = vec3(this->colors[ColorIndex(j, slices)]);
			}

			this->atts_pcn.push_back(cur_vertex_top);
			this->atts_pcn.push_back(cur_vertex_bottom);
			this->atts_pcn.push_back(nxt_vertex_bottom);
	
			this->vertex_indices.push_back(this->atts_pcn.size() - 3);
			this->vertex_indices.push_back(this->atts_pcn.size() - 1);
			this->vertex_indices.push_back(this->atts_pcn.size() - 2);

			this->BuildNormalVisualizationGeometry();

			this->atts_pcn.push_back(cur_vertex_top);
			this->atts_pcn.push_back(nxt_vertex_bottom);
			this->atts_pcn.push_back(nxt_vertex_top);
	
			this->vertex_indices.push_back(this->atts_pcn.size() - 3);
			this->vertex_indices.push_back(this->atts_pcn.size() - 1);
			this->vertex_indices.push_back(this->atts_pcn.size() - 2);

			this->BuildNormalVisualizationGeometry();
		}
		m = m_nxt;
	}



	if (!this->bindArray(&this->vertex_arr_handle, &this->vertex_coor_handle, this->atts_pcn.size() * sizeof(VertexAttPCN), &this->atts_pcn[0]))
		return false;

	/*	The VertexAttributesPCN class stores vertex attributes: position, color and normal in that order.

		Vertex attributes are stored in an interleaved manner aiding speed of vertex processing.
	*/

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexAttPCN), (GLvoid *) 0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(VertexAttPCN), (GLvoid *) (sizeof(vec3) * 2));	// Note offset - legacy of older code
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(VertexAttPCN), (GLvoid *) (sizeof(vec3) * 1));	// Same
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	/*
	We do normals in DrawObject

	if (this->norm_vertices.size() > 0)
	{
		if (!this->PostGLInitialize(&this->normal_array_handle, &this->normal_coordinate_handle, this->norm_vertices.size() * sizeof(VertexAttributesP), &this->norm_vertices[0]))
			return false;

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexAttributesP), (GLvoid *) 0);
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	}*/
	
	if (GLReturnedError("Sphere::Initialize - on exit"))
		return false;

	return true;
}

/* TakeDown is also handled by DrawObject
void Sphere::TakeDown()
{
	this->atts_pcn.clear();
	this->shader.TakeDown();
	this->solid_color.TakeDown();
	super::TakeDown();
}*/

/*
void Sphere::Draw(const ivec2 & size)
{
	assert(false);
}*/

/*	A note about drawing the normals.

	If you scale this object non-uniformly, drawing the normals will
	not be correct. This is because the normals are being stored for
	visualization as geometry. As such, scaling will not be corrected
	by the normal matrix.
*/

/*	A note about the index arrays.
 
	In this example, the index arrays are unsigned ints. If you know
	for certain that the number of vertices will be small enough, you
	can change the index array type to shorts or bytes. This will have
	the two fold benefit of using less storage and transferring fewer
	bytes.
*/

bool Sphere::draw(const glm::mat4 & proj, glm::mat4 mv, const glm::ivec2 & size, const float time, lightInfo * & l, materialInfo * & m)
{
	if (GLReturnedError("Sphere draw - on entry\n")) return false;
	super::s_draw(proj, mv, size, time, l, m);
#ifdef _DEBUG
	//Axes a;
	//a.init();
	//lightInfo * x = NULL;
	//a.draw(proj, glm::scale(mv, vec3(2.0, 2.0, 2.0)), size, time, x);
#endif

	if (GLReturnedError("Sphere - draw exit\n")) return false;
	return true;
}

void Sphere::updatePos(void)
{
	b2Vec2 pos = circleBody->GetPosition();
	this->position = glm::vec3(pos.x, 0.0, pos.y);
	//printf("x: %f, y: %f, q: %f\n", circleBody->GetPosition().x, circleBody->GetPosition().y, circleBody->GetAngle());
	//printf("sphere pos: %f, %f, %f\n", this->position.x, this->position.y, this->position.z);
	//printf("body pos: %f, %f\n", pos.x, pos.y);
}

//NOTE: WE NEED TO CONVERT BOX2D UNITS TO FEET AND VICE-VERSA
void Sphere::initPhysics(b2World * world)
{
	circleDef.type = b2_dynamicBody;
	circleDef.position.Set(this->position.x, this->position.z);
	circleDef.bullet = true;
	circleBody = world->CreateBody(&circleDef);
	circleShape.m_p.SetZero();
	circleShape.m_radius = own_radius;
	circleFixtureDef.shape = &circleShape;
	circleFixtureDef.density = 1.0f;
	circleFixtureDef.friction = 0.1001f;

	circleBody->CreateFixture(&circleFixtureDef);
}

//void Sphere::Draw(const mat4 & projection, mat4 modelview, const ivec2 & size)
//{
//	if (this->GLReturnedError("Sphere::Draw - on entry"))
//		return;
//	glEnable(GL_CULL_FACE); 
////	glDisable(GL_CULL_FACE);
//	glEnable(GL_DEPTH_TEST);
//
//	mat4 mvp = projection * modelview;
//	mat3 nm = inverse(transpose(mat3(modelview)));
//
//	shader.Use();
//	shader.CommonSetup(0.0f, value_ptr(size), value_ptr(projection), value_ptr(modelview), value_ptr(mvp), value_ptr(nm), value_ptr(worldModelView));
//	glBindVertexArray(this->vertex_array_handle);
//	glDrawElements(GL_TRIANGLES , this->vertex_indices.size(), GL_UNSIGNED_INT , &this->vertex_indices[0]);
//	glBindVertexArray(0);
//	glUseProgram(0);
//
//	if (this->draw_normals)
//	{
//		this->solid_color.Use();
//		this->solid_color.CommonSetup(0.0f, value_ptr(size), value_ptr(projection), value_ptr(modelview), value_ptr(mvp), value_ptr(nm), value_ptr(worldModelView));
//		glBindVertexArray(this->normal_array_handle);
//		glDrawElements(GL_LINES , this->norm_indices.size(), GL_UNSIGNED_INT , &this->norm_indices[0]);
//		glBindVertexArray(0);
//		glUseProgram(0);
//	}
//	
//	glDisable(GL_CULL_FACE);
//
//	if (this->GLReturnedError("Sphere::Draw - on exit"))
//		return;
//}
