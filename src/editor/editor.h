#ifndef EDITOR_H
#define EDITOR_H

#include <regex>
#include "../pch.h"
#include "../scene_file_loader.h"
#include "../shader.h"
#include "editor_camera.h"
#include "entity3d.h"
#include "construction_grid.h"
#include "../utils/mesh_utils.h"

#include "raycaster2.h"
#include "kdnode2.h"

#include "handles/base_handle.h"

#include "../vendor/imgui/imgui_impl_sdl.h"






class Editor
{
public :
	
	Editor();
	

	void init();
	void initHandlesFBODepthBuffer();
	void initHandlesFBOTexture();
	void initHandlesFBO();
	void renderHandlesFBO();
	void displayHandlesFBO();

	void manageEvents();
	void buildDisplayGeoData();
	void saveScene();
	void setCamPosFromPolar(float u, float v, float _radius, glm::vec3 center);
	void cycleCameras();
	void update();
	
	void unselectAll();
	void addMeshObject();
	void addCamera();
	void deleteEntity(int id);
	void deleteCamera(int id);
	
	std::string uniqueEntityName(std::string _str);
	~Editor();
	
	Shader 
		default_shader, 
		line_shader,
		fbo_shader;
	
	
	
	bool left_mouse_button_down = false;
	bool left_mouse_dragging = false;
	
	bool right_mouse_button_down = false;
	bool right_mouse_dragging = false;
	
	bool b_handle_clicked = false;
	bool b_handle_dragged = false;
	
	
	float mouse_old_x = 0.0;
	float mouse_old_y = 0.0;
	float mouse_delta_x, mouse_delta_y;	

	bool mouse_over_ui = false;
	bool keyboard_captured = false;

	
	std::vector<std::shared_ptr<Entity3D> > entities;
	std::vector<std::shared_ptr<Camera> > cameras;	
	int cur_cam_id = -1;	
	std::vector<OGL_geometry_data> OGL_geometry_datas;
	
	// window params
	int w_width, w_height;

	bool is_running = true;
	
	int update_inc = 0;
	
	SDL_Window * window;
	//~ SDL_Renderer * w_renderer;	
	SDL_GLContext gl_context;
	
	int kd_polygon_limit;
	



	ConstructionGrid c_grid;
	bool show_construction_grid = true;
	void toggleConstructionGrid();
	
	bool show_wireframe = false;
	
	int cur_entity_id = -1;
	
	std::shared_ptr<BaseHandle> handle;
	
	unsigned int handles_fbo = 0;
	unsigned int handles_fbo_depth = 0;
	unsigned int handles_fbo_texture = 0;
	unsigned int handles_fbo_vbo = 0; //// for 'screen'
};
#endif /* EDITOR_H */
