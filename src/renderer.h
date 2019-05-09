#ifndef RENDERER_H
#define RENDERER_H

#include <ctime>
#include "pch.h"

#include "utils/system_utils.h"

#include "camera.h"
#include "light.h"
#include "texture.h"
#include "mesh.h"
#include "rtmaterial.h"
#include "shader.h"
#include "raycaster.h"
#include "kdnode.h"
#include "color.h"

//~ #include "include/boost/threadpool.hpp"
//~ using namespace boost::threadpool;

#include "include/taskqueue.hpp"

struct RenderBucket
{
	int x;
	int y;
	
	int width = 100;
	int height = 100;
	
	int render_width = 320;
	int render_height = 240;
	
	bool finished = false;
};


struct OGL_geometry_data
{
	std::vector<float> vertices;
	std::vector<unsigned> indices;
	
	glm::vec3 translate = glm::vec3(0.0, 0.0, 0.0);
	glm::vec3 rotate = glm::vec3(0.0, 0.0, 0.0);
	glm::vec3 scale = glm::vec3(1.0, 1.0, 1.0);
	
};
class Renderer
{
	public:
		Renderer();
		
		
		static void char_mods_callback(GLFWwindow* window, unsigned int key, int action);
		static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
		static void cursor_pos_callback(GLFWwindow* window, double xpos, double ypos);
		static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);    
		static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
		
		
		int init(int limit);
		void initFBO(int width, int height);
		void drawFBO(int r_width, int r_height);
		void setCamPosFromPolar(float u, float v, float _radius, glm::vec3 center = glm::vec3(0.0,0.0,0.0));
		void buildRenderGeometry();
		void displayScene();
		bool shouldClose();
		
		Mesh loadMesh(std::string path);
		
		//~ void renderMaterials(int w, int h, Camera& camera, std::vector<Mesh>& meshes);
		
		Color shade(Mesh& mesh, Face& face, RTMaterial material, HitData& hit_data, int depth = 0);
		
		std::vector<RenderBucket> createBuckets(int size, int r_width, int r_height);
		
		void renderBucket(RenderBucket& bucket, Camera& camera);
		void renderBuckets(std::vector<RenderBucket>& buckets, Camera& camera);
		
		
		
		void buildKDTree();
		void displayKDTree();
		void collectKDBoungingBoxes(KDNode* node_ptr);
		void buildKDTreeBBoxes(std::vector<KDBoundingBox> bboxes);
		
		int kd_polygon_limit;
		
		std::vector<KDNode *> kd_nodes;
		
		
		
		std::vector<KDBoundingBox> kd_bboxes;
		unsigned int kdtree_vbo, kdtree_ibo;
		
		std::vector<float> kdtree_vertices;
		std::vector<unsigned int> kdtree_indices;
		
		std::vector<Mesh> meshes;
		std::vector<OGL_geometry_data> geo_data_array;
		
		std::vector<unsigned int> vbos;
		std::vector<unsigned int> ibos;
		
		GLFWwindow * window;
		
		Shader default_shader, fbo_shader;
		
		Camera camera;
		
		float camera_u_pos = 0.5;
		float camera_v_pos = PI / 4.0 ;
		float camera_orbit_radius = 5.0;
		glm::vec3 camera_view_center = glm::vec3(0.0, 0.0, 0.0);
		
		std::vector<Light> lights;
		std::vector<RTMaterial> materials;
		
		
		bool left_mouse_button_down = false;
		bool left_mouse_dragging = false;
		
		bool right_mouse_button_down = false;
		bool right_mouse_dragging = false;
		
		float mouse_old_x = 0.0;
		float mouse_old_y = 0.0;
		float mouse_delta_x, mouse_delta_y;
		
		Texture fbo;
		unsigned int fbo_vbo, fbo_texture_id;
		bool show_fbo = false;
		
		int render_width;
		int render_height;
		std::vector<unsigned char> render_buffer_data;
		
			
	private:
		/* add your private declarations */
};



struct testTaskResult{
	int i;
};

struct testTask{
	typedef testTaskResult result_type;
	
	testTask(int n): i_(n){
		//~ boost::this_thread::sleep(boost::posix_time::milliseconds(1000));
		//~ std::cout << "doing task " << n << "\n";
	}
	
	result_type operator()(){
		
		result_type result;
		result.i = i_ * i_;
		return result;
	}
	
	int i_;
};

struct RenderTaskResult{
	std::vector<unsigned char> data;
};

struct RenderTask{
	typedef RenderTaskResult result_type;
	
	RenderTask(Renderer * renderer, RenderBucket& bucket): m_renderer(renderer), m_bucket(bucket)
	{

	}
	
	result_type operator ()(){
		
		result_type result;
		m_renderer->renderBucket(m_bucket, m_renderer->camera);
		//~ m_renderer->displayScene();
		std::vector<unsigned char> chars(3);
		chars[0] = (unsigned char)5;
		chars[1] = (unsigned char)15;
		chars[2] = (unsigned char)42;
		m_data = chars; 		
		result.data = m_data;
		
		return result;
	}
	
	std::vector<unsigned char> m_data;
	Renderer * m_renderer;
	RenderBucket m_bucket;
};

#endif /* RENDERER_H */ 
