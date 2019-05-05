#include "pch.h"

//~ #include <thread>

#include "mesh.h"
#include "utils/mesh_utils.h"
#include "utils/objLoader.h"
#include "renderer.h"


struct LoadedMeshData
{
	std::string path;
	float scale = 1.0;
	glm::vec3 rotate;
	glm::vec3 translate;
	
};

std::vector<std::string> file_mesh_paths;
std::vector<LoadedMeshData> loaded_mesh_datas;
std::vector<Mesh> meshes;

int kd_polygon_limit = 50;

Renderer renderer;


void createMeshes()
{
	if( loaded_mesh_datas.size() > 0){
		
		ObjLoader loader;
		MeshUtils mesh_utils;
		for (int i = 0; i < loaded_mesh_datas.size(); i++)
		{
			Mesh m = loader.assimp_load(loaded_mesh_datas[i].path);
			m.triangulate();
			m.computeNormals();
			
			Color clr;
			m.material.color = clr;
			
			float scale = loaded_mesh_datas[i].scale;
			glm::vec3 rotate = loaded_mesh_datas[i].rotate;
			glm::vec3 translate = loaded_mesh_datas[i].translate;
			printf("scale --> %.3f \n", scale);
			mesh_utils.scale(m, glm::vec3(scale, scale, scale));
			mesh_utils.rotate(m, glm::vec3(rotate.x, rotate.y, rotate.z));
			mesh_utils.translate(m, glm::vec3(translate.x, translate.y, translate.z));
			meshes.push_back(m);
			
		}
		
		
		
	}

	
	
	renderer.meshes = meshes;
	
	renderer.buildRenderGeometry();	
}


int main(int argc, char ** argv){
	
	
	if(argc > 1){
		
		if(argc % 2 != 1){
			printf("bad command...\n");
		}else{
			
			for (int i = 1; i < (argc-1); i+=2)
			{
				std::string cmd(argv[i]);
				std::string arg(argv[i+1]);
				
				if( cmd == "-o" ){
					LoadedMeshData m_data;
					m_data.path = arg;
					
					
					int temp_i = i+2;
					
					std::string cmd2(argv[temp_i]);
					std::string arg2(argv[temp_i+1]);
					while( (cmd2 == "-s" || cmd2 == "-r" || cmd2 == "-t") && argv[temp_i] != NULL)// || argv[temp_i] == "-t" || argv[temp_i] == "-r")
					{
						//~ printf("--------WHILE----------\n");
						//~ 
						if( cmd2 == "-s" ){
							//~ // scaling
							printf("SCALING !!!!%s\n", argv[temp_i]);
							m_data.scale = std::atof(std::string(argv[temp_i+1]).c_str());
							
							temp_i += 2;
							
						}else if( cmd2 == "-t"){
							float x = std::atof(std::string(argv[temp_i+1]).c_str());
							float y = std::atof(std::string(argv[temp_i+2]).c_str());
							float z = std::atof(std::string(argv[temp_i+3]).c_str());
							printf("TRANSLATING !!!! %.3f %.3f %.3f\n", x, y ,z);
							
							m_data.translate = glm::vec3(x, y, z);
							temp_i += 4;
						}else if( cmd2 == "-r"){
							float x = std::atof(std::string(argv[temp_i+1]).c_str());
							float y = std::atof(std::string(argv[temp_i+2]).c_str());
							float z = std::atof(std::string(argv[temp_i+3]).c_str());
							printf("ROTATING !!!! %.3f %.3f %.3f\n", x, y ,z);
							
							m_data.rotate = glm::vec3(x, y, z);
							
							temp_i += 4;
						}
						
						
						if( argv[temp_i] != NULL)
							cmd2 = std::string(argv[temp_i]);
						else
							break;
					}
					
					i = temp_i - 2; // -2 because i goes back to the for loop and is incremented by 2

					loaded_mesh_datas.push_back(m_data);
				}
				else if(cmd == "-limit"){
					kd_polygon_limit = atoi(arg.c_str());
				}
				
				printf("-----------------------\n");
				printf("command  :%s\n", cmd.c_str());
				printf("argument :%s\n", arg.c_str());				
				printf("°°°°°°°°°°°°°°°°°°°°°°°\n\n");
			}
			

		}
	}
	renderer.init(kd_polygon_limit);
	
	createMeshes();

	//~ printf("num points = %d\n", tri_mesh.points.size());
	//~ printf("num faces = %d\n", tri_mesh.faces.size());	
	
	Camera camera;
	camera.position.y = 5.0;
		

	while(!renderer.shouldClose()){
			
		renderer.displayScene();

	}		


	
		
	
	return 0;
}
