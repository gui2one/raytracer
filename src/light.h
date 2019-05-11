#ifndef LIGHT_H
#define LIGHT_H

#include "pch.h"
#include "color.h"

class Light
{
	
	public:
		Light();
		virtual ~Light();
		
		glm::vec3 position;
		//~ Vector3 position;
		float intensity;
		Color color;		
	
	private:
	

		/* add your private declarations */
};

#endif /* LIGHT_H */ 
