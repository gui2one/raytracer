#ifndef EDITOR_MESH_UTILS_H
#define EDITOR_MESH_UTILS_H

#include "../../pch.h"
#include "../../mesh.h"
namespace EditorMeshUtils{
	
	
	Mesh makeQuad(float width, float length);
	Mesh makeSimpleBox();
	
	Mesh makeGrid(float width, float length, int segs_width, int segs_length);
	Mesh makeCylinder(float radius, float height, int segs_radius, int segs_height);
	Mesh merge(Mesh& mesh1, Mesh& mesh2);
	
	void scale(Mesh& _mesh, glm::vec3 _scale);
	void translate(Mesh& _mesh, glm::vec3 _vec);
	void rotate(Mesh& _mesh, glm::vec3 _vec);	
};

#endif /* EDITOR_MESH_UTILS_H */
