#ifndef MESH_UTILS_H
#define MESH_UTILS_H

#include "../pch.h"
#include "../mesh.h"

class MeshUtils
{
	public:
		MeshUtils();
		
		Mesh makeQuad();
		Mesh makeSimpleBox(float w, float h);
		
		Mesh uniquePoints(Mesh input_mesh);
		
		void translate(Mesh& _mesh, glm::vec3 _vec);
		void scale(Mesh& _mesh, glm::vec3 _scale);
			
	private:
		/* add your private declarations */
};

#endif /* MESH_UTILS_H */ 
