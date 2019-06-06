#include "plane_mesh_generator.h"


PlaneMeshGenerator::PlaneMeshGenerator()
	: MeshGenerator()
{
	
	param_menu = new ParamMenu({"XY", "XZ", "YZ"});
	param_menu->setName("Orient");
	param_menu->setValue(0);
	params.push_back(param_menu);
		
	param_width = new Param<float>();
	param_width->setName("Width");
	param_width->setValue(1.0);
	params.push_back(param_width);
		
	param_length = new Param<float>();
	param_length->setName("Length");
	param_length->setValue(1.0);
	params.push_back(param_length);
	
	
	param_segs_width = new Param<int>();
	param_segs_width->setName("Segs Width");
	param_segs_width->setValue(2);
	params.push_back(param_segs_width);	
	
	param_segs_length = new Param<int>();
	param_segs_length->setName("Segs Length");
	param_segs_length->setValue(2);
	params.push_back(param_segs_length);		
	


}

Mesh PlaneMeshGenerator::generate()
{
	//~ std::cout << "PLANE Generator Generate function" << std::endl;
	
	//~ Mesh mesh = EditorMeshUtils::makeQuad(param_width->getValue(), param_length->getValue());
	Mesh mesh = EditorMeshUtils::makeGrid(
		param_width->getValue(), 
		param_length->getValue(), 
		param_segs_width->getValue(), 
		param_segs_length->getValue());
	
	
	if(param_menu->getValue() == 1)
	{
		EditorMeshUtils::rotate(mesh, glm::vec3(90.0, 0.0,0.0));
		
	}else if(param_menu->getValue() == 2){
		
		EditorMeshUtils::rotate(mesh, glm::vec3(0.0, -90.0,0.0));
	}
	mesh.computeNormals();
	
	return mesh;
}


