#ifndef UI_H
#define UI_H

#include "../../pch.h"
#include "../vendor/imgui/imgui.h"
#include "../vendor/imgui/imgui_impl_sdl.h"
#include "../vendor/imgui/imgui_impl_opengl3.h"

#include "../editor.h"
//~ class Editor;
//~ typedef Editor;
class UI
{
public:
	UI();
	
	void init(Editor* editor);
	
	void menu();
	void optionsDialog();
	void entitiesDialog();
	void camerasDialog();
	
	void showAllDialogs();
	void hideAllDialogs();
	void draw();
	
	void paramWidget(BaseParam * param);
		
		
	bool b_show_options_dialog = false;
	bool b_show_entities_dialog = true;
	bool b_show_cameras_dialog = true;
private:
	SDL_Window * m_window;
	Editor * m_editor;
	
};

#endif /* UI_H */ 
