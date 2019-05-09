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

static void stbi_save(int w, int h, unsigned char* data)
{
	//~ int stbi_write_jpg(char const *filename, int w, int h, int comp, const void *data, int quality);

	//~ int saved = stbi_write_jpg("stbi_test.jpg", w, h, 3, data,100);
	int saved = stbi_write_png("stbi_test.png", w, h, 3, data, w * 3 * sizeof(unsigned char));
	if(saved){
		printf("saved !!! \n");
	}else{
		printf("NOT saved !!! \n");
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

Mesh Renderer::loadMesh(std::string path)
{

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

		KDNode * kd_node = new KDNode();
		kd_node = kd_node->build(tris, 0);
		kd_nodes.push_back(kd_node);
		printf("created KDNode !!!!!\n");
	}
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

	//~ GLCall(glPointSize(10));
	//~ GLCall(glDrawArrays(GL_POINTS,0, 8));

	GLCall(glDrawElements(GL_LINES, kdtree_indices.size() , GL_UNSIGNED_INT, nullptr ));

	GLCall(glDisableVertexAttribArray(0));
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));

	//~ printf(" Node num triangles --> %d\n", node_ptr->triangles.size());

}

Color Renderer::shade(Mesh& mesh, Face& face, RTMaterial material, HitData& hit_data, int depth/* = 0*/)
{
	Raycaster raycaster;

	Color clr(0.0,0.0,0.0,1.0); //= material.color;
	glm::vec3 normal = mesh.points[face.getVertex(1).point_id].normal;
	glm::vec3 view_dir = glm::normalize( (hit_data.position - hit_data.ray_origin) );


	for (int i = 0; i < lights.size(); i++)
	{

		glm::vec3 light_dir = lights[i].position - hit_data.position;
		light_dir = glm::normalize(light_dir);
		float light_dist = glm::distance( lights[i].position, hit_data.position);
		float dot = glm::dot(glm::normalize(normal) , light_dir);

		dot *= 1.0/ (light_dist * light_dist);
		dot *= lights[i].intensity;
		//~ dot *= 10.0;


		// shadow second attempt 
		float shadow_amount = 0.0;
		
		//cast a ray from hit_data.position
		
		Ray shadow_ray;
		shadow_ray.origin = hit_data.position;
		shadow_ray.direction = glm::vec3((lights[i].position - hit_data.position));
		shadow_ray = offset_ray(shadow_ray, 0.001);
		
		
		
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
		
		
		/////


		//~ clr.r = clampf(normal.x, 0.0,1.0);
		//~ clr.g = clampf(normal.y, 0.0,1.0);
		//~ clr.b = clampf(normal.z, 0.0,1.0);
		clr.r += clampf(dot * mesh.material.color.r *  lights[i].color.r  * (1.0-shadow_amount), 0.0,1.0);
		clr.g += clampf(dot * mesh.material.color.g *  lights[i].color.g  * (1.0-shadow_amount), 0.0,1.0);
		clr.b += clampf(dot * mesh.material.color.b *  lights[i].color.b  * (1.0-shadow_amount), 0.0,1.0);
	}

	if(material.refl_amount > 0.0 && depth < 5)
	{
		// reflection ray
		Ray refl_ray;
		refl_ray.origin = hit_data.position;

		refl_ray.direction = glm::reflect( view_dir , normal);

		refl_ray = offset_ray(refl_ray, 0.001);

		std::vector<HitData> refl_hit_datas;
		depth++;
		bool refl_hit = raycaster.intersectKDNodes(refl_ray, kd_nodes, refl_hit_datas);

		if(refl_hit_datas.size() > 0)
		{
			Color refl_clr = shade(
				meshes[refl_hit_datas[0].mesh_id],
				meshes[refl_hit_datas[0].mesh_id].faces[refl_hit_datas[0].face_id],
				meshes[refl_hit_datas[0].mesh_id].material,
				refl_hit_datas[0],
				depth);

			clr.r += refl_clr.r * material.refl_amount;
			clr.g += refl_clr.g * material.refl_amount;
			clr.b += refl_clr.b * material.refl_amount;
		}
	}
	
	
	//clamp final color
	clr.r = clampf(clr.r, 0.0, 1.0);
	clr.g = clampf(clr.g, 0.0, 1.0);
	clr.b= clampf(clr.b, 0.0, 1.0);
	clr.a = clampf(clr.r, 0.0, 1.0);
	
	return  clr;
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
		click_data.y = ((float)click_data.height / (float)bucket.render_height * (float)(y));

		for (int x = bucket.x; x < bucket.x+bucket.width; x++)
		{
			click_data.x = ((float)click_data.width / (float)bucket.render_width * (float)(x));

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
				//~

				//~ std::sort(hit_datas.begin(), hit_datas.end(), [camera](HitData data1 , HitData data2){
					//~ float dist1 = glm::distance(data1.position, camera.position);
					//~ float dist2 = glm::distance(data2.position, camera.position);
					//~ return dist1 < dist2;
				//~ });
				if( hit_datas.size() > 0)
				{
				//~
					hit_tri = true;
				}
			}




			long int index = (bucket.x + (i%bucket.width)) + (bucket.y + i/bucket.width) * bucket.render_width;

			if(hit_tri){

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



    duration = ( std::clock() - start ) / (double) CLOCKS_PER_SEC;

    printf("duration %f\n", duration / 4.0);


    int red[render_width * render_height];
    int green[render_width * render_height];
    int blue[render_width * render_height];

    for (int i = 0; i < render_buffer_data.size() / 4; i++)
	{
		red[i]   = render_buffer_data[(i * 4) + 0];
		green[i] = render_buffer_data[(i * 4) + 1];
		blue[i]  = render_buffer_data[(i * 4) + 2];
	}


    saveToBitmap2("render.bmp", render_width, render_height, red, green, blue);
	printf("SAVE BITMAP\n");
	
	
	// stbi save test

	unsigned char data[render_width*render_height*3];
	int index = 0;
	for (int i = 0; i < render_width*render_height; i++)
	{


			//~ 
			data[index++] = (int)render_buffer_data[i * 4 + 0];
			data[index++] = (int)render_buffer_data[i * 4 + 1];
			data[index++] = (int)render_buffer_data[i * 4 + 2];
			
			//~ 


	}

	stbi_save(render_width ,render_height, data);
	
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

void Renderer::cursor_pos_callback(GLFWwindow* window, double xpos, double ypos)
{

	Renderer* app = static_cast<Renderer*>(glfwGetWindowUserPointer(window));

	if(app->left_mouse_button_down)
	{

		app->mouse_delta_x = app->mouse_old_x - xpos;
		app->mouse_old_x = xpos;
		app->mouse_delta_y = app->mouse_old_y - ypos;
		app->mouse_old_y = ypos;


		double rot_speed = 0.01;

		app->camera_u_pos -= app->mouse_delta_x * rot_speed;



		app->camera_v_pos += app->mouse_delta_y * rot_speed;

		if(app->camera_v_pos < 0.2)
				app->camera_v_pos = 0.2;
		else if(app->camera_v_pos > PI-0.2)
				app->camera_v_pos = PI-0.2;

		//~ printf("delta : %.2f %.2f\n", app->mouse_delta_x, app->mouse_delta_y);
		//~ printf("upos : %.2f -- vpos %.2f\n", app->camera_u_pos, app->camera_v_pos);
		//~ printf("--------------------------------\n");


		app->setCamPosFromPolar(app->camera_u_pos, app->camera_v_pos, app->camera_orbit_radius, app->camera_view_center);

	}else if(app->right_mouse_button_down){

		app->mouse_delta_x = app->mouse_old_x - xpos;
		app->mouse_old_x = xpos;
		app->mouse_delta_y = app->mouse_old_y - ypos;
		app->mouse_old_y = ypos;

		glm::mat4 view = glm::lookAt(
			app->camera.position,
			app->camera.target_position,
			app->camera.up_vector
			);

		glm::vec3 pan_dir = glm::vec3(app->mouse_delta_x, -app->mouse_delta_y, 0.0);

		vec_mult_by_matrix(pan_dir, view, true);
		pan_dir = pan_dir - app->camera.position;
		app->camera_view_center.x += pan_dir.x * 0.02;
		app->camera_view_center.y += pan_dir.y * 0.02;
		app->camera_view_center.z += pan_dir.z * 0.02;

		app->setCamPosFromPolar(app->camera_u_pos, app->camera_v_pos, app->camera_orbit_radius, app->camera_view_center);
	}

}

void Renderer::mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	Renderer* app = static_cast<Renderer*>(glfwGetWindowUserPointer(window));

	if(button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
	{
		app->left_mouse_button_down = true;

		double x_pos, y_pos;
		glfwGetCursorPos(window, &x_pos, &y_pos);
		app->mouse_old_x = x_pos;
		app->mouse_old_y = y_pos;

		int width, height;
		glfwGetFramebufferSize(window, &width, &height);



		// raycast test

		ClickData click_data;

		click_data.x = x_pos;
		click_data.y = y_pos;
		click_data.width = width;
		click_data.height = height;

		Raycaster raycaster;
		//~ HitData hit_data;
		//~ bool hit = raycaster.intersectMeshes(click_data, app->camera, app->meshes, hit_data);
//~
		//~ if( hit ){
			//~ hit_data.print();
//~
		//~ }

		Ray ray = raycaster.castRay(click_data, app->camera);
		std::vector<HitData> hit_datas;
		bool hit2 = raycaster.intersectKDNodes(ray, app->kd_nodes,  hit_datas);
		if( hit2 ){
			//~ printf("hit bbox !!!!!!!!!!\n");

			std::sort(hit_datas.begin(), hit_datas.end(), [app](HitData data1 , HitData data2){
				float dist1 = glm::distance(data1.position, app->camera.position);
				float dist2 = glm::distance(data2.position, app->camera.position);
				return dist1 < dist2;
			});
			if( hit_datas.size() > 0)
			{
				printf("polygon hit --> %d\n", hit_datas[0].face_id);
			}
		}





	}else if(button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE)
	{
		app->left_mouse_button_down = false;
	}else if(button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS)
	{
		double x_pos, y_pos;
		glfwGetCursorPos(window, &x_pos, &y_pos);
		app->mouse_old_x = x_pos;
		app->mouse_old_y = y_pos;

		app->right_mouse_button_down = true;


	}else if(button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_RELEASE)
	{

		app->right_mouse_button_down = false;
	}
}

void Renderer::char_mods_callback(GLFWwindow* window, unsigned int key, int action)
{
	Renderer* app = static_cast<Renderer*>(glfwGetWindowUserPointer(window));

	if( (char)key == 'B' ) // B
	{
		// saveToBitmap2();
	}else if( (char)key == 'r' ){

		printf("Starting Rendering... \n");

		std::vector<RenderBucket> buckets;
		buckets = app->createBuckets(32, app->render_width, app->render_height);
		app->renderBuckets( buckets, app->camera);
		printf("DONE... \n");
	}else if( (char)key == 's' ){
		app->show_fbo = !app->show_fbo;
	}

}

void Renderer::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	Renderer* app = static_cast<Renderer*>(glfwGetWindowUserPointer(window));
    //~ printf("cur key is %d\n" ,scancode);
    if ((key == GLFW_KEY_LEFT  || key == GLFW_KEY_RIGHT ) && action == GLFW_PRESS){
			printf("GLFW_KEY_LEFT %d\n" ,scancode);

			glm::mat4 view = glm::lookAt(
				app->camera.position,
				app->camera.target_position,
				app->camera.up_vector
				);

			glm::vec3 x_template = glm::vec3(1.0, 0.0, 0.0);

			vec_mult_by_matrix(x_template, view, true);
			x_template = x_template - app->camera.position;
			app->camera_view_center.x += x_template.x * 0.1 * (key == GLFW_KEY_RIGHT ? 1.0 : -1.0) ;
			app->camera_view_center.y += x_template.y * 0.1 * (key == GLFW_KEY_RIGHT ? 1.0 : -1.0) ;
			app->camera_view_center.z += x_template.z * 0.1 * (key == GLFW_KEY_RIGHT ? 1.0 : -1.0) ;

			app->setCamPosFromPolar(app->camera_u_pos, app->camera_v_pos, app->camera_orbit_radius, app->camera_view_center);
	}if( key == GLFW_KEY_ESCAPE && action == GLFW_PRESS){
		printf("escape \n");
		app->b_cancel_render = true;
	}

}

void Renderer::scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	Renderer* app = static_cast<Renderer*>(glfwGetWindowUserPointer(window));
	//~ 
	//~ printf("--------------\n");
	//~ printf("\tx offset : %.3f\n", xoffset);
	//~ printf("\ty offset : %.3f\n", yoffset);
	
	
	app->camera_orbit_radius += yoffset * -0.1;
	app->setCamPosFromPolar(app->camera_u_pos, app->camera_v_pos, app->camera_orbit_radius, app->camera_view_center);
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

	int w_width, w_height;
	glfwGetWindowSize(window, &w_width, &w_height);

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
		// position        //uvs
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
	GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, r_width, r_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, render_buffer_data.data()));

	GLCall(glBindTexture(GL_TEXTURE_2D, 0));
}

void Renderer::drawFBO(int r_width, int r_height)
{
	//~ int r_width = 320;
	//~ int r_height = 240;
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

int Renderer::init(int limit)
{



	SystemUtils sys_utils;
	bool test1 = sys_utils.check_dir_exists(".", "render");
	bool test2 = sys_utils.check_dir_exists(".", "render_");
	
	printf(" test 1 ==> %s\n", (test1 ? "true": "false"));
	printf(" test 2 ==> %s\n", (test2 ? "true": "false"));


	render_width = 320 *1;
	render_height = 240 *1;

	//~ std::cout << "raytracer PROJECT" << std::endl;

	if(!glfwInit()){
		std::cout<<"Problem with GLFW"<< std::endl;
		glfwTerminate();
		return -1;
	}

	//~ std::cout<<"initializing GLFW"<< std::endl;
	window = glfwCreateWindow(640,480, "raytracer", NULL, NULL);

	if(!window){
		std::cout << "Problem with window " << std::endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);


	//~ camera.position = glm::vec3(0.0, 0.0, 2.4142);
	camera.target_position = glm::vec3(0.0, 0.0, 0.0);
	camera.up_vector = glm::vec3(0.0, 0.0, 1.0);

	setCamPosFromPolar(camera_u_pos, camera_v_pos, camera_orbit_radius);

	glewInit();

	glfwSetWindowUserPointer(window, this);

	glfwSetCharModsCallback(window, char_mods_callback);
	glfwSetKeyCallback(window, key_callback);
	glfwSetCursorPosCallback(window, cursor_pos_callback);
	glfwSetMouseButtonCallback(window, mouse_button_callback);
	glfwSetScrollCallback(window, scroll_callback);
	
	default_shader.loadVertexShaderSource("../src/shaders/basic_shader.vert");
	default_shader.loadFragmentShaderSource("../src/shaders/basic_shader.frag");

	default_shader.createShader();

	fbo_shader.loadVertexShaderSource("../src/shaders/fbo_shader.vert");
	fbo_shader.loadFragmentShaderSource("../src/shaders/fbo_shader.frag");

	fbo_shader.createShader();


	Light light1;
	light1.position = glm::vec3(2.0, 0.0, 1.5);
	light1.color = Color(1.0, 1.0, 1.0, 1.0);
	light1.intensity = 2.0;
	lights.push_back(light1);

	Light light2;
	light2.position = glm::vec3(3.0, -3.0, 4.0);
	light2.color = Color(1.0, 1.0, 1.0, 1.0);
	light2.intensity = 5.0;
	lights.push_back(light2);

	// materials
	RTMaterial material1;
	material1.color = Color(0.0, 0.0, 0.0, 1.0);
	material1.refl_amount = 0.9;
	materials.push_back(material1);

	RTMaterial material2;
	material2.color = Color(1.0,1.0,1.0,1.0);
	material2.refl_amount = 0.8;
	materials.push_back(material2);

	RTMaterial material3;
	material3.color = Color(0.2,1.0,0.2,1.0);
	material3.refl_amount = 0.0;
	materials.push_back(material3);

	initFBO(render_width,render_height);
	//~ kd_node = new KDNode(limit);
}

void Renderer::buildRenderGeometry()
{
	vbos.clear();
	ibos.clear();
	geo_data_array.clear();

	for (int i = 0; i < meshes.size(); i++)
	{
		meshes[i].material = materials[i];
		OGL_geometry_data geo_data;
		for(int pt_id = 0; pt_id < meshes[i].points.size(); pt_id++)
		{
			glm::vec3 point_pos = meshes[i].points[pt_id].position;
			glm::vec3 point_normal = meshes[i].points[pt_id].normal;
			geo_data.vertices.insert(
				geo_data.vertices.end(), {
					point_pos.x, point_pos.y, point_pos.z,
					point_normal.x, point_normal.y, point_normal.z,
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
		printf("----- BUILDING KD TREE\n");
		buildKDTree();
		printf("KDnodes num : %d\n", kd_nodes.size());
		collectKDBoungingBoxes(kd_nodes[0]);
		printf("BBoxes vector size is %d\n", kd_bboxes.size());
		buildKDTreeBBoxes(kd_bboxes);
	}

}

void Renderer::displayScene()
{

		GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
		GLCall(glClearColor(0.2,0.5,0.2,1.0));

		GLCall(glDisable(GL_CULL_FACE));
		GLCall(glEnable(GL_DEPTH_TEST));
		int width, height;

		glfwGetFramebufferSize(window, &width, &height);
		camera.setProjection(45.0f * (float)PI / 180.0f, (float)width / (float)height, 0.01f, 100.0f);
		GLCall(glViewport(0,0,width, height));

		//~ buildRenderGeometry();


		glm::mat4 model = glm::mat4(1.0f);
		glm::mat4 view = glm::mat4(1.0f);



		view *= glm::lookAt(
			camera.position, //glm::vec3(0.0,  0.0, 3.0),
			camera.target_position, //glm::vec3(0.0,  0.0, 0.0),
			camera.up_vector //glm::vec3(0.0,  1.0, 0.0)
		);

		default_shader.useProgram();

		GLCall(glUniformMatrix4fv(glGetUniformLocation(default_shader.m_id, "projection"), 1, GL_FALSE, glm::value_ptr(camera.projection)));
		GLCall(glUniformMatrix4fv(glGetUniformLocation(default_shader.m_id, "view"), 1, GL_FALSE, glm::value_ptr(view)));
		GLCall(glUniformMatrix4fv(glGetUniformLocation(default_shader.m_id, "model"), 1, GL_FALSE, glm::value_ptr(model)));


		// send lights data to opengl shader


		float light_positions[3] = { lights[0].position.x, lights[0].position.y, lights[0].position.z};
		GLCall(
			glUniform3fv(glGetUniformLocation(default_shader.m_id, "u_light_positions"), 1, light_positions)
		);

		for (int i = 0; i < meshes.size(); i++)
		{
			GLCall(glUniform4f(glGetUniformLocation(default_shader.m_id, "u_color"),
				meshes[i].material.color.r,
				meshes[i].material.color.g,
				meshes[i].material.color.b,
				1.0
			));

			GLCall(glBindBuffer(GL_ARRAY_BUFFER, vbos[i]));
			GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibos[i]));
			GLCall(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, 0));
			GLCall(glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, (void*)(sizeof(float)*3)));
			GLCall(glEnableVertexAttribArray(0));
			GLCall(glEnableVertexAttribArray(1));


			GLCall(glDrawElements(GL_TRIANGLES, geo_data_array[i].indices.size(), GL_UNSIGNED_INT, nullptr));

			GLCall(glDisableVertexAttribArray(0));
			GLCall(glDisableVertexAttribArray(1));
			GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
			GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
			//~ printf("rendering  mesh %d\n", i);
		}




		//~ displayKDTree();


		GLCall(glUseProgram(0));

		if( show_fbo )
		{
			GLCall(glDisable(GL_DEPTH_TEST));

			fbo_shader.useProgram();
			drawFBO(render_width,render_height);

			GLCall(glUseProgram(0));
		}

		glfwSwapBuffers(window);
		glfwPollEvents();
}

bool Renderer::shouldClose()
{
	return glfwWindowShouldClose(window);
}

