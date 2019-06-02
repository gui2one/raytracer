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



void UI::camerasDialog()
{
	ImGui::Begin("Cameras", &b_show_cameras_dialog);
	
	if( ImGui::ListBoxHeader("cameras"))
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
	
	if(ImGui::Button("Add Camera"))
	{
		m_editor->addCamera();
	}
	
	if(ImGui::Button("Delete Camera"))
	{
		
		if(m_editor->cameras.size() > 1)
		{
			printf("command delete camera : %d\n", m_editor->cur_cam_id);
			m_editor->deleteCamera(m_editor->cur_cam_id);
		}
	}	
	ImGui::End();
}

void UI::showAllDialogs()
{
	b_show_options_dialog = true;
	b_show_cameras_dialog = true;
}

void UI::hideAllDialogs()
{
	b_show_options_dialog = false;
	b_show_cameras_dialog = false;	
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

