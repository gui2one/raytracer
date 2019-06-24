#ifndef ENTITY_3D_H
#define ENTITY_3D_H

#include "../pch.h"
#include "../mesh.h"
#include "ogl_geometry_data.h"
#include "utils/editor_gizmo_utils.h"

#include "mesh_generators/mesh_generator.h"
#include "mesh_generators/grid_mesh_generator.h"
#include "mesh_generators/box_mesh_generator.h"
#include "mesh_generators/cylinder_mesh_generator.h"

#include "mesh_filters/mesh_filter.h"
#include "mesh_filters/transform_mesh_filter.h"



#include "kdnode2.h"

class Entity3D
{
public:
	
	Entity3D();
	
	virtual void draw();
	virtual void buildVBO(){}
	virtual void buildKDTree(int _limit = 5){};
	

	virtual ~Entity3D();
	
	glm::mat4 getParentsTransform();
	std::vector<std::shared_ptr<Entity3D> > getParentChain();
	void applyTransforms();
	glm::mat4 transforms;	
	glm::vec3 position;
	glm::vec3 rotation;
	glm::vec3 scale;
	
	
	std::string name = "default_name";
	OGL_geometry_data OGL_geo_data;
	OGL_DATA_2 geo_data_2;
	
	bool is_selected = false;
	
	std::shared_ptr<Entity3D> parent;
	std::shared_ptr<Entity3D> look_at_target;
	
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
	
	
	
	void buildVBO() override;
	void draw() override;
	

	
	void setMeshGenerator(MESH_GENERATOR_TYPE _type);
	void updateMeshGenerator();
	unsigned int m_vbo=0, m_ibo=0;
	
	MeshGenerator * generator;
	MESH_GENERATOR_TYPE generator_type;
	Mesh mesh;
	
	
	std::vector<std::shared_ptr<MeshFilter> > mesh_filters;
	void addMeshFilter(MESH_FILTER_TYPE filter_type);
	void deleteMeshFilter(unsigned int id);
	void moveMeshFilter(int _origin, int _dest);
	void applyFilters();
	void buildKDTree(int _limit = 5) override;

	
	
	
	
private:
	
};

class NullObject : public Entity3D
{
public :
	NullObject();
	
	void buildVBO() override;
	void draw() override;	
	void buildKDTree(int _limit = 5) override;
	
	unsigned int m_vbo=0, m_ibo=0;
	
	OGL_DATA_2 click_geo;
private :
	
};
#endif 
