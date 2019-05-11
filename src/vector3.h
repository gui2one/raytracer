#ifndef VECTOR3_H
#define VECTOR3_H

#include "pch.h"

class Vector3 : public glm::vec3
{
	public:
		glm::vec3 ref;
		Vector3();
		Vector3(glm::vec3 glm_vec) : x(glm_vec.x),y(glm_vec.y), z(glm_vec.z){
			
		}
		Vector3(double x_, double y_, double z_);
		
		//~ operator const glm::vec3&(){
			//~ ref.x = x;
			//~ ref.y = y;
			//~ ref.z = z;
			//~ return ref;
		//~ }
		//~ virtual ~Vector3(){
			//~ 
		//~ }
			
		double x;
		double y;
		double z;			
	private:

		/* add your private declarations */
};

#endif /* VECTOR3_H */ 
