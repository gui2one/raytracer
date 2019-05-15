#ifndef SCENE_FILE_LOADER_H
#define SCENE_FILE_LOADER_H


#include "pch.h"
#include "color.h"
#include "mesh.h"
#include "light.h"
#include "rtmaterial.h"
#include "utils/objLoader.h"

//-----------------------------------------------------------------------------
// Code support required for serialization.


//~ namespace glm{
	//~ namespace vec3{
		//~ public : 
			//~ void serialize(JSON::Adapter& adapter){
				//~ JSON::Class root(adpater, "glm_vec3");
				//~ JSON_E(adapter, x);
				//~ JSON_E(adapter, y);
				//~ JSON_T(adapter, z);
			//~ }
	//~ }
//~ }

class JSONExample
{
public:
    // to be JSON'ised
    std::string text;
public:
    // each class requires a public serialize function
    void serialize(JSON::Adapter& adapter)
    {
        // this pattern is required 
        JSON::Class root(adapter,"JSONExample");
        // this is the last member variable we serialize so use the _T variant
        JSON_T(adapter,text);
    }
};

struct JsonMaterial : public RTMaterial
{

	public :
	
		//~ double refl_amount;
		//~ Color color;	
	
		JsonMaterial(){
			//~ refl_amount = 0.5;
			//~ color = Color(0.1,0.5,0.8,1.0);
		}
	
		JsonMaterial(RTMaterial& material){
			color = material.color;
			refl_amount = material.refl_amount;
			refl_amount = 0.3;
		}	
		void serialize(JSON::Adapter& adapter){
			JSON::Class root(adapter, "json_material");
			JSON_E(adapter, refl_amount);
			JSON_E(adapter, shininess);
			JSON_T(adapter, color);
		}
		
		RTMaterial create(){
			RTMaterial m;
			m.shininess = shininess;
			m.refl_amount = refl_amount;
			m.color = color;
			
			return m;
		}
};

struct JsonFileMesh
{
	std::string path = "hello";
	std::vector<double> translate = {0.0, 0.0, 0.0};
	std::vector<double> rotate = {0.0, 0.0, 0.0};
	
	void serialize(JSON::Adapter& adapter){
	
		JSON::Class root(adapter, "json_file_mesh");
		JSON_E(adapter, path);
		JSON_E(adapter, rotate);
		JSON_T(adapter, translate);
	
	}
	
	Mesh create(){
		ObjLoader loader;
		
		Mesh mesh = loader.assimp_load(path);
		//~ printf("mesh points num : %d\n", mesh.points.size());
		mesh.computeNormals();
		mesh.translate.x = translate[0];
		mesh.translate.y = translate[1];
		mesh.translate.z = translate[2];		
		return mesh;
	}
};

struct JsonScene
{
	public:
		std::vector<JsonMaterial> materials;
		std::vector<JsonFileMesh> file_meshes;
		
		void serialize(JSON::Adapter& adapter){
			JSON::Class root(adapter, "json_scene");
			
			JSON_E(adapter, materials);
			JSON_T(adapter, file_meshes);
		}	
		


};

class SceneFileLoader
{
	public:
		SceneFileLoader();
		
		void load(
			std::string path, 
			std::vector<Mesh> & meshes,
			std::vector<RTMaterial> & materials, 
			std::vector<Light> & lights
		);
	private:
		/* add your private declarations */
};

#endif /* SCENE_FILE_LOADER_H */ 
