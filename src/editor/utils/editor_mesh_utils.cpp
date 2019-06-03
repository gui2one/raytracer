#include "editor_mesh_utils.h"

namespace EditorMeshUtils{
	
	Mesh makeQuad()
	{
		Mesh mesh;
		
		
		
		std::vector<Point> points;
		//~ Vertex vert1(glm::vec3(0.0,1.0,2.0));
		points.push_back(Point(0.0, 0.0, 0.0));
		points.push_back(Point(0.0, 1.0, 0.0));
		points.push_back(Point(1.0, 1.0, 0.0));
		points.push_back(Point(1.0, 0.0, 0.0));
		
		
		mesh.points = points;
		
		std::vector<Face> faces;
		Face face;
		face.setVertices({ Vertex(0), Vertex(1), Vertex(2), Vertex(3)});
		faces.push_back(face);
		mesh.faces = faces;
		//~ printf("vertex --> %.3f, %.3f, %.3f\n", verts[0].position.x, verts[0].position.y, verts[0].position.z);
		
		return mesh;		
	}
	
	Mesh makeSimpleBox()
	{
		Mesh mesh;
		
		//~ std::vector<Point> points;
		
		mesh.points.reserve(8);
		
		mesh.points.emplace_back(Point(0.0, 0.0, 0.0));
		mesh.points.emplace_back(Point(0.0, 1.0, 0.0));
		mesh.points.emplace_back(Point(1.0, 1.0, 0.0));
		mesh.points.emplace_back(Point(1.0, 0.0, 0.0));
		
		mesh.points.emplace_back(Point(0.0, 0.0, 1.0));
		mesh.points.emplace_back(Point(0.0, 1.0, 1.0));
		mesh.points.emplace_back(Point(1.0, 1.0, 1.0));
		mesh.points.emplace_back(Point(1.0, 0.0, 1.0));
		
		
		
		
		//~ mesh.faces.reserve(6);
		mesh.faces.insert( mesh.faces.end(), {
			Face( { Vertex(0), Vertex(1), Vertex(2), Vertex(3) }),
			Face( { Vertex(4), Vertex(5), Vertex(6), Vertex(7) }),
			
			Face( { Vertex(0), Vertex(1), Vertex(5), Vertex(4) }),
			Face( { Vertex(1), Vertex(2), Vertex(6), Vertex(5) }),
			Face( { Vertex(2), Vertex(3), Vertex(7), Vertex(6) }),
			Face( { Vertex(3), Vertex(0), Vertex(4), Vertex(7) })
		});


		
		return mesh;
	}
};
