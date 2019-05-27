#ifndef SCENE_FILE_LOADER_H
#define SCENE_FILE_LOADER_H


#include "pch.h"
#include "color.h"
#include "mesh.h"
#include "light.h"
#include "rtmaterial.h"
#include "utils/mesh_utils.h"
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


struct JsonMaterial : public RTMaterial
{

	public :
	
		//~ double refl_amount;
		//~ Color color;	
	
		JsonMaterial(){

		}
	

		void serialize(JSON::Adapter& adapter){
			JSON::Class root(adapter, "json_material");
			JSON_E(adapter, refl_amount);
			JSON_E(adapter, shininess);
			JSON_E(adapter, color);
			JSON_T(adapter, diff_texture_path);
		}
		
		RTMaterial create(){
			RTMaterial m;
			m.shininess = shininess;
			m.refl_amount = refl_amount;
			m.color = color;
			m.diff_texture_path = diff_texture_path;
			
			return m;
		}
};

struct JsonFileMesh : public Mesh
{
	std::string path = "hello";
	int material_id;
	std::vector<double> translate;
	std::vector<double> rotate;
	std::vector<double> scale;
	
	
	JsonFileMesh()
	{
		translate.reserve(3);
		rotate.reserve(3);
		scale.reserve(3);
	};
	

	//~ JsonFileMesh(Mesh& mesh){
		//~ translate[0] = mesh.translate.x;
		//~ translate[1] = mesh.translate.y;
		//~ translate[2] = mesh.translate.z;
	//~ }
	//~ 
	void serialize(JSON::Adapter& adapter){
	
		JSON::Class root(adapter, "json_file_mesh");
		JSON_E(adapter, path);		
		JSON_E(adapter, material_id);		
		JSON_E(adapter, translate);
		JSON_E(adapter, rotate);
		JSON_T(adapter, scale);
	
	}
	
	Mesh create(){
		
		MeshUtils mesh_utils;
		ObjLoader loader;
		
		Mesh mesh = loader.assimp_load(path);
		//~ printf("mesh points num : %d\n", mesh.points.size());
		mesh.computeNormals();
		//~ mesh.translate.x = translate[0];
		//~ mesh.translate.y = translate[1];
		//~ mesh.translate.z = translate[2];	
		
		
		
		
		float rx = (float)rotate[0] / 180 * PI;
		float ry = (float)rotate[1] / 180 * PI;
		float rz = (float)rotate[2] / 180 * PI;
		
		
		mesh_utils.scale(mesh, glm::vec3( scale[0], scale[1], scale[2] ));
		mesh_utils.rotate(mesh, glm::vec3( rx, ry, rz ));
		mesh_utils.translate(mesh, glm::vec3( (float)translate[0], (float)translate[1], (float)translate[2] ));
		printf("translate ----> %.3f %.3f %.3f\n", translate[0], translate[1], translate[2]);
		return mesh;
	}
};


struct JsonLight : public Light
{
	
	std::vector<double> position;
	double intensity;
	JsonLight(){
		position.reserve(3);
	}
	
	Light create(){
		Light light;
		light.position = glm::vec3(position[0], position[1], position[2]);
		light.color = color;
		light.intensity = intensity;
		return light;
	}
	void serialize(JSON::Adapter& adapter){
	
		JSON::Class root(adapter, "json_light");
		
		JSON_E(adapter, color);
		JSON_E(adapter, position);
		JSON_T(adapter, intensity);
		
	
	}	
};

struct JsonScene
{
	public:
	
		//~ JsonScene(
			//~ std::vector<JsonMaterial> _materials,
			//~ std::vector<JsonFileMesh> _file_meshes,
			//~ std::vector<JsonLight> _lights
		//~ ):materials(_materials), file_meshes(_file_meshes), lights(_lights){};
		
		std::vector<JsonMaterial> materials;
		std::vector<JsonFileMesh> file_meshes;
		std::vector<JsonLight> lights;
		
		void serialize(JSON::Adapter& adapter){
			JSON::Class root(adapter, "json_scene");
			
			JSON_E(adapter, materials);
			JSON_E(adapter, file_meshes);
			JSON_T(adapter, lights);
		}	
		


};

struct RenderOptions
{
	int kd_polygon_limit; // = 100;
	int render_width; // = 320;
	int render_height; // = 240;
	Color background_color;
	int reflection_limit;
	
	void serialize(JSON::Adapter& adapter)
	{
		JSON::Class root(adapter, "render_options");
		JSON_E(adapter, kd_polygon_limit);
		JSON_E(adapter, render_width);
		JSON_E(adapter, render_height);
		JSON_E(adapter, background_color);
		JSON_T(adapter, reflection_limit);
	}
	
	
};

class SceneFileLoader
{
	public:
		SceneFileLoader();
		
		void loadSceneFile(
			std::string path, 
			std::vector<Mesh> & meshes,
			std::vector<RTMaterial> & materials, 
			std::vector<Light> & lights
		);
		
		RenderOptions loadOptionsFile(std::string path);
	private:
		/* add your private declarations */
};

#endif /* SCENE_FILE_LOADER_H */ 
