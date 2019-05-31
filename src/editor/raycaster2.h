#ifndef RAYCASTER2_H
#define RAYCASTER2_H

#include "../pch.h"
#include "../camera.h"
#include "../light.h"
#include "../mesh.h"
#include "kdnode2.h"
#include "../ray.h"


struct HitData
{
	glm::vec3 position;
	glm::vec3 barycentric_coords;
	glm::vec3 ray_origin;
	glm::vec3 ray_direction;
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

class Raycaster
{
	public:
		Raycaster();
		Ray castRay(ClickData click_data, Camera& camera);
		
		glm::vec3 screenToWorld(ClickData click_data, Camera& camera);
		glm::vec3 screenToWorld_2(ClickData click_data, Camera& camera);
		glm::vec3 cartesian_to_barycentric(glm::vec3& p, glm::vec3& a, glm::vec3& b, glm::vec3& c);
		bool ray_triangle_intersect(Ray& ray, glm::vec3& vtx_a, glm::vec3& vtx_b, glm::vec3& vtx_c, glm::vec3& hit_pos, glm::vec3& bary_coords);
		

		bool intersectKDNode(Ray& ray, KDNode * kd_node, int mesh_id, std::vector<HitData>& hit_datas, bool bail_early = false);
		bool intersectKDNodes(Ray& ray, std::vector<KDNode *> kd_nodes, std::vector<HitData>& hit_datas, bool bail_early = false);
	
		
			
	private:
		/* add your private declarations */
};

#endif /* RAYCASTER2_H */ 
