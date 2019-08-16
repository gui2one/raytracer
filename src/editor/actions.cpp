#include "actions.h"

ActionParamChange::ActionParamChange(){
	
}

void ActionParamChange::Do(){
	printf("Doing Action\n");
}

void ActionParamChange::Undo(){
	printf("Undoing Action\n");
}
