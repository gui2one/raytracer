#include "base_handle.h"


BaseHandle::BaseHandle()
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
	geo_data = EditorGizmoUtils::makeCone(0.1, 2.0, 12, 2);
	printf("geo_data num vertices : %d\n" , geo_data.vertices.size());
	printf("geo_data num indices : %d\n" , geo_data.indices.size());

	if(m_vbo == 0){
		
		GLCall(glGenBuffers(1, &m_vbo));
		
	}else{
		GLCall(glDeleteBuffers(1, &m_vbo));
		GLCall(glGenBuffers(1, &m_vbo));
	}
	
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_vbo));
	GLCall(glBufferData(GL_ARRAY_BUFFER, sizeof(float)* geo_data.vertices.size(), geo_data.vertices.data(), GL_DYNAMIC_DRAW));
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
	
	GLCall(glEnableVertexAttribArray(0));
	GLCall(glDrawElements(GL_TRIANGLES, geo_data.indices.size(), GL_UNSIGNED_INT, nullptr));
	
	GLCall(glDisableVertexAttribArray(0));
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));		
}
