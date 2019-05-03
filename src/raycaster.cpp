#include "raycaster.h"


Raycaster::Raycaster()
{
	//~ printf("I am a raycaster ....\n");
}

static void vec_mult_by_matrix( glm::vec3 & _vec, glm::mat4 & _mat, bool invert = false){
	
	glm::vec4 temp_vec4 = glm::vec4(_vec.x, _vec.y, _vec.z,1.0f);
	
	
	if( invert){
		_vec = glm::inverse(_mat) * temp_vec4 ;
	} else{
		_vec = _mat * temp_vec4;
		//~ printf("__VEC X : %.3f\n", _vec.x);
	}

}

Ray Raycaster::ray_from_camera(ClickData click_data, Camera& camera)
{

	printf("camera position --> %.2f %.2f %.2f\n", camera.position.x, camera.position.y, camera.position.z);
	printf("click data : \n");
	printf("\tx : %.3f\n", click_data.x);
	printf("\ty : %.3f\n", click_data.y);
	printf("\twidth : %d\n", click_data.width);
	printf("\theight : %d\n", click_data.height);
	glm::vec3 screen_pos = glm::vec3((float)click_data.x, (float)click_data.y, 1.0f);
	
				
		//~ glm::vec3 rayDir = glm::vec3(0.0f, 0.0f , -1.0f);
		
		glm::mat4 projection = camera.projection;
		glm::mat4 view = glm::mat4(1.0f);

		
		
		// not sure why I need this, but it gets rid off a nasty offset 
		// found a solution here : https://stackoverflow.com/questions/48514387/can-anyone-explain-this-small-offset-from-ray-casting-by-mouse-click?rq=1
		// but the guy says he forced projection[3][3] to be 0.0, I have to do 1.0f for this to work
		
		projection[3][3] = 1.0f; 

		

		view *= glm::lookAt(
								camera.position, 
								camera.target_position, 
								camera.up_vector
							);			
							
		glm::vec4 dir = inverse(projection * view)* glm::vec4(screen_pos.x, screen_pos.y, screen_pos.z, 1.0f) ;
		dir /= dir.w *0.5f;	
	
	
	Ray ray;
	ray.pos = camera.position;
	ray.dir = glm::vec3(dir.x, dir.y, dir.z);
	
	glm::vec3 norm = glm::normalize(ray.dir);
	
	printf("ray direction  --> %.2f %.2f %.2f\n", norm.x, norm.y, norm.z);
	return ray;
}
		
static glm::vec3 cartesian_to_barycentric(glm::vec3 p, glm::vec3 a, glm::vec3 b, glm::vec3 c)
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

int Raycaster::ray_plane_intersect(glm::vec3 planeN, glm::vec3 planeP, glm::vec3 pointP, glm::vec3 rayDir, glm::vec3& hitP)
{
    glm::vec3 W = planeP - pointP;
    
    float K = glm::dot(W, planeN) / glm::dot( rayDir, planeN);
    
    hitP = pointP + ( K * rayDir);
    return  K>= 0.0 && K <= 1.0;
}

static bool point_in_triangle(glm::vec3 bary)
{
	bool result = 	0.0 <= bary.x && bary.x <= 1.0 &&
					0.0 <= bary.y && bary.y <= 1.0 &&
					0.0 <= bary.z && bary.z <= 1.0;
	return result;
}

bool Raycaster::ray_triangle_intersect(Ray& ray, glm::vec3 vtx_a, glm::vec3 vtx_b, glm::vec3 vtx_c)
{
		glm::vec3 plane_pos = (vtx_a + vtx_b + vtx_c);
		plane_pos = plane_pos / 3.0f;

		
		
		glm::vec3 plane_normal = glm::normalize(glm::cross( (vtx_b - vtx_a) , (vtx_c - vtx_a) ));
		
		glm::vec3 hitP = glm::vec3(0.0f);
		int hit = ray_plane_intersect(plane_normal, plane_pos, ray.pos, ray.dir, hitP);	
		if(hit){
			printf("just hit plane\n");
		}
		if( point_in_triangle( cartesian_to_barycentric(hitP, vtx_a, vtx_b, vtx_c)))
		{
			printf("IN TRIANGLE !!!!!!\n");
			return true;
		}	
		
		return false;	
}

std::vector<int> Raycaster::check_triangles(Ray& ray, Mesh& mesh)
{
	std::vector<int> triangles_ids;
	
	for (int i = 0; i < mesh.faces.size(); i += 3)
	{
		//~ printf("triangle number %d\n", i / 3);
		
		// ray vs plane intersection first
		
		//~ glm::vec3 vtx_a = object->mesh.vertices[object->mesh.indices[i]].position;
		//~ vec_mult_by_matrix(vtx_a, object->transforms);
//~ 
		//~ 
		//~ glm::vec3 vtx_b = object->mesh.vertices[object->mesh.indices[i+1]].position;
		//~ vec_mult_by_matrix(vtx_b, object->transforms);
		//~ 
		//~ glm::vec3 vtx_c = object->mesh.vertices[object->mesh.indices[i+2]].position;
		//~ vec_mult_by_matrix(vtx_c, object->transforms);
				//~ 
		//~ bool hit = ray_triangle_intersect(ray, vtx_a, vtx_b, vtx_c);
		//~ 
		//~ if(hit)
		//~ {				
			//~ printf("hit triangle !! \n");			
			//~ triangles_ids.push_back(i/3);			
		//~ }
	}
	
	return triangles_ids;
	
}

bool Raycaster::intersectBoudingBox(
						ClickData _click_data, 
						Camera& _camera, 
						Mesh& _target_mesh)
{
	
	
	//~ double pos_x = _click_data.x;
	//~ double pos_y = _click_data.y;
	//~ 
	//~ 
	//~ float width = (float)_click_data.width;
	//~ float height = (float)_click_data.height;
	//~ 
	//~ float x = (2.0f * pos_x) / width - 1.0f;
	//~ float y = 1.0f - (2.0f * pos_y) / height;	


		
		BoundingBox AABB = _target_mesh.computeAABB();
		
		glm::vec3 bbox_pos = AABB.position;
		glm::vec3 bbox_size = AABB.size;
		glm::vec3 bbox_center = bbox_pos + glm::vec3(bbox_size.x/2.0f, bbox_size.y/2.0f, bbox_size.y/2.0f) ;		
		
	
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
		
		
		Ray ray = ray_from_camera(_click_data, _camera);
		
		for (int id = 0; id < indices.size()/3; id++)
		{
			glm::vec3 vtx_a = bbox_vertices[indices[(id*3) + 0]];
			glm::vec3 vtx_b = bbox_vertices[indices[(id*3) + 1]];
			glm::vec3 vtx_c = bbox_vertices[indices[(id*3) + 2]];
			
			bool hit = ray_triangle_intersect(ray , vtx_a, vtx_b, vtx_c);
			
			if(hit)
			{
				//~ printf(" just hit boudingox triangle !!! for fuck sake !!!\n");
				return true;
			}else{
				//~ printf("no hit\n");
			}
		}
		
	
	
		
		
	
	
	return false;
}

bool Raycaster::intersectMeshes(
						ClickData _click_data, 
						Camera& _camera, 
						std::vector<Mesh> _target_meshes)
{
	
	//~ 
	//~ double pos_x, pos_y;
	//~ glfwGetCursorPos(_window->win, &pos_x, &pos_y);
	//~ 
	//~ float width = _window->width;
	//~ float height = _window->height;
//~ 
	//~ float x = (2.0f * pos_x) / width - 1.0f;
	//~ float y = 1.0f - (2.0f * pos_y) / height;
	//~ 
	//~ Ray  ray = ray_from_camera(_window, x, y);	
	//~ 
//~ 
		//~ 
	//~ for (int i = 0; i < _target_objects.size(); i++)
	//~ {
		//~ Entity3D * cur = _target_objects[i];
		//~ 
		//~ Object * p_object = nullptr;
		//~ if( p_object = dynamic_cast<Object *>(cur)){
			//~ 
			//~ bool hit_bbox = intersectBoudingBox(_window, _camera, p_object);
			//~ 
			//~ if( hit_bbox)
			//~ {
				//~ std::vector<int> triangles_ids = check_triangles(ray, p_object);
				//~ if( triangles_ids.size() > 0){
									//~ 
	//~ 
					//~ 
					//~ _result_objects.push_back(p_object);
				//~ }				
			//~ }
		//~ }
	//~ }
	//~ 
	//~ if( _result_objects.size() > 0 ){
		//~ 
		//~ sort( _result_objects.begin(), _result_objects.end(), [_camera](Entity3D* obj1, Entity3D* obj2 ){
			//~ 
				//~ float dist1 = glm::distance(obj1->position, _camera.position);
				//~ float dist2 = glm::distance(obj2->position, _camera.position);
				//~ return (dist1 < dist2);
		//~ } );
		//~ return true;
	//~ }
		
		

	return false;
}



