#include "box_mesh_generator.h"


BoxMeshGenerator::BoxMeshGenerator()
	: MeshGenerator()
{

		
	param_width = new Param<float>();
	param_width->setName("Width");
	param_width->setValue(1.0);
	params.push_back(param_width);
		
	param_length = new Param<float>();
	param_length->setName("Length");
	param_length->setValue(1.0);
	params.push_back(param_length);
	
	param_height = new Param<float>();
	param_height->setName("Height");
	param_height->setValue(1.0);
	params.push_back(param_height);	
	
	param_segs_width = new Param<int>();
	param_segs_width->setName("Segs Width");
	param_segs_width->setValue(5);
	params.push_back(param_segs_width);	
	
	param_segs_length = new Param<int>();
	param_segs_length->setName("Segs Length");
	param_segs_length->setValue(5);
	params.push_back(param_segs_length);		
	
	param_segs_height = new Param<int>();
	param_segs_height->setName("Segs Height");
	param_segs_height->setValue(5);
	params.push_back(param_segs_height);

}

Mesh BoxMeshGenerator::generate()
{
	Mesh other_side;
	//// Z facing sides
	Mesh mesh = EditorMeshUtils::makeGrid(
		param_width->getValue(), 
		param_length->getValue(), 
		param_segs_width->getValue(), 
		param_segs_length->getValue()
	);
	EditorMeshUtils::translate(mesh, glm::vec3(0.0, 0.0, param_height->getValue() / 2.0));
	other_side = mesh;
	EditorMeshUtils::rotate(other_side, glm::vec3(180.0, 0.0, 0.0));
	//~ EditorMeshUtils::translate(other_side, glm::vec3(0.0, 0.0, 0.0));
	mesh = EditorMeshUtils::merge(mesh, other_side);
	
	
	//// X facing sides
	
	Mesh x_facing = EditorMeshUtils::makeGrid(		
		param_height->getValue(), 
		param_length->getValue(), 		
		param_segs_height->getValue(),
		param_segs_length->getValue() 
	);
	EditorMeshUtils::translate(x_facing, glm::vec3(0.0, 0.0, param_width->getValue() / 2.0));
	
	other_side = x_facing;
	EditorMeshUtils::rotate(other_side, glm::vec3(180.0, 0.0, 0.0));
	//~ EditorMeshUtils::translate(other_side, glm::vec3(0.0, 0.0, 0.0));
	x_facing = EditorMeshUtils::merge(x_facing, other_side);
	EditorMeshUtils::rotate(x_facing, glm::vec3(0.0, -90.0, 0.0));	
	
	mesh = EditorMeshUtils::merge(mesh, x_facing);
	
	
	//// Y facing sides
	
	Mesh y_facing = EditorMeshUtils::makeGrid(		
		
		param_width->getValue(), 		
		param_height->getValue(), 
		
		param_segs_width->getValue() ,
		param_segs_height->getValue()
	);
	EditorMeshUtils::translate(y_facing, glm::vec3(0.0, 0.0, param_length->getValue() / 2.0));
	
	other_side = y_facing;
	EditorMeshUtils::rotate(other_side, glm::vec3(180.0, 0.0, 0.0));
	//~ EditorMeshUtils::translate(other_side, glm::vec3(0.0, 0.0, 0.0));
	y_facing = EditorMeshUtils::merge(y_facing, other_side);
	EditorMeshUtils::rotate(y_facing, glm::vec3(-90.0, 0.0, 0.0));	
	
	mesh = EditorMeshUtils::merge(mesh, y_facing);	
	mesh.computeNormals();
	
	return mesh;
}


