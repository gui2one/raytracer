#ifndef RAYCASTER2_H
#define RAYCASTER2_H

#include "pch.h"
#include "camera.h"
#include "light.h"
#include "mesh.h"
#include "kdnode.h"
#include "ray.h"
//~ struct Ray
//~ {	
	//~ glm::vec3 origin;
	//~ glm::vec3 direction;
		//~ 
//~ };

struct HitData
{
	glm::vec3 position;
	unsigned int face_id;
	unsigned int mesh_id;
	
	void print(){
		printf("Hit Data : \n");
		printf("\tposition : %.3f %.3f %.3f\n", position.x, position.y, position.z);
		printf("\tface_id : %d\n", face_id);
		printf("--------------------\n");
	}
};

struct ClickData
{
	double x, y;
	int width, height;
};

class Raycaster2
{
	public:
		Raycaster2();
		Ray castRay(ClickData click_data, Camera& camera);
		//~ glm::vec2 toScreenSpace(ClickData click_data);
		glm::vec3 screenToWorld(ClickData click_data, Camera& camera);
		
		bool ray_triangle_intersect(Ray& ray, glm::vec3& vtx_a, glm::vec3& vtx_b, glm::vec3& vtx_c, glm::vec3& hit_pos);
		
		bool intersectBoudingBox(ClickData _click_data, Camera& _camera, Mesh& _target_mesh, HitData& _hit_data);
		
		bool intersectMesh(ClickData click_data, Camera& camera, Mesh& mesh, HitData& _hit_data);
		bool intersectMeshes(ClickData click_data, Camera& camera, std::vector<Mesh>& meshes, HitData& _hit_data);
		bool intersectKDNode(Ray& ray, KDNode * kd_node, int mesh_id, std::vector<HitData>& hit_datas, bool bail_early = false);
		bool intersectKDNodes(Ray& ray, std::vector<KDNode *> kd_nodes, std::vector<HitData>& hit_datas, bool bail_early = false);
		
		bool shadowRay(glm::vec3 pos, std::vector<KDNode *> kd_nodes, Light& light);
			
	private:
		/* add your private declarations */
};

#endif /* RAYCASTER2_H */ 
