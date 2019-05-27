#include "ui_text.h"

void UIText::convertSDLSurface(SDL_Surface* surface, SDL_Texture * texture)
{
	printf("surface width : %d\n", surface->w);
	printf("\tPixel Format : %#08x\n", surface->format->format);
	if(surface->format->format == SDL_PIXELFORMAT_UNKNOWN){
		printf("SDL_PIXELFORMAT_UNKNOWN\n");
	}else if(surface->format->format == SDL_PIXELFORMAT_INDEX1LSB){
		printf("SDL_PIXELFORMAT_INDEX1LSB\n");
	}else if(surface->format->format == SDL_PIXELFORMAT_INDEX1MSB){
		printf("SDL_PIXELFORMAT_INDEX1MSB\n");
	}else if(surface->format->format == SDL_PIXELFORMAT_INDEX4LSB){
		printf("SDL_PIXELFORMAT_INDEX4LSB\n");
	}else if(surface->format->format == SDL_PIXELFORMAT_INDEX4MSB){
		printf("SDL_PIXELFORMAT_INDEX4MSB\n");
	}else if(surface->format->format == SDL_PIXELFORMAT_INDEX8){
		printf("SDL_PIXELFORMAT_INDEX8\n");
	}else if(surface->format->format == SDL_PIXELFORMAT_RGB332){
		printf("SDL_PIXELFORMAT_RGB332\n");
	}else if(surface->format->format == SDL_PIXELFORMAT_RGB444){
		printf("SDL_PIXELFORMAT_RGB444\n");
	}else if(surface->format->format == SDL_PIXELFORMAT_RGB555){
		printf("SDL_PIXELFORMAT_RGB555\n");
	}else if(surface->format->format == SDL_PIXELFORMAT_BGR555){
		printf("SDL_PIXELFORMAT_BGR555\n");
	}
	
	
	SDL_LockSurface(surface);
	unsigned char* pixels = (unsigned char*)surface -> pixels; 
	
	
	
	
	for (int i = 0; i < surface->w * surface->h; i+=surface->w)
	{
		for(int j = 0; j < surface->w; j++)
		{
			printf("%d", pixels[i+j]);
		}
		
		printf("\n");
	}
	
	SDL_UnlockSurface(surface);
	//~ pixels[4 * (y * surface -> w + x) + c] = 255;
	
	
	
	
}


UIText::UIText()
{
	m_text = "Test ";
}
UIText::UIText(Shader& _shader, TTF_Font* font):m_shader(&_shader), m_font(font)
{
	
}

void UIText::init()
{
		SDL_Color White = {255, 255, 255};  // this is the color in rgb format, maxing out all would give you the color white, and it will be your text's color

		//~ char buff[100];
		//~ snprintf(buff, sizeof(buff), "A", mesh_objects.size());
		//~ std::string buffAsStdStr = buff;		
		
		SDL_Surface* surfaceMessage = TTF_RenderText_Solid(m_font, m_text.c_str(), White); // as TTF_RenderText_Solid could only be used on SDL_Surface then you have to create the surface first


		
		SDL_Texture* Message = SDL_CreateTextureFromSurface(m_renderer, surfaceMessage); //now you can convert it into a texture

		
		SDL_Rect rect;
		rect.x = 0;
		rect.y = 0;
		rect.w = surfaceMessage->w;
		rect.h = surfaceMessage->h;
		
		texture_width = surfaceMessage->w;
		texture_height = surfaceMessage->h;
		
		//~ SDL_SetClipRect(surfaceMessage, &rect);
		convertSDLSurface(surfaceMessage, Message);
		//~ SDL_Rect Message_rect; //create a rect
		//~ Message_rect.x = 20;  //controls the rect's x coordinate 
		//~ Message_rect.y = 20; // controls the rect's y coordinte
		//~ Message_rect.w = surfaceMessage->w; // controls the width of the rect
		//~ Message_rect.h = surfaceMessage->h; // controls the height of the rect



		
		//~ SDL_RenderCopy(w_renderer, Message, NULL, &Message_rect); //you put the renderer's name first, the Message, the crop size(you can ignore this if you don't want to dabble with cropping), and the rect which is the size and coordinate of your texture

		SDL_DestroyTexture(Message);
		//Don't forget too free your surface and texture

		//~ SDL_RenderPresent(w_renderer);

		//~ SDL_SetRenderTarget(w_renderer, NULL);
		
		SDL_FreeSurface(surfaceMessage);
		
		
		
		vertices.clear();
		vertices.insert(
			vertices.end(),{
				0.0, 0.0, 0.0, 		0.0, 0.0,
				1.0, 0.0, 0.0,		1.0, 0.0,
				1.0, 1.0, 0.0,		1.0, 1.0,
				0.0, 1.0, 0.0,		0.0, 1.0
			}
		);
		
		indices.clear();
		indices.insert(
			indices.end(),{
				0, 1, 2,
				0, 2, 3
			}
		);
		
		GLCall(glDeleteBuffers(1, &m_vbo));
		GLCall(glGenBuffers(1, &m_vbo));
		GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_vbo));
		GLCall(glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertices.size(), vertices.data(), GL_STATIC_DRAW));
		GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
		
		GLCall(glDeleteBuffers(1, &m_ibo));
		GLCall(glGenBuffers(1, &m_ibo));
		GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo));
		GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * indices.size(), indices.data(), GL_STATIC_DRAW));
		GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));		
	
	
	GLCall(glDeleteTextures(1, &m_texture_id));
	GLCall(glGenTextures(1, &m_texture_id));
	GLCall(glBindTexture(GL_TEXTURE_2D, m_texture_id));

	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER));

//~ 
	GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texture_width, texture_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, texture_data.data()));

	GLCall(glBindTexture(GL_TEXTURE_2D, 0));	
	
	
	
	
	
	
}

void UIText::draw()
{
	GLCall(glActiveTexture(GL_TEXTURE0));
	GLCall(glBindTexture(GL_TEXTURE_2D, m_texture_id));
	
	
	
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_vbo));
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo));
	GLCall(glVertexAttribPointer(0,3, GL_FLOAT, GL_FALSE, sizeof(float) * 5, 0));
	GLCall(glVertexAttribPointer(1,2, GL_FLOAT, GL_FALSE, sizeof(float) * 5, (void*)(sizeof(float) * 3)));

	
	
	GLCall(glEnableVertexAttribArray(0));
	GLCall(glEnableVertexAttribArray(1));
	
	//~ GLCall(glDrawArrays(GL_TRIANGLES, 0, mesh.points.size()));
	GLCall(glDrawElements(GL_TRIANGLES, 6 , GL_UNSIGNED_INT, nullptr ));

	GLCall(glDisableVertexAttribArray(0));
	GLCall(glDisableVertexAttribArray(1));
	
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));	
	
	GLCall(glBindTexture(GL_TEXTURE_2D, 0));
	
}


