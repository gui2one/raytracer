#include "raycaster.h"

Raycaster::Raycaster()
{
	
}


static float distance_squared(glm::vec3 pt1, glm::vec3 pt2){
	return (pt2.x - pt1.x)*(pt2.x - pt1.x) + (pt2.y - pt1.y)*(pt2.y - pt1.y) + (pt2.z - pt1.z)*(pt2.z - pt1.z);
}

static float degToRad(float degrees)
{
	return ((degrees * PI) / 180.0);
}

static void vec_mult_by_matrix( glm::vec3 & _vec, glm::mat4 & _mat, bool invert = false)
{
    
        glm::vec4 temp_vec4 = glm::vec4(_vec.x, _vec.y, _vec.z,1.0f);
    
    
        if( invert){
                _vec = glm::inverse(_mat) * temp_vec4 ;
        } else{
                _vec = _mat * temp_vec4;
                //~ printf("__VEC X : %.3f\n", _vec.x);
        }

}

static int ray_plane_intersect(glm::vec3 planeN, glm::vec3 planeP, glm::vec3 pointP, glm::vec3 rayDir, glm::vec3& hitP)
{
    glm::vec3 W = planeP - pointP;

    float K = glm::dot(W, planeN) / glm::dot( rayDir, planeN);

    hitP = pointP + ( K * rayDir);
    return  K>= 0.0 && K <= 1.0;
}

static Ray offset_ray(Ray& src, float amount)
{
	Ray ray;
	ray.direction = src.direction;
	ray.origin = src.origin + (glm::normalize(src.direction) * amount);
	
	return ray;
}

static bool point_in_triangle(glm::vec3& bary)
{
	bool result = 	0.0 <= bary.x && bary.x <= 1.0 &&
					0.0 <= bary.y && bary.y <= 1.0 &&
					0.0 <= bary.z && bary.z <= 1.0;
	return result;
}

glm::vec3 Raycaster::cartesian_to_barycentric(glm::vec3& p, glm::vec3& a, glm::vec3& b, glm::vec3& c)
{
    glm::vec3 v0 = b - a, v1 = c - a, v2 = p - a;
    float d00 = glm::dot(v0, v0);
    float d01 = glm::dot(v0, v1);
    float d11 = glm::dot(v1, v1);
    float d20 = glm::dot(v2, v0);
    float d21 = glm::dot(v2, v1);
    float denom = d00 * d11 - d01 * d01;
    
    
    float v = (d11 * d20 - d01 * d21) / denom;
    float w = (d00 * d21 - d01 * d20) / denom;
    float u = 1.0f - v - w;
    
    return glm::vec3(u,v,w);
}

bool Raycaster::ray_triangle_intersect(Ray& ray, glm::vec3& vtx_a, glm::vec3& vtx_b, glm::vec3& vtx_c, glm::vec3& hit_pos, glm::vec3& bary_coords)
{
		glm::vec3 plane_pos = (vtx_a + vtx_b + vtx_c);
		plane_pos = plane_pos / 3.0f;

		
		
		glm::vec3 plane_normal = glm::normalize(glm::cross( (vtx_b - vtx_a) , (vtx_c - vtx_a) ));
		
		glm::vec3 hitP = glm::vec3(0.0f);
		int hit = ray_plane_intersect(plane_normal, plane_pos, ray.origin, ray.direction, hitP);	
		if(hit){
			//~ printf("just hit plane\n");
		}
		glm::vec3 pt = cartesian_to_barycentric(hitP, vtx_a, vtx_b, vtx_c);
		if( point_in_triangle( pt ))
		{
			//~ printf("IN TRIANGLE !!!!!!\n");
			bary_coords = pt;
			hit_pos = hitP;
			return true;
		}	
		
		return false;	
}


Ray Raycaster::castRay(ClickData click_data, Camera& camera)
{

	glm::vec3 screen_world_pos = screenToWorld( click_data, camera);
	glm::vec3 direction = screen_world_pos;
	
	Ray ray;
	ray.origin = glm::vec3(0.0,0.0,0.0);
	
	glm::mat4 view_matrix = glm::lookAt(camera.position, camera.target_position, camera.up_vector);
	

	ray.origin = camera.position;
	ray.direction = direction;
	
	vec_mult_by_matrix(ray.direction, view_matrix, true);
	

	return ray;
}


glm::vec3 Raycaster::screenToWorld(ClickData click_data, Camera& camera)
{
	// there I build the image plane	
	// dz = - ( height /2 ) / tan( fov * 0.5)
	
	
	// do I need to offset by half a pixel size ? 
	

	
	/////
	
	float x_pos = (float)click_data.x - (float)(click_data.width) / 2.0;
	float y_pos =  (float)(click_data.height) / 2.0 - (float)click_data.y;
	float z_pos = -( (float)(click_data.height) / 2.0) / tan( camera.fov*0.5 );
	
	glm::vec3 world_pos = glm::vec3(x_pos, y_pos, z_pos) ;
	
	return world_pos;
	
}



bool Raycaster::intersectKDNode(Ray& ray, KDNode * kd_node, int mesh_id, std::vector<HitData>& hit_datas, bool bail_early)
{
	
	bool hit;
	KDNode * target = kd_node;
	
	if( kd_node->bbox.intersect(ray))
	{

		if( kd_node->left->triangles.size() > 0 || kd_node->right->triangles.size() > 0)
		{
			//~ printf("------- checking left and right \n");
			bool hit_left = intersectKDNode(ray, kd_node->left,  mesh_id, hit_datas, bail_early);
			bool hit_right = intersectKDNode(ray, kd_node->right, mesh_id, hit_datas, bail_early);

			return hit_left || hit_right;
			
		}else{
		
			//~ printf("------- reached leaf\n");

			for (int i = 0; i < kd_node->triangles.size(); i++)
			{
				glm::vec3 hit_pos;
				glm::vec3 bary_coords;
				bool hit_tri = ray_triangle_intersect(ray, kd_node->triangles[i]->A, kd_node->triangles[i]->B, kd_node->triangles[i]->C, hit_pos, bary_coords);
				if(hit_tri)
				{
					glm::vec3 collide_dir = hit_pos - ray.origin;
					if( glm::dot( collide_dir, ray.direction) > 0.0){
						
						HitData data;
						data.position = hit_pos;
						data.barycentric_coords = bary_coords;
						data.ray_origin = ray.origin;
						data.ray_direction = ray.direction;
						data.face_id = kd_node->triangles[i]->id;
						data.mesh_id = mesh_id;
						hit_datas.push_back(data);
						
						if( bail_early ) return true;
						//~ printf("TRIANGLE HIT !!!!!!\n");
						//~ printf("\t id : %d\n", data.face_id);							
					}
				
				}
			}

			
			
			return true;
		}
		
		
	}
	
	return false;
}

bool Raycaster::intersectKDNodes(Ray& ray, std::vector<KDNode *> kd_nodes, std::vector<HitData>& hit_datas, bool bail_early)
{
	int num_hits = 0;
	for (int i = 0; i < kd_nodes.size(); i++)
	{
		bool hit = intersectKDNode(ray, kd_nodes[i], i, hit_datas, bail_early);
		if(hit){
			
			num_hits++;
			
		}
	}
	
	if( num_hits > 0){
		
		std::sort(hit_datas.begin(), hit_datas.end(), [ray](HitData data1 , HitData data2){
			float dist1 = glm::distance(data1.position, ray.origin);
			//~ float dist1 = distance_squared(data1.position, ray.origin);
			float dist2 = glm::distance(data2.position, ray.origin);
			//~ float dist2 = distance_squared(data2.position, ray.origin);
			return dist1 < dist2;
		});			
		return true;
	}else{
		return false;
	}
	
}

