#include "rtmaterial.h"


RTMaterial::RTMaterial():
	color(Color(1.0, 0.2, 0.2, 1.0)),
	shininess(0.5),
	refl_amount(0.0),
	diff_texture_path("../src/res/textures/uvgrid.jpg")
{
	
	
}

RTMaterial::RTMaterial(const RTMaterial& other):
	color(other.color),
	shininess(other.shininess),
	refl_amount(other.refl_amount),
	diff_texture_path(other.diff_texture_path),
	diff_texture(other.diff_texture)
{
	printf("material copy ........\n");
}

void RTMaterial::loadDiffTexture()
{
	
	diff_texture.load(diff_texture_path);
	
	
	//~ if( diff_texture_path != "")
	//~ {
		//~ diff_texture.load(diff_texture_path);
	//~ }else{
		//~ // create white default texture
		//~ printf("creating default white texture\n");
		//~ 
		//~ int w=32;
		//~ int h=32;
		//~ 
		//~ unsigned char white_data[w*h*4];
		//~ for (int i = 0; i < w*h*4; i++)
		//~ {
			//~ white_data[i] = (unsigned char)255;
		//~ }
		//~ 
		//~ diff_texture.setData(w, h, white_data);
	//~ }
	printf("Texture loaded. %d bytes per pixel \n", diff_texture.getBPP());
}


