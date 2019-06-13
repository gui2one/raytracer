#include "base_handle.h"


BaseHandle::BaseHandle() : 
			position(glm::vec3(0.0,0.0,0.0)), 
			rotation(glm::vec3(0.0,0.0,0.0)),
			scale(glm::vec3(1.0,1.0,1.0))
{
	
}

BaseHandle::~BaseHandle()
{
	
}

void BaseHandle::applyTransforms()
{
	glm::mat4 temp = glm::mat4(1.0f);
	
	

	//~ printf("entity pos --> %.3f %.3f %.3f\n", param_position->getValue().x, param_position->getValue().y, param_position->getValue().z);
	temp = glm::translate(temp, position);
	temp = glm::rotate(temp, glm::radians(rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
	temp = glm::rotate(temp, glm::radians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
	temp = glm::rotate(temp, glm::radians(rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
	
	temp = glm::scale(temp , scale);
	
	transforms = temp;	
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
	// make main tube
	geo_data = EditorGizmoUtils::makeCone(0.02,0.02, 0.9, 10, 2);
	
	// make arrow head
	OGL_DATA_2 pointy_end = EditorGizmoUtils::makeCone(0.04, 0.0, 0.1, 10, 2);
	EditorGizmoUtils::translate(pointy_end, glm::vec3(0.0,0.0,0.9));	
	geo_data = EditorGizmoUtils::merge(geo_data, pointy_end);		
	//~ EditorGizmoUtils::rotate(copy, glm::vec3(0.0, 0.0, 0.0))
	geo_data.setColor(0.0, 0.0, 1.0);
	// end Z_axis
	
	OGL_DATA_2 x_axis = geo_data;
	EditorGizmoUtils::rotate(x_axis, glm::vec3(0.0, 90.0, 0.0));
	x_axis.setColor(1.0, 0.0, 0.0);
	// end  X_AXIS
	geo_data = EditorGizmoUtils::merge(geo_data, x_axis);
	
	OGL_DATA_2 y_axis = x_axis;
	EditorGizmoUtils::rotate(y_axis, glm::vec3(0.0, 0.0, 90.0));
	y_axis.setColor(0.0, 1.0, 0.0);
	
	geo_data = EditorGizmoUtils::merge(geo_data, y_axis);	
	// end  Y_AXIS
	
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
