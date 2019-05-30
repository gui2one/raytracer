#ifndef MESH_UTILS_H
#define MESH_UTILS_H

#include "../pch.h"
#include "../mesh.h"

#include <opensubdiv/far/topologyDescriptor.h>
#include <opensubdiv/far/stencilTableFactory.h>
#include <opensubdiv/osd/cpuEvaluator.h>
#include <opensubdiv/osd/cpuVertexBuffer.h>



class MeshUtils
{
	public:
		MeshUtils();
		
		Mesh makeQuad();
		Mesh makeSimpleBox(float w = 1.0, float h = 1.0);
		
		Mesh uniquePoints(Mesh input_mesh);
		
		
		
		void scale(Mesh& _mesh, glm::vec3 _scale);
		void translate(Mesh& _mesh, glm::vec3 _vec);
		void rotate(Mesh& _mesh, glm::vec3 _vec);
			
			
		
		
	private:
		/* add your private declarations */
};

#endif /* MESH_UTILS_H */ 
