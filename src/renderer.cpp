#include "renderer.h"
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

static void alphaMask(int w, int h, Camera& camera, Mesh& mesh)
{
	
	Raycaster2 raycaster;
	int red[w*h];
	int green[w*h];
	int blue[w*h];
	
	ClickData click_data;
	click_data.width = 640;
	click_data.height = 480;
	//~ saveToBitmap2(red);
	for (int y = 0; y < h; y++)
	{
		click_data.y = (float)click_data.height / (float)h * y;
		for (int x = 0; x < w; x++)
		{
			int index = x + y * w;
			click_data.x = (float)click_data.width / (float)w * x;
			
			HitData hit_data;
			
			red[index] = raycaster.intersectMesh(click_data, camera, mesh, hit_data) == true ? 255 : 0;
			green[index] = red[index];
			blue[index] = red[index];
		}
		int progress = (float)y / (float)h * 100.0;
		printf("progress %d%\n",progress);
	}
	saveToBitmap2("alpha_mask.bmp",w, h, red, green ,blue);
	printf("done alpha mask\n");
	
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

void Renderer::renderBucket(int x_start, int y_start, int b_width, int b_height, int r_width, int r_height, Camera& camera)
{
	Raycaster2 raycaster;
	
	ClickData click_data;
	click_data.width = 640;
	click_data.height = 480;
		
	for (int y = y_start; y < y_start+b_height; y++)
	{
		click_data.y = (float)click_data.height / (float)r_height * (float)y;
		
		for (int x = x_start; x < x_start+b_width; x++)
		{
			click_data.x = (float)click_data.width / (float)r_width * (float)x;
			
			bool hit_tri = false;
			//~ HitData hit_data;
			//~ hit_tri = raycaster.intersectMeshes(click_data, camera, meshes, hit_data);
			
			Ray ray = raycaster.castRay(click_data, camera);
			std::vector<HitData> hit_datas;
			bool hit2 = raycaster.intersectKDNode(ray, kd_nodes[0], camera, hit_datas);
			if( hit2 )
			{
				//~ 
				
				std::sort(hit_datas.begin(), hit_datas.end(), [camera](HitData data1 , HitData data2){
					float dist1 = glm::distance(data1.position, camera.position);
					float dist2 = glm::distance(data2.position, camera.position);
					return dist1 < dist2;
				});			
				if( hit_datas.size() > 0)
				{	
				//~ 
					hit_tri = true;
				}
			}				
			
			
			long int index = x + y * 320;			
			
			if(hit_tri){
				
				float dist = glm::distance(camera.position, hit_datas[0].position);
				
				
				
				int depth = 255 - (int)((float)dist / 10.0 * 255.0);
				
				render_buffer_data[(index * 4)] = (unsigned char)depth;
				render_buffer_data[(index * 4)+1] = (unsigned char)depth;
				render_buffer_data[(index * 4)+2] = (unsigned char)depth;


			}else{
				render_buffer_data[(index * 4)] = (unsigned char)0;
				render_buffer_data[(index * 4)+1] = (unsigned char)0;
				render_buffer_data[(index * 4)+2] = (unsigned char)0;
			
			}			
		}
	}
	
}

void Renderer::renderMaterials(int w, int h, Camera& camera, std::vector<Mesh>& meshes)
{
	
	Raycaster2 raycaster;
	int red[w*h];
	int green[w*h];
	int blue[w*h];
	
	ClickData click_data;
	click_data.width = 640;
	click_data.height = 480;
	//~ saveToBitmap2(red);
	for (int y = 0; y < h; y++)
	{
		click_data.y = (float)click_data.height / (float)h * (float)y;
		for (int x = 0; x < w; x++)
		{
			click_data.x = (float)click_data.width / (float)w * (float)x;
			
			bool hit_tri = false;
			//~ HitData hit_data;
			//~ hit_tri = raycaster.intersectMeshes(click_data, camera, meshes, hit_data);
			
			Ray ray = raycaster.castRay(click_data, camera);
			std::vector<HitData> hit_datas;
			bool hit2 = raycaster.intersectKDNode(ray, kd_nodes[0], camera, hit_datas);
			if( hit2 )
			{
				//~ 
				
				std::sort(hit_datas.begin(), hit_datas.end(), [camera](HitData data1 , HitData data2){
					float dist1 = glm::distance(data1.position, camera.position);
					float dist2 = glm::distance(data2.position, camera.position);
					return dist1 < dist2;
				});			
				if( hit_datas.size() > 0)
				{	
				//~ 
					hit_tri = true;
				}
			}				
			
			
			long int index = x + y * w;
			if(hit_tri){
				
				float dist = glm::distance(camera.position, hit_datas[0].position);
				
				
				
				int depth = 255 - (int)((float)dist / 10.0 * 255.0);
				
				render_buffer_data[(index * 4)] = (unsigned char)depth;
				render_buffer_data[(index * 4)+1] = (unsigned char)depth;
				render_buffer_data[(index * 4)+2] = (unsigned char)depth;
				//~ render_buffer_data[index+3] = (unsigned char)255;
				
				red[index] = depth;
				green[index] = depth;
				blue[index] = depth;
			}else{
				render_buffer_data[(index * 4)] = (unsigned char)0;
				render_buffer_data[(index * 4)+1] = (unsigned char)0;
				render_buffer_data[(index * 4)+2] = (unsigned char)0;
				//~ render_buffer_data[index+3] = (unsigned char)0;				
				red[index] =  0;
				green[index] = 0;
				blue[index] = 0;				
			}
		}
		
		if(y % 20 == 0) render();
		
		int progress = (float)y / (float)h * 100.0;
		printf("progress %d%\n",progress);
	}
	saveToBitmap2("materials.bmp", w, h, red, green ,blue);
	printf("done Render Materials\n");
	
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


                app->setCamPosFromPolar(app->camera_u_pos, app->camera_v_pos, app->camera_orbit_radius);

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

		int width, height;
		glfwGetFramebufferSize(window, &width, &height);
		app->mouse_old_x = x_pos;
		app->mouse_old_y = y_pos;


		// raycast test

		ClickData click_data;

		click_data.x = x_pos;
		click_data.y = y_pos;
		click_data.width = width;
		click_data.height = height;

		Raycaster2 raycaster;
		HitData hit_data;
		bool hit = raycaster.intersectMeshes(click_data, app->camera, app->meshes, hit_data);

		if( hit ){
			hit_data.print();

		}
		
		Ray ray = raycaster.castRay(click_data, app->camera);
		std::vector<HitData> hit_datas;
		bool hit2 = raycaster.intersectKDNode(ray, app->kd_nodes[0], app->camera, hit_datas);
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
	}
}

void Renderer::char_mods_callback(GLFWwindow* window, unsigned int key, int action)
{
	Renderer* app = static_cast<Renderer*>(glfwGetWindowUserPointer(window));

	if( (char)key == 'B' ) // B
	{
		// saveToBitmap2();
	}else if( (char)key == 'r' ){
		//~ alphaMask(320, 240, app->camera, app->meshes[0]);
		//~ app->renderMaterials(320, 240, app->camera, app->meshes);
		app->renderBucket(10,10,64,64, 320, 240, app->camera);
	}

}

void Renderer::setCamPosFromPolar(float u, float v, float _radius)
{
        camera.position.x = sin(u)* sin(v) * _radius;
        camera.position.y = cos(u)* sin(v) * _radius;
        camera.position.z = cos(v) * _radius;
}

void Renderer::initFBO()
{
	GLCall(glDeleteBuffers(1, &fbo_vbo));
	GLCall(glGenBuffers(1, &fbo_vbo));
	
	float fbo_vertices[6*3 + 6*2] = {
		// position        //uvs
		-0.5,-0.5, 0.0,    0.0, 1.0,
		 0.5,-0.5, 0.0,    1.0, 1.0,
		 0.5, 0.5, 0.0,    1.0, 0.0,
		 
		-0.5,-0.5, 0.0,    0.0, 1.0,
		 0.5, 0.5, 0.0,    1.0, 0.0,
		-0.5, 0.5, 0.0,    0.0, 0.0
				
	};
	
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, fbo_vbo));
	GLCall(glBufferData(GL_ARRAY_BUFFER, sizeof(float) * (6*3 + 6*2), fbo_vertices, GL_DYNAMIC_DRAW));
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
	
	
	int r_width = 320;
	int r_height = 240;

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

void Renderer::drawFBO()
{
	int r_width = 320;
	int r_height = 240;
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
	glfwSetCursorPosCallback(window, cursor_pos_callback);
	glfwSetMouseButtonCallback(window, mouse_button_callback);

	default_shader.loadVertexShaderSource("../src/shaders/basic_shader.vert");
	default_shader.loadFragmentShaderSource("../src/shaders/basic_shader.frag");

	default_shader.createShader();
	
	fbo_shader.loadVertexShaderSource("../src/shaders/fbo_shader.vert");
	fbo_shader.loadFragmentShaderSource("../src/shaders/fbo_shader.frag");

	fbo_shader.createShader();	
	
	
	initFBO();
	//~ kd_node = new KDNode(limit);
}

void Renderer::buildRenderGeometry()
{
	vbos.clear();
	ibos.clear();
	geo_data_array.clear();

	for (int i = 0; i < meshes.size(); i++)
	{

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

void Renderer::render()
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
		
		
		
		for (int i = 0; i < meshes.size(); i++)
		{
			GLCall(glUniform4f(glGetUniformLocation(default_shader.m_id, "u_color"), 
				meshes[i].material.color.x,
				meshes[i].material.color.y,
				meshes[i].material.color.z,
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
		
		GLCall(glDisable(GL_DEPTH_TEST));
		GLCall(glUseProgram(0));

		
		fbo_shader.useProgram();
		drawFBO();

		GLCall(glUseProgram(0));
		
		glfwSwapBuffers(window);
		glfwPollEvents();
}

bool Renderer::shouldClose()
{
	return glfwWindowShouldClose(window);
}

