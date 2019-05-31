#ifndef EDITOR_H
#define EDITOR_H

#include "../pch.h"
#include "../scene_file_loader.h"
#include "../shader.h"
#include "../camera.h"
#include "entity3d.h"
#include "construction_grid.h"
#include "../utils/mesh_utils.h"

#include "raycaster2.h"
#include "kdnode2.h"




class Editor
{
public :
	
	Editor();
	
	void init();
	

	void manageEvents();
	void buildDisplayGeoData();
	void saveScene();
	void setCamPosFromPolar(float u, float v, float _radius, glm::vec3 center);
	void update();
	
	
	void addMeshObject();
	
	~Editor();
	
	Shader default_shader, line_shader;
	
	Camera camera;
	float camera_u_pos = 0.5;
	float camera_v_pos = PI / 4.0 ;
	float camera_orbit_radius = 5.0;
	glm::vec3 camera_view_center = glm::vec3(0.0, 0.0, 0.0);
	
	bool left_mouse_button_down = false;
	bool left_mouse_dragging = false;
	
	bool right_mouse_button_down = false;
	bool right_mouse_dragging = false;
	
	float mouse_old_x = 0.0;
	float mouse_old_y = 0.0;
	float mouse_delta_x, mouse_delta_y;	

	bool mouse_over_ui = false;
	
	std::vector<MeshObject*> mesh_objects;
	std::vector<OGL_geometry_data> OGL_geometry_datas;
	
	// window params
	int w_width, w_height;
	
	// TTF_Font* font;
	bool is_running = true;
	
	int update_inc = 0;
	
	SDL_Window * window;
	SDL_Renderer * w_renderer;	
	SDL_GLContext gl_context;
	
	
	
	// KD Nodes and raycasting stuff
	void buildKDTree(int _limit = 5);
	void displayKDTree();
	void collectKDBoungingBoxes(KDNode* node_ptr);
	void buildKDTreeBBoxes(std::vector<KDBoundingBox> bboxes);	
	int kd_polygon_limit;
	
	std::vector<KDNode *> kd_nodes;
	
	
	
	std::vector<KDBoundingBox> kd_bboxes;
	GLenum kdtree_vbo = 0, kdtree_ibo = 0;
	
	std::vector<float> kdtree_vertices;
	std::vector<unsigned int> kdtree_indices;	


	ConstructionGrid c_grid;
	bool show_construction_grid = true;
	void toggleConstructionGrid();
	
	//~ UI ui;
};
#endif /* EDITOR_H */
