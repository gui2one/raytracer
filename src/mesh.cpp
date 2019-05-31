#include "mesh.h"


Mesh::Mesh() : translate(glm::vec3(0.0, 0.0, 0.0)),rotate(glm::vec3(0.0, 0.0, 0.0)), scale(glm::vec3(1.0, 1.0, 1.0))
{
	
}

//~ Mesh::Mesh(const Mesh& other):translate(other.translate), rotate(other.rotate),	scale(other.scale)
//~ {
	//~ 
//~ }


Mesh::~Mesh()
{
	
}

void Mesh::triangulate()
{
	Mesh tri_mesh;
	std::vector<Face> new_faces;
	//~ int cur_id = 0;
	for(size_t i = 0; i < faces.size(); i++)
	{
		unsigned int num_verts = faces[i].getNumVertices();


			
		unsigned int num_tris = num_verts - 3 + 1;
		
		for (size_t tri = 0; tri < num_tris; tri++)
		{

			Face face;
			face.setVertices(					
				{ 
					Vertex(faces[i].getVertex(0).point_id),
					Vertex(faces[i].getVertex(tri+1).point_id),
					Vertex(faces[i].getVertex(tri+2).point_id)
				}
			);
			
			new_faces.push_back(face);

		}
			

	}
	

	//~ tri_mesh.points = points;
	faces = new_faces;
	
	
	//~ return tri_mesh;
}

void Mesh::printData()
{
	printf("Mesh Data ----------------\n");
	
	printf("\tPoints: \n");
	for (size_t i = 0; i < points.size(); i++)
	{
		printf("\t\t%02d -- %.2f %.2f %.2f\n", i, points[i].position.x, points[i].position.y, points[i].position.z);
	}
	
	printf("\n\tFaces:\n");
	

	for(size_t face_id = 0; face_id < faces.size(); face_id++)
	{
		
		unsigned int num_verts = faces[face_id].getNumVertices();
		for (size_t i = 0; i < num_verts; i++)
		{
			
			printf(" %d", faces[face_id].getVertex(i).point_id);
		}
		
		printf("\n");
		
		printf("normal --> %.2f %.2f %.2f\n",faces[face_id].getVertex(0).normal.x, faces[face_id].getVertex(0).normal.y, faces[face_id].getVertex(0).normal.z);
	
	}	
	
	
}

void Mesh::computeNormals()
{
	// compute flat face normals
	//~ if( faces.size() > 2)
	//~ {
		for (size_t face_id = 0; face_id < faces.size(); face_id++)
		{
			Point pA = points[faces[face_id].getVertex(0).point_id];
			Point pB = points[faces[face_id].getVertex(1).point_id];
			Point pC = points[faces[face_id].getVertex(2).point_id];
			
			glm::vec3 AB = pB.position - pA.position;
			glm::vec3 AC = pC.position - pA.position;
			
			glm::vec3 cross = glm::normalize(glm::cross(glm::normalize(AB), glm::normalize(AC)));
			
			std::vector<Vertex> vertices;
			for (size_t vert_id = 0; vert_id < faces[face_id].getNumVertices(); vert_id++)
			{
				Vertex vert(faces[face_id].getVertex(vert_id).point_id);
				vert.normal = cross;
				vertices.push_back(vert);
			}
			
			faces[face_id].setVertices(vertices);
			
		}
		
		// compute points normals
		
		// create an array of vec3 for normals
		std::vector<glm::vec3> point_normals(points.size());
		std::vector<int> num_normals(points.size());
		// init values to zeros
		for (size_t i = 0; i < point_normals.size(); i++)
		{
			point_normals[i] = glm::vec3(0.0, 0.0, 0.0);
			num_normals[i] = 0;
		}
		
		for (size_t face_id = 0; face_id < faces.size(); face_id++)
		{
			for (size_t vert_id = 0; vert_id < faces[face_id].getNumVertices(); vert_id++)
			{
				int point_id = faces[face_id].getVertex(vert_id).point_id;
				//~ Point point = points[point_id];
				
				num_normals[point_id]++;
				point_normals[point_id] = point_normals[point_id] + faces[face_id].getVertex(vert_id).normal;
			}			
		}		
		
		for (size_t i = 0; i < point_normals.size(); i++)
		{
			point_normals[i] /= num_normals[i];
			
			// finally set normal on point
			points[i].normal = point_normals[i];
		}
		
		
		
		
		
	//~ }
}


BoundingBox Mesh::computeAABB()
{
	BoundingBox bbox;
	float minx = 10000000.0;
	float miny = 10000000.0;
	float minz = 10000000.0;
	
	float maxx = -10000000.0;
	float maxy = -10000000.0;
	float maxz = -10000000.0;
	
	for (size_t i = 0; i < points.size(); i++)
	{
		//~ printf("point %d !!!!!\n",i);
		if(points[i].position.x < minx){
			minx = points[i].position.x;
		}else if(points[i].position.x > maxx){
			maxx = points[i].position.x;
		}
		
		if(points[i].position.y < miny){
			miny = points[i].position.y;
		}else if(points[i].position.y > maxy){
			maxy = points[i].position.y;
		}		
		
		if(points[i].position.z < minz){
			minz = points[i].position.z;
		}else if(points[i].position.z > maxz){
			maxz = points[i].position.z;
		}				
	}
	
	bbox.position = glm::vec3(minx, miny, minz);
	bbox.size = glm::vec3(maxx - minx, maxy - miny, maxz - minz);
	
	return bbox;
	
}
