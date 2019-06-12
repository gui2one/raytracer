#include "base_handle.h"


BaseHandle::BaseHandle() : position(glm::vec3(0.0,0.0,0.0)), rotation(glm::vec3(0.0,0.0,0.0)),scale(glm::vec3(1.0,1.0,1.0))
{
	
}

BaseHandle::~BaseHandle()
{
	
}


//// translate Handle

TranslateHandle::TranslateHandle() : BaseHandle()
{
	buildDisplayData();
}


TranslateHandle::~TranslateHandle()
{
	
}

void TranslateHandle::buildDisplayData()
{
	geo_data = EditorGizmoUtils::makeCone2(0.02,0.02, 0.9, 10, 2);
	
	OGL_DATA_2 pointy_end = EditorGizmoUtils::makeCone2(0.04, 0.0, 0.1, 10, 2);
	EditorGizmoUtils::translate2(pointy_end, glm::vec3(0.0,0.0,0.9));
	
	geo_data = EditorGizmoUtils::merge2(geo_data, pointy_end);
		
	geo_data.setColor(1.0, 0.0, 0.0);
	//~ printf("geo_data num positions : %d\n" , geo_data.positions.size());
	//~ printf("geo_data num indices : %d\n" , geo_data.indices.size());

	if(m_vbo == 0){
		
		GLCall(glGenBuffers(1, &m_vbo));
		
	}else{
		GLCall(glDeleteBuffers(1, &m_vbo));
		GLCall(glGenBuffers(1, &m_vbo));
	}
	
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_vbo));
	GLCall(glBufferData(GL_ARRAY_BUFFER, sizeof(float)* (geo_data.positions.size() + geo_data.colors.size()), 0, GL_DYNAMIC_DRAW));
	GLCall(glBufferSubData(
			GL_ARRAY_BUFFER, 
			0, // offset
			sizeof(float)* geo_data.positions.size(), 
			geo_data.positions.data()
	));
	GLCall(glBufferSubData(
			GL_ARRAY_BUFFER, 
			sizeof(float)* geo_data.positions.size(), // offset
			sizeof(float)* geo_data.colors.size(), 
			geo_data.colors.data()
	));	
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));	
	
	if(m_ibo == 0)
	{
		GLCall(glGenBuffers(1, &m_ibo));
	}else{		
		GLCall(glDeleteBuffers(1, &m_ibo));
		GLCall(glGenBuffers(1, &m_ibo));
	}

	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo));
	GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int)* geo_data.indices.size(), geo_data.indices.data(), GL_DYNAMIC_DRAW));
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));			
}

void TranslateHandle::draw()
{
	//~ printf("drawing translateHandle\n");
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_vbo));
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo));
	GLCall(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, 0));
	GLCall(glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, (const void*)(sizeof(float)*geo_data.positions.size())));
	
	GLCall(glEnableVertexAttribArray(0));
	GLCall(glEnableVertexAttribArray(1));
	
	GLCall(glDrawElements(GL_TRIANGLES, geo_data.indices.size(), GL_UNSIGNED_INT, nullptr));
	
	GLCall(glDisableVertexAttribArray(0));
	GLCall(glDisableVertexAttribArray(1));
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));		
}
