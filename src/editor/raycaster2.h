#ifndef RAYCASTER2_H
#define RAYCASTER2_H

#include "../pch.h"
#include "editor_camera.h"
#include "../light.h"
#include "../mesh.h"
#include "kdnode2.h"
#include "../ray.h"
#include "handles/base_handle.h"


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
		Ray castRay(ClickData click_data, const Camera& camera);
		
		glm::vec3 screenToWorld_2(ClickData click_data, const Camera& camera);
		glm::vec3 cartesian_to_barycentric(glm::vec3& p, glm::vec3& a, glm::vec3& b, glm::vec3& c);
		bool ray_triangle_intersect(Ray& ray, glm::vec3& vtx_a, glm::vec3& vtx_b, glm::vec3& vtx_c, glm::vec3& hit_pos, glm::vec3& bary_coords);
		

		bool intersectKDNode(Ray& ray, std::shared_ptr<KDNode> kd_node, const int& mesh_id, std::vector<HitData>& hit_datas, bool bail_early = false);
		bool intersectKDNodes(Ray& ray, std::vector<std::shared_ptr<KDNode>> kd_nodes, std::vector<HitData>& hit_datas, bool bail_early = false);
	
		
		bool intersectHandles(Ray& ray, std::vector<std::shared_ptr<BaseHandle> > handles, std::vector<HitData>& hit_datas);
		bool intersectEntities(Ray& ray, std::vector<std::shared_ptr<Entity3D> > entities, std::vector<HitData>& hit_datas);
		
			
	private:
		/* add your private declarations */
};

#endif /* RAYCASTER2_H */ 
