#ifndef PCH_H
#define PCH_H

#include <algorithm>
#include <memory>
#include <GL/glew.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <SDL2/SDL_ttf.h>
//~ #include <GLFW/glfw3.h>

#include "vendor/stb_image.h"
#include "vendor/stb_image_write.h"

//~ #include <vector>


#include <string>
#include <iostream>
#include <fstream>
//~ #include <stdio>

#include "esj/json_reader.h"
#include "esj/json_writer.h"

#define GLM_ENABLE_EXPERIMENTAL
#include "vendor/glm/glm.hpp"
#include "vendor/glm/gtx/rotate_vector.hpp"
#include "vendor/glm/gtx/matrix_decompose.hpp"
#include "vendor/glm/gtx/string_cast.hpp"
#include "vendor/glm/gtc/matrix_transform.hpp"
#include "vendor/glm/gtc/type_ptr.hpp"


#include "../vendor/imgui/imgui.h"
#include "../vendor/imgui/imgui_impl_sdl.h"
#include "../vendor/imgui/imgui_impl_opengl3.h"


#define PI 3.14159265359


// opengl debugging

#include <csignal>

#define ASSERT(x) if(!(x)) std::raise(SIGINT);
#define GLCall(x) GLClearError(); \
        x;\
        ASSERT(GLLogCall(#x, __FILE__, __LINE__))


static void GLClearError()
{
        while(glGetError() != GL_NO_ERROR);
}

static bool GLLogCall(const char* function, const char* file, int line)
{
        while( GLenum error = glGetError()){
                std::cout << "[OpenGL Error] (" << error << ") : " << function << " " << file <<  " : " << line << std::endl;
    
                return false;
        }
    
        return true;
}




#endif /*PCH_H*/

