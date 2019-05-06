#include "mesh_utils.h"



MeshUtils::MeshUtils()
{
	
}

Mesh MeshUtils::makeQuad()
{
	Mesh mesh;
	
	
	
	std::vector<Point> points;
	//~ Vertex vert1(glm::vec3(0.0,1.0,2.0));
	points.push_back(Point(0.0, 0.0, 0.0));
	points.push_back(Point(1.0, 0.0, 0.0));
	points.push_back(Point(1.0, 1.0, 0.0));
	points.push_back(Point(0.0, 1.0, 0.0));
	
	
	mesh.points = points;
	
	std::vector<Face> faces;
	Face face;
	face.setVertices({ Vertex(0), Vertex(1), Vertex(2), Vertex(3)});
	faces.push_back(face);
	mesh.faces = faces;
	//~ printf("vertex --> %.3f, %.3f, %.3f\n", verts[0].position.x, verts[0].position.y, verts[0].position.z);
	
	return mesh;
}

Mesh MeshUtils::makeSimpleBox(float w, float h)
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
	
	
	
	
	mesh.faces.reserve(6);
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

Mesh MeshUtils::uniquePoints(Mesh input_mesh)
{
	Mesh mesh;
	for (int i = 0; i < input_mesh.faces.size(); i++)
	{
		std::vector<Vertex> new_vertices;
		
		for (int vert_id = 0; vert_id < input_mesh.faces[i].getNumVertices(); vert_id++)
		{
			
			mesh.points.push_back( Point( input_mesh.points[input_mesh.faces[i].getVertex(vert_id).point_id].position));
			
			Vertex vert;
			vert.point_id = mesh.points.size() - 1;
			new_vertices.push_back(vert);
		}
		
		input_mesh.faces[i].setVertices( new_vertices);		
	}
	
	mesh.faces = input_mesh.faces;
	
	return mesh;
	
}

void MeshUtils::translate(Mesh& _mesh, glm::vec3 _vec)
{
	for (int i = 0; i < _mesh.points.size(); i++)
	{
		_mesh.points[i].position = _mesh.points[i].position + _vec;
	}
	
}

void MeshUtils::scale(Mesh& _mesh, glm::vec3 _scale)
{
	for (int i = 0; i < _mesh.points.size(); i++)
	{
		_mesh.points[i].position = _mesh.points[i].position * _scale;
	}	
}

void MeshUtils::rotate(Mesh& _mesh, glm::vec3 _rot)
{
	for (int i = 0; i < _mesh.points.size(); i++)
	{
		_mesh.points[i].position = glm::rotateX(_mesh.points[i].position, _rot.x);
		_mesh.points[i].position = glm::rotateY(_mesh.points[i].position, _rot.y);
		_mesh.points[i].position = glm::rotateZ(_mesh.points[i].position, _rot.z);
		
	}	
}
