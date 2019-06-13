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

	MeshObject * box = new MeshObject();
	box->setMeshGenerator(BOX_MESH_GENERATOR);
	box->position = glm::vec3(0.0, 0.0, 2.0);
	box->applyTransforms();
	box->buildVBO();
	entities.push_back(box);
	
	MeshObject* ground = new MeshObject();
	ground->name = "ground";
	
	ground->setMeshGenerator(GRID_MESH_GENERATOR);
	//~ ground->scale = glm::vec3(5.0,5.0,5.0);
	
	entities.push_back(ground);
	ground->buildVBO();
	
	default_shader.loadVertexShaderSource("../src/editor/shaders/basic_shader.vert");
	default_shader.loadFragmentShaderSource("../src/editor/shaders/basic_shader.frag");

	default_shader.createShader();	
	
	line_shader.loadVertexShaderSource("../src/editor/shaders/line_shader.vert");
	line_shader.loadFragmentShaderSource("../src/editor/shaders/line_shader.frag");

	line_shader.createShader();		
	
	fbo_shader.loadVertexShaderSource("../src/editor/shaders/fbo_shader.vert");
	fbo_shader.loadFragmentShaderSource("../src/editor/shaders/fbo_shader.frag");

	fbo_shader.createShader();		
	
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
	
	//// init construction grid
	c_grid.init();

	handle = new TranslateHandle();
	//~ handle->position = glm::vec3(0.0, 0.0, 0.0);
	
	GLCall(glCullFace(GL_FRONT));
	GLCall(glEnable(GL_TEXTURE_2D));
	GLCall(glEnable(GL_BLEND));
	GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
	
	initHandlesFBO();
}

void Editor::initHandlesFBODepthBuffer()
{

	if(handles_fbo_depth != 0)
	{
		glDeleteRenderbuffersEXT(1, &handles_fbo_depth);
		glGenRenderbuffersEXT(1, &handles_fbo_depth); // Generate one render buffer and store the ID in fbo_depth
	}else{
		glGenRenderbuffersEXT(1, &handles_fbo_depth); // Generate one render buffer and store the ID in fbo_depth
	}
	glBindRenderbufferEXT(GL_RENDERBUFFER_EXT, handles_fbo_depth); // Bind the fbo_depth render buffer

	glRenderbufferStorageEXT(GL_RENDERBUFFER_EXT, GL_DEPTH_COMPONENT, w_width, w_height); // Set the render buffer storage to be a depth component, with a width and height of the window

	glFramebufferRenderbufferEXT(GL_FRAMEBUFFER_EXT, GL_DEPTH_ATTACHMENT_EXT, GL_RENDERBUFFER_EXT, handles_fbo_depth); // Set the render buffer of this buffer to the depth buffer

	glBindRenderbufferEXT(GL_RENDERBUFFER_EXT, 0); // Unbind the render buffer
}

void Editor::initHandlesFBOTexture() 
{
	if( handles_fbo_texture != 0)
	{
		glDeleteTextures(1, &handles_fbo_texture);
		glGenTextures(1, &handles_fbo_texture); // Generate one texture
	}else{
		glGenTextures(1, &handles_fbo_texture); // Generate one texture
	}
	glBindTexture(GL_TEXTURE_2D, handles_fbo_texture); // Bind the texture fbo_texture

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w_width, w_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL); // Create a standard texture with the width and height of our window

	// Setup the basic texture parameters
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	// Unbind the texture
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Editor::initHandlesFBO() 
{
	initHandlesFBODepthBuffer(); // Initialize our frame buffer depth buffer

	initHandlesFBOTexture(); // Initialize our frame buffer texture

	if(handles_fbo != 0)
	{
		glDeleteFramebuffersEXT(1, &handles_fbo); 
	}
	
	glGenFramebuffersEXT(1, &handles_fbo); // Generate one frame buffer and store the ID in fbo
	
	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, handles_fbo); // Bind our frame buffer

	glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT, GL_TEXTURE_2D, handles_fbo_texture, 0); // Attach the texture fbo_texture to the color buffer in our frame buffer

	glFramebufferRenderbufferEXT(GL_FRAMEBUFFER_EXT, GL_DEPTH_ATTACHMENT_EXT, GL_RENDERBUFFER_EXT, handles_fbo_depth); // Attach the depth buffer fbo_depth to our frame buffer

	GLenum status = glCheckFramebufferStatusEXT(GL_FRAMEBUFFER_EXT); // Check that status of our generated frame buffer

	if (status != GL_FRAMEBUFFER_COMPLETE_EXT) // If the frame buffer does not report back as complete
	{
		std::cout << "Couldn't create frame buffer" << std::endl; // Output an error to the console
		exit(0); // Exit the application
	}

	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0); // Unbind our frame buffer
	
	
	//// init 'screen'
	//~ GLCall(glDeleteBuffers(1, &handles_fbo_vbo));
	if(handles_fbo_vbo != 0)
	{
		glDeleteBuffers(1, &handles_fbo_vbo);
	}
	GLCall(glGenBuffers(1, &handles_fbo_vbo));


	float fbo_vertices[6*3 + 6*2] = {
		// position        //uvs:
		-1.0,-1.0, 0.0,    0.0, 0.0,
		 1.0,-1.0, 0.0,    1.0, 0.0,
		 1.0, 1.0, 0.0,    1.0, 1.0,

		-1.0,-1.0, 0.0,    0.0, 0.0,
		 1.0, 1.0, 0.0,    1.0, 1.0,
		-1.0, 1.0, 0.0,    0.0, 1.0

	};

	GLCall(glBindBuffer(GL_ARRAY_BUFFER, handles_fbo_vbo));
	GLCall(glBufferData(GL_ARRAY_BUFFER, sizeof(float) * (6*3 + 6*2), fbo_vertices, GL_DYNAMIC_DRAW));
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));		
}

void Editor::renderHandlesFBO()
{
	glm::mat4 model = glm::mat4(1.0f);

	// check for selected entity
	for (Entity3D* entity : entities)
	{
		if(entity->is_selected)
		{
			//~ entity->applyTransforms();
			handle->position = entity->position;
			handle->rotation = entity->rotation;
			handle->applyTransforms();
			//~ printf("handle pos --> %.3f %.3f %.3f\n", handle->position.x, handle->position.y, handle->position.z);
			//~ printf("entity pos --> %.3f %.3f %.3f\n", entity->position.x, entity->position.y, entity->position.z);
			break;
		}
	}
	
	
	float cam_distance = glm::distance(handle->position, cameras[cur_cam_id]->position);
	float scale = cam_distance / 8.0f;
	//~ printf("%f \n", scale);
	model = handle->transforms;
	model  = glm::scale(model , glm::vec3(scale, scale, scale));
	
	glm::mat4 view = glm::mat4(1.0f);

	view *= glm::lookAt(
		cameras[cur_cam_id]->position, //glm::vec3(0.0,  0.0, 3.0),
		cameras[cur_cam_id]->target_position, //glm::vec3(0.0,  0.0, 0.0),
		cameras[cur_cam_id]->up_vector //glm::vec3(0.0,  1.0, 0.0)
	);

	line_shader.useProgram();
	
	
	GLCall(glUniformMatrix4fv(glGetUniformLocation(line_shader.m_id, "projection"), 1, GL_FALSE, glm::value_ptr(cameras[cur_cam_id]->projection)));
	GLCall(glUniformMatrix4fv(glGetUniformLocation(line_shader.m_id, "view"), 1, GL_FALSE, glm::value_ptr(view)));	
	GLCall(glUniformMatrix4fv(glGetUniformLocation(line_shader.m_id, "model"), 1, GL_FALSE, glm::value_ptr(model)));	
	
	GLCall(glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, handles_fbo)); // Bind our frame buffer for rendering 
	GLCall(glPushAttrib(GL_VIEWPORT_BIT | GL_ENABLE_BIT)); // Push our glEnable and glViewport states 
	GLCall(glViewport(0, 0, w_width, w_height)); // Set the size of the frame buffer view port 
	 
	GLCall(glClearColor (0.0f, 0.0f, 0.0f, 0.0f)); // Set the clear colour 
	GLCall(glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT)); // Clear the depth and colour buffers 

	GLCall(glPolygonMode( GL_FRONT_AND_BACK, GL_FILL ));

	handle->draw();
	 
	GLCall(glPopAttrib()); // Restore our glEnable and glViewport states 
	GLCall(glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0)); // Unbind our texture 	
}


void Editor::displayHandlesFBO()
{
	GLCall(glEnable(GL_BLEND));
	GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
	fbo_shader.useProgram();
	
	GLCall(glActiveTexture(GL_TEXTURE0));
	GLCall(glBindTexture(GL_TEXTURE_2D, handles_fbo_texture));
	//~ GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w_width, w_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, render_buffer_data.data()));
	
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, handles_fbo_vbo));

	GLCall(glEnableVertexAttribArray(0));
	GLCall(glEnableVertexAttribArray(1));
	GLCall(glVertexAttribPointer(0,3, GL_FLOAT, GL_FALSE, sizeof(float) * 5, 0));
	GLCall(glVertexAttribPointer(1,2, GL_FLOAT, GL_FALSE, sizeof(float) * 5, (void*)(sizeof(float) * 3)));



	GLCall(glDrawArrays(GL_TRIANGLES, 0, 6));


	GLCall(glDisableVertexAttribArray(0));
	GLCall(glDisableVertexAttribArray(1));
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
	GLCall(glBindTexture(GL_TEXTURE_2D, 0));
	
	GLCall(glUseProgram(0));
	
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
						std::vector<std::shared_ptr<KDNode> > kd_nodes2;
						for (Entity3D* entity: entities)
						{
							MeshObject * p_mesh = nullptr;
							
							if((p_mesh = dynamic_cast<MeshObject*>(entity))){
								if(p_mesh->kd_node != nullptr)
								{
									//~ printf("check kdnode\n");
									//~ printf("check kdnode. num triangles : %d\n", p_mesh->kd_node->triangles.size());
									kd_nodes2.push_back(p_mesh->kd_node);
								}
							}
						}
						
						caster.intersectKDNodes(ray, kd_nodes2, hit_datas, false);
						//~ printf("got hit ??? \n");
						if(hit_datas.size() > 0 )
						{
							//~ printf("got hit\n");
							if(keyboard_state[SDL_SCANCODE_LSHIFT])
							{
								
								cur_entity_id = hit_datas[0].mesh_id;
								entities[cur_entity_id]->is_selected = !entities[cur_entity_id]->is_selected;
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

		}
		
		if(Event.type == SDL_WINDOWEVENT){
		
			if (Event.window.event == SDL_WINDOWEVENT_RESIZED  || Event.window.event == SDL_WINDOWEVENT_MAXIMIZED) {
				//~ printf("MESSAGE:Resizing window... %d %d\n", Event.window.data1, Event.window.data2);
				
				w_width = Event.window.data1;
				w_height = Event.window.data2;
				
				initHandlesFBO();
				
			}
			if(Event.window.event == SDL_WINDOWEVENT_MINIMIZED){
				//~ printf("MESSAGE:Minimizing window...\n" );
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

	GLCall(glDisable(GL_BLEND));
	

	GLCall(glViewport(0,0,w_width, w_height));
	GLCall(glClearColor(0.2,0.2,0.2,1.0));
	GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
	


	cameras[cur_cam_id]->setProjection(45.0f * (float)PI / 180.0f, (float)w_width / (float)w_height, 0.01f, 100.0f);



	glm::mat4 model = glm::mat4(1.0f);
	glm::mat4 view = glm::mat4(1.0f);


	//~ GLCall(glEnable(GL_CULL_FACE));
	//~ GLCall(glCullFace(GL_FRONT));
	view *= glm::lookAt(
		cameras[cur_cam_id]->position, //glm::vec3(0.0,  0.0, 3.0),
		cameras[cur_cam_id]->target_position, //glm::vec3(0.0,  0.0, 0.0),
		cameras[cur_cam_id]->up_vector //glm::vec3(0.0,  1.0, 0.0)
	);

	default_shader.useProgram();
	
	
	
	GLCall(glUniformMatrix4fv(glGetUniformLocation(default_shader.m_id, "projection"), 1, GL_FALSE, glm::value_ptr(cameras[cur_cam_id]->projection)));
	GLCall(glUniformMatrix4fv(glGetUniformLocation(default_shader.m_id, "view"), 1, GL_FALSE, glm::value_ptr(view)));

	
	if(show_wireframe == true)
	{
		GLCall(glPolygonMode( GL_FRONT_AND_BACK, GL_LINE ));
	}else{
		
		GLCall(glPolygonMode( GL_FRONT_AND_BACK, GL_FILL ));
	}



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


	//~ displayKDTree();


	model = glm::mat4(1.0f);
	
	if(show_construction_grid)
	{		
		line_shader.useProgram();
		GLCall(glUniformMatrix4fv(glGetUniformLocation(line_shader.m_id, "model"), 1, GL_FALSE, glm::value_ptr(model)));
		
		GLCall(glUniform4f(glGetUniformLocation(line_shader.m_id, "u_color"), 0.3, 1.0, 0.3, 1.0 ));		
		//~ GLCall(glUniform4f(glGetUniformLocation(default_shader.m_id, "u_color"), 0.5, 0.5, 0.5, 1.0 ));
		c_grid.draw(line_shader);
			
		GLCall(glUseProgram(0));
		
	}
	

	renderHandlesFBO();
	GLCall(glDisable(GL_DEPTH_TEST));
	
	GLCall(glPolygonMode( GL_FRONT_AND_BACK, GL_FILL ));	
	
	displayHandlesFBO();
	

	
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
	//~ printf("addMeshObject function fired !!! \n");
	
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



Editor::~Editor()
{
	//~ printf("--- DELETE Editor\n");
}
