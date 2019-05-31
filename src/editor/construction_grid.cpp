#include "construction_grid.h"


ConstructionGrid::ConstructionGrid():
	position(glm::vec3(0.0, 0.0, 0.0)), 
	size(glm::vec2(12.0, 12.0))
{
	
}

void ConstructionGrid::init()
{
	// center lines
	main_vertices.clear();
	main_indices.clear();
	
	
	main_vertices.insert(
		main_vertices.end(),{
			-size.x / 2.0f + position.x,
			0.0f + position.y, 
			0.0f + position.z,
			 
			size.x/2.0f + position.x, 
			0.0f + position.y, 
			0.0f + position.z,
			
			0.0f + position.x, 
			-size.y/2.0f + position.y, 
			0.0f + position.z,
						
			0.0f + position.x, 
			size.y/2.0f + position.y, 
			0.0f + position.z
		}
	);

	main_indices.insert(
		main_indices.end(),{
			0,1,
			2,3
		}
	);	
	if(main_vbo == 0){
		GLCall(glGenBuffers(1, &main_vbo));
	}else{
		GLCall(glDeleteBuffers(1, &main_vbo));
		GLCall(glGenBuffers(1, &main_vbo));
	}
	
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, main_vbo));
	GLCall(glBufferData(GL_ARRAY_BUFFER, sizeof(float) * main_vertices.size(), main_vertices.data(), GL_STATIC_DRAW));
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));	
	
	if(main_ibo == 0){
		GLCall(glGenBuffers(1, &main_ibo));
	}else{
		GLCall(glDeleteBuffers(1, &main_ibo));
		GLCall(glGenBuffers(1, &main_ibo));
	}
	
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, main_ibo));
	GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * main_indices.size(), main_indices.data(), GL_STATIC_DRAW));
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));		
	
	// minor lines
	minor_vertices.clear();	
	minor_indices.clear();	
	
	// major lines 
	major_vertices.clear();
	major_indices.clear();


	// positive X
	float inc = (double)major_space / (double)minor_divs;
	
	float x = inc;
	int counter = 1;
	while(x < (size.x / 2.0f))
	{
		if( counter % minor_divs == 0)
		{
			//~ printf("adding major line, \n\tincrement : %.3f  \n\tX : %.3f\n", inc, x);
			major_vertices.insert(
				major_vertices.end(),{
					x + position.x, 
					-size.y/2.0f + position.y,  
					0.0f + position.z,
					
					x + position.x,  
					size.y/2.0f + position.y,  
					0.0f + position.z
				}
			);
			
			major_indices.insert(
				major_indices.end(),{
					(unsigned int)major_vertices.size()/3-2,
					(unsigned int)major_vertices.size()/3-1
				}
			);
		}else{
			//~ printf("adding minor line, \n\tincrement : %.3f  \n\tX : %.3f\n", inc, x);
			minor_vertices.insert(
				minor_vertices.end(),{
					x + position.x, 
					-size.y/2.0f + position.y,  
					0.0f + position.z,
					
					x + position.x,  
					size.y/2.0f + position.y, 
					0.0f + position.z
				}
			);
			
			minor_indices.insert(
				minor_indices.end(),{
					(unsigned int)minor_vertices.size()/3-2,
					(unsigned int)minor_vertices.size()/3-1
				}
			);			
		}
		counter++;
		x += inc;
	}
	
	// negative X
	
	x = -inc;
	counter = 1;
	while(x > -(size.x / 2.0f))
	{
		if( counter % minor_divs == 0)
		{
			//~ printf("adding major line, \n\tincrement : %.3f  \n\tX : %.3f\n", inc, x);
			major_vertices.insert(
				major_vertices.end(),{
					x + position.x, 
					-size.y/2.0f + position.y,  
					0.0f + position.z,
					
					x + position.x,  
					size.y/2.0f + position.y,  
					0.0f + position.z
				}
			);
			
			major_indices.insert(
				major_indices.end(),{
					(unsigned int)major_vertices.size()/3-2,
					(unsigned int)major_vertices.size()/3-1
				}
			);
		}else{
			//~ printf("adding minor line, \n\tincrement : %.3f  \n\tX : %.3f\n", inc, x);
			minor_vertices.insert(
				minor_vertices.end(),{
					x + position.x, 
					-size.y/2.0f + position.y,  
					0.0f + position.z,
					
					x + position.x,  
					size.y/2.0f + position.y,  
					0.0f + position.z
				}
			);
			
			minor_indices.insert(
				minor_indices.end(),{
					(unsigned int)minor_vertices.size()/3-2,
					(unsigned int)minor_vertices.size()/3-1
				}
			);			
		}
		counter++;
		x -= inc;
	}	
	
	
	// positive Y
	float y = inc;
	counter = 1;
	while(y < (size.y / 2.0f))
	{
		if( counter % minor_divs == 0)
		{
			//~ printf("adding major line, \n\tincrement : %.3f  \n\tX : %.3f\n", inc, x);
			major_vertices.insert(
				major_vertices.end(),{
					-size.x/2.0f + position.x,
					y + position.y,
					0.0f + position.z,
					
					size.x/2.0f + position.x,
					y + position.y,
					0.0f + position.z
				}
			);
			
			major_indices.insert(
				major_indices.end(),{
					(unsigned int)major_vertices.size()/3-2,
					(unsigned int)major_vertices.size()/3-1
				}
			);
		}else{
			//~ printf("adding minor line, \n\tincrement : %.3f  \n\tX : %.3f\n", inc, x);
			minor_vertices.insert(
				minor_vertices.end(),{
					-size.x/2.0f + position.x,
					y + position.y,
					0.0f + position.z,
					
					size.x/2.0f + position.x,
					y + position.y, 
					0.0f + position.z
				}
			);
			
			minor_indices.insert(
				minor_indices.end(),{
					(unsigned int)minor_vertices.size()/3-2,
					(unsigned int)minor_vertices.size()/3-1
				}
			);			
		}
		counter++;
		y += inc;
	}
	
	
	// Negative Y
	y = -inc;
	counter = 1;
	while(y > -(size.y / 2.0f))
	{
		if( counter % minor_divs == 0)
		{
			//~ printf("adding major line, \n\tincrement : %.3f  \n\tX : %.3f\n", inc, x);
			major_vertices.insert(
				major_vertices.end(),{
					-size.x/2.0f + position.x, 
					y + position.y,  
					0.0f + position.z,
					
					size.x/2.0f + position.x, 
					y + position.y,  
					0.0f + position.z
				}
			);
			
			major_indices.insert(
				major_indices.end(),{
					(unsigned int)major_vertices.size()/3-2,
					(unsigned int)major_vertices.size()/3-1
				}
			);
		}else{
			//~ printf("adding minor line, \n\tincrement : %.3f  \n\tX : %.3f\n", inc, x);
			minor_vertices.insert(
				minor_vertices.end(),{
					-size.x/2.0f + position.x,  
					y + position.y,  
					0.0f + position.z,
					
					size.x/2.0f + position.x,  
					y + position.y,  
					0.0f + position.z
				}
			);
			
			minor_indices.insert(
				minor_indices.end(),{
					(unsigned int)minor_vertices.size()/3-2,
					(unsigned int)minor_vertices.size()/3-1
				}
			);			
		}
		counter++;
		y -= inc;
	}	
		
	//~ printf("major lines indices num : %d\n", major_indices.size());
	
	if(major_vbo == 0){
		GLCall(glGenBuffers(1, &major_vbo));
	}else{
		GLCall(glDeleteBuffers(1, &major_vbo));
		GLCall(glGenBuffers(1, &major_vbo));
	}
	
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, major_vbo));
	GLCall(glBufferData(GL_ARRAY_BUFFER, sizeof(float) * major_vertices.size(), major_vertices.data(), GL_STATIC_DRAW));
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
	
	
	if(major_ibo == 0){
		GLCall(glGenBuffers(1, &major_ibo));
	}else{
		GLCall(glDeleteBuffers(1, &major_ibo));
		GLCall(glGenBuffers(1, &major_ibo));
	}
	
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, major_ibo));
	GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * major_indices.size(), major_indices.data(), GL_STATIC_DRAW));
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));		
	
	


	
	if(minor_vbo == 0){
		GLCall(glGenBuffers(1, &minor_vbo));
	}else{
		GLCall(glDeleteBuffers(1, &minor_vbo));
		GLCall(glGenBuffers(1, &minor_vbo));
	}
	
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, minor_vbo));
	GLCall(glBufferData(GL_ARRAY_BUFFER, sizeof(float) * minor_vertices.size(), minor_vertices.data(), GL_STATIC_DRAW));
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
	
	
	if(minor_ibo == 0){
		GLCall(glGenBuffers(1, &minor_ibo));
	}else{
		GLCall(glDeleteBuffers(1, &minor_ibo));
		GLCall(glGenBuffers(1, &minor_ibo));
	}
	
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, minor_ibo));
	GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * minor_indices.size(), minor_indices.data(), GL_STATIC_DRAW));
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));	
}

void ConstructionGrid::draw(Shader& shader)
{	
	
	
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, main_vbo));
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, main_ibo));
	GLCall(glVertexAttribPointer(0,3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, 0));
	
	GLCall(glEnableVertexAttribArray(0));

	GLCall(glLineWidth(2));
	
	GLCall(glUniform4f(glGetUniformLocation(shader.m_id, "u_color"), 0.6, 0.6, 0.6, 1.0 ));
	GLCall(glDrawElements(GL_LINES, main_indices.size(), GL_UNSIGNED_INT, nullptr));
	
	GLCall(glDisableVertexAttribArray(0));
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0))
	
	// draw major lines	
	
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, major_vbo));
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, major_ibo));
	GLCall(glVertexAttribPointer(0,3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, 0));
	
	GLCall(glEnableVertexAttribArray(0));

	GLCall(glLineWidth(2));
	GLCall(glUniform4f(glGetUniformLocation(shader.m_id, "u_color"), 0.4, 0.4, 0.4, 1.0 ));
	GLCall(glDrawElements(GL_LINES, major_indices.size(), GL_UNSIGNED_INT, nullptr));
	
	GLCall(glDisableVertexAttribArray(0));
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
	
	
	// draw minor lines
	
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, minor_vbo));
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, minor_ibo));
	GLCall(glVertexAttribPointer(0,3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, 0));
	
	GLCall(glEnableVertexAttribArray(0));

	
	GLCall(glLineWidth(1));
	GLCall(glUniform4f(glGetUniformLocation(shader.m_id, "u_color"), 0.4, 0.4, 0.4, 1.0 ));
	GLCall(glDrawElements(GL_LINES, minor_indices.size(), GL_UNSIGNED_INT, nullptr));
	
	GLCall(glDisableVertexAttribArray(0));
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));	
	
	
}
