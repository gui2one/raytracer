#ifndef RTMATERIAL_H
#define RTMATERIAL_H


#include "pch.h"
#include "color.h"
class RTMaterial
{
	public:
		RTMaterial();
		
		
		Color color;
		
		double shininess;	
		double refl_amount;
	private:
		/* add your private declarations */
};

#endif /* RTMATERIAL_H */ 
