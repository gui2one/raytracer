#include <stdio.h>
#include "editor.h"

int main(int argc, char** argv){
	
	
	
	printf("Hello Editor\n");
	Editor editor;
	
	editor.init();
	
	
	while( editor.is_running)
	{
		editor.update();
	}
	//~ editor.saveScene();
	return 0;
}
