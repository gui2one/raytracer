#ifndef MESH_FILTER_H
#define MESH_FILTER_H

#include "../../pch.h"
#include "../param.h"
#include "../../mesh.h"


enum MESH_FILTER_TYPE{
	TRANSFORM_MESH_FILTER
};

class MeshFilter
{
	public:
		MeshFilter();
		
		virtual void applyFilter(Mesh& mesh){ 
			//printf("default filter apply\n"); 
		};
			
		MESH_FILTER_TYPE type;
		
		std::vector<BaseParam*> params;
		
		std::string name;
	private:
		/* add your private declarations */
};

#endif /* MESH_FILTER_H */ 
