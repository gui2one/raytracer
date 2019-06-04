#include <stdio.h>
#include "editor.h"
#include "ui/ui.h"


int main(int argc, char** argv){
	
	
	
	printf("Hello Editor\n");
	Editor editor;
	UI ui;
	editor.init();
	ui.init(&editor);
	
	while( editor.is_running)
	{
		
		editor.update();
		ui.draw();
		
		SDL_GL_SwapWindow(editor.window);
		SDL_Delay(1000/60);
			
	}
	//~ editor.saveScene();
	return 0;
}
