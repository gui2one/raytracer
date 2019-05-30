#include "entity3d.h"

Entity3D::Entity3D()
{
	
}

void Entity3D::draw()
{
	printf("--- Drawing Entity3D  -----\n");
}

Entity3D::~Entity3D()
{
	printf("--- Delete Entity3D\n");
}

MeshObject::MeshObject() : Entity3D()
{
	
}

void MeshObject::buildVBO()
{
	
	OGL_geo_data.vertices.clear();
	OGL_geo_data.indices.clear();
	

	Mesh tri_copy = mesh;
	tri_copy.triangulate();
	tri_copy.computeNormals();
	//vertices
	for (int i = 0; i < tri_copy.points.size(); i++)
	{	
		OGL_geo_data.vertices.insert(
			OGL_geo_data.vertices.end(), {
				tri_copy.points[i].position.x, tri_copy.points[i].position.y, tri_copy.points[i].position.z,
				tri_copy.points[i].normal.x, tri_copy.points[i].normal.y, tri_copy.points[i].normal.z,
				1.0, 1.0
			}
		);			
	}
	
	// indices
	for (int i = 0; i < tri_copy.faces.size(); i++)
	{
		if( tri_copy.faces[i].getNumVertices() == 3)
		{
			OGL_geo_data.indices.insert(
				OGL_geo_data.indices.end(), {
					tri_copy.faces[i].getVertex(0).point_id,
					tri_copy.faces[i].getVertex(2).point_id,
					tri_copy.faces[i].getVertex(1).point_id
				}
			
			);
		}
	}
	
		
	
	
	if(m_vbo == 0){
		
		GLCall(glGenBuffers(1, &m_vbo));
		printf("m_vbo from mesh object --> %d\n", m_vbo);
	}else{
		GLCall(glDeleteBuffers(1, &m_vbo));
		GLCall(glGenBuffers(1, &m_vbo));
	}
	
	
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_vbo));
	GLCall(glBufferData(GL_ARRAY_BUFFER, sizeof(float)* OGL_geo_data.vertices.size(), OGL_geo_data.vertices.data(), GL_DYNAMIC_DRAW));
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));	
	
	if(m_ibo == 0)
	{
		GLCall(glGenBuffers(1, &m_ibo));
	}else{		
		GLCall(glDeleteBuffers(1, &m_ibo));
		GLCall(glGenBuffers(1, &m_ibo));
	}
	
	GLCall(glGenBuffers(1, &m_ibo));
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo));
	GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int)* OGL_geo_data.indices.size(), OGL_geo_data.indices.data(), GL_DYNAMIC_DRAW));
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));		
	
	
	
	
}

void MeshObject::draw()
{
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_vbo));
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo));
	GLCall(glVertexAttribPointer(0,3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, 0));
	GLCall(glVertexAttribPointer(1,3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (void*)(sizeof(float) * 3)));
	//~ GLCall(glVertexAttribPointer(2,2, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (void*)(sizeof(float) * 6)));
	
	
	GLCall(glEnableVertexAttribArray(0));
	GLCall(glEnableVertexAttribArray(1));
	//~ GLCall(glEnableVertexAttribArray(2));
	
	//~ GLCall(glDrawArrays(GL_TRIANGLES, 0, mesh.points.size()));
	GLCall(glDrawElements(GL_TRIANGLES, OGL_geo_data.indices.size() , GL_UNSIGNED_INT, nullptr ));

	GLCall(glDisableVertexAttribArray(0));
	GLCall(glDisableVertexAttribArray(1));
	//~ GLCall(glDisableVertexAttribArray(2));
	
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
	//~ printf("--- Drawing MeshObject  -----\n");
}

MeshObject::~MeshObject()
{
	printf("--- Delete MeshObject\n");
}
