#include "ui.h"


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

// TODO
static std::string unique_name(std::string candidate, std::vector<std::string> names_set)
{
	return candidate;
}
//
 
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
    style.WindowRounding = 3.0f;	
	ImVec4* colors = style.Colors;
	//~ colors[ImGuiCol_TitleBgActive]   = ImVec4(0.68f, 0.31f, 0.20f, 1.00f);
	colors[ImGuiCol_TabActive]       = ImVec4(0.68f, 0.31f, 0.20f, 1.00f);
	//~ colors[ImGuiCol_Border]     = ImVec4(0.68f, 0.31f, 0.20f, 1.00f);
	colors[ImGuiCol_WindowBg]        = ImVec4(0.059f, 0.059f, 0.059f, 1.00f);
    
    
    style.FrameBorderSize = 0.0f;
    
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
            //~ ImGui::MenuItem("Cameras", NULL, &b_show_cameras_dialog);
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
        
        if(ImGui::BeginMenu("Add"))
        {
			if(ImGui::MenuItem("Mesh Object"))
			{
				m_editor->addMeshObject();
			}
			if(ImGui::MenuItem("Null Object"))
			{
				m_editor->addNullObject();
			}
			if(ImGui::MenuItem("Camera"))
			{
				m_editor->addCamera();
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
		for(std::shared_ptr<Entity3D> entity : m_editor->entities)
		{
			if(ImGui::Selectable(entity->name.c_str(), inc == m_editor->cur_entity_id)){
				cur = inc;
				
				//~ if( m_editor->cur_entity_id != -1)
				//~ {
					m_editor->unselectAll();
					m_editor->cur_entity_id = cur;
					entity->is_selected = true;
				//~ }
			}
			inc++;
		}
		ImGui::ListBoxFooter();
		
		if(ImGui::Button("Add Entity"))
		{
			m_editor->addMeshObject();
		}
		
		if(ImGui::Button("Delete"))
		{
			m_editor->deleteEntity(m_editor->cur_entity_id);
		}		
	}	
	ImGui::End();
	// display params
	
	ImGui::Begin("Params", &b_show_entities_dialog);
	MeshObject * p_mesh = nullptr;
	if( m_editor->cur_entity_id != -1)
	{
		
		if(ImGui::InputText("name", (char *)m_editor->entities[m_editor->cur_entity_id]->name.c_str() ,200 ))
		{

		}		
		if(ImGui::BeginTabBar("Main"))
		{		

			if(ImGui::BeginTabItem("Transforms"))
			{
				int inc = 0;
				for(auto param : m_editor->entities[m_editor->cur_entity_id]->params)
				{
					paramWidget(param, inc, [this](){
						m_editor->entities[m_editor->cur_entity_id]->buildKDTree(50);
						});
					inc++;
				}
				
				ImGui::Separator();
				
				
				// parenting
				std::vector<std::shared_ptr<Entity3D> > parent_choices;
				for(std::shared_ptr<Entity3D> entity : m_editor->entities)
				{
					std::vector<std::shared_ptr<Entity3D> > chain;
					chain = entity->getParentChain();
					auto pos = std::find(chain.begin(), chain.end(), m_editor->entities[m_editor->cur_entity_id] );
					
					bool is_sibling = false;
					if( pos != chain.end() )
					{
						//~ printf("found !!!\n");
						is_sibling = true;
					}else{
						//~ printf("not a sibling  !!!\n");
						is_sibling = false;
					}
					if(	entity != m_editor->entities[m_editor->cur_entity_id] && !is_sibling )
					{
						parent_choices.push_back(entity);	
					}
				}
				
				if(ImGui::BeginCombo("Parent", "...", 0 )  )
				{			
						if( ImGui::Selectable("None")) 
						{
							m_editor->entities[m_editor->cur_entity_id]->parent = nullptr;
						}
					for(auto item : parent_choices)
					{
						if( ImGui::Selectable(item->name.c_str())) 
						{
							m_editor->entities[m_editor->cur_entity_id]->parent = item;
						}
					}
					ImGui::EndCombo();
				}
				
				
				
				// look at target
				std::vector<std::shared_ptr<Entity3D> > target_choices;
				for(std::shared_ptr<Entity3D> entity : m_editor->entities)
				{

					if(	entity != m_editor->entities[m_editor->cur_entity_id])
					{
						target_choices.push_back(entity);	
					}
				}	
				
				if(ImGui::BeginCombo("Look At Target", "...", 0 )  )
				{			
						if( ImGui::Selectable("None")) 
						{
							m_editor->entities[m_editor->cur_entity_id]->look_at_target = nullptr;
						}
					for(auto item : parent_choices)
					{
						if( ImGui::Selectable(item->name.c_str())) 
						{
							m_editor->entities[m_editor->cur_entity_id]->look_at_target = item;
						}
					}
					ImGui::EndCombo();
				}					
								
				ImGui::EndTabItem();
			}	
					
			if((p_mesh = dynamic_cast<MeshObject* >( m_editor->entities[m_editor->cur_entity_id].get())))
			{
				

				if(ImGui::BeginTabItem("Generator"))
				{
					ImGui::Text("Mesh Object");
					std::vector<const char*> generator_types_strings = {"...", "Grid Mesh", "Box Mesh", "Cylinder Mesh"};
					static int cur_choice = 0;
					if( p_mesh->generator != nullptr)
					{
						char label[100];
						sprintf(label, "current generator : %s", generator_types_strings[(int)p_mesh->generator_type+1]);
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
				// MESH FILTERS
				if(ImGui::BeginTabItem("Filters"))
				{
					std::vector<const char *> filter_types_strings = {"..." , "transform"};
					
					static int cur_choice = -1;
					ImGui::Columns(2);
					ImGui::PushItemWidth(-1);
					if(ImGui::BeginCombo("##choose", filter_types_strings[cur_choice+1],0))
					{
						for (size_t i = 0; i < filter_types_strings.size()-1; i++)
						{
							if(ImGui::Selectable( filter_types_strings[i+1], false))
							{
								cur_choice = i;
								
							}
						}
						
						ImGui::EndCombo();												
					}
					
					ImGui::NextColumn();
					if(ImGui::Button("Add"))
					{
						if(cur_choice != -1)
						{
							p_mesh->addMeshFilter((MESH_FILTER_TYPE)cur_choice);
							p_mesh->applyFilters();
						}
					}
					ImGui::PopItemWidth();
					ImGui::Columns(1);
					ImGui::PushItemWidth(-1);			
					static int cur_selected_filter = -1;		
					if(ImGui::ListBoxHeader("##Mesh Filters"))
					{
						
						for (size_t i = 0; i < p_mesh->mesh_filters.size(); i++)
						{
							ImGui::PushID((void *)i);
							ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0,0));							
							//~ ImGui::PushItemWidth(-1);
							
							if (ImGui::ArrowButton("##up", ImGuiDir_Down)) 
							{
								if(i < p_mesh->mesh_filters.size()-1)
								{
									p_mesh->moveMeshFilter(i, i+1);
									printf("moving filter UP the pile\n"); 
									p_mesh->applyFilters();
								}
								 
								 
							}
							ImGui::SameLine();
							ImGui::PopStyleVar();
							//~ ImGui::PushItemWidth(-1);

							if (ImGui::ArrowButton("##down", ImGuiDir_Up)) 
							{
								if(i > 0)
								{
									p_mesh->moveMeshFilter(i, i-1);
									printf("moving filter DOWN the pile\n"); 
									p_mesh->applyFilters();
								} 
							}
							ImGui::SameLine();		


							if (ImGui::Button("X")) 
							{

									p_mesh->deleteMeshFilter(i);
									printf("Deleting filter from the pile\n"); 
									p_mesh->applyFilters();
								 
							}
							ImGui::SameLine();		

							//~ ImGui::PopItemWidth();
							
												
							if(ImGui::Selectable(
								p_mesh->mesh_filters[i]->name.c_str(),
								
								cur_selected_filter == (int)i))
							{
								cur_selected_filter = i;
							}
							
							ImGui::PopID();
						}
						
						ImGui::ListBoxFooter();
					}
					
					ImGui::PopItemWidth();
					
					// display filter params
					if(cur_selected_filter != -1 && cur_selected_filter <= (int)(p_mesh->mesh_filters.size()-1))
					{
						//~ static char _name[255] = {p_mesh->mesh_filters[cur_selected_filter].name.c_str()};
						if(ImGui::InputText("name", (char *)p_mesh->mesh_filters[cur_selected_filter]->name.c_str() ,200 ))
						{
							
						}
						
						int inc = 0;
						for(auto param : p_mesh->mesh_filters[cur_selected_filter]->params)
						{
							paramWidget(param, inc, [p_mesh](){
								p_mesh->applyFilters();
								p_mesh->buildVBO();
								
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



void UI::showAllDialogs()
{
	b_show_options_dialog  = true;
	//~ b_show_cameras_dialog  = true;
	b_show_entities_dialog = true;
}

void UI::hideAllDialogs()
{
	b_show_options_dialog  = false;
	//~ b_show_cameras_dialog  = false;	
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
//~ 
	//~ if(b_show_cameras_dialog)
		//~ camerasDialog();
	
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
			//~ p_int->setValue(_val);
			
			ActionParamChange<int> action(p_int, _val);
			m_editor->actions.push_back(action);
			callback();
		}
	}
	else if(( p_float = dynamic_cast<Param<float>*>( param )))
	{
		float _val = p_float->getValue();
		if( ImGui::DragFloat(p_float->getName().c_str(), &_val, 0.05f))
		{
			//~ printf("set int value\n");
			//~ p_float->setValue(_val);
			ActionParamChange<float> action(p_float, _val);
			m_editor->actions.push_back(action);			
			callback();
		}
				
	}
	else if( ( p_vec3 = dynamic_cast<Param<glm::vec3>*>( param )))
	{
		glm::vec3 _val = p_vec3->getValue();
		
		ImGui::PushID((const void*)imgui_ID);
		
		ImGui::Text(p_vec3->getName().c_str());
		ImGui::Columns(3);
		ImGui::PushStyleColor(ImGuiCol_Border, ImVec4(0.91f, 0.05f, 0.05f, 0.25f));
		ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, 1.0f);
		ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0,0));	
		ImGui::PushItemWidth(-1);	
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
		
		ImGui::PopStyleColor();
		ImGui::PopStyleVar();
		ImGui::PopStyleVar();
		ImGui::PopItemWidth();	
		
		ImGui::NextColumn();
		
		ImGui::PushStyleColor(ImGuiCol_Border, ImVec4(0.05f, 0.91f, 0.05f, 0.25f));
		ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, 1.0f);		
		ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0,0));	
		ImGui::PushItemWidth(-1);	
		
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
		ImGui::PopStyleColor();
		ImGui::PopStyleVar();
		ImGui::PopStyleVar();
		ImGui::PopItemWidth();	
			
		ImGui::NextColumn();	
		
		ImGui::PushStyleColor(ImGuiCol_Border, ImVec4(0.05f, 0.05f, 0.91f, 0.25f));
		ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, 1.0f);	
		ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0,0));	
		ImGui::PushItemWidth(-1);	
				
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
		
		ImGui::PopStyleColor();
		ImGui::PopStyleVar();		
		ImGui::PopStyleVar();		
		ImGui::PopItemWidth();	
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
