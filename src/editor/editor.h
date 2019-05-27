#ifndef EDITOR_H
#define EDITOR_H

#include "../pch.h"
#include "../scene_file_loader.h"
#include "../shader.h"
#include "../camera.h"
#include "entity3d.h"
#include "../utils/mesh_utils.h"

#include "ui/ui_text.h"



//~ #include "vendor/undo.h"


class Editor
{
public :
	
	Editor();
	
	void init();
	
	SDL_Window * window;
	SDL_Renderer * w_renderer;
	void manageEvents();
	void buildDisplayGeoData();
	void saveScene();
	void update();
	~Editor();
	
	Shader default_shader, font_shader;
	Camera camera;
	std::vector<MeshObject> mesh_objects;
	std::vector<OGL_geometry_data> OGL_geometry_datas;
	
	// window params
	int w_width, w_height;
	
	TTF_Font* font;
	bool is_running = true;
	
	int update_inc = 0;
	
	std::vector<UIText> ui_texts;
};
#endif /* EDITOR_H */
