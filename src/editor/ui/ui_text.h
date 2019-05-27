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

		
		unsigned int m_vbo, m_ibo;
		
		
		std::vector<float> vertices;
		std::vector<unsigned int> indices;
		
		Shader* m_shader;
		TTF_Font* m_font;
		std::string m_text;
	private:
	
		
		
		/* add your private declarations */
};

#endif /* UI_TEXT_H */ 
