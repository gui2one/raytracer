#version 300 es


layout(location = 0) out mediump vec4 color;
in mediump vec2 f_t_coords;
in mediump vec4 f_color;

in mediump vec3 f_normal;
in mediump vec3 f_pos;
uniform sampler2D u_tex; //this is the texture
uniform mediump vec3 u_light_positions[2];

mediump vec3 norm;
mediump vec3 lightDir;

void main()
{          
	
	norm = normalize(f_normal);
	lightDir = normalize(u_light_positions[0] - f_pos);   
	//~ color = vec4(0.0,0.8,0.5,1.0);  
	
	mediump float diff = max(dot(norm, lightDir), 0.0);
	
	//~ color = diff * f_color;
	//~ color = vec4(norm,1.0);
	color = diff * f_color * texture2D(u_tex,f_t_coords);
	//~ color = texture2D(u_tex,f_t_coords);
}



                                
                                

