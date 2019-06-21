#include "cylinder_mesh_generator.h"


CylinderMeshGenerator::CylinderMeshGenerator()
	: MeshGenerator()
{
	
	param_menu = new ParamMenu({"X", "Y", "Z"});
	param_menu->setName("Orient");
	param_menu->setValue(0);
	params.push_back(param_menu);
		
	param_radius = new Param<float>();
	param_radius->setName("Radius");
	param_radius->setValue(1.0);
	params.push_back(param_radius);
		
	param_height = new Param<float>();
	param_height->setName("Height");
	param_height->setValue(1.0);
	params.push_back(param_height);
	
	
	param_segs_radius = new Param<int>();
	param_segs_radius->setName("Segs Radius");
	param_segs_radius->setValue(5);
	params.push_back(param_segs_radius);	
	
	param_segs_height = new Param<int>();
	param_segs_height->setName("Segs Height");
	param_segs_height->setValue(5);
	params.push_back(param_segs_height);		
	


}

Mesh CylinderMeshGenerator::generate()
{
	//~ std::cout << "PLANE Generator Generate function" << std::endl;
	
	//~ Mesh mesh = EditorMeshUtils::makeQuad(param_width->getValue(), param_length->getValue());
	Mesh mesh = EditorMeshUtils::makeCylinder(
		param_radius->getValue(), 
		param_height->getValue(), 
		param_segs_radius->getValue(), 
		param_segs_height->getValue()
	);
	
	
	if(param_menu->getValue() == 1)
	{
		EditorMeshUtils::rotate(mesh, glm::vec3(90.0, 0.0,0.0));
		
	}else if(param_menu->getValue() == 2){
		
		EditorMeshUtils::rotate(mesh, glm::vec3(0.0, -90.0,0.0));
	}
	mesh.computeNormals();
	
	return mesh;
}


