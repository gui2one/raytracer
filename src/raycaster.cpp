#include "raycaster.h"

Raycaster::Raycaster()
{
	
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

static glm::vec3 cartesian_to_barycentric(glm::vec3& p, glm::vec3& a, glm::vec3& b, glm::vec3& c)
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

bool Raycaster::ray_triangle_intersect(Ray& ray, glm::vec3& vtx_a, glm::vec3& vtx_b, glm::vec3& vtx_c, glm::vec3& hit_pos)
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

bool Raycaster::intersectBoudingBox(
						ClickData _click_data, 
						Camera& _camera, 
						Mesh& _target_mesh,
						HitData& hit_data)
{

		BoundingBox AABB = _target_mesh.computeAABB();
		
		glm::vec3 bbox_pos = AABB.position;
		glm::vec3 bbox_size = AABB.size;
		glm::vec3 bbox_center = bbox_pos + glm::vec3(bbox_size.x/2.0f, bbox_size.y/2.0f, bbox_size.z/2.0f) ;		
		
	
		// build bbox out of triangles for intersection by ray
		
		std::vector<glm::vec3> bbox_vertices;
		
		bbox_vertices.push_back(bbox_pos);
		bbox_vertices.push_back(bbox_pos + glm::vec3( bbox_size.x,        0.0f,        0.0f));
		bbox_vertices.push_back(bbox_pos + glm::vec3(        0.0f,        0.0f, bbox_size.z));
		bbox_vertices.push_back(bbox_pos + glm::vec3( bbox_size.x,        0.0f, bbox_size.z));
		
		bbox_vertices.push_back(bbox_pos + glm::vec3(         0.0, bbox_size.y,        0.0f));
		bbox_vertices.push_back(bbox_pos + glm::vec3( bbox_size.x, bbox_size.y,        0.0f));
		bbox_vertices.push_back(bbox_pos + glm::vec3(        0.0f, bbox_size.y, bbox_size.z));
		bbox_vertices.push_back(bbox_pos + glm::vec3( bbox_size.x, bbox_size.y, bbox_size.z));
		
		
		
		std::vector<int> indices;
					
		indices.insert(indices.end(), {0, 2, 3});
		indices.insert(indices.end(), {0, 3, 1});
		
		indices.insert(indices.end(), {1, 3, 7});
		indices.insert(indices.end(), {1, 7, 5});
		
		indices.insert(indices.end(), {5, 7, 6});
		indices.insert(indices.end(), {5, 6, 4});
		
		indices.insert(indices.end(), {4, 6, 2});
		indices.insert(indices.end(), {4, 2, 0});
		
		indices.insert(indices.end(), {2, 6, 7});
		indices.insert(indices.end(), {2, 7, 3});
		
		indices.insert(indices.end(), {0, 4, 5});
		indices.insert(indices.end(), {0, 5, 1});
		
		
		// now perform triangle intersections
		
		
		Ray ray = castRay(_click_data, _camera);
		
		for (int id = 0; id < indices.size()/3; id++)
		{
			glm::vec3 vtx_a = bbox_vertices[indices[(id*3) + 0]];
			glm::vec3 vtx_b = bbox_vertices[indices[(id*3) + 1]];
			glm::vec3 vtx_c = bbox_vertices[indices[(id*3) + 2]];
			
			glm::vec3 hit_pos;
			bool hit = ray_triangle_intersect(ray , vtx_a, vtx_b, vtx_c, hit_pos);
			
			if(hit)
			{
				//~ printf(" just hit boudingox triangle !!! for fuck sake !!!\n");
				hit_data.position = hit_pos;
				hit_data.face_id = id;
				return true;
			}else{
				//~ printf("no hit\n");
			}
		}
		
	
	
		
		
	
	
	return false;
}

bool Raycaster::intersectMesh(ClickData click_data, Camera& camera, Mesh& mesh, HitData& _hit_data)
{
	
	//// why a new ray ???!!!	
	Ray ray = castRay(click_data, camera);
	std::vector<HitData> hits;
	for (int tri_id = 0; tri_id < mesh.faces.size(); tri_id++)
	{
		Face& face = mesh.faces[tri_id];
		glm::vec3 vtx_a = mesh.points[face.getVertex(0).point_id].position;
		glm::vec3 vtx_b = mesh.points[face.getVertex(1).point_id].position;
		glm::vec3 vtx_c = mesh.points[face.getVertex(2).point_id].position;
		
		glm::vec3 hit_pos;
		bool hit = ray_triangle_intersect(ray ,vtx_a , vtx_b, vtx_c, hit_pos);
		
		if(hit){
			HitData temp_data;
			temp_data.position = hit_pos;
			temp_data.face_id = tri_id;
			//~ printf("hit Mesh object !!! \n");
			hits.push_back(temp_data);
			//~ return true;
		}
		
	}
	
	
	std::sort(hits.begin(), hits.end(), [camera](HitData hit1, HitData hit2){
		float dist1 = glm::distance(hit1.position, camera.position);
		float dist2 = glm::distance(hit2.position, camera.position);
		return dist1 < dist2;
	});
	
	if( hits.size() > 0)
	{
		_hit_data = hits[0];
		return true;
	}
	
	
	return false;
}

bool Raycaster::intersectMeshes(ClickData click_data, Camera& camera, std::vector<Mesh>& meshes, HitData& _hit_data)
{
	std::vector<int> hit_ids;
	for(int mesh_id = 0; mesh_id < meshes.size(); mesh_id++)
	{
		HitData bbox_hit_data;
		bool hit_bbox = intersectBoudingBox( click_data, camera, meshes[mesh_id], bbox_hit_data);
		if(hit_bbox)
		{
			//~ printf("hit bbox %d\n", mesh_id);
			//~ bbox_hit_data.print();
			hit_ids.push_back(mesh_id);
			//~ return true;
		}
	}
	
	if(hit_ids.size() > 0)
	{
		
		std::vector<HitData> mesh_hits;
		for (int i = 0; i < hit_ids.size(); i++)
		{
			Mesh& cur_mesh = meshes[hit_ids[i]];
			HitData mesh_hit_data;
			bool hit_mesh = intersectMesh(click_data, camera, cur_mesh, mesh_hit_data);
			
			if( hit_mesh){
				mesh_hits.push_back(mesh_hit_data);
				//~ printf("HIT MESH !!!!!\n");
			}
		}
		
		if( mesh_hits.size() > 0){
				
			glm::vec3 cam_pos = camera.position;	
			std::sort( mesh_hits.begin(), mesh_hits.end(), [cam_pos](HitData hit1,HitData hit2){
				float dist1 = glm::distance(cam_pos, hit1.position);
				float dist2 = glm::distance(cam_pos, hit2.position);
				return dist1 < dist2;
			});
			
			_hit_data = mesh_hits[0];
			return true;
		}
		
	}
	
	return false;
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
				bool hit_tri = ray_triangle_intersect(ray, kd_node->triangles[i]->A, kd_node->triangles[i]->B, kd_node->triangles[i]->C, hit_pos);
				if(hit_tri)
				{
					glm::vec3 collide_dir = hit_pos - ray.origin;
					if( glm::dot( collide_dir, ray.direction) > 0.0){
						
						HitData data;
						data.position = hit_pos;
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
			float dist2 = glm::distance(data2.position, ray.origin);
			return dist1 < dist2;
		});			
		return true;
	}else{
		return false;
	}
	
}





