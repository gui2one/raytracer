#ifndef MESH_H
#define MESH_H

#include "pch.h"
#include "rtmaterial.h"


struct Point
{
	Point(){}
	Point(float x, float y, float z){
		position.x = x;
		position.y = y;
		position.z = z;
	}
	Point(glm::vec3 _position) { position = _position; }
	Point(const Point& other) : position(other.position), normal(other.normal), t_coords(other.t_coords)
	{
		//~ printf("copy Point !!\n");
	}
	
	
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec2 t_coords;
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
	
	inline void setPointID(unsigned int _id)
	{
		point_id = _id;
	}
	
	
	
	unsigned int point_id;
	glm::vec3 normal;
	glm::vec2 t_coords;
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
		
		inline size_t getNumVertices(){ return vertices.size(); }
		inline Vertex getVertex(int _id) const { return vertices[_id];}
		inline void setVertices( std::vector<Vertex> _vertices){ vertices = _vertices; }
		
		std::vector<Vertex> vertices;
	private :
		
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
		Mesh(const Mesh& other);
		virtual ~Mesh();
		
		void triangulate();
		void computeNormals();
		
		BoundingBox computeAABB();
		
		void printData();
		std::vector<Point> points;
		std::vector<Face> faces;
		
		RTMaterial* material;
		
		glm::vec3 translate;
		glm::vec3 rotate;
		glm::vec3 scale;
		
		
		
		
	
	private:
		/* add your private declarations */
};

#endif /* MESH_H */ 
