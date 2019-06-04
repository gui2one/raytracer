#include "editor.h"

static double degToRad(double degrees)
{
	
	return degrees / 180.0 * PI;
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

static std::string increment_name(std::string _name)
{
	std::string s = _name;
	std::smatch m;
	std::regex e("\\d+?$");
	bool found = std::regex_search(_name, m, e);
	if(found)
	{
		int num = std::stoi(m.str());
		for(size_t i=0; i < std::strlen(m.str().c_str()); i++){
			s.pop_back();
		}
		printf("found digit ! %d\n", num);
		s += std::to_string(num+1);
	}else{
		s += "2";
	}
		
	return s;
}


Editor::Editor()
{
	//~ printf("--- CONSTRUCT Editor\n");
}

void Editor::setCamPosFromPolar(float u, float v, float _radius, glm::vec3 center)
{
        cameras[cur_cam_id]->position.x = (sin(u)* sin(v) * _radius) + center.x;
        cameras[cur_cam_id]->position.y = (cos(u)* sin(v) * _radius) + center.y;
        cameras[cur_cam_id]->position.z = (cos(v) * _radius) + center.z;

        cameras[cur_cam_id]->target_position = center;

        cameras[cur_cam_id]->up_vector = glm::vec3(0.0, 0.0, 1.0);
}

void Editor::cycleCameras()
{
	if(cur_cam_id < (int)cameras.size()-1)
	{
		cur_cam_id++;
		
	}else{
		cur_cam_id = 0;
		
	}
}

void Editor::init()
{
	MeshUtils mesh_utils;
	
	

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, 0);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
	
	
	w_width = 700; 
	w_height = 450; 
	if( SDL_Init(SDL_INIT_EVERYTHING) == 0){
			//~ printf("SDL initialized correctly\n");
	}     
 
	SDL_Init(SDL_INIT_VIDEO);
	uint32_t WindowFlags = SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE;
	//~ SDL_SetVideoMode(w_width, w_height, 32, SDL_GL_DOUBLEBUF);
	window = SDL_CreateWindow("Editor", 0, 0, w_width, w_height, WindowFlags);
	assert(window);
	gl_context = SDL_GL_CreateContext(window);

	glewInit();
	
	glewExperimental = GL_TRUE;

	
	MeshObject* item1 = new MeshObject();
	item1->name = "item 1";	
	item1->mesh = mesh_utils.makeSimpleBox();
	item1->buildVBO();
	item1->position = glm::vec3(0.0, 0.0, 1.0);
	item1->rotation = glm::vec3(0.0, 0.0, 45.0);
	entities.push_back(item1);
	
	MeshObject* ground = new MeshObject();
	ground->name = "ground";
	//~ Mesh mesh = mesh_utils.makeQuad();	
	//~ ground->mesh = mesh;	
	ground->setMeshGenerator(PLANE_MESH_GENERATOR);
	//~ for (auto param : ground->generator->params)
	//~ {
		//~ Param<int>* p_int = nullptr;
		//~ Param<glm::vec3>* p_vec3 = nullptr;
		//~ if( (p_int = dynamic_cast<Param<int>*>(param)))
		//~ {
			//~ std::cout << p_int->getValue() << std::endl;
		//~ }else if((p_vec3 = dynamic_cast<Param<glm::vec3>*>(param))){
			//~ std::cout << glm::to_string(p_vec3->getValue())  << std::endl;
		//~ }
		//~ 
	//~ }
	
	//~ ground->position = glm::vec3(5.0,5.0,0.0);
	ground->scale = glm::vec3(5.0,5.0,5.0);
	//~ ground->rotation = glm::vec3(180.0,0.0,0.0);	
	ground->buildVBO();
	entities.push_back(ground);
	
	default_shader.loadVertexShaderSource("../src/editor/shaders/basic_shader.vert");
	default_shader.loadFragmentShaderSource("../src/editor/shaders/basic_shader.frag");

	default_shader.createShader();	
	
	line_shader.loadVertexShaderSource("../src/editor/shaders/line_shader.vert");
	line_shader.loadFragmentShaderSource("../src/editor/shaders/line_shader.frag");

	line_shader.createShader();		
	
	Camera* camera = new Camera();
	camera->position = glm::vec3(5.0, 2.0 , 3.0);
	camera->target_position = glm::vec3(0.0, 0.0 , 0.0);
	camera->up_vector = glm::vec3(0.0, 0.0 , 1.0);	
	camera->setProjection(45.0f * (float)PI / 180.0f, (float)w_width / (float)w_height, 0.01f, 100.0f);
	camera->name = uniqueEntityName(camera->name);
	cameras.push_back(camera);
	
	cur_cam_id = 0;
	
	
	Camera * camera2 = new Camera();
	camera2->position = glm::vec3(5.0, 2.0 , 3.0);
	camera2->target_position = glm::vec3(0.0, 0.0 , 0.0);
	camera2->up_vector = glm::vec3(0.0, 0.0 , 1.0);	
	camera2->setProjection(45.0f * (float)PI / 180.0f, (float)w_width / (float)w_height, 0.01f, 100.0f);
	camera2->name = uniqueEntityName(camera2->name);
	cameras.push_back(camera2);	
	if(entities.size() > 0)
	{
		for(auto entity : entities)
		{
			buildKDTree(entity);
		}
				
		for(auto node : kd_nodes)
		{
			collectKDBoungingBoxes(node);
		}
		
		buildKDTreeBBoxes(kd_bboxes);		
	}
	
	c_grid.init();

}

void Editor::manageEvents()
{
	
	
    SDL_Event Event;
    
    
    
    
	
	while (SDL_PollEvent(&Event))
	{
		
		// process ImGui Events !!!!
		ImGui_ImplSDL2_ProcessEvent(&Event);
		
		const Uint8 *keyboard_state = SDL_GetKeyboardState(NULL);
		
		if (Event.type == SDL_QUIT)
		{
				is_running = false;
				
		}
		else if(!mouse_over_ui && !keyboard_captured){
			if( Event.type == (SDL_MOUSEMOTION)){
				
				if(Event.motion.state == SDL_BUTTON_LMASK )
				{
					left_mouse_dragging = true;
					
					if(keyboard_state[SDL_SCANCODE_LCTRL])
					{
						double rot_speed = 0.01;

						cameras[cur_cam_id]->orbit_u += (float)Event.motion.xrel * rot_speed;
						cameras[cur_cam_id]->orbit_v -= (float)Event.motion.yrel * rot_speed;

						if(cameras[cur_cam_id]->orbit_v < 0.2)
								cameras[cur_cam_id]->orbit_v = 0.2;
						else if(cameras[cur_cam_id]->orbit_v > PI-0.2)
								cameras[cur_cam_id]->orbit_v = PI-0.2;



						setCamPosFromPolar(
							cameras[cur_cam_id]->orbit_u, 
							cameras[cur_cam_id]->orbit_v, 
							cameras[cur_cam_id]->orbit_radius, 
							cameras[cur_cam_id]->orbit_center
						);	
					}						
				}else if(Event.motion.state == SDL_BUTTON_RMASK){
					
					right_mouse_dragging = true;
					
					if(keyboard_state[SDL_SCANCODE_LCTRL])
					{
						mouse_delta_x = -(float)Event.motion.xrel;						
						mouse_delta_y = -(float)Event.motion.yrel;
						
						glm::mat4 view = glm::lookAt(
							cameras[cur_cam_id]->position,
							cameras[cur_cam_id]->target_position,
							cameras[cur_cam_id]->up_vector
							);
				
						glm::vec3 pan_dir = glm::vec3(mouse_delta_x, -mouse_delta_y, 0.0);
				
						vec_mult_by_matrix(pan_dir, view, true);
						pan_dir = pan_dir - cameras[cur_cam_id]->position;
						cameras[cur_cam_id]->orbit_center.x += pan_dir.x * 0.02;
						cameras[cur_cam_id]->orbit_center.y += pan_dir.y * 0.02;
						cameras[cur_cam_id]->orbit_center.z += pan_dir.z * 0.02;
				
						setCamPosFromPolar(
							cameras[cur_cam_id]->orbit_u, 
							cameras[cur_cam_id]->orbit_v, 
							cameras[cur_cam_id]->orbit_radius, 
							cameras[cur_cam_id]->orbit_center);
					}							
				}
			}

				else if(Event.type == SDL_MOUSEBUTTONUP){
					
					if(Event.button.button == SDL_BUTTON_LEFT && !left_mouse_dragging)
					{
						// normal click
						
						int x, y;
						SDL_GetMouseState(&x, &y);

						
						ClickData cd;
						cd.width = w_width;
						cd.height = w_height;
						cd.x = (double)x;
						cd.y = (double)y;
						Raycaster caster;
						
						Ray ray = caster.castRay(cd, *(cameras[cur_cam_id]));
						
						std::vector<HitData> hit_datas;
						caster.intersectKDNodes(ray, kd_nodes, hit_datas, false);
						
						if(hit_datas.size() > 0 )
						{
							
							if(keyboard_state[SDL_SCANCODE_LSHIFT])
							{
								
								
								entities[hit_datas[0].mesh_id]->is_selected = !entities[hit_datas[0].mesh_id]->is_selected;
							}else{
								unselectAll();
								entities[hit_datas[0].mesh_id]->is_selected = true;
								
							}
						}else{
							unselectAll();
						}									
					}
					
					left_mouse_dragging = false;

					
				}else if(Event.type == SDL_MOUSEWHEEL){
					
					float norm_dist = glm::distance(cameras[cur_cam_id]->position, cameras[cur_cam_id]->orbit_center) / 5.0;
					cameras[cur_cam_id]->orbit_radius += (float)Event.wheel.y * -0.15 * norm_dist;
					
					setCamPosFromPolar(
						cameras[cur_cam_id]->orbit_u, 
						cameras[cur_cam_id]->orbit_v, 
						cameras[cur_cam_id]->orbit_radius, 
						cameras[cur_cam_id]->orbit_center
					);	
						
				}
			
			
			//~ else if(Event.type == SDL_KEYUP){
				//~ if(Event.key.keysym.scancode == SDL_SCANCODE_C)
				//~ {
					//~ 
					//~ cycleCameras();
				//~ }
			//~ }		
			if(Event.type == SDL_WINDOWEVENT){
			
				if (Event.window.event == SDL_WINDOWEVENT_RESIZED  || Event.window.event == SDL_WINDOWEVENT_MAXIMIZED) {
					printf("MESSAGE:Resizing window... %d %d\n", Event.window.data1, Event.window.data2);
					
					w_width = Event.window.data1;
					w_height = Event.window.data2;
					
				}
				if(Event.window.event == SDL_WINDOWEVENT_MINIMIZED){
					printf("MESSAGE:Minimizing window...\n" );
				}
			}
		}
	}
}

void Editor::update()
{
	
	
	
	manageEvents();

	//~ camera_u_pos += 0.01;
	setCamPosFromPolar(
		cameras[cur_cam_id]->orbit_u, 
		cameras[cur_cam_id]->orbit_v, 
		cameras[cur_cam_id]->orbit_radius, 
		cameras[cur_cam_id]->orbit_center
	);
	
	//~ printf("FOV %.3f\n",cameras[cur_cam_id]->fov);

	//~ GLCall(glDisable(GL_CULL_FACE));
	GLCall(glEnable(GL_DEPTH_TEST));

	

	GLCall(glViewport(0,0,w_width, w_height));

	GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
	GLCall(glClearColor(0.2,0.2,0.2,1.0));


	cameras[cur_cam_id]->setProjection(45.0f * (float)PI / 180.0f, (float)w_width / (float)w_height, 0.01f, 100.0f);



	glm::mat4 model = glm::mat4(1.0f);
	glm::mat4 view = glm::mat4(1.0f);



	view *= glm::lookAt(
		cameras[cur_cam_id]->position, //glm::vec3(0.0,  0.0, 3.0),
		cameras[cur_cam_id]->target_position, //glm::vec3(0.0,  0.0, 0.0),
		cameras[cur_cam_id]->up_vector //glm::vec3(0.0,  1.0, 0.0)
	);

	default_shader.useProgram();
	
	
	GLCall(glUniformMatrix4fv(glGetUniformLocation(default_shader.m_id, "projection"), 1, GL_FALSE, glm::value_ptr(cameras[cur_cam_id]->projection)));
	GLCall(glUniformMatrix4fv(glGetUniformLocation(default_shader.m_id, "view"), 1, GL_FALSE, glm::value_ptr(view)));

	
	


	for (size_t i = 0; i < entities.size(); i++)
	{
		//~ std::find(selected_entities.begin(), selected_entities.end(), (unsigned int)i);
		
		entities[i]->applyTransforms();
		model = entities[i]->transforms;
		GLCall(glUniformMatrix4fv(glGetUniformLocation(default_shader.m_id, "model"), 1, GL_FALSE, glm::value_ptr(model)));
		
		if( entities[i]->is_selected)
		{
			GLCall(glUniform4f(glGetUniformLocation(default_shader.m_id, "u_color"), 1.0, 1.0, 0.3, 1.0 ));
		}else{	
			GLCall(glUniform4f(glGetUniformLocation(default_shader.m_id, "u_color"), 1.0, 1.0, 1.0, 1.0 ));
		}
		
		entities[i]->draw();		
			
			

	}
	
	
	GLCall(glUseProgram(0));
	
	line_shader.useProgram();
	GLCall(glUniformMatrix4fv(glGetUniformLocation(line_shader.m_id, "model"), 1, GL_FALSE, glm::value_ptr(model)));
	GLCall(glUniformMatrix4fv(glGetUniformLocation(line_shader.m_id, "projection"), 1, GL_FALSE, glm::value_ptr(cameras[cur_cam_id]->projection)));
	GLCall(glUniformMatrix4fv(glGetUniformLocation(line_shader.m_id, "view"), 1, GL_FALSE, glm::value_ptr(view)));		
	for (Camera* cam : cameras)
	{
		
		if(cam != cameras[cur_cam_id])
		{
			model = glm::mat4(1.0f);		
			cam->applyTransforms();
			model *= cam->transforms;		
			
			GLCall(glUniformMatrix4fv(glGetUniformLocation(line_shader.m_id, "model"), 1, GL_FALSE, glm::value_ptr(model)));
			GLCall(glUniform4f(glGetUniformLocation(line_shader.m_id, "u_color"), 0.0, 0.0, 1.0, 1.0 ));
			cam->draw();
		}
	}
	
	
	GLCall(glUseProgram(0));

	model = glm::mat4(1.0f);
	
	line_shader.useProgram();
	GLCall(glUniformMatrix4fv(glGetUniformLocation(line_shader.m_id, "model"), 1, GL_FALSE, glm::value_ptr(model)));
	
	GLCall(glUniform4f(glGetUniformLocation(line_shader.m_id, "u_color"), 0.3, 1.0, 0.3, 1.0 ));
	displayKDTree();



	
	if(show_construction_grid)
	{
		
		//~ GLCall(glUniform4f(glGetUniformLocation(default_shader.m_id, "u_color"), 0.5, 0.5, 0.5, 1.0 ));
		c_grid.draw(line_shader);
	}
	
	GLCall(glUseProgram(0));
	
	//~ ui.draw();

	//~ update_inc++;
	
}

void Editor::saveScene()
{
	std::vector<JsonMaterial> materials;
	JsonMaterial mat1;
	materials.push_back(mat1);
	JsonScene scene;
	
	scene.materials = materials;
	std::string json = JSON::producer<JsonScene>::convert(scene);
	
	printf("%s\n", json.c_str());
	
}

void Editor::unselectAll()
{
	for(Entity3D* entity: entities)
	{
		entity->is_selected = false;
	}
}

void Editor::addMeshObject()
{
	printf("addMeshObject function fired !!! \n");
	
	MeshUtils mesh_utils;
	MeshObject* obj2 = new MeshObject();
	obj2->name = "object 2";
	Mesh mesh = mesh_utils.makeSimpleBox();
	
	mesh = mesh_utils.uniquePoints(mesh);
	//~ mesh.triangulate();
	//~ mesh.computeNormals();
	
	obj2->mesh = mesh;
	obj2->buildVBO();
	obj2->position = glm::vec3( (double)(entities.size()) * 0.5, 0.0, 0.0);
	obj2->scale = glm::vec3(0.4,0.4,2.0);
	entities.push_back(obj2);
	
	buildKDTree(entities[ entities.size() - 1]);
	collectKDBoungingBoxes(kd_nodes[ kd_nodes.size() - 1]);
	buildKDTreeBBoxes(kd_bboxes);
	//~ collectKDBoungingBoxes(
}

void Editor::addCamera()
{
	Camera * cam = new Camera();
	cam->name = uniqueEntityName(cam->name);
	cameras.push_back(cam);
}

void Editor::deleteCamera(int id)
{
	delete cameras[id];
	cameras.erase(cameras.begin() + id);
	if(cur_cam_id > (int)cameras.size()-1)
	{
		cur_cam_id = cameras.size()-1;
	}
}

std::string Editor::uniqueEntityName(std::string _str)
{
	

	for(Entity3D * entity : entities)
	{
		if(_str == entity->name)
		{
			//~ printf("same name \n");
			_str = increment_name(_str);
			_str = uniqueEntityName(_str);
			break;
		}
	}
	
	for(Camera * cam : cameras)
	{
		if(_str == cam->name)
		{
			//~ printf("same name \n");
			_str = increment_name(_str);
			_str = uniqueEntityName(_str);
			break;
		}
	}	
	return _str;
}

void Editor::toggleConstructionGrid()
{
	show_construction_grid = !show_construction_grid;
}

void Editor::buildKDTree(Entity3D * entity, int _limit)
{

	Entity3D  * p = entity;
	MeshObject * mesh_p = nullptr;
	if( (mesh_p = dynamic_cast<MeshObject *>(p)))
	{
		std::vector<Triangle*> tris;
		//~ tris.reserve(entities[mesh_id]->mesh.faces.size());

		for (size_t i = 0; i < mesh_p->mesh.faces.size(); i++)
		{
			// triangulate face if needed ... 
			for (size_t j = 0; j < mesh_p->mesh.faces[i].getNumVertices()-2; j++)
			{
				
				glm::vec3 A, B, C;
				A = B = C = glm::vec3(0.0, 0.0, 0.0);

		
				mesh_p->applyTransforms();
				// apply transforms matrix
				glm::vec3 tempA = mesh_p->mesh.points[ mesh_p->mesh.faces[i].getVertex(0).point_id ].position;
				vec_mult_by_matrix(tempA, mesh_p->transforms, false);

				glm::vec3 tempB = mesh_p->mesh.points[ mesh_p->mesh.faces[i].getVertex(1+j).point_id ].position;
				vec_mult_by_matrix(tempB, mesh_p->transforms, false);				

				glm::vec3 tempC = mesh_p->mesh.points[ mesh_p->mesh.faces[i].getVertex(2+j).point_id ].position;
				vec_mult_by_matrix(tempC, mesh_p->transforms, false);							
				
				A = tempA;
				B = tempB;
				C = tempC;

				//~ printf("vec3 value -> %.3f %.3f %.3f\n", A.x, A.y, A.z);

				Triangle* tri_ptr = new Triangle(A, B, C);
				tri_ptr->id = i;
				//~ tris.emplace_back(tri_ptr);
				tris.push_back(tri_ptr);
				
			}

		}

		KDNode * kd_node = new KDNode(_limit);
		kd_node = kd_node->build(tris, 0);
		kd_nodes.push_back(kd_node);
	}

	
	//~ if(entities.size() > 0){
		//~ printf("Created  %d KD Tree(s)\n", (int)entities.size());
	//~ }
}

void Editor::collectKDBoungingBoxes(KDNode* node_ptr)
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

void Editor::buildKDTreeBBoxes(std::vector<KDBoundingBox> bboxes)
{
	kdtree_vertices.clear();
	kdtree_indices.clear();

	for (size_t box_id = 0; box_id < bboxes.size(); box_id++)
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

		for (size_t i = 0; i < indices.size(); i++)
		{
			indices[i] += box_id * 8;
		}

		kdtree_indices.insert(kdtree_indices.end(), indices.begin(), indices.end());


	}


	//~ GLCall(glDeleteBuffers(1, &kdtree_vbo));
	if(kdtree_vbo == 0)
	{
		GLCall(glGenBuffers(1, &kdtree_vbo));
		//~ printf("m_vbo from KDBBox --> %d\n", kdtree_vbo);
	}else{		
		GLCall(glDeleteBuffers(1, &kdtree_vbo));
		GLCall(glGenBuffers(1, &kdtree_vbo));
	}	
	GLCall(glGenBuffers(1,&kdtree_vbo));
	

	GLCall(glBindBuffer(GL_ARRAY_BUFFER, kdtree_vbo));
	GLCall(glBufferData(GL_ARRAY_BUFFER, sizeof(float)* kdtree_vertices.size(), kdtree_vertices.data(), GL_STATIC_DRAW));
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));

	if(kdtree_ibo == 0)
	{
		GLCall(glGenBuffers(1, &kdtree_ibo));
	}else{		
		GLCall(glDeleteBuffers(1, &kdtree_ibo));
		GLCall(glGenBuffers(1, &kdtree_ibo));
	}
	
	GLCall(glGenBuffers(1,&kdtree_ibo));

	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, kdtree_ibo));
	GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int)* kdtree_indices.size(), kdtree_indices.data(), GL_STATIC_DRAW));
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));

}

void Editor::displayKDTree()
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

Editor::~Editor()
{
	//~ printf("--- DELETE Editor\n");
}
