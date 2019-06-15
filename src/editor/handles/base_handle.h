#ifndef BASE_HANDLE_H
#define BASE_HANDLE_H

#include "../../pch.h"
#include "../utils/editor_gizmo_utils.h"
#include "../entity3d.h"

class BaseHandle
{
public:
	BaseHandle();
	virtual ~BaseHandle();
	virtual void buildKDTree(int _limit){};
	virtual void deleteKDTree(){};			
		
	virtual void draw(){};
	void applyTransforms();
	glm::mat4 transforms;
	
	glm::vec3 position;
	glm::vec3 rotation;
	glm::vec3 scale;
		//~ 
		
	unsigned int m_vbo = 0, m_ibo = 0;
	OGL_DATA_2 geo_data;
	std::shared_ptr<KDNode> kd_node;
	
private:
	/* add your private declarations */
};

class TranslateHandle: public BaseHandle
{
	
	public: 
		TranslateHandle();
		~TranslateHandle();
		
		void buildDisplayData();
		void draw() override;
		void buildKDTree(int _limit) override;
		
		
		
	private:
};

#endif /* BASE_HANDLE_H */ 
