#ifndef RENDER_TASK_H
#define RENDER_TASK_H

#include "pch.h"
#include "renderer.h"
#include "include/taskqueue.hpp"
		
class RenderTaskResult{
	public :
		std::vector<unsigned char> data;
};

class RenderTask
{
	public : 
		typedef RenderTaskResult result_type;
		
		
		RenderTask(Renderer * renderer, RenderBucket* bucket): m_renderer(renderer), m_bucket(bucket)
		{
			printf("empty task for now \n");
		}

		result_type operator ()(){
			
			result_type result;
			m_renderer->renderBucket(m_bucket, m_renderer->camera);
			//~ m_renderer->displayScene();
			//~ std::vector<unsigned char> chars(3);
			//~ chars[0] = (unsigned char)5;
			//~ chars[1] = (unsigned char)15;
			//~ chars[2] = (unsigned char)42;
			//~ m_data = chars; 		
			//~ result.data = m_data;
			
			return result;
		}
		
		std::vector<unsigned char> m_data;
		Renderer * m_renderer;
		RenderBucket* m_bucket;
};		


#endif /* RENDER_TASK_H */ 
