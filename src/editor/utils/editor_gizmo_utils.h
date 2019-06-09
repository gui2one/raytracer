#ifndef EDITOR_GIZMO_UTILS_H
#define EDITOR_GIZMO_UTILS_H

#include "../../pch.h"
#include "../ogl_geometry_data.h"

enum EDITOR_GIZMO_ROTATION_ORDER{
	ROT_ORDER_XYZ,
	ROT_ORDER_XZY,
	ROT_ORDER_YXZ,
	ROT_ORDER_ZXY,
	ROT_ORDER_YZX,
	ROT_ORDER_ZYX
};

namespace EditorGizmoUtils
{
	
	
		OGL_geometry_data makeWireBox();
		
		OGL_geometry_data makeWirePrism();
		
		OGL_geometry_data makeCone(float radius, float length, int segs_radius, int segs_length);
		
		OGL_geometry_data merge(const OGL_geometry_data& geo1, const OGL_geometry_data& geo2);
		
		void translate(OGL_geometry_data& geo_data, glm::vec3 values);
		void rotate(OGL_geometry_data& geo_data, glm::vec3 values, EDITOR_GIZMO_ROTATION_ORDER order = ROT_ORDER_XYZ);
		void scale(OGL_geometry_data& geo_data, glm::vec3 values);
		
	
};

#endif /* EDITOR_GIZMO_UTILS_H */ 
