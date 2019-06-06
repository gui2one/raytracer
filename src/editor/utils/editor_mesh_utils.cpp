#include "editor_mesh_utils.h"

static float degToRad(float degrees)
{
	return degrees / 180.0 * PI;
}

namespace EditorMeshUtils{
	
	Mesh makeQuad(float width, float length)
	{
		Mesh mesh;
		
		
		
		std::vector<Point> points;
		//~ Vertex vert1(glm::vec3(0.0,1.0,2.0));
		points.push_back(Point(0.0, 0.0, 0.0));
		points.push_back(Point(0.0,   length, 0.0));
		points.push_back(Point(width, length, 0.0));
		points.push_back(Point(width, 0.0, 0.0));
		
		
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
	
	Mesh makeGrid(float width, float length, int segs_width, int segs_length)
	{
		Mesh mesh;
		
		
		std::vector<Point> points;
		for (int j = 0; j < segs_length; j++)
		{
			
			for (int i = 0; i < segs_width; i++)
			{			
				points.push_back(Point(width / (segs_width-1) * (i)  , length / (segs_length-1) * (j), 0.0));
				//~ points.push_back(Point(width / (segs_width-1) * (i)  , length / (segs_length-1) * (j+1), 0.0));
				//~ points.push_back(Point(width / (segs_width-1) * (i+1), length / (segs_length-1) * (j+1), 0.0));
				//~ points.push_back(Point(width / (segs_width-1) * (i+1), length / (segs_length-1) * (j), 0.0));			
			}
		}
		

		
		
		mesh.points = points;
		printf("num points in Grid : %d\n", points.size());
		std::vector<Face> faces;
		//~ int num_faces = (segs_width-1) * (segs_length-1);

		for (int j = 0; j < segs_length-1; j++)
		{
			for (int i = 0; i < segs_width-1; i++)
			{
				Face face;
				face.setVertices(
					{ 
						Vertex(i+ j * (segs_width-1)), 
						Vertex(i+ j * (segs_width-1) + 1), 
						Vertex(i+ j * (segs_width-1) + segs_width +1),
						Vertex(i+ j * (segs_width-1) + segs_width)
					}
				);
				faces.push_back(face);			
			}
		}

		mesh.faces = faces;		
		printf("num faces in Grid : %d\n", faces.size());
		return mesh;
	}
	
	void translate(Mesh& _mesh, glm::vec3 _vec)
	{
		for (size_t i = 0; i < _mesh.points.size(); i++)
		{
			_mesh.points[i].position = _mesh.points[i].position + _vec;
		}
		
	}

	void scale(Mesh& _mesh, glm::vec3 _scale)
	{
		for (size_t i = 0; i < _mesh.points.size(); i++)
		{
			_mesh.points[i].position = _mesh.points[i].position * _scale;
		}	
	}

	void rotate(Mesh& _mesh, glm::vec3 _rot)
	{
		for (size_t i = 0; i < _mesh.points.size(); i++)
		{
			_mesh.points[i].position = glm::rotateX(_mesh.points[i].position, degToRad(_rot.x));
			_mesh.points[i].position = glm::rotateY(_mesh.points[i].position, degToRad(_rot.y));
			_mesh.points[i].position = glm::rotateZ(_mesh.points[i].position, degToRad(_rot.z));
			
		}	
	}	
};
