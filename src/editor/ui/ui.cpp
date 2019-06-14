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
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;  // Enable Keyboard Controls

    // Setup Platform/Renderer bindings
    ImGui_ImplSDL2_InitForOpenGL(m_window, editor->gl_context);
    ImGui_ImplOpenGL3_Init(glsl_version);

    // Setup Style
    //~ ImGui::StyleColorsDark();	
    
	
    ImGuiStyle& style = ImGui::GetStyle();
    style.WindowRounding = 0.02f;	
    
    
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
	
	static bool show_wireframe = m_editor->show_wireframe;
	if(ImGui::CheckboxFlags("wireframe", (unsigned int*)&show_wireframe, 1))
	{
		m_editor->show_wireframe = show_wireframe;		
		//~ printf("%s --\n", (m_editor->show_wireframe == true ? "true":"false"));
	}	
	
	ImGui::End();
}

void UI::entitiesDialog()
{
	static int cur = m_editor->cur_entity_id;
	ImGui::Begin("Entities", &b_show_entities_dialog);
	
	ImGui::PushItemWidth(-1);
	if( ImGui::ListBoxHeader("Entities"))
	{
		
		int inc =0;
		for(Entity3D* entity : m_editor->entities)
		{
			if(ImGui::Selectable(entity->name.c_str(), inc == cur)){
				cur = inc;
				m_editor->cur_entity_id = cur;
				m_editor->unselectAll();
				m_editor->entities[cur]->is_selected = true;
			}
			inc++;
		}
		ImGui::ListBoxFooter();
		
		if(ImGui::Button("Add Entity"))
		{
			m_editor->addMeshObject();
		}
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
			
			if(ImGui::BeginTabBar("Main"))
			{
				if(ImGui::BeginTabItem("Transforms"))
				{
					int inc = 0;
					for(auto param : m_editor->entities[cur]->params)
					{
						paramWidget(param, inc, [](){});
						inc++;
					}
					ImGui::EndTabItem();
				}
				if(ImGui::BeginTabItem("Generator"))
				{
					std::vector<const char*> generator_types_strings = {"...", "Grid Mesh", "Box Mesh"};
					static int cur_choice = 0;
					if( p_mesh->generator != nullptr)
					{
						char label[100];
						sprintf(label, "current generatpr : %s", generator_types_strings[(int)p_mesh->generator_type+1]);
						ImGui::Text( label );
						//~ cur_choice = p_mesh->generator_type;
					}
					
					if(ImGui::BeginCombo("Choose", generator_types_strings[cur_choice+1],0)){
						
						for (size_t i = 0; i < generator_types_strings.size()-1; i++)
						{
							if(ImGui::Selectable( generator_types_strings[i+1], false))
							{
								cur_choice = i;
								p_mesh->setMeshGenerator((MESH_GENERATOR_TYPE)cur_choice);
							}
						}
						
						
						
						ImGui::EndCombo();
					}
					
					if(p_mesh->generator != nullptr)
					{
						int inc = 0;
						for(auto param : p_mesh->generator->params)
						{
							paramWidget(param, inc, [p_mesh](){
								p_mesh->updateMeshGenerator();
							});
							
							inc++;
						}
					}
					ImGui::EndTabItem();
				}
				
				
				ImGui::EndTabBar();
			}
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
	//~ m_editor->keyboard_captured = io.WantCaptureKeyboard;
	
	menu();
	if(b_show_options_dialog)
		optionsDialog();

	if(b_show_cameras_dialog)
		camerasDialog();
	
	if(b_show_entities_dialog)
		entitiesDialog();	

	ImGui::Render();	
	
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void UI::paramWidget(BaseParam * param, int imgui_ID, std::function<void()> callback)
{
	Param<int> * p_int = nullptr;
	Param<float> * p_float = nullptr;
	//~ Param<std::string> * p_string = nullptr;
	Param<glm::vec3> * p_vec3 = nullptr;
	ParamMenu * p_menu = nullptr;
	
	if( ( p_int = dynamic_cast<Param<int>*>( param )))
	{
		int _val = p_int->getValue();
		if( ImGui::DragInt(p_int->getName().c_str(), &_val))
		{
			//~ printf("set int value\n");
			p_int->setValue(_val);
			callback();
		}
	}
	else if(( p_float = dynamic_cast<Param<float>*>( param )))
	{
		float _val = p_float->getValue();
		if( ImGui::DragFloat(p_float->getName().c_str(), &_val, 0.05f))
		{
			//~ printf("set int value\n");
			p_float->setValue(_val);
			callback();
		}
				
	}
	else if( ( p_vec3 = dynamic_cast<Param<glm::vec3>*>( param )))
	{
		glm::vec3 _val = p_vec3->getValue();
		
		ImGui::PushID((const void*)imgui_ID);
		
		ImGui::Text(p_vec3->getName().c_str());
		ImGui::Columns(3);
		if(ImGui::DragFloat("##X", &_val.x, 0.05f))
		{
			p_vec3->setValue(
				glm::vec3(
					_val.x,
					p_vec3->getValue().y,
					p_vec3->getValue().z
				)
			);
			callback();			
		}
		ImGui::NextColumn();
		if(ImGui::DragFloat("##Y", &_val.y, 0.05f))
		{
			p_vec3->setValue(
				glm::vec3(
					p_vec3->getValue().x,
					_val.y,
					p_vec3->getValue().z
				)
			);
			callback();
		}
		ImGui::NextColumn();	
		if(ImGui::DragFloat("##Z", &_val.z, 0.05f))
		{
			p_vec3->setValue(
				glm::vec3(
					p_vec3->getValue().x,
					p_vec3->getValue().y,
					_val.z
				)
			);
			callback();
		}
		
		ImGui::Columns(1);
		ImGui::PopID();
		
	}
	else if((p_menu = dynamic_cast<ParamMenu*>(param)))
	{
		static int choice = 0;
		if(ImGui::BeginCombo(p_menu->getName().c_str(), p_menu->entries[choice].first.c_str(),0))
		{
			int inc = 0;
			for(auto entry : p_menu->entries)
			{
				if(ImGui::Selectable(entry.first.c_str(), choice == inc))
				{
					choice = inc;
					p_menu->setValue(choice);
					callback();
				}
				inc++;
			}
			ImGui::EndCombo();
		}
	}
}
