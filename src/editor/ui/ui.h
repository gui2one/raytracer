#ifndef UI_H
#define UI_H

#include "../../pch.h"


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
	void actionsDialog();
	//~ void camerasDialog();
	
	void showAllDialogs();
	void hideAllDialogs();
	void draw();
	
	void paramWidget( BaseParam * param, int imgui_ID, std::function<void()> callback = [](){});
		
		
	bool b_show_options_dialog = false;
	bool b_show_entities_dialog = true;
	bool b_show_cameras_dialog = true;
	
	bool b_show_actions_dialog = true;
private:
	SDL_Window * m_window;
	Editor * m_editor;
	
};

#endif /* UI_H */ 
