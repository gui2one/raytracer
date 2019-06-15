#ifndef ENTITY_3D_H
#define ENTITY_3D_H

#include "../pch.h"
#include "../mesh.h"
#include "ogl_geometry_data.h"

#include "mesh_generators/mesh_generator.h"
#include "mesh_generators/grid_mesh_generator.h"
#include "mesh_generators/box_mesh_generator.h"

#include "kdnode2.h"

class Entity3D
{
public:
	
	Entity3D();
	
	virtual void draw();
	virtual void buildKDTree(int _limit){};
	

	virtual ~Entity3D();
	
	void applyTransforms();
	glm::mat4 transforms;	
	glm::vec3 position;
	glm::vec3 rotation;
	glm::vec3 scale;
	
	
	std::string name = "default_name";
	OGL_geometry_data OGL_geo_data;
	
	bool is_selected = false;
	
	Entity3D * parent;
	
	std::vector<BaseParam*> params;	
	Param<glm::vec3> * param_position;
	Param<glm::vec3> * param_rotation;
	Param<glm::vec3> * param_scale;
	
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

	
	void setMeshGenerator(MESH_GENERATOR_TYPE _type);
	void updateMeshGenerator();
	unsigned int m_vbo=0, m_ibo=0;
	
	MeshGenerator * generator;
	MESH_GENERATOR_TYPE generator_type;
	Mesh mesh;
	
	void buildKDTree(int _limit) override;

	
	
	
	
private:
	
};


#endif 
