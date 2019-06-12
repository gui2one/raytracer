#ifndef BASE_HANDLE_H
#define BASE_HANDLE_H

#include "../../pch.h"
#include "../utils/editor_gizmo_utils.h"

class BaseHandle
{
	public:
		BaseHandle();
		virtual ~BaseHandle();
		
		virtual void draw(){};
		
		glm::mat4 transforms;
		
		glm::vec3 position;
		glm::vec3 rotation;
		glm::vec3 scale;
		
		
		unsigned int m_vbo, m_ibo;
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
		OGL_DATA_2 geo_data;
		
	private:
};

#endif /* BASE_HANDLE_H */ 
