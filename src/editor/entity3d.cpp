#include "entity3d.h"

static void vec_mult_by_matrix( glm::vec3 & _vec, glm::mat4 & _mat, bool invert = false)
{
	glm::vec4 temp_vec4 = glm::vec4(_vec.x, _vec.y, _vec.z,1.0f);

	if( invert){
			_vec = glm::inverse(_mat) * temp_vec4 ;
	}else{
			_vec = _mat * temp_vec4;
	}
}

Entity3D::Entity3D():
	position(glm::vec3(0.0,0.0,0.0)),
	rotation(glm::vec3(0.0,0.0,0.0)),
	scale(glm::vec3(1.0,1.0,1.0)),
	name("entity3d"),
	parent(nullptr),
	kd_node(nullptr)
{
	
	param_position = new Param<glm::vec3>();
	param_position->setName("Position");
	param_position->setValue(position);
	params.push_back(param_position);
	
	param_rotation = new Param<glm::vec3>();
	param_rotation->setName("Rotation");	
	param_rotation->setValue(rotation);
	params.push_back(param_rotation);
	
	param_scale = new Param<glm::vec3>();
	param_scale->setValue(scale);
	param_scale->setName("scale");		
	params.push_back(param_scale);
}

void Entity3D::draw()
{
	printf("--- Drawing Entity3D  ----- Weird .... \n");
}

glm::mat4 Entity3D::getParentsTransform()
{
	glm::mat4 matrix = glm::mat4(1.0f);
	std::shared_ptr<Entity3D> target = parent;
	std::vector<glm::mat4> matrices;
	int inc = 0;
	while(target != nullptr)
	{
		//~ printf("Got a parent %d\n", inc);
		target->applyTransforms();
		//~ matrix *= target->transforms;
		
		
		matrices.push_back(target->transforms);
		target = target->parent;
		
		inc++;
	}
	
	for(int i=matrices.size()-1; i >= 0; i--)
	{
		matrix *= matrices[i];
	}
	
	return matrix;
}

std::vector<std::shared_ptr<Entity3D> > Entity3D::getParentChain()
{
	std::vector<std::shared_ptr<Entity3D> > result;
	std::shared_ptr<Entity3D> target = parent;
	
	while (target != nullptr)
	{
		result.push_back(target);
		
		target = target->parent;
	}
	
	return result;
}

void Entity3D::applyTransforms()
{
	//~ glm::mat4 parent_transforms = getParentsTransform();
	glm::mat4 temp = glm::mat4(1.0f);
	
	//~ temp *= parent_transforms;
	
	position = param_position->getValue();
	rotation = param_rotation->getValue();
	scale = param_scale->getValue();
	//~ printf("entity pos --> %.3f %.3f %.3f\n", param_position->getValue().x, param_position->getValue().y, param_position->getValue().z);
	temp = glm::translate(temp, param_position->getValue());
	temp = glm::rotate(temp, glm::radians(param_rotation->getValue().x), glm::vec3(1.0f, 0.0f, 0.0f));
	temp = glm::rotate(temp, glm::radians(param_rotation->getValue().y), glm::vec3(0.0f, 1.0f, 0.0f));
	temp = glm::rotate(temp, glm::radians(param_rotation->getValue().z), glm::vec3(0.0f, 0.0f, 1.0f));
	
	temp = glm::scale(temp , param_scale->getValue());
	
	transforms = temp;	
	//~ transforms *= parent_transforms;
	
	
}

Entity3D::~Entity3D()
{
	printf("--- Delete Entity3D\n");
}

//// MeshObject implementation

MeshObject::MeshObject() : Entity3D(), generator(nullptr)
{
	
}

void MeshObject::setMeshGenerator(MESH_GENERATOR_TYPE _type)
{
	switch(_type){
		case GRID_MESH_GENERATOR :
			generator = new GridMeshGenerator();
			
			mesh = generator->generate();
			generator_type = GRID_MESH_GENERATOR;
			break;
		case BOX_MESH_GENERATOR :
			generator = new BoxMeshGenerator();
			
			mesh = generator->generate();
			generator_type = BOX_MESH_GENERATOR;
			break;	
			
		case CYLINDER_MESH_GENERATOR :
			generator = new CylinderMeshGenerator();
			
			mesh = generator->generate();
			generator_type = CYLINDER_MESH_GENERATOR;
			break;	
	}
}

void MeshObject::updateMeshGenerator()
{
	if(generator != nullptr)
	{
		//~ printf("updateMesh Generator Function\n");
		mesh = generator->generate();
		buildVBO();
		
	}
}

void MeshObject::buildVBO()
{
	
	OGL_geo_data.vertices.clear();
	OGL_geo_data.indices.clear();
	

	Mesh tri_copy = mesh;
	tri_copy.triangulate();
	tri_copy.computeNormals();
	//vertices
	for (size_t i = 0; i < tri_copy.points.size(); i++)
	{	
		OGL_geo_data.vertices.insert(
			OGL_geo_data.vertices.end(), {
				
				// pos
				tri_copy.points[i].position.x, tri_copy.points[i].position.y, tri_copy.points[i].position.z,
				// normals
				tri_copy.points[i].normal.x, tri_copy.points[i].normal.y, tri_copy.points[i].normal.z,
				// texture coords
				1.0, 1.0
			}
		);			
	}
	
	// indices
	for (size_t i = 0; i < tri_copy.faces.size(); i++)
	{
		if( tri_copy.faces[i].getNumVertices() == 3)
		{
			OGL_geo_data.indices.insert(
				OGL_geo_data.indices.end(), {
					tri_copy.faces[i].getVertex(0).point_id,
					tri_copy.faces[i].getVertex(2).point_id,
					tri_copy.faces[i].getVertex(1).point_id
				}
			
			);
		}
	}
	
		
	
	
	if(m_vbo == 0){
		
		GLCall(glGenBuffers(1, &m_vbo));
		//~ printf("m_vbo from mesh object --> %d\n", m_vbo);
	}else{
		GLCall(glDeleteBuffers(1, &m_vbo));
		GLCall(glGenBuffers(1, &m_vbo));
	}
	
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_vbo));
	GLCall(glBufferData(GL_ARRAY_BUFFER, sizeof(float)* OGL_geo_data.vertices.size(), OGL_geo_data.vertices.data(), GL_DYNAMIC_DRAW));
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));	
	
	if(m_ibo == 0)
	{
		GLCall(glGenBuffers(1, &m_ibo));
	}else{		
		GLCall(glDeleteBuffers(1, &m_ibo));
		GLCall(glGenBuffers(1, &m_ibo));
	}

	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo));
	GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int)* OGL_geo_data.indices.size(), OGL_geo_data.indices.data(), GL_DYNAMIC_DRAW));
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));		
	
	
	
	buildKDTree(50);
	
	
}

void MeshObject::draw()
{
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_vbo));
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo));
	GLCall(glVertexAttribPointer(0,3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, 0));
	GLCall(glVertexAttribPointer(1,3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (void*)(sizeof(float) * 3)));
	//~ GLCall(glVertexAttribPointer(2,2, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (void*)(sizeof(float) * 6)));
	
	
	GLCall(glEnableVertexAttribArray(0));
	GLCall(glEnableVertexAttribArray(1));
	//~ GLCall(glEnableVertexAttribArray(2));
	
	//~ GLCall(glDrawArrays(GL_TRIANGLES, 0, mesh.points.size()));
	GLCall(glDrawElements(GL_TRIANGLES, OGL_geo_data.indices.size() , GL_UNSIGNED_INT, nullptr ));

	GLCall(glDisableVertexAttribArray(0));
	GLCall(glDisableVertexAttribArray(1));
	//~ GLCall(glDisableVertexAttribArray(2));
	
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
	//~ printf("--- Drawing MeshObject  -----\n");
}

void MeshObject::buildKDTree(int _limit)
{
	//~ printf("building Entity3D kdtree\n");
	
	//~ int _limit = 5;
	std::vector<std::shared_ptr<Triangle> > tris;
	//~ tris.reserve(entities[mesh_id]->mesh.faces.size());

	for (size_t i = 0; i < mesh.faces.size(); i++)
	{
		
		// triangulate face if needed ... 
		for (size_t j = 0; j < mesh.faces[i].getNumVertices()-2; j++)
		{
			
			glm::vec3 A, B, C;
			
			glm::mat4 parent_t = getParentsTransform();
			applyTransforms();
			parent_t *= transforms;
			
			A = mesh.points[ mesh.faces[i].getVertex(0).point_id ].position;
			vec_mult_by_matrix(A, parent_t);
			
			B = mesh.points[ mesh.faces[i].getVertex(1+j).point_id ].position;	
			vec_mult_by_matrix(B, parent_t);
			
			C = mesh.points[ mesh.faces[i].getVertex(2+j).point_id ].position;
			vec_mult_by_matrix(C, parent_t);


			std::shared_ptr<Triangle> tri_ptr = std::make_shared<Triangle>(A, B, C);
			tri_ptr->id = i;
			tris.push_back(tri_ptr);
			
		}

	}
	


	kd_node = std::make_shared<KDNode>(_limit);
	kd_node = kd_node->build(tris, 0);	

}


MeshObject::~MeshObject()
{
	printf("--- Delete MeshObject\n");
}

//// implement NULL OBJECT

NullObject::NullObject(): Entity3D()
{
	
}

void NullObject::buildVBO()
{
	geo_data_2 = EditorGizmoUtils::makeLine(glm::vec3(-0.5, 0.0, 0.0), glm::vec3(0.5, 0.0, 0.0));
	geo_data_2.setColor(0.2, 1.0, 0.2);
	
	OGL_DATA_2 line_y = EditorGizmoUtils::makeLine(glm::vec3(0.0,-0.5, 0.0), glm::vec3(0.0, 0.5, 0.0));
	line_y.setColor(0.2, 1.0, 0.2);
	
	geo_data_2 = EditorGizmoUtils::merge(geo_data_2, line_y);
	
	OGL_DATA_2 line_z = EditorGizmoUtils::makeLine(glm::vec3(0.0, 0.0, -0.5), glm::vec3(0.0, 0.0, 0.5));
	line_z.setColor(0.2, 1.0, 0.2);
	
	geo_data_2 = EditorGizmoUtils::merge(geo_data_2, line_z);
		
	if(m_vbo == 0){
		
		GLCall(glGenBuffers(1, &m_vbo));
		
	}else{
		GLCall(glDeleteBuffers(1, &m_vbo));
		GLCall(glGenBuffers(1, &m_vbo));
	}
	
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_vbo));
	
	
	GLCall(glBufferData(GL_ARRAY_BUFFER, sizeof(float)* (geo_data_2.positions.size() + geo_data_2.colors.size()), 0, GL_DYNAMIC_DRAW));
	GLCall(glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(float)* geo_data_2.positions.size(), geo_data_2.positions.data()));
	GLCall(glBufferSubData(GL_ARRAY_BUFFER, sizeof(float)* geo_data_2.positions.size(), sizeof(float)* geo_data_2.colors.size(), geo_data_2.colors.data()));
	
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));	
	
	if(m_ibo == 0)
	{
		GLCall(glGenBuffers(1, &m_ibo));
	}else{		
		GLCall(glDeleteBuffers(1, &m_ibo));
		GLCall(glGenBuffers(1, &m_ibo));
	}

	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo));
	GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int)* geo_data_2.indices.size(), geo_data_2.indices.data(), GL_DYNAMIC_DRAW));
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));		
	
	
	
	// build click geo

	click_geo = EditorGizmoUtils::makeSimpleBox();
	//~ EditorGizmoUtils::translate(click_geo, glm::vec3(0.0,0.0,0.5));
	buildKDTree();	
}

void NullObject::buildKDTree(int _limit)
{
	//~ printf("building Null Object KDTree\n");

	std::vector<std::shared_ptr<Triangle> > tris;


	for (size_t i = 0; i < click_geo.indices.size(); i+=3)
	{
		

		int id_A = click_geo.indices[i+0];
		int id_B = click_geo.indices[i+1];
		int id_C = click_geo.indices[i+2];
		glm::vec3 A, B, C;
		A = B = C = glm::vec3(0.0, 0.0, 0.0);

		glm::mat4 parent_t = getParentsTransform();
		applyTransforms();
		parent_t *= transforms;
		// apply transforms matrix
		glm::vec3 tempA = glm::vec3(
			click_geo.positions[(id_A * 3) + 0],
			click_geo.positions[(id_A * 3) + 1],
			click_geo.positions[(id_A * 3) + 2] 
		);
		vec_mult_by_matrix(tempA, parent_t, false);

		glm::vec3 tempB = glm::vec3(
			click_geo.positions[(id_B * 3) + 0],
			click_geo.positions[(id_B * 3) + 1],
			click_geo.positions[(id_B * 3) + 2] 
		);
		vec_mult_by_matrix(tempB, parent_t, false);
			

		glm::vec3 tempC = glm::vec3(
			click_geo.positions[(id_C * 3) + 0],
			click_geo.positions[(id_C * 3) + 1],
			click_geo.positions[(id_C * 3) + 2] 
		);
		vec_mult_by_matrix(tempC, parent_t, false);
						
		
		A = tempA;
		B = tempB;
		C = tempC;

		//~ printf("vec3 value -> %.3f %.3f %.3f\n", A.x, A.y, A.z);

		std::shared_ptr<Triangle> tri_ptr = std::make_shared<Triangle>(A, B, C);
		tri_ptr->id = i/3;
		tris.push_back(tri_ptr);
		
	}
	


	kd_node = std::make_shared<KDNode>(_limit);
	kd_node = kd_node->build(tris, 0);				
}

void NullObject::draw()
{
	//~ printf("drawing NULL OBJECT\n");
	
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_vbo));
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo));
	//pos
	GLCall(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, 0));
	//color
	GLCall(glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, (const void *)(sizeof(float) * geo_data_2.positions.size())));

	
	GLCall(glEnableVertexAttribArray(0));// pos
	GLCall(glEnableVertexAttribArray(1));// color

	GLCall(glDrawElements(GL_LINES, geo_data_2.indices.size(), GL_UNSIGNED_INT, nullptr));
	
	GLCall(glDisableVertexAttribArray(0));// pos
	GLCall(glDisableVertexAttribArray(1));// color

	GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));	
	
}
