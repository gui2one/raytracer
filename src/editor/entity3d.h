#ifndef ENTITY_3D_H
#define ENTITY_3D_H

#include "../pch.h"
#include "../mesh.h"
#include "ogl_geometry_data.h"
#include "mesh_generators/mesh_generator.h"
#include "mesh_generators/plane_mesh_generator.h"
#include "kdnode2.h"

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
	
	std::shared_ptr<KDNode> kd_node;
	
private:


};

class MeshObject : public Entity3D
{
	
public :
	MeshObject();
	
	~MeshObject();
	
	
	
	void buildVBO();
	void draw() override;
	void buildKDTree(int _limit);
	
	void deleteKDTree();
	
	void setMeshGenerator(MESH_GENERATOR_TYPE _type);
	void updateMeshGenerator();
	unsigned int m_vbo=0, m_ibo=0;
	
	MeshGenerator * generator;
	Mesh mesh;
	
	
	
	
private:
	
};


#endif 
