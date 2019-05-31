#include "scene_file_loader.h"


SceneFileLoader::SceneFileLoader()
{
	
}

void SceneFileLoader::loadSceneFile(std::string path, std::vector<Mesh> & meshes, std::vector<RTMaterial> & materials, std::vector<Light> & lights)
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
		JsonScene json_scene = JSON::consumer<JsonScene>::convert(full_json_string);
		//~ 

		MeshUtils mesh_utils;
		for (size_t i = 0; i < json_scene.materials.size(); i++)
		{
			//~ 
			try{
				
				RTMaterial mat = json_scene.materials[i].create();
				materials.push_back(mat);
			}catch(JSON::json_exception e){
				printf("\tproblem with JSON Material \n");
			}
		}
		
		printf("File Meshes : \n");
		for (size_t i = 0; i < json_scene.file_meshes.size(); i++)		
		{
			printf("\t%d -- path : %s\n", i, json_scene.file_meshes[i].path.c_str());
			Mesh mesh = json_scene.file_meshes[i].create();
			// mesh = mesh_utils.uniquePoints(mesh);
			mesh.computeNormals();
			
			mesh.material = &materials[json_scene.file_meshes[i].material_id];
			mesh.material->loadDiffTexture();
			if(mesh.material->diff_texture.is_valid == false)
			{
				printf("Creating Fallback Texture\n");
				mesh.material->createFallbackTexture();
			}
			meshes.push_back(mesh);
			
		}
		for (size_t i = 0; i < json_scene.lights.size(); i++)		
		{		
			Light light = json_scene.lights[i].create();
			lights.push_back(light);
		}
		
		
		
		//~ printf("result color : %.3f %.3f %.3f %.3f\n", json_material.color.r, json_material.color.g, json_material.color.b, json_material.color.a);
	}catch(JSON::json_exception e){
		printf("problem with Scene JSON \n");
	}
	
	
	
}


RenderOptions SceneFileLoader::loadOptionsFile(std::string path)
{
	RenderOptions render_options;
	std::ifstream infile;
	infile.open(path.c_str() , std::ifstream::in);
	std::string full_json_string;
	std::string line;
	while( std::getline(infile, line)){
		full_json_string += line;
		//~ printf("line --> %s\n", line.c_str());
	}
	
	infile.close();	
	
	try{
		render_options = JSON::consumer<RenderOptions>::convert(full_json_string);
		
		printf("render option kd limit --> %d\n", render_options.kd_polygon_limit);
		
	}catch(JSON::json_exception e){
		printf("problem with Render Options JSON \n");
	}	
	
	printf("scene options path : %s\n", path.c_str());
	
	return render_options;
}
