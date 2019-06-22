#include "editor_mesh_utils.h"

static float degToRad(float degrees)
{
	return degrees / 180.0 * PI;
}

static void offset_indices(std::vector<unsigned int>& indices, int offset)
{
	for (size_t i = 0; i < indices.size(); i++)
	{
		indices[i] += offset;
	}
	
}

static void offsetFacesPointID(std::vector<Face>& faces, int offset)
{
	for (size_t face_id = 0; face_id < faces.size(); face_id++)
	{
		for (size_t vert_id = 0; vert_id < faces[face_id].getNumVertices(); vert_id++)
		{
			Vertex* cur_vert = &faces[face_id].vertices[vert_id];
			
			cur_vert->setPointID(cur_vert->point_id + offset);
		}
	}
}

namespace EditorMeshUtils{
	
	Mesh makeQuad(float width, float length)
	{
		Mesh mesh;
		
		std::vector<Point> points;
		
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
				points.push_back(
					Point(
						(width / (segs_width-1) * i) - width / 2, 
						(length / (segs_length-1) * j) - length / 2, 
						0.0
						)
					);			
			}
		}
		
		mesh.points = points;
		
		std::vector<Face> faces;
		

		for (int j = 0; j < segs_length-1; j++)
		{
			for (int i = 0; i < segs_width-1; i++)
			{
				Face face;
				face.setVertices(
					{ 
						Vertex(i+ j * (segs_width)), 
						Vertex(i+ j * (segs_width) + 1),
						Vertex(i+ j * (segs_width) + segs_width +1),
						Vertex(i+ j * (segs_width) + segs_width)
					}
				);
				faces.push_back(face);			
			}
		}

		mesh.faces = faces;		
		
		return mesh;
	}
	
	Mesh makeCylinder(float radius, float height, int segs_radius, int segs_height)
	{	
		Mesh mesh;
				
		std::vector<Point> points;
		for (int j = 0; j < segs_height; j++)
		{
			
			for (int i = 0; i < segs_radius; i++)
			{			
				float angle = ((float)i / (float)(segs_radius-1)) * PI * 2.0;
				points.push_back(
					Point(
						cos(angle) * radius, 
						sin(angle) * radius, 
						(float)j/ (float)(segs_height-1) * height
					)
				);			
			}
		}
		
		mesh.points = points;
		
		std::vector<Face> faces;
		

		for (int j = 0; j < segs_height-1; j++)
		{
			for (int i = 0; i < segs_radius-1; i++)
			{
				Face face;
				face.setVertices(
					{ 
						Vertex(i+ j * (segs_radius)), 
						Vertex(i+ j * (segs_radius) + 1),
						Vertex(i+ j * (segs_radius) + segs_radius +1),
						Vertex(i+ j * (segs_radius) + segs_radius)
					}
				);
				faces.push_back(face);			
			}
		}

		
		if( segs_radius >= 3)
		{
			// bottom cap
			std::vector<Vertex> bottom_verts;
			for (int i = segs_radius-1; i >= 0 ; i--)
			{
				bottom_verts.push_back(Vertex(i));
			}
			
			Face bottom_face;
			bottom_face.setVertices(bottom_verts);
			faces.push_back(bottom_face);		
			
			
			// top cap
			std::vector<Vertex> top_verts;
			for (int i = segs_radius * (segs_height-1); i < (segs_radius * segs_height)-1 ; i++)
			{
				top_verts.push_back(Vertex(i));
			}
			
			Face top_face;
			top_face.setVertices(top_verts);
			faces.push_back(top_face);							
		}
		mesh.faces = faces;		
		
		return mesh;
	}		
	
	Mesh merge(Mesh& mesh1, Mesh& mesh2)
	{
		Mesh merged = mesh1;
		Mesh temp2 = mesh2;

		merged.points.insert(
			merged.points.end(), temp2.points.begin(), temp2.points.end()
		);
		

		offsetFacesPointID(temp2.faces, mesh1.points.size());

		merged.faces.insert(
			merged.faces.end(), temp2.faces.begin(), temp2.faces.end()
		);
		
		return merged;
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
