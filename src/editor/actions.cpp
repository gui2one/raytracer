#include "actions.h"

ActionEditorAddEntity::ActionEditorAddEntity(ENTITY_TYPE type) : Action()
{
	m_type = type;
	if( m_type == CAMERA ){
		
	}else if(m_type == MESH_OBJECT){
		
	}else if(m_type == NULL_OBJECT){
		
	}
}

void ActionEditorAddEntity::undo(){
	printf("undoing add entity Action\n");
}
