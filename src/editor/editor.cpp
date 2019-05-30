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


Editor::Editor()
{
	//~ printf("--- CONSTRUCT Editor\n");
}

void Editor::setCamPosFromPolar(float u, float v, float _radius, glm::vec3 center)
{
        camera.position.x = (sin(u)* sin(v) * _radius) + center.x;
        camera.position.y = (cos(u)* sin(v) * _radius) + center.y;
        camera.position.z = (cos(v) * _radius) + center.z;

        camera.target_position = center;

        camera.up_vector = glm::vec3(0.0, 0.0, 1.0);
}


void Editor::init()
{
	MeshUtils mesh_utils;
	
	

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, 0);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
	
	
	w_width = 640; 
	w_height = 480; 
	if( SDL_Init(SDL_INIT_EVERYTHING) == 0){
			printf("SDL initialized correctly\n");
	}     
 
	SDL_Init(SDL_INIT_VIDEO);
	uint32_t WindowFlags = SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE;
	//~ SDL_SetVideoMode(w_width, w_height, 32, SDL_GL_DOUBLEBUF);
	window = SDL_CreateWindow("Editor", 0, 0, w_width, w_height, WindowFlags);
	assert(window);
	gl_context = SDL_GL_CreateContext(window);

	

	glewInit();
	
	//~ glewExperimental = GL_TRUE;
	
	
	//~ ui.init(window, gl_context, this);

	
	MeshObject* item1 = new MeshObject();
	item1->name = "item 1";
	
	item1->mesh = mesh_utils.makeSimpleBox();
	//~ item1->mesh.triangulate();
	//~ item1->mesh.computeNormals();
	//~ mesh_utils.rotate(item1->mesh, glm::vec3(0.0, 0.0, degToRad(33.0)));
	item1->buildVBO();
	mesh_objects.push_back(item1);
	
	MeshObject* ground = new MeshObject();
	ground->name = "ground";
	Mesh mesh = mesh_utils.makeQuad();

	ground->mesh = mesh;
	ground->scale = glm::vec3(5.0,5.0,5.0);
	ground->rotation = glm::vec3(180.0,0.0,0.0);
	
	
	ground->buildVBO();
	mesh_objects.push_back(ground);
	
	

	
	default_shader.loadVertexShaderSource("../src/editor/shaders/basic_shader.vert");
	default_shader.loadFragmentShaderSource("../src/editor/shaders/basic_shader.frag");

	default_shader.createShader();	
	
	line_shader.loadVertexShaderSource("../src/editor/shaders/line_shader.vert");
	line_shader.loadFragmentShaderSource("../src/editor/shaders/line_shader.frag");

	line_shader.createShader();		
	
	camera.position = glm::vec3(5.0, 2.0 , 3.0);
	camera.target_position = glm::vec3(0.0, 0.0 , 0.0);
	camera.up_vector = glm::vec3(0.0, 0.0 , 1.0);	
	
	
	if(mesh_objects.size() > 0)
	{
		buildKDTree();
		//~ printf("KDnodes num : %d\n", kd_nodes.size());
		
		for(auto node : kd_nodes)
		{
			collectKDBoungingBoxes(node);
		}
		
		printf("BBoxes vector size is %d\n", kd_bboxes.size());
		buildKDTreeBBoxes(kd_bboxes);		
	}
	
	
	
	c_grid.init();

}

void Editor::manageEvents()
{
    SDL_Event Event;
    while (SDL_PollEvent(&Event))
    {
		if (Event.type == SDL_QUIT)
		{
				is_running = false;
		}else if(( SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT))){
			
			if(!mouse_over_ui)
			{
				if( Event.type == SDL_MOUSEMOTION)
				{

				
					double rot_speed = 0.01;

					camera_u_pos += (float)Event.motion.xrel * rot_speed;



					camera_v_pos -= (float)Event.motion.yrel * rot_speed;

					if(camera_v_pos < 0.2)
							camera_v_pos = 0.2;
					else if(camera_v_pos > PI-0.2)
							camera_v_pos = PI-0.2;



					setCamPosFromPolar(camera_u_pos, camera_v_pos, camera_orbit_radius, camera_view_center);		
				}else{
					//~ int x, y;
					//~ SDL_GetMouseState(&x, &y);
					//~ printf("left click : %d %d\n",x, y);
					//~ ClickData cd;
					//~ cd.width = 640;
					//~ cd.height = 480;
					//~ cd.x = (double)x;
					//~ cd.y = (double)y;
					//~ Raycaster caster;
					//~ glm::vec3 test_screen = caster.screenToWorld_2(cd, camera);
					//~ printf("screen position : %.3f %.3f %.3f\n", test_screen.x, test_screen.y, test_screen.z);
					
					
				}
			}

		}else if( (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_RIGHT))){

			if(!mouse_over_ui)
			{
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
			}
		}else if(Event.type == SDL_MOUSEWHEEL){

			if(!mouse_over_ui)
			{			
				//~ printf("wheel event\n");
				//~ printf("\twheel x : %d\n", Event.wheel.x);
				//~ printf("\twheel y : %d\n", Event.wheel.y);
				
				camera_orbit_radius += (float)Event.wheel.y * -0.1;
				setCamPosFromPolar(camera_u_pos, camera_v_pos, camera_orbit_radius, camera_view_center);	
			}	
		}else if(Event.type == SDL_WINDOWEVENT){
			


			if (Event.window.event == SDL_WINDOWEVENT_RESIZED) {
				printf("MESSAGE:Resizing window... %d %d\n", Event.window.data1, Event.window.data2);
				
				w_width = Event.window.data1;
				w_height = Event.window.data2;
				
			}			
		}
	}
}

void Editor::update()
{
	
	
	
	manageEvents();

	camera_u_pos += 0.001;
	setCamPosFromPolar(camera_u_pos, camera_v_pos, camera_orbit_radius, camera_view_center);


	//~ GLCall(glDisable(GL_CULL_FACE));
	GLCall(glEnable(GL_DEPTH_TEST));

	

	GLCall(glViewport(0,0,w_width, w_height));

	GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
	GLCall(glClearColor(0.2,0.2,0.2,1.0));


	camera.setProjection(45.0f * (float)PI / 180.0f, (float)w_width / (float)w_height, 0.01f, 100.0f);



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

	
	


	for (int i = 0; i < mesh_objects.size(); i++)
	{
		mesh_objects[i]->applyTransforms();
		model = mesh_objects[i]->transforms;
		GLCall(glUniformMatrix4fv(glGetUniformLocation(default_shader.m_id, "model"), 1, GL_FALSE, glm::value_ptr(model)));
		GLCall(glUniform4f(glGetUniformLocation(default_shader.m_id, "u_color"), 1.0, 0.3, 0.3, 1.0 ));
		mesh_objects[i]->draw();		
			
			

	}
	
	GLCall(glUseProgram(0));

	model = glm::mat4(1.0f);
	
	line_shader.useProgram();
	GLCall(glUniformMatrix4fv(glGetUniformLocation(line_shader.m_id, "model"), 1, GL_FALSE, glm::value_ptr(model)));
	GLCall(glUniformMatrix4fv(glGetUniformLocation(line_shader.m_id, "projection"), 1, GL_FALSE, glm::value_ptr(camera.projection)));
	GLCall(glUniformMatrix4fv(glGetUniformLocation(line_shader.m_id, "view"), 1, GL_FALSE, glm::value_ptr(view)));	
	
	GLCall(glUniform4f(glGetUniformLocation(default_shader.m_id, "u_color"), 0.3, 1.0, 0.3, 1.0 ));
	displayKDTree();



	
	if(show_construction_grid)
	{
		GLCall(glUniform4f(glGetUniformLocation(default_shader.m_id, "u_color"), 0.5, 0.5, 0.5, 1.0 ));
		c_grid.draw();
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


void Editor::addMeshObject()
{
	printf("addMeshObject function fired !!! \n");
	
	MeshUtils mesh_utils;
	MeshObject* obj2 = new MeshObject();
	obj2->name = "object 2";
	Mesh mesh = mesh_utils.makeSimpleBox();
	mesh_utils.translate( mesh, glm::vec3(0.0,-1.5,0.0));
	mesh = mesh_utils.uniquePoints(mesh);
	//~ mesh.triangulate();
	//~ mesh.computeNormals();
	
	obj2->mesh = mesh;
	obj2->buildVBO();
	mesh_objects.push_back(obj2);
}


void Editor::toggleConstructionGrid()
{
	show_construction_grid = !show_construction_grid;
}

void Editor::buildKDTree(int _limit)
{


	for(int mesh_id = 0; mesh_id < mesh_objects.size(); mesh_id++)
	{
		std::vector<Triangle*> tris;
		tris.reserve(mesh_objects[mesh_id]->mesh.faces.size());

		for (int i = 0; i < mesh_objects[mesh_id]->mesh.faces.size(); i++)
		{
			glm::vec3 A, B, C;
			A = B = C = glm::vec3(0.0, 0.0, 0.0);

			A = mesh_objects[mesh_id]->mesh.points[ mesh_objects[mesh_id]->mesh.faces[i].getVertex(0).point_id ].position;
			B = mesh_objects[mesh_id]->mesh.points[ mesh_objects[mesh_id]->mesh.faces[i].getVertex(1).point_id ].position;
			C = mesh_objects[mesh_id]->mesh.points[ mesh_objects[mesh_id]->mesh.faces[i].getVertex(2).point_id ].position;

			//~ printf("vec3 value -> %.3f %.3f %.3f\n", A.x, A.y, A.z);

			Triangle* tri_ptr = new Triangle(A, B, C);
			tri_ptr->id = i;
			tris.emplace_back(tri_ptr);

		}

		KDNode * kd_node = new KDNode(_limit);
		kd_node = kd_node->build(tris, 0);
		kd_nodes.push_back(kd_node);
		
	}
	
	if(mesh_objects.size() > 0)
		printf("Created  %d KD Tree(s)\n", (int)mesh_objects.size());
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


	//~ GLCall(glDeleteBuffers(1, &kdtree_vbo));
	if(kdtree_vbo == 0)
	{
		GLCall(glGenBuffers(1, &kdtree_vbo));
		printf("m_vbo from KDBBox --> %d\n", kdtree_vbo);
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
