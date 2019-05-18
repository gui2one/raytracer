#ifndef RTMATERIAL_H
#define RTMATERIAL_H


#include "pch.h"
#include "color.h"
#include "texture.h"
class RTMaterial
{
	public:
		RTMaterial();
		RTMaterial(const RTMaterial& other);
		
		Color color;
		
		double shininess;	
		double refl_amount;
		std::string diff_texture_path;
		
		void loadDiffTexture();		
		Texture diff_texture;
	private:
		/* add your private declarations */
};

#endif /* RTMATERIAL_H */ 
