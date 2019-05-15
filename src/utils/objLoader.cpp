#include "objLoader.h"


ObjLoader::ObjLoader(){
	//~ std::cout << "ObjLoader initiatied ----\n";
}

ObjLoader::~ObjLoader(){
	//~ std::cout << "ObjLoader DELETED ----\n";
}


Mesh ObjLoader::assimp_load(std::string file_path){
	const struct aiScene* scene = NULL;
	scene = aiImportFile(file_path.c_str(), aiProcessPreset_TargetRealtime_MaxQuality);
	
	if(scene){
		
		//~ std::cout << "ObjLoader assimp loading V2 : " << file_path << "\n";
		//~ std::cout << "----------------------------\n";
		
		
		std::vector<Point> points;
		for (int i = 0; i < scene->mMeshes[0]->mNumVertices; i++){
			Point point;
			point.position.x = scene->mMeshes[0]->mVertices[i].x;
			point.position.y = scene->mMeshes[0]->mVertices[i].y;
			point.position.z = scene->mMeshes[0]->mVertices[i].z;
			
			point.normal.x = scene->mMeshes[0]->mNormals[i].x;
			point.normal.y = scene->mMeshes[0]->mNormals[i].y;
			point.normal.z = scene->mMeshes[0]->mNormals[i].z;
			
			if(scene->mMeshes[0]->HasTextureCoords(0)){
				
				//~ printf("getting t_coords from the model\n");
				point.t_coords.x = scene->mMeshes[0]->mTextureCoords[0][i].x;
				point.t_coords.y = scene->mMeshes[0]->mTextureCoords[0][i].y;
			}else{
				point.t_coords.x = 0.0;
				point.t_coords.y = 0.0;
			}
			points.push_back(point);
			//~ std::cout<< "Vertex " <<  "\n";
			//~ std::cout << "\tX: " << vertex.position.x << ", Y: " << vertex.position.y << ", Z: " << vertex.position.z <<"\n";
		
		}
		
		std::vector<Face> faces;
		for (int i = 0; i < scene->mMeshes[0]->mNumFaces; i++)
		{
			//~ std::cout << "Face : "<< i << "\n";
			std::vector<Vertex> vertices;
			
			for (int j = 0; j < scene->mMeshes[0]->mFaces[i].mNumIndices; j++)
			{
				
				unsigned int index = scene->mMeshes[0]->mFaces[i].mIndices[j];
				//~ Vertex vert(index);
				vertices.push_back(Vertex(index));
				
				
				//~ std::cout << "\tindex : "<< j << " | " << index << "\n";
			}
			//~ Face face;
			//~ face.setVertices();
			faces.push_back(Face(vertices));
		}
		
		
		Mesh mesh;
		mesh.points = points;
		mesh.faces = faces;
		
		//~ printf("num points = %d\n", mesh.points.size());
		//~ printf("num faces = %d\n", mesh.faces.size());
		return mesh;
	}
	std::cout<< "problem loading " << file_path << "\n";
	Mesh empty_mesh;
	return empty_mesh;
}
