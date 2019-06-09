#version 300 es


layout(location = 0) out mediump vec4 color;
in mediump vec2 f_t_coords;
//~ in mediump vec4 f_color;

//~ in mediump vec3 f_normal;

uniform sampler2D u_tex; //this is the texture


void main()
{          

	

	
	//~ color = vec4(f_t_coords.x, f_t_coords.y, 0.0,1.0);
	color = texture2D(u_tex,f_t_coords);
	//~ color = texture2D(u_tex,f_t_coords);
}



                                
                                

