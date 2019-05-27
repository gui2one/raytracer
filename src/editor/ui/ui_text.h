#ifndef UI_TEXT_H
#define UI_TEXT_H


#include "../../pch.h"
#include "../../shader.h"
class UIText
{
	public:
		UIText();
		UIText(Shader& shader, TTF_Font* font);
			
		void init();
		void draw();
		inline void setText( std::string text){ m_text = text; }
		void convertSDLSurface(SDL_Surface* surf, SDL_Texture * texture);
		
		unsigned int m_vbo, m_ibo, m_texture_id;
		
		int texture_width, texture_height;
		std::vector<unsigned char> texture_data;
		
		
		std::vector<float> vertices;
		std::vector<unsigned int> indices;
		
		
		SDL_Renderer * m_renderer;
		
		Shader* m_shader;
		TTF_Font* m_font;
		std::string m_text;
	private:
	
		
		
		/* add your private declarations */
};

#endif /* UI_TEXT_H */ 
