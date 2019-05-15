#include "scene_file_loader.h"


SceneFileLoader::SceneFileLoader()
{
	
}

void SceneFileLoader::load(std::string path, std::vector<Mesh> & meshes, std::vector<RTMaterial> & materials, std::vector<Light> & lights)
{
	std::ifstream infile;
	infile.open(path.c_str() , std::ifstream::in);
	std::string full_json_string;
	std::string line;
	while( std::getline(infile, line)){
		full_json_string += line;
		//~ printf("line --> %s\n", line.c_str());
	}
	
	infile.close();
	
	//~ printf("%s\n", full_json_string.c_str());
	

	try{
		//~ JsonScene json_scene = JSON::consumer<JsonScene>::convert(full_json_string);
		
		//~ for (int i = 0; i < json_scene.materials.size(); i++)
		//~ {
			
			//~ RTMaterial mat = json_scene.materials[i].create();
			//~ materials.push_back(mat);
			//~ 
		//~ }
		//~ 
		//~ printf("File Meshes : \n");
		//~ for (int i = 0; i < json_scene.file_meshes.size(); i++)		
		//~ {
			//~ printf("\t%d -- path : %s\n", i, json_scene.file_meshes[i].path.c_str());
			//~ Mesh mesh = json_scene.file_meshes[i].create();
//~ 
			//~ meshes.push_back(mesh);
			//~ 
		//~ }
		
		
		
		
		//~ printf("result color : %.3f %.3f %.3f %.3f\n", json_material.color.r, json_material.color.g, json_material.color.b, json_material.color.a);
	}catch(JSON::json_exception e){
		printf("problem with JSON \n");
	}
	
	
	
}


