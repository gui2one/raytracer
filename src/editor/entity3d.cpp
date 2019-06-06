#include "entity3d.h"

static void vec_mult_by_matrix( glm::vec3 & _vec, glm::mat4 & _mat, bool invert = false)
{

        glm::vec4 temp_vec4 = glm::vec4(_vec.x, _vec.y, _vec.z,1.0f);


        if( invert){
                _vec = glm::inverse(_mat) * temp_vec4 ;
        } else{
                _vec = _mat * temp_vec4;
                //~ printf("__VEC X : %.3f\n", _vec.x);
        }

}

Entity3D::Entity3D():
	position(glm::vec3(0.0,0.0,0.0)),
	rotation(glm::vec3(0.0,0.0,0.0)),
	scale(glm::vec3(1.0,1.0,1.0)),
	name("entity3d"),
	kd_node(nullptr)
{
	
}

void Entity3D::draw()
{
	printf("--- Drawing Entity3D  -----\n");
}

void Entity3D::applyTransforms()
{
	glm::mat4 temp = glm::mat4(1.0f);
	
	
	temp = glm::rotate(temp, glm::radians(rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
	temp = glm::rotate(temp, glm::radians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
	temp = glm::rotate(temp, glm::radians(rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
	temp = glm::translate(temp, position);
	temp = glm::scale(temp , scale);
	
	transforms = temp;	
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
			generator = new PlaneMeshGenerator();
			
			mesh = generator->generate();
			//~ buildVBO();
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
				tri_copy.points[i].position.x, tri_copy.points[i].position.y, tri_copy.points[i].position.z,
				tri_copy.points[i].normal.x, tri_copy.points[i].normal.y, tri_copy.points[i].normal.z,
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
	
	
	
	buildKDTree(5);
	
	
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
	
	//~ int _limit = 5;
	std::vector<Triangle*> tris;
	//~ tris.reserve(entities[mesh_id]->mesh.faces.size());

	for (size_t i = 0; i < mesh.faces.size(); i++)
	{
		
		// triangulate face if needed ... 
		for (size_t j = 0; j < mesh.faces[i].getNumVertices()-2; j++)
		{
			
			glm::vec3 A, B, C;
			A = B = C = glm::vec3(0.0, 0.0, 0.0);

	
			applyTransforms();
			// apply transforms matrix
			glm::vec3 tempA = mesh.points[ mesh.faces[i].getVertex(0).point_id ].position;
			vec_mult_by_matrix(tempA, transforms, false);

			glm::vec3 tempB = mesh.points[ mesh.faces[i].getVertex(1+j).point_id ].position;
			vec_mult_by_matrix(tempB, transforms, false);				

			glm::vec3 tempC = mesh.points[ mesh.faces[i].getVertex(2+j).point_id ].position;
			vec_mult_by_matrix(tempC, transforms, false);							
			
			A = tempA;
			B = tempB;
			C = tempC;

			//~ printf("vec3 value -> %.3f %.3f %.3f\n", A.x, A.y, A.z);

			Triangle* tri_ptr = new Triangle(A, B, C);
			tri_ptr->id = i;
			//~ tris.emplace_back(tri_ptr);
			tris.push_back(tri_ptr);
			
		}

	}

	kd_node = new KDNode(_limit);
	kd_node = kd_node->build(tris, 0);	
	
	printf("TRIANGLES --> %d\n", kd_node->triangles.size());
}

MeshObject::~MeshObject()
{
	printf("--- Delete MeshObject\n");
}


