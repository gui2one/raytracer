#ifndef RAYCASTER_H
#define RAYCASTER_H

#include "pch.h"
#include "camera.h"
#include "mesh.h"


struct Ray{
	
	glm::vec3 pos;
	glm::vec3 dir;
	
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
		Ray ray_from_camera(ClickData click_data, Camera& camera);
		bool intersectBoudingBox(ClickData click_data, Camera& _camera, Mesh& _target_mesh);
		bool intersectMeshes(ClickData click_data, Camera& _camera, std::vector<Mesh> _target_meshes);
		
		int ray_plane_intersect(glm::vec3 planeN, glm::vec3 planeP, glm::vec3 pointP, glm::vec3 rayDir, glm::vec3& hitP);
		bool ray_triangle_intersect(Ray& ray, glm::vec3 vtx_a, glm::vec3 vtx_b, glm::vec3 vtx_c);
		
		std::vector<int> check_triangles(Ray& ray, Mesh& mesh);
	private:
		/* add your private declarations */
};

#endif /* RAYCASTER_H */ 
