#include "renderer.h"


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

static Ray offset_ray(Ray& src, float amount)
{
	Ray ray;
	ray.direction = src.direction;
	ray.origin = src.origin + (glm::normalize(src.direction) * amount);

	return ray;
}

static void stbi_save(std::string path, int w, int h, unsigned char* data)
{
	//~ int stbi_write_jpg(char const *filename, int w, int h, int comp, const void *data, int quality);

	//~ int saved = stbi_write_jpg("stbi_test.jpg", w, h, 3, data,100);
	int saved = stbi_write_png( path.c_str() , w, h, 3, data, w * 3 * sizeof(unsigned char));
	if(saved){
		printf("saved %s \n", path.c_str());
	}else{
		printf("Problem saving PNG file\n");
	}
}

static void save_render_to_file(int width, int height, unsigned char * data)
{

	SystemUtils sys_utils;
	bool test_dir = sys_utils.check_dir_exists(".", "render");
	
	if( test_dir )
	{
		char buffer[500];
		int n;
		int inc = 0;
		bool file_exists;
		n = sprintf(buffer, "auto_save_%d.png", inc);
		std::string test_name(buffer);
		
		while( file_exists = sys_utils.check_file_exists("render", test_name))
		{
			inc++;
			sprintf(buffer, "auto_save_%d.png", inc);
			test_name = std::string(buffer);
			
		}
		
		sprintf(buffer, "render/%s", test_name.c_str());
		std::string final_path(buffer);
		//~ printf("test name --> %s\n\n", test_name.c_str());		

		//~ bool test2 = sys_utils.check_file_exists("render", test_name);	
		
		stbi_save(final_path.c_str(), width , height, data);
	}else{
		printf("Couldn't find a 'render' directory,\naborting saving... \n");
	}
}

static void saveToBitmap2(std::string file_name, int width, int height, int* red, int* green, int* blue)
{
	//~ printf("RED : %d\n",red[0]);

	FILE *f;
	int w = width;
	int h = height;
	int r, g, b;
	int x, y;
	unsigned char * img = NULL;
	int filesize = 54 + 3*w*h;  //w is your image width, h is image height, both int
	img = (unsigned char *)malloc(3*w*h);
	memset(img,0,3*w*h);


	for(int i=0; i<w; i++)
	{
		for(int j=0; j<h; j++)
		{
			x=i; y=(h-1)-j;

			r = red[(x+y*w)];
			g = green[(x+y*w)];
			b = blue[(x+y*w)];
			if (r > 255) r=255;
			if (g > 255) g=255;
			if (b > 255) b=255;
			img[(x+y*w)*3+2] = (unsigned char)(r);
			img[(x+y*w)*3+1] = (unsigned char)(g);
			img[(x+y*w)*3+0] = (unsigned char)(b);
		}
	}

	unsigned char bmpfileheader[14] = {'B','M', 0,0,0,0, 0,0, 0,0, 54,0,0,0};
	unsigned char bmpinfoheader[40] = {40,0,0,0, 0,0,0,0, 0,0,0,0, 1,0, 24,0};
	unsigned char bmppad[3] = {0,0,0};

	bmpfileheader[ 2] = (unsigned char)(filesize    );
	bmpfileheader[ 3] = (unsigned char)(filesize>> 8);
	bmpfileheader[ 4] = (unsigned char)(filesize>>16);
	bmpfileheader[ 5] = (unsigned char)(filesize>>24);

	bmpinfoheader[ 4] = (unsigned char)(       w    );
	bmpinfoheader[ 5] = (unsigned char)(       w>> 8);
	bmpinfoheader[ 6] = (unsigned char)(       w>>16);
	bmpinfoheader[ 7] = (unsigned char)(       w>>24);
	bmpinfoheader[ 8] = (unsigned char)(       h    );
	bmpinfoheader[ 9] = (unsigned char)(       h>> 8);
	bmpinfoheader[10] = (unsigned char)(       h>>16);
	bmpinfoheader[11] = (unsigned char)(       h>>24);

	f = fopen(file_name.c_str(),"wb");
	fwrite(bmpfileheader,1,14,f);
	fwrite(bmpinfoheader,1,40,f);
	for(int i=0; i<h; i++)
	{
		fwrite(img+(w*(h-i-1)*3),3,w,f);
		fwrite(bmppad,1,(4-(w*3)%4)%4,f);
	}

	free(img);
	fclose(f);
}

static float clampf(float value, float min, float max )
{
	
	if(value > max){

		return max;

	}else if (value < min){

		return min;

	}else{

		return value;
	}

}

Renderer::Renderer()
{

}

int Renderer::init(std::string scene_file_ , std::string options_file_)
{
	scene_file_path_save = scene_file_;
	options_file_path_save = options_file_;

	
	window_width = 640;
	window_height = 480;
	if( SDL_Init(SDL_INIT_EVERYTHING) == 0){
		printf("SDL OK !!!!\n");
	}	
	
	uint32_t WindowFlags = SDL_WINDOW_OPENGL;
	Window = SDL_CreateWindow("Raytracer SDL2", 0, 0, window_width, window_height, WindowFlags);
	assert(Window);
	SDL_GLContext Context = SDL_GL_CreateContext(Window);

	glewInit();
	
	initScene();


	//~ std::cout << "raytracer PROJECT" << std::endl;


	camera.target_position = glm::vec3(0.0, 0.0, 0.0);
	camera.up_vector = glm::vec3(0.0, 0.0, 1.0);
//~ 
	setCamPosFromPolar(camera_u_pos, camera_v_pos, camera_orbit_radius);

	
	default_shader.loadVertexShaderSource("../src/shaders/basic_shader.vert");
	default_shader.loadFragmentShaderSource("../src/shaders/basic_shader.frag");

	default_shader.createShader();
//~ 
	fbo_shader.loadVertexShaderSource("../src/shaders/fbo_shader.vert");
	fbo_shader.loadFragmentShaderSource("../src/shaders/fbo_shader.frag");

	fbo_shader.createShader();


	default_texture.load("../src/res/textures/uvgrid.jpg");
	
	printf("texture Bytes per pixel : %d\n", default_texture.getBPP());
	Light light1;
	light1.position = glm::vec3(4.0, 5.0, 4.0);
	light1.color = Color(1.0, 0.9, 0.9, 1.0);
	light1.intensity = 20.0;
	lights.push_back(light1);

	Light light2;
	light2.position = glm::vec3(-5.0, -3.0, 3.5);
	light2.color = Color(0.9, 0.9, 1.0, 1.0);
	light2.intensity = 15.0;
	lights.push_back(light2);
//~ 
	//~ // materials
	//~ RTMaterial material1;
	//~ material1.color = Color(0.9, 0.0, 0.0, 1.0);
	//~ material1.refl_amount = 0.9;
	//~ materials.push_back(material1);
//~ 
	//~ RTMaterial material2;
	//~ material2.color = Color(1.0,1.0,1.0,1.0);
	//~ material2.refl_amount = 0.3;
	//~ materials.push_back(material2);
//~ 
	//~ RTMaterial material3;
	//~ material3.color = Color(1.0, 1.0, 1.0, 1.0);
	//~ material3.refl_amount = 0.9;
	//~ materials.push_back(material3);


	


	
	//~ printf("render options width --> %d\n", render_options.render_width);
	
	
	
	
}

void Renderer::manageEvents()
{
    SDL_Event Event;
    while (SDL_PollEvent(&Event))
    {
		if (Event.type == SDL_QUIT)
		{
			running = false;
		}else if(( SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT))){
			
			if( Event.type == SDL_MOUSEMOTION)
			{
				//~ printf("mouse motion :\n");
				//~ printf("\tXREL -> %d\n", Event.motion.xrel);
				//~ printf("\tYREL -> %d\n", Event.motion.yrel);
			 
			 
			 
				double rot_speed = 0.01;

				camera_u_pos += (float)Event.motion.xrel * rot_speed;



				camera_v_pos -= (float)Event.motion.yrel * rot_speed;

				if(camera_v_pos < 0.2)
						camera_v_pos = 0.2;
				else if(camera_v_pos > PI-0.2)
						camera_v_pos = PI-0.2;

				//~ printf("delta : %.2f %.2f\n", (float)Event.motion.xrel, (float)Event.motion.yrel);
				//~ printf("upos : %.2f -- vpos %.2f\n", camera_u_pos, camera_v_pos);
				//~ printf("--------------------------------\n");


				setCamPosFromPolar(camera_u_pos, camera_v_pos, camera_orbit_radius, camera_view_center);		
			}else{
				int x, y;
				SDL_GetMouseState(&x, &y);
				printf("left click : %d %d\n",x, y);
				ClickData cd;
				cd.width = 640;
				cd.height = 480;
				cd.x = (double)x;
				cd.y = (double)y;
				Raycaster caster;
				glm::vec3 test_screen = caster.screenToWorld_2(cd, camera);
				printf("screen position : %.3f %.3f %.3f\n", test_screen.x, test_screen.y, test_screen.z);
				
				
			}
		}else if( (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_RIGHT))){
			if( Event.type == SDL_MOUSEMOTION)
			{
				mouse_delta_x = -(float)Event.motion.xrel;
				//~ mouse_old_x = xpos;
				mouse_delta_y = -(float)Event.motion.yrel;
				//~ mouse_old_y = ypos;
		
				glm::mat4 view = glm::lookAt(
					camera.position,
					camera.target_position,
					camera.up_vector
					);
		
				glm::vec3 pan_dir = glm::vec3(mouse_delta_x, -mouse_delta_y, 0.0);
		
				vec_mult_by_matrix(pan_dir, view, true);
				pan_dir = pan_dir - camera.position;
				camera_view_center.x += pan_dir.x * 0.02;
				camera_view_center.y += pan_dir.y * 0.02;
				camera_view_center.z += pan_dir.z * 0.02;
		
				setCamPosFromPolar(camera_u_pos, camera_v_pos, camera_orbit_radius, camera_view_center);				
			}
		}else if(Event.type == SDL_MOUSEWHEEL){
			//~ printf("wheel event\n");
			//~ printf("\twheel x : %d\n", Event.wheel.x);
			//~ printf("\twheel y : %d\n", Event.wheel.y);
			
			camera_orbit_radius += (float)Event.wheel.y * -0.1;
			setCamPosFromPolar(camera_u_pos, camera_v_pos, camera_orbit_radius, camera_view_center);			
		}else if(Event.type == SDL_KEYDOWN){
			switch(Event.key.keysym.scancode){
				case SDL_SCANCODE_F9:{
					//~ printf("RRRRRRRR\n");
					
					printf("--- Starting Rendering... \n");
			
					std::vector<RenderBucket> buckets;
					buckets.clear();
					buckets = createBuckets(32, render_width, render_height);
					renderBuckets( buckets, camera);
					//~ printf("--- Finished Rendering... \n");					
					break;
				}
				case SDL_SCANCODE_R : {
					printf("--- Reloading ? \n");
					initScene();
				}
				case SDL_SCANCODE_S : {
					show_fbo = !show_fbo;
					break;
				}
				case SDL_SCANCODE_ESCAPE:{
					b_cancel_render = true;
				}
				default : 
					break;

			}
			//~ printf("keyboard event\n");
		}
	}		
}


void Renderer::initScene()
{
	kd_nodes.clear();
	meshes.clear();
	materials.clear();
	
	SceneFileLoader scene_loader;
	render_options = scene_loader.loadOptionsFile(options_file_path_save);	
	scene_loader.loadSceneFile(scene_file_path_save, meshes, materials, lights);	
	
	render_width = render_options.render_width;
	render_height = render_options.render_height;
	
	initFBO(render_width,render_height);
	
	kd_polygon_limit = render_options.kd_polygon_limit;	
	
	buildDisplayGeometry();
}
void Renderer::buildKDTree()
{


	for(int mesh_id = 0; mesh_id < meshes.size(); mesh_id++)
	{
		std::vector<Triangle*> tris;
		tris.reserve(meshes[mesh_id].faces.size());

		for (int i = 0; i < meshes[mesh_id].faces.size(); i++)
		{
			glm::vec3 A, B, C;
			A = B = C = glm::vec3(0.0, 0.0, 0.0);

			A = meshes[mesh_id].points[ meshes[mesh_id].faces[i].getVertex(0).point_id ].position;
			B = meshes[mesh_id].points[ meshes[mesh_id].faces[i].getVertex(1).point_id ].position;
			C = meshes[mesh_id].points[ meshes[mesh_id].faces[i].getVertex(2).point_id ].position;

			//~ printf("vec3 value -> %.3f %.3f %.3f\n", A.x, A.y, A.z);

			Triangle* tri_ptr = new Triangle(A, B, C);
			tri_ptr->id = i;
			tris.emplace_back(tri_ptr);

		}

		KDNode * kd_node = new KDNode(kd_polygon_limit);
		kd_node = kd_node->build(tris, 0);
		kd_nodes.push_back(kd_node);
		
	}
	
	if(meshes.size() > 0)
		printf("Created  %d KD Tree(s)\n", (int)meshes.size());
}

void Renderer::collectKDBoungingBoxes(KDNode* node_ptr)
{
	//~ printf("collecting bboxes ???? \n\n");
	kd_bboxes.push_back(node_ptr->bbox);
	if( node_ptr->left->triangles.size() > 0)
	{
		collectKDBoungingBoxes(node_ptr->left);
	}
	if( node_ptr->right->triangles.size() > 0)
	{
		collectKDBoungingBoxes(node_ptr->right);
	}

	//~ printf("collected bboxes \n\n");
}

void Renderer::buildKDTreeBBoxes(std::vector<KDBoundingBox> bboxes)
{
	kdtree_vertices.clear();
	kdtree_indices.clear();

	for (int box_id = 0; box_id < bboxes.size(); box_id++)
	{

		// bottom 4 points
		kdtree_vertices.insert( kdtree_vertices.end(), { bboxes[box_id].min.x, bboxes[box_id].min.y, bboxes[box_id].min.z});
		kdtree_vertices.insert( kdtree_vertices.end(), { bboxes[box_id].max.x, bboxes[box_id].min.y, bboxes[box_id].min.z});
		kdtree_vertices.insert( kdtree_vertices.end(), { bboxes[box_id].max.x, bboxes[box_id].max.y, bboxes[box_id].min.z});
		kdtree_vertices.insert( kdtree_vertices.end(), { bboxes[box_id].min.x, bboxes[box_id].max.y, bboxes[box_id].min.z});

		// top 4 points
		kdtree_vertices.insert( kdtree_vertices.end(), { bboxes[box_id].min.x, bboxes[box_id].min.y, bboxes[box_id].max.z});
		kdtree_vertices.insert( kdtree_vertices.end(), { bboxes[box_id].max.x, bboxes[box_id].min.y, bboxes[box_id].max.z});
		kdtree_vertices.insert( kdtree_vertices.end(), { bboxes[box_id].max.x, bboxes[box_id].max.y, bboxes[box_id].max.z});
		kdtree_vertices.insert( kdtree_vertices.end(), { bboxes[box_id].min.x, bboxes[box_id].max.y, bboxes[box_id].max.z});



		std::vector<unsigned int> indices = {

			0,1,1,2,2,3,3,0,
			4,5,5,6,6,7,7,4,
			0,4,1,5,2,6,3,7
		};

		for (int i = 0; i < indices.size(); i++)
		{
			indices[i] += box_id * 8;
		}

		kdtree_indices.insert(kdtree_indices.end(), indices.begin(), indices.end());


	}


	GLCall(glDeleteBuffers(1, &kdtree_vbo));
	GLCall(glGenBuffers(1,&kdtree_vbo));


	GLCall(glBindBuffer(GL_ARRAY_BUFFER, kdtree_vbo));
	GLCall(glBufferData(GL_ARRAY_BUFFER, sizeof(float)* kdtree_vertices.size(), kdtree_vertices.data(), GL_STATIC_DRAW));
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));

	GLCall(glDeleteBuffers(1, &kdtree_ibo));
	GLCall(glGenBuffers(1,&kdtree_ibo));

	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, kdtree_ibo));
	GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int)* kdtree_indices.size(), kdtree_indices.data(), GL_STATIC_DRAW));
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));

}

void Renderer::displayKDTree()
{

	GLCall(glBindBuffer(GL_ARRAY_BUFFER, kdtree_vbo));
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, kdtree_ibo));
	GLCall(glEnableVertexAttribArray(0));

	GLCall(glVertexAttribPointer(0, 3, GL_FLOAT, false, 0, 0));


	GLCall(glDrawElements(GL_LINES, kdtree_indices.size() , GL_UNSIGNED_INT, nullptr ));

	GLCall(glDisableVertexAttribArray(0));
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));

}

Color Renderer::shade(Mesh& mesh, Face& face, RTMaterial* material, HitData& hit_data, int depth/* = 0*/)
{
	Raycaster raycaster;

	Color clr(0.0,0.0,0.0,1.0); //= material->color;
	
	// interpolate normal from barycentric coordinates

	glm::vec3 normal;
	glm::vec3 bary =  hit_data.barycentric_coords; //raycaster.cartesian_to_barycentric(hit_data.position, A, B, C);
	
	glm::vec3 normalA = mesh.points[face.getVertex(0).point_id].normal;
	glm::vec3 normalB = mesh.points[face.getVertex(1).point_id].normal;
	glm::vec3 normalC = mesh.points[face.getVertex(2).point_id].normal;
	
	normal = (normalA * bary.x) + (normalB * bary.y) + (normalC * bary.z);
	
	

	
	glm::vec2 uvA = mesh.points[face.getVertex(0).point_id].t_coords;
	glm::vec2 uvB = mesh.points[face.getVertex(1).point_id].t_coords;
	glm::vec2 uvC = mesh.points[face.getVertex(2).point_id].t_coords;
	
	
	glm::vec2 uv = (uvA * bary.x) + (uvB * bary.y) + (uvC * bary.z);	
	Color diff_texture_color = sampleTexture( material->diff_texture, uv);
	
	//~ printf("shading uv : %.3f %.3f \n", uv.x, uv.y);
	
	glm::vec3 view_dir = glm::normalize( (hit_data.position - hit_data.ray_origin) );
	//~ glm::vec3 view_dir = hit_data.position - hit_data.ray_origin ;

	float diff_amount = 1.0;
	
	
//~ 
	//~ clr.r = diff_texture_color.r;
	//~ clr.g = diff_texture_color.g;
	//~ clr.b = diff_texture_color.b;
	
	for (int i = 0; i < lights.size(); i++)
	{

		glm::vec3 light_dir = lights[i].position - hit_data.position;
		light_dir = glm::normalize(light_dir);
		float light_dist = glm::distance( lights[i].position, hit_data.position);
		float dot = glm::dot(glm::normalize(normal) , light_dir);

		diff_amount = dot;
		diff_amount *= 1.0/ (light_dist * light_dist);
		diff_amount *= lights[i].intensity;
		//~ dot *= 10.0;



		
		// shadow second attempt 
		float shadow_amount = 0.0;
		
		//cast a ray from hit_data.position
		
		Ray shadow_ray;
		shadow_ray.origin = hit_data.position;
		shadow_ray.direction = glm::vec3((lights[i].position - hit_data.position));
		shadow_ray = offset_ray(shadow_ray, 0.0001);
		
		
		
		std::vector<HitData> shadow_hit_datas;
		bool shadow_hit = raycaster.intersectKDNodes(shadow_ray, kd_nodes, shadow_hit_datas, true);
		
		if(shadow_hit){
			if(shadow_hit_datas.size() > 0){
				for (int hit_id = 0; hit_id < shadow_hit_datas.size(); hit_id++)
				{
					float hit_dist = glm::distance(hit_data.position, shadow_hit_datas[hit_id].position);
					
					if( hit_dist < light_dist ) 
					{
						shadow_amount = 1.0;
						break;
					}
				}
				//~ shadow_amount = 0.0;
			}
		}
		
		float dot2 = clampf(glm::dot(glm::normalize(normal) , view_dir),-1.0, 0.0);

		clr.r += clampf(diff_texture_color.r * diff_amount * mesh.material->color.r *  lights[i].color.r  * (1.0-shadow_amount), 0.0,1.0); //  * (-dot2)
		clr.g += clampf(diff_texture_color.g * diff_amount * mesh.material->color.g *  lights[i].color.g  * (1.0-shadow_amount) , 0.0,1.0);
		clr.b += clampf(diff_texture_color.b * diff_amount * mesh.material->color.b *  lights[i].color.b  * (1.0-shadow_amount) , 0.0,1.0);
	}


	if(material->refl_amount > 0.0 && depth < render_options.reflection_limit)
	{
		// reflection ray
		Ray refl_ray;
		refl_ray.origin = hit_data.position;

		refl_ray.direction = glm::reflect( view_dir , normal * 1.0f);

		refl_ray = offset_ray(refl_ray, 0.0001);

		std::vector<HitData> refl_hit_datas;
		depth++;
		bool refl_hit = raycaster.intersectKDNodes(refl_ray, kd_nodes, refl_hit_datas);
		float dot2 = clampf(glm::dot(glm::normalize(normal) * -1.0f , view_dir),0.0, 1.0);
		dot2 = pow(dot2, 2.0);
		if(refl_hit_datas.size() > 0)
		{
			
			Color refl_clr = shade(
				meshes[refl_hit_datas[0].mesh_id],
				meshes[refl_hit_datas[0].mesh_id].faces[refl_hit_datas[0].face_id],
				meshes[refl_hit_datas[0].mesh_id].material,
				refl_hit_datas[0],
				depth);

			clr.r += refl_clr.r * material->refl_amount * (1.0-(dot2));
			clr.g += refl_clr.g * material->refl_amount * (1.0-(dot2));
			clr.b += refl_clr.b * material->refl_amount * (1.0-(dot2));
		}else{
			//~ printf("set background color\n");
			clr.r += render_options.background_color.r * material->refl_amount * (1.0-(dot2));
			clr.g += render_options.background_color.g * material->refl_amount * (1.0-(dot2));
			clr.b += render_options.background_color.b * material->refl_amount * (1.0-(dot2));
		}
	}
	
	
	//clamp final color
	clr.r = clampf(clr.r, 0.0, 1.0);
	clr.g = clampf(clr.g, 0.0, 1.0);
	clr.b = clampf(clr.b, 0.0, 1.0);
	clr.a = 1.0;
	
	return  clr;
}

Color Renderer::sampleTexture(Texture& texture, glm::vec2 t_coords)
{
	
	Color clr;
	
	if(texture.is_valid)
	{
		int t_bpp = texture.getBPP();
		int t_width = texture.getWidth();
		int t_height = texture.getHeight();
		
		
		t_coords.x = t_coords.x - floor(t_coords.x);
		t_coords.y = t_coords.y - floor(t_coords.y);
		
		
		
		int pix_x = (int)(t_coords.x * (t_width));
		int pix_y = (int)(t_coords.y * (t_height));
		
		clr.r = (double)texture.data[(pix_y * t_width + pix_x) * 4 ] / 256.0;
		clr.g = (double)texture.data[(pix_y * t_width + pix_x) * 4 + 1] / 256.0;
		clr.b = (double)texture.data[(pix_y * t_width + pix_x) * 4 + 2] / 256.0;
		clr.a = 1.0;
	}else{
		clr.r = 1.0;
		clr.g = 1.0;
		clr.b = 1.0;
		clr.a = 1.0;
	}
	return clr;
}

void Renderer::renderBucket(RenderBucket& bucket, Camera& camera)
{
	Raycaster raycaster;

	ClickData click_data;
	click_data.width = 640;
	click_data.height = 480;


	std::vector<Ray> rays;
	rays.clear();
	rays.reserve(bucket.width * bucket.height);


	// cast all rays
	for (int y = bucket.y; y < bucket.y+bucket.height; y++)
	{
		// -1.0 is important !!!! in x and y
		click_data.y = (((float)click_data.height) / (float)(bucket.render_height) * ((float)(y) + 0.0)); // + 0.5 to be in the middle of the pixel
		//~ click_data.y = ((float)y) + 0.5 ; 
		
		for (int x = bucket.x; x < bucket.x+bucket.width; x++)
		{
			click_data.x = (((float)click_data.width) / (float)(bucket.render_width) * ((float)(x) + 0.0)); // + 0.5 to be in the middle of the pixel
			//~ click_data.x = ((float)x) + 0.5;
			bool hit_tri = false;
			//~ HitData hit_data;
			//~ hit_tri = raycaster.intersectMeshes(click_data, camera, meshes, hit_data);

			Ray ray = raycaster.castRay(click_data, camera);
			rays.emplace_back(ray);
		}
	}


	// then intersect
	for (int i = 0; i < rays.size(); i++)
	{
			bool hit_tri = false;
			std::vector<HitData> hit_datas;

			bool hit2 = raycaster.intersectKDNodes(rays[i], kd_nodes, hit_datas);
			if( hit2 )
			{

				if( hit_datas.size() > 0)
				{
					hit_tri = true;
				}
			}
			
			long int index = (bucket.x + (i%bucket.width)) + (bucket.y + i/bucket.width) * bucket.render_width;

			if(hit_tri)
			{

				Color clr = shade(meshes[hit_datas[0].mesh_id], meshes[hit_datas[0].mesh_id].faces[ hit_datas[0].face_id], meshes[hit_datas[0].mesh_id].material, hit_datas[0]);
				//~ float dist = glm::distance(camera.position, hit_datas[0].position);
				//~ int depth = 255 - (int)(clampf((float)dist, 0.0, 5.0) / 5.0 * 255.0);

				render_buffer_data[(index * 4)+0] = (unsigned char)((int)(clr.r*255.0));
				render_buffer_data[(index * 4)+1] = (unsigned char)((int)(clr.g*255.0));
				render_buffer_data[(index * 4)+2] = (unsigned char)((int)(clr.b*255.0));


			}else{
				render_buffer_data[(index * 4)+0] = (unsigned char)0;
				render_buffer_data[(index * 4)+1] = (unsigned char)0;
				render_buffer_data[(index * 4)+2] = (unsigned char)0;

			}
	}

	bucket.finished = true;

}

void Renderer::renderBuckets(std::vector<RenderBucket>& buckets, Camera& camera)
{
	show_fbo = true;
	initFBO(render_width, render_height);

	std::clock_t start;
	double duration = 0.0;

	start = std::clock();

	TaskQueue<RenderTask> queue(4);

	for (int i = 0; i < buckets.size(); i++)
	{
		queue.QueueTask(RenderTask(this, buckets[i]));
	}




	std::vector<RenderTaskResult> __results;
    while (queue.TasksCompleted()){
      RenderTaskResult __result = queue.GetCompletedTaskResult();
      __results.push_back(__result);
    }

	int old_num = -1;
	std::cout << "\n";
	while (queue.NumPendingTasks()){

		//~ LOG(INFO) << "All tasks submitted, waiting for last tasks to complete... \r\r";
		boost::this_thread::sleep(boost::posix_time::milliseconds(100));
		
		if(b_cancel_render){
			queue.Stop();
			b_cancel_render = false;
			break;
		}else{
			if(old_num != queue.NumPendingTasks()){
				std::cout  << "\r"  << "Rendering Tasks : " << (buckets.size() - queue.NumPendingTasks()) << " / " << buckets.size() << "      " << std::flush;
				old_num = queue.NumPendingTasks();
				displayScene();
			}
		}
	}

	std::cout << "\n";
    duration = ( std::clock() - start ) / (double) CLOCKS_PER_SEC / 4.0;
    
    int hours = (int)duration / (60 * 60);
    int minutes = (int)(duration - hours * 60 * 60) / (60);
    int seconds = ((int)duration % (60*60)) % 60;
    
    //~ printf("Frame duration : %.3f\n", duration);
    printf("Frame Rendering Time : %d hrs %d mns %d secs\n", hours , minutes, seconds);


	
	
	// stbi save test

	unsigned char data[render_width*render_height*3];
	int index = 0;
	for (int i = 0; i < render_width*render_height; i++)
	{
		data[index++] = (int)render_buffer_data[i * 4 + 0];
		data[index++] = (int)render_buffer_data[i * 4 + 1];
		data[index++] = (int)render_buffer_data[i * 4 + 2];
	}


	save_render_to_file(render_width, render_height, data);
	
	
	/////
	/////	
}

std::vector<RenderBucket> Renderer::createBuckets(int size, int r_width, int r_height)
{
	std::vector<RenderBucket> buckets;

	for (int y = 0; y < r_height; y += size)
	{
		for (int x = 0; x < r_width; x += size)
		{
			RenderBucket b;
			b.x = x;
			b.y = y;
			if( x + size > r_width){
				b.width = size - (x+size - r_width);
			}else{
				b.width = size;
			}

			if( y + size > r_height){
				b.height = size - (y+size - r_height);
			}else{
				b.height = size;
			}

			b.render_width = r_width;
			b.render_height = r_height;

			buckets.push_back(b);
		}
	}

	return buckets;
}

void Renderer::setCamPosFromPolar(float u, float v, float _radius, glm::vec3 center)
{
        camera.position.x = (sin(u)* sin(v) * _radius) + center.x;
        camera.position.y = (cos(u)* sin(v) * _radius) + center.y;
        camera.position.z = (cos(v) * _radius) + center.z;

        camera.target_position = center;

        camera.up_vector = glm::vec3(0.0, 0.0, 1.0);
}

void Renderer::initFBO(int width, int height)
{




	int r_width = width;
	int r_height = height;

	GLCall(glDeleteBuffers(1, &fbo_vbo));
	GLCall(glGenBuffers(1, &fbo_vbo));

	int w_width = window_width;
	int w_height = window_height;
	

	//~ if(r_width > w_width)r_width = w_width;
	//~ if(r_height > w_height)r_height = w_height;

	float fbo_min_x = -( (float)r_width / (float)w_width);
	if(fbo_min_x < -1.0) fbo_min_x = -1.0;
	float fbo_min_y = -( (float)r_height / (float)w_height);
	if(fbo_min_y < -1.0) fbo_min_y = -1.0;
	float fbo_max_x = ( (float)r_width / (float)w_width);
	if(fbo_max_x > 1.0) fbo_max_x = 1.0;
	float fbo_max_y = ( (float)r_height / (float)w_height);
	if(fbo_max_y > 1.0) fbo_max_y = 1.0;

	float fbo_vertices[6*3 + 6*2] = {
		// position                  //uvs: note --> v coords is flipped
		fbo_min_x,fbo_min_y, 0.0,    0.0, 1.0,
		fbo_max_x,fbo_min_y, 0.0,    1.0, 1.0,
		fbo_max_x,fbo_max_y, 0.0,    1.0, 0.0,

		fbo_min_x,fbo_min_y, 0.0,    0.0, 1.0,
		fbo_max_x,fbo_max_y, 0.0,    1.0, 0.0,
		fbo_min_x,fbo_max_y, 0.0,    0.0, 0.0

	};

	GLCall(glBindBuffer(GL_ARRAY_BUFFER, fbo_vbo));
	GLCall(glBufferData(GL_ARRAY_BUFFER, sizeof(float) * (6*3 + 6*2), fbo_vertices, GL_DYNAMIC_DRAW));
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));



	render_buffer_data.clear();
	render_buffer_data.reserve(r_width * r_height * 4);
	for (long int i = 0; i < r_width * r_height * 4; i+=4)
	{
		float x = (float)((i/4) % r_width)/ (float)r_width;
		float y = (float)((i/4) / r_width) / (float)r_height;

		render_buffer_data.emplace_back((unsigned char)(x * 255));
		render_buffer_data.emplace_back((unsigned char)(y * 255));
		render_buffer_data.emplace_back((unsigned char) 0);
		render_buffer_data.emplace_back((unsigned char) 255);
	}


	//~ GLuint texture_map;
	GLCall(glDeleteTextures(1, &fbo_texture_id));
	GLCall(glGenTextures(1, &fbo_texture_id));
	GLCall(glBindTexture(GL_TEXTURE_2D, fbo_texture_id));

	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER));

	//~ GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 320, 240, 0, GL_RGBA, GL_UNSIGNED_BYTE, fbo_data));
	GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, r_width, r_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr));

	GLCall(glBindTexture(GL_TEXTURE_2D, 0));
}

void Renderer::drawFBO(int r_width, int r_height)
{
	//~ int r_width = 320;
	//~ int r_height = 240;
	GLCall(glActiveTexture(GL_TEXTURE0));
	GLCall(glBindTexture(GL_TEXTURE_2D, fbo_texture_id));
	GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, r_width, r_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, render_buffer_data.data()));
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, fbo_vbo));

	GLCall(glEnableVertexAttribArray(0));
	GLCall(glEnableVertexAttribArray(1));
	GLCall(glVertexAttribPointer(0,3, GL_FLOAT, GL_FALSE, sizeof(float) * 5, 0));
	GLCall(glVertexAttribPointer(1,2, GL_FLOAT, GL_FALSE, sizeof(float) * 5, (void*)(sizeof(float) * 3)));



	GLCall(glDrawArrays(GL_TRIANGLES, 0, 6));


	GLCall(glDisableVertexAttribArray(0));
	GLCall(glDisableVertexAttribArray(1));
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
	GLCall(glBindTexture(GL_TEXTURE_2D, 0));
}

void Renderer::buildDisplayGeometry()
{
	vbos.clear();
	ibos.clear();
	geo_data_array.clear();

	for (int i = 0; i < meshes.size(); i++)
	{
		meshes[i].material = &materials[i];
		OGL_geometry_data geo_data;
		for(int pt_id = 0; pt_id < meshes[i].points.size(); pt_id++)
		{
			//~ printf("t_coords --> %.3f %.3f \n",meshes[i].points[pt_id].t_coords.x, meshes[i].points[pt_id].t_coords.y );
			glm::vec3 point_pos = meshes[i].points[pt_id].position;
			glm::vec3 point_normal = meshes[i].points[pt_id].normal;
			glm::vec2 t_coords = meshes[i].points[pt_id].t_coords;
			geo_data.vertices.insert(
				geo_data.vertices.end(), {
					point_pos.x, point_pos.y, point_pos.z,
					point_normal.x, point_normal.y, point_normal.z,
					t_coords.x, t_coords.y
				});
		}

		int index = 0;
		for( int face_id = 0; face_id < meshes[i].faces.size(); face_id++)
		{

			if( meshes[i].faces[face_id].getNumVertices() == 3)
			{
				//~ printf("building triangle \n");
				geo_data.indices.insert(geo_data.indices.end(),{
						meshes[i].faces[face_id].getVertex(0).point_id,
						meshes[i].faces[face_id].getVertex(1).point_id,
						meshes[i].faces[face_id].getVertex(2).point_id
				});

			}

		}

		//~ geo_data.indices = indices;
		geo_data_array.push_back(geo_data);

		vbos.push_back(0);
		GLCall(glDeleteBuffers(1, &vbos[i]));
		GLCall(glGenBuffers(1, &vbos[i]));
		GLCall(glBindBuffer(GL_ARRAY_BUFFER, vbos[i]));
		GLCall(glBufferData(GL_ARRAY_BUFFER, sizeof(float)* geo_data.vertices.size(), geo_data.vertices.data(), GL_STATIC_DRAW));
		GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));



		ibos.push_back(0);
		GLCall(glDeleteBuffers(1, &ibos[i]));
		GLCall(glGenBuffers(1, &ibos[i]));
		GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibos[i]));
		GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int)* geo_data.indices.size(), geo_data.indices.data(), GL_STATIC_DRAW));
		GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));

	}

	//~ printf("vbos[0] : %d\n", vbos[0]);
	//~ printf("ibos[0] : %d\n", ibos[0]);

	if(meshes.size() > 0)
	{
		//~ printf("----- BUILDING KD TREE\n");
		buildKDTree();
		//~ printf("KDnodes num : %d\n", kd_nodes.size());
		//~ collectKDBoungingBoxes(kd_nodes[0]);
		//~ printf("BBoxes vector size is %d\n", kd_bboxes.size());
		//~ buildKDTreeBBoxes(kd_bboxes);
	}

}

void Renderer::displayScene()
{
	
	manageEvents();
	


	GLCall(glDisable(GL_CULL_FACE));
	GLCall(glEnable(GL_DEPTH_TEST));

	
	GLCall(glViewport(0,0,window_width, window_height));
	
	GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
	GLCall(glClearColor(0.2,0.5,0.2,1.0));		
	
	//~ printf("drawing %d\n", temp_inc_test++);
	camera.setProjection(45.0f * (float)PI / 180.0f, (float)window_width / (float)window_height, 0.01f, 100.0f);



	glm::mat4 model = glm::mat4(1.0f);
	glm::mat4 view = glm::mat4(1.0f);



	view *= glm::lookAt(
		camera.position, //glm::vec3(0.0,  0.0, 3.0),
		camera.target_position, //glm::vec3(0.0,  0.0, 0.0),
		camera.up_vector //glm::vec3(0.0,  1.0, 0.0)
	);

	default_shader.useProgram();
	GLCall(glUniformMatrix4fv(glGetUniformLocation(default_shader.m_id, "model"), 1, GL_FALSE, glm::value_ptr(model)));
	GLCall(glUniformMatrix4fv(glGetUniformLocation(default_shader.m_id, "projection"), 1, GL_FALSE, glm::value_ptr(camera.projection)));
	GLCall(glUniformMatrix4fv(glGetUniformLocation(default_shader.m_id, "view"), 1, GL_FALSE, glm::value_ptr(view)));
	


	// send lights data to opengl shader


	float light_positions[6] = { 
		(float)lights[0].position.x, (float)lights[0].position.y, (float)lights[0].position.z,
		(float)lights[1].position.x, (float)lights[1].position.y, (float)lights[1].position.z		
	};
	GLCall(
		glUniform3fv(glGetUniformLocation(default_shader.m_id, "u_light_positions"), 1, light_positions)
	);

	for (int i = 0; i < meshes.size(); i++)
	{
		//~ printf("drawing meshe %d\n", i);
		GLCall(glUniform1i(glGetUniformLocation(default_shader.m_id,"u_tex"), 0));
		meshes[i].material->diff_texture.bind();
		
		//~ GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, default_texture.getWidth(), default_texture.getHeight(), 0, GL_RGBA, GL_UNSIGNED_BYTE, default_texture.data.data()));
		
		GLCall(glUniform4f(glGetUniformLocation(default_shader.m_id, "u_color"),
			meshes[i].material->color.r,
			meshes[i].material->color.g,
			meshes[i].material->color.b,
			1.0
		));

		
		GLCall(glBindBuffer(GL_ARRAY_BUFFER, vbos[i]));
		GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibos[i]));
		GLCall(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, 0));
		GLCall(glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (void*)(sizeof(float)*3)));
		GLCall(glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (void*)(sizeof(float)*6)));
		GLCall(glEnableVertexAttribArray(0));
		GLCall(glEnableVertexAttribArray(1));
		GLCall(glEnableVertexAttribArray(2));


		GLCall(glDrawElements(GL_TRIANGLES, geo_data_array[i].indices.size(), GL_UNSIGNED_INT, nullptr));

		GLCall(glDisableVertexAttribArray(0));
		GLCall(glDisableVertexAttribArray(1));
		GLCall(glDisableVertexAttribArray(2));
		GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
		GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
		
		
		meshes[i].material->diff_texture.unbind();
	
	}
//~ 



	//~ displayKDTree();


	GLCall(glUseProgram(0));

	if( show_fbo )
	{

		GLCall(glDisable(GL_DEPTH_TEST));

		fbo_shader.useProgram();
		drawFBO(render_width,render_height);

		GLCall(glUseProgram(0));
	}


	SDL_GL_SwapWindow(Window);
	SDL_Delay(1000/60);

}

bool Renderer::shouldClose()
{
	return false;
}

//~ void Renderer::cursor_pos_callback(GLFWwindow* window, double xpos, double ypos)
//~ {
//~ 
	//~ Renderer* app = static_cast<Renderer*>(glfwGetWindowUserPointer(window));
//~ 
	//~ if(app->left_mouse_button_down)
	//~ {
//~ 
		//~ app->mouse_delta_x = app->mouse_old_x - xpos;
		//~ app->mouse_old_x = xpos;
		//~ app->mouse_delta_y = app->mouse_old_y - ypos;
		//~ app->mouse_old_y = ypos;
//~ 
//~ 
		//~ double rot_speed = 0.01;
//~ 
		//~ app->camera_u_pos -= app->mouse_delta_x * rot_speed;
//~ 
//~ 
//~ 
		//~ app->camera_v_pos += app->mouse_delta_y * rot_speed;
//~ 
		//~ if(app->camera_v_pos < 0.2)
				//~ app->camera_v_pos = 0.2;
		//~ else if(app->camera_v_pos > PI-0.2)
				//~ app->camera_v_pos = PI-0.2;
//~ 
		//~ printf("delta : %.2f %.2f\n", app->mouse_delta_x, app->mouse_delta_y);
		//~ printf("upos : %.2f -- vpos %.2f\n", app->camera_u_pos, app->camera_v_pos);
		//~ printf("--------------------------------\n");
//~ 
//~ 
		//~ app->setCamPosFromPolar(app->camera_u_pos, app->camera_v_pos, app->camera_orbit_radius, app->camera_view_center);
//~ 
	//~ }else if(app->right_mouse_button_down){
//~ 
		//~ app->mouse_delta_x = app->mouse_old_x - xpos;
		//~ app->mouse_old_x = xpos;
		//~ app->mouse_delta_y = app->mouse_old_y - ypos;
		//~ app->mouse_old_y = ypos;
//~ 
		//~ glm::mat4 view = glm::lookAt(
			//~ app->camera.position,
			//~ app->camera.target_position,
			//~ app->camera.up_vector
			//~ );
//~ 
		//~ glm::vec3 pan_dir = glm::vec3(app->mouse_delta_x, -app->mouse_delta_y, 0.0);
//~ 
		//~ vec_mult_by_matrix(pan_dir, view, true);
		//~ pan_dir = pan_dir - app->camera.position;
		//~ app->camera_view_center.x += pan_dir.x * 0.02;
		//~ app->camera_view_center.y += pan_dir.y * 0.02;
		//~ app->camera_view_center.z += pan_dir.z * 0.02;
//~ 
		//~ app->setCamPosFromPolar(app->camera_u_pos, app->camera_v_pos, app->camera_orbit_radius, app->camera_view_center);
	//~ }
//~ 
//~ }

//~ void Renderer::mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
//~ {
	//~ Renderer* app = static_cast<Renderer*>(glfwGetWindowUserPointer(window));
//~ 
	//~ if(button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
	//~ {
		//~ app->left_mouse_button_down = true;
//~ 
		//~ double x_pos, y_pos;
		//~ glfwGetCursorPos(window, &x_pos, &y_pos);
		//~ app->mouse_old_x = x_pos;
		//~ app->mouse_old_y = y_pos;
//~ 
		//~ int width, height;
		//~ glfwGetFramebufferSize(window, &width, &height);
//~ 
//~ 
//~ 
		//~ // raycast test
//~ 
		//~ ClickData click_data;
//~ 
		//~ click_data.x = x_pos;
		//~ click_data.y = y_pos;
		//~ click_data.width = width;
		//~ click_data.height = height;
//~ 
		//~ Raycaster raycaster;
//~ 
		//~ Ray ray = raycaster.castRay(click_data, app->camera);
		//~ std::vector<HitData> hit_datas;
		//~ bool hit2 = raycaster.intersectKDNodes(ray, app->kd_nodes,  hit_datas);
		//~ if( hit2 ){
			//~ printf("hit bbox !!!!!!!!!!\n");
//~ 
			//~ std::sort(hit_datas.begin(), hit_datas.end(), [app](HitData data1 , HitData data2){
				//~ float dist1 = glm::distance(data1.position, app->camera.position);
				//~ float dist2 = glm::distance(data2.position, app->camera.position);
				//~ return dist1 < dist2;
			//~ });
			//~ if( hit_datas.size() > 0)
			//~ {
				//~ printf("polygon hit --> %d\n", hit_datas[0].face_id);
				//~ 
				//~ Face f = app->meshes[hit_datas[0].mesh_id].faces[hit_datas[0].face_id];
				//~ glm::vec3 A = app->meshes[hit_datas[0].mesh_id].points[f.getVertex(0).point_id].position;
				//~ glm::vec3 B = app->meshes[hit_datas[0].mesh_id].points[f.getVertex(1).point_id].position;
				//~ glm::vec3 C = app->meshes[hit_datas[0].mesh_id].points[f.getVertex(2).point_id].position;
				//~ 
				//~ glm::vec3 bary = raycaster.cartesian_to_barycentric(hit_datas[0].position, A, B, C);
				//~ 
				//~ printf("barycentric coords : %.3f %.3f %.3f \n", bary.x, bary.y, bary.z);
			//~ }
		//~ }
//~ 
//~ 
//~ 
//~ 
//~ 
	//~ }else if(button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE)
	//~ {
		//~ app->left_mouse_button_down = false;
	//~ }else if(button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS)
	//~ {
		//~ double x_pos, y_pos;
		//~ glfwGetCursorPos(window, &x_pos, &y_pos);
		//~ app->mouse_old_x = x_pos;
		//~ app->mouse_old_y = y_pos;
//~ 
		//~ app->right_mouse_button_down = true;
//~ 
//~ 
	//~ }else if(button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_RELEASE)
	//~ {
//~ 
		//~ app->right_mouse_button_down = false;
	//~ }
//~ }
//~ 
//~ void Renderer::char_mods_callback(GLFWwindow* window, unsigned int key, int action)
//~ {
	//~ Renderer* app = static_cast<Renderer*>(glfwGetWindowUserPointer(window));
//~ 
	//~ if( (char)key == 'B' ) // B
	//~ {
		//~ // saveToBitmap2();
	//~ }else if( (char)key == 'r' ){
//~ 
		//~ printf("Starting Rendering... \n");
//~ 
		//~ std::vector<RenderBucket> buckets;
		//~ buckets = app->createBuckets(32, app->render_width, app->render_height);
		//~ app->renderBuckets( buckets, app->camera);
		//~ printf("DONE... \n");
	//~ }else if( (char)key == 's' ){
		//~ app->show_fbo = !app->show_fbo;
	//~ }
//~ 
//~ }

//~ void Renderer::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
//~ {
	//~ Renderer* app = static_cast<Renderer*>(glfwGetWindowUserPointer(window));
    //~ printf("cur key is %d\n" ,scancode);
    //~ if ((key == GLFW_KEY_LEFT  || key == GLFW_KEY_RIGHT ) && action == GLFW_PRESS){
			//~ printf("GLFW_KEY_LEFT %d\n" ,scancode);
//~ 
			//~ glm::mat4 view = glm::lookAt(
				//~ app->camera.position,
				//~ app->camera.target_position,
				//~ app->camera.up_vector
				//~ );
//~ 
			//~ glm::vec3 x_template = glm::vec3(1.0, 0.0, 0.0);
//~ 
			//~ vec_mult_by_matrix(x_template, view, true);
			//~ x_template = x_template - app->camera.position;
			//~ app->camera_view_center.x += x_template.x * 0.1 * (key == GLFW_KEY_RIGHT ? 1.0 : -1.0) ;
			//~ app->camera_view_center.y += x_template.y * 0.1 * (key == GLFW_KEY_RIGHT ? 1.0 : -1.0) ;
			//~ app->camera_view_center.z += x_template.z * 0.1 * (key == GLFW_KEY_RIGHT ? 1.0 : -1.0) ;
//~ 
			//~ app->setCamPosFromPolar(app->camera_u_pos, app->camera_v_pos, app->camera_orbit_radius, app->camera_view_center);
	//~ }if( key == GLFW_KEY_ESCAPE && action == GLFW_PRESS){
		//~ printf("escape \n");
		//~ app->b_cancel_render = true;
	//~ }
//~ 
//~ }

//~ void Renderer::scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
//~ {
	//~ Renderer* app = static_cast<Renderer*>(glfwGetWindowUserPointer(window));
	
	//~ printf("--------------\n");
	//~ printf("\tx offset : %.3f\n", xoffset);
	//~ printf("\ty offset : %.3f\n", yoffset);
	//~ 
	//~ 
	//~ app->camera_orbit_radius += yoffset * -0.1;
	//~ app->setCamPosFromPolar(app->camera_u_pos, app->camera_v_pos, app->camera_orbit_radius, app->camera_view_center);
//~ }



