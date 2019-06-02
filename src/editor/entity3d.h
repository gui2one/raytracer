#ifndef ENTITY_3D_H
#define ENTITY_3D_H

#include "../pch.h"
#include "../mesh.h"
#include "ogl_geometry_data.h"
//~ struct OGL_geometry_data
//~ {
	//~ std::vector<float> vertices;
	//~ std::vector<unsigned int> indices;
	//~ 
	//~ glm::vec3 translate = glm::vec3(0.0, 0.0, 0.0);
	//~ glm::vec3 rotate = glm::vec3(0.0, 0.0, 0.0);
	//~ glm::vec3 scale = glm::vec3(1.0, 1.0, 1.0);
	//~ 
//~ };

class Entity3D
{
public:
	
	Entity3D();
	
	virtual void draw();
	virtual ~Entity3D();
	
	void applyTransforms();
	glm::mat4 transforms;	
	glm::vec3 position;
	glm::vec3 rotation;
	glm::vec3 scale;
	
	
	std::string name = "default_name";
	OGL_geometry_data OGL_geo_data;
	
	bool is_selected = false;
	
private:


};

class MeshObject : public Entity3D
{
	
public :
	MeshObject();
	
	~MeshObject();
	
	void buildVBO();
	void draw() override;
	unsigned int m_vbo=0, m_ibo=0;
	
	Mesh mesh;
	
private:

};


#endif 
