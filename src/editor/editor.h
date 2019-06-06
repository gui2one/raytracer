#ifndef EDITOR_H
#define EDITOR_H

#include "../pch.h"
#include "../scene_file_loader.h"
#include "../shader.h"
#include "editor_camera.h"
#include "entity3d.h"
#include "construction_grid.h"
#include "../utils/mesh_utils.h"

#include "raycaster2.h"
#include "kdnode2.h"
#include <regex>

#include "../vendor/imgui/imgui_impl_sdl.h"






class Editor
{
public :
	
	Editor();
	

	void init();
	

	void manageEvents();
	void buildDisplayGeoData();
	void saveScene();
	void setCamPosFromPolar(float u, float v, float _radius, glm::vec3 center);
	void cycleCameras();
	void update();
	
	void unselectAll();
	void addMeshObject();
	void addCamera();
	void deleteCamera(int id);
	
	std::string uniqueEntityName(std::string _str);
	~Editor();
	
	Shader default_shader, line_shader;
	
	std::vector<Camera*> cameras;	
	int cur_cam_id = -1;	
	
	bool left_mouse_button_down = false;
	bool left_mouse_dragging = false;
	
	bool right_mouse_button_down = false;
	bool right_mouse_dragging = false;
	
	float mouse_old_x = 0.0;
	float mouse_old_y = 0.0;
	float mouse_delta_x, mouse_delta_y;	

	bool mouse_over_ui = false;
	bool keyboard_captured = false;
	
	//~ std::vector<unsigned int> selected_entities;
	
	std::vector<Entity3D*> entities;
	std::vector<OGL_geometry_data> OGL_geometry_datas;
	
	// window params
	int w_width, w_height;
	
	// TTF_Font* font;
	bool is_running = true;
	
	int update_inc = 0;
	
	SDL_Window * window;
	SDL_Renderer * w_renderer;	
	SDL_GLContext gl_context;
	
	int kd_polygon_limit;
	
	// KD Nodes and raycasting stuff
	//~ void buildKDTree(Entity3D * entity, int _limit = 5);
	//~ void displayKDTree();
	//~ void collectKDBoungingBoxes(KDNode* node_ptr);
	//~ void buildKDTreeBBoxes(std::vector<KDBoundingBox> bboxes);	
	
	
	//~ std::vector<KDNode *> kd_nodes;
	
	
	//~ 
	//~ std::vector<KDBoundingBox> kd_bboxes;
	//~ GLenum kdtree_vbo = 0, kdtree_ibo = 0;
	//~ 
	//~ std::vector<float> kdtree_vertices;
	//~ std::vector<unsigned int> kdtree_indices;	


	ConstructionGrid c_grid;
	bool show_construction_grid = true;
	void toggleConstructionGrid();
	
	bool show_wireframe = false;
	
	int cur_entity_id = -1;
	
	//~ UI ui;
};
#endif /* EDITOR_H */
