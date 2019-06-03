#include "ui.h"


UI::UI()
{
	
}

void UI::init(Editor* editor)
{
    // GL 3.0 + GLSL 130
    const char* glsl_version = "#version 130";	
    // Setup Dear ImGui context
    m_editor = editor;
    m_window = editor->window;
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;  // Enable Keyboard Controls

    // Setup Platform/Renderer bindings
    ImGui_ImplSDL2_InitForOpenGL(m_window, editor->gl_context);
    ImGui_ImplOpenGL3_Init(glsl_version);

    // Setup Style
    ImGui::StyleColorsDark();	
    
    //~ editor->addMeshObject();
}

void UI::menu()
{
	//~ static bool test = false;
    if (ImGui::BeginMainMenuBar())
    {
        
        if (ImGui::BeginMenu("File"))
        {
			if(ImGui::MenuItem("Exit"))
			{
				m_editor->is_running = false;
			}
			
			ImGui::EndMenu();
		}
		
        if (ImGui::BeginMenu("Windows"))
        {
            ImGui::MenuItem("Options", NULL, &b_show_options_dialog);
            ImGui::MenuItem("Cameras", NULL, &b_show_cameras_dialog);
            ImGui::MenuItem("Entities", NULL, &b_show_entities_dialog);
            ImGui::Separator();
            if(ImGui::MenuItem("Show All"))
            {
				showAllDialogs();
			}
            if(ImGui::MenuItem("Hide All"))
            {
				hideAllDialogs();
			}			
            ImGui::EndMenu();
        }
        
        ImGui::EndMainMenuBar();
	}
}

void UI::optionsDialog()
{
	//~ static bool b_show_options_dialog = false;
	ImGui::Begin("Options", &b_show_options_dialog);
	
	static bool show_grid = m_editor->show_construction_grid;
	if(ImGui::CheckboxFlags("show grid", (unsigned int*)&show_grid, 1))
	{
		m_editor->toggleConstructionGrid();		
	}
	
	ImGui::End();
}

void UI::entitiesDialog()
{
	static int cur = -1;
	ImGui::Begin("Entities", &b_show_entities_dialog);
	
	ImGui::PushItemWidth(-1);
	if( ImGui::ListBoxHeader("Entities"))
	{
		
		int inc =0;
		for(Entity3D* entity : m_editor->entities)
		{
			if(ImGui::Selectable(entity->name.c_str(), inc == cur)){
				cur = inc;
			}
			inc++;
		}
		ImGui::ListBoxFooter();
	}	
	ImGui::End();
	// display params
	
	ImGui::Begin("Params", &b_show_entities_dialog);
	MeshObject * p_mesh = nullptr;
	if( cur != -1)
	{
		if((p_mesh = dynamic_cast<MeshObject*>( m_editor->entities[cur])))
		{
			ImGui::Text("Mesh Object");
			if(p_mesh->generator != nullptr)
				paramWidget(p_mesh->generator->params[0]);
		}
	}	
	ImGui::End();
	
	
}

void UI::camerasDialog()
{
	ImGui::Begin("Cameras", &b_show_cameras_dialog);

	ImGui::PushItemWidth(-1);
	if( ImGui::ListBoxHeader(""))
	{
		int inc =0;
		for(Camera* cam : m_editor->cameras)
		{
			if(ImGui::Selectable(cam->name.c_str(), inc == m_editor->cur_cam_id)){
				m_editor->cur_cam_id = inc;
			}
			inc++;
		}
		ImGui::ListBoxFooter();
	}
	

	ImGui::PushItemWidth(-1);
	if(ImGui::Button("Add Camera"))
	{
		m_editor->addCamera();
	}
	ImGui::SameLine();
	ImGui::PushItemWidth(-1);
	if(ImGui::Button("Delete Camera"))
	{		
		if(m_editor->cameras.size() > 1)
		{
			printf("command delete camera : %d\n", m_editor->cur_cam_id);
			m_editor->deleteCamera(m_editor->cur_cam_id);
		}
	}	
	
	ImGui::Columns(1);
	ImGui::End();
}

void UI::showAllDialogs()
{
	b_show_options_dialog  = true;
	b_show_cameras_dialog  = true;
	b_show_entities_dialog = true;
}

void UI::hideAllDialogs()
{
	b_show_options_dialog  = false;
	b_show_cameras_dialog  = false;	
	b_show_entities_dialog = false;
}

void UI::draw()
{

	// Start the Dear ImGui frame
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplSDL2_NewFrame(m_window);
	ImGui::NewFrame();
	//~ static bool show_another_window = true;
	
	
	
	ImGuiIO& io = ImGui::GetIO();
	m_editor->mouse_over_ui = io.WantCaptureMouse;
	
	menu();
	if(b_show_options_dialog)
		optionsDialog();

	if(b_show_cameras_dialog)
		camerasDialog();
	
	if(b_show_entities_dialog)
		entitiesDialog();	
	//~ if(show_another_window)
	//~ {
		//~ ImGui::Begin("Another Window", &show_another_window);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
		//~ ImGui::Text("Hello from another window!");
		//~ if (ImGui::Button("Close Me"))
		//~ {
			//~ m_editor->addMeshObject();
			
		//~ }
		//~ ImGui::End();
	//~ }
	ImGui::Render();	
	
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void UI::paramWidget(BaseParam * param)
{
	Param<int> * p_int = nullptr;
	//~ Param<float> * p_float = nullptr;
	//~ Param<std::string> * p_string = nullptr;
	//~ Param<glm::vec3> * p_vec3 = nullptr;
	
	if( ( p_int = dynamic_cast<Param<int>*>( param )))
	{
		int _val = p_int->getValue();
		if( ImGui::DragInt("##aaa", &_val))
		{
			printf("set int value\n");
			p_int->setValue(_val);
		}
	}
}
