#ifndef MESH_H
#define MESH_H

#include "pch.h"
#include "rtmaterial.h"
#include "vector3.h"

struct Point
{
	Point(){}
	Point(float x, float y, float z){
		position.x = x;
		position.y = y;
		position.z = z;
	}
	Point( glm::vec3 _position) { position = _position; }
	Point(const Point& other) : position(other.position), normal(other.normal)
	{
		//~ printf("copy Point !!\n");
	}
	
	
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec2 t_coords = glm::vec2(0.0f, 0.0f);
};

struct Vertex
{
	
	Vertex(){}
	Vertex(unsigned int _point_id){
		point_id = _point_id;
	}
	
	Vertex(const Vertex& other)
		:point_id(other.point_id), normal(other.normal)
	{
		//~ printf("copy Vertex !!\n");
	}
	
	
	
	unsigned int point_id;
	glm::vec3 normal;
	glm::vec2 t_coords = glm::vec2(0.0f, 0.0f);
};

class Face
{
	public : 
		Face(){}
		Face(std::vector<Vertex> _vertices){ vertices = _vertices; }
		Face(const Face& other)
			:vertices(other.vertices)
		{
			//~ printf("copy Face !!!!\n");
		}
		
		inline int getNumVertices(){ return vertices.size(); }
		inline Vertex getVertex(int _id) const { return vertices[_id];}
		inline void setVertices( std::vector<Vertex> _vertices){ vertices = _vertices; }
	private :
		std::vector<Vertex> vertices;
};

struct BoundingBox
{
	glm::vec3 position;
	glm::vec3 size;
};

class Mesh
{
	public:
		Mesh();
		virtual ~Mesh();
		
		void triangulate();
		void computeNormals();
		
		BoundingBox computeAABB();
		
		void printData();
		std::vector<Point> points;
		std::vector<Face> faces;
		
		RTMaterial material;
		
		glm::vec3 translate;
		glm::vec3 rotate;
		glm::vec3 scale;
		
		
		
		
	
	private:
		/* add your private declarations */
};

#endif /* MESH_H */ 
