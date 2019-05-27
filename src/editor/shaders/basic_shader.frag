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
	
	mediump float diff = 0.0;
	
	for(int i=0; i< 2; i++){
		mediump float light_dist = distance(f_pos, u_light_positions[i]);
		lightDir = normalize(u_light_positions[i] - f_pos);   
		diff += (max(dot(norm, lightDir), 0.0)  / (light_dist * light_dist)) * 1.0;
	}
	
	color = diff * f_color;	
	//~ color = diff * f_color * texture2D(u_tex,f_t_coords);
	//~ color = vec4(1.0,0.0,0.0,1.0);
	
}



                                
                                

