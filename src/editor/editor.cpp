#include "editor.h"


Editor::Editor()
{
	//~ printf("--- CONSTRUCT Editor\n");
}

//~ void Editor::buildDisplayGeoData()
//~ {
	//~ for (int i = 0; i < mesh_objects.size(); i++)
	//~ {
		//~ Mesh mesh_copy = mesh_objects[i].mesh;
		//~ mesh_copy.triangulate();
		//~ 
		//~ OGL_geometry_data geo_data;
		//~ 
	//~ }
	//~ 
//~ }

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

	w_renderer = SDL_CreateRenderer(window, -1, 0); // SDL_RENDERER_SOFTWARE);
	
	TTF_Init();
	
	font = TTF_OpenFont("../src/res/fonts/DroidSans.ttf", 20); //this opens a font style and sets a size
    if( font == NULL )
    {
        printf( "Failed to load font! SDL_ttf Error: %s\n", TTF_GetError() );
        //~ success = false;
    }	
	glewInit();
	
	//~ glewExperimental = GL_TRUE;
	
	
	//~ ui.init(window, gl_context, this);

	
	
	
	
	
	
	
	//~ Entity3D item1;
	MeshObject item1;
	item1.name = "item 1";
	
	item1.mesh = mesh_utils.makeSimpleBox();
	//~ item1.mesh.triangulate();
	//~ item1.mesh.computeNormals();
	item1.buildVBO();
	mesh_objects.push_back(item1);
	
	
	//~ buildDisplayGeoData();
	
	
	default_shader.loadVertexShaderSource("../src/editor/shaders/basic_shader.vert");
	default_shader.loadFragmentShaderSource("../src/editor/shaders/basic_shader.frag");

	default_shader.createShader();	
	
	font_shader.loadVertexShaderSource("../src/editor/shaders/font_shader.vert");
	font_shader.loadFragmentShaderSource("../src/editor/shaders/font_shader.frag");

	font_shader.createShader();		
	
	camera.position = glm::vec3(5.0, 2.0 , 3.0);
	camera.target_position = glm::vec3(0.0, 0.0 , 0.0);
	camera.up_vector = glm::vec3(0.0, 0.0 , 1.0);
	
	//~ UIText text1;
	//~ text1.m_renderer = w_renderer;
	//~ text1.m_font = font;
	//~ text1.m_shader = &font_shader;

	
	//~ text1.init();
	//~ ui_texts.push_back(text1);
}

void Editor::manageEvents()
{
    SDL_Event Event;
    while (SDL_PollEvent(&Event))
    {
		if (Event.type == SDL_QUIT)
		{
				is_running = false;
		}
	}
}

void Editor::update()
{
	
	
	
	manageEvents();




	//~ GLCall(glDisable(GL_CULL_FACE));
	GLCall(glEnable(GL_DEPTH_TEST));

	

	GLCall(glViewport(0,0,w_width, w_height));

	GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
	GLCall(glClearColor(0.2,0.5,0.2,1.0));


	camera.setProjection(45.0f * (float)PI / 180.0f, (float)w_width / (float)w_height, 0.01f, 100.0f);



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

	
	
	float light_positions[6] = { 
		3.0, 3.0 ,3.0,
		1.0, -2.5, 2.0
	};
	
	GLCall(
		glUniform3fv(glGetUniformLocation(default_shader.m_id, "u_light_positions"), 1, light_positions)
	);

	for (int i = 0; i < mesh_objects.size(); i++)
	{
			
		GLCall(glUniform4f(glGetUniformLocation(default_shader.m_id, "u_color"), 1.0, 0.3, 0.3, 1.0 ));
		mesh_objects[i].draw();		
			
			

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
}

Editor::~Editor()
{
	//~ printf("--- DELETE Editor\n");
}
