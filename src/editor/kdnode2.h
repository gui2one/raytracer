#ifndef KDNODE2_H
#define KDNODE2_H

#include "../pch.h"
#include "../ray.h"


struct KDBoundingBox{
	
	
	void expand(KDBoundingBox other);
	int getLongestAxis();
	
	bool intersect(const Ray &r);
	void print();
	glm::vec3 min;
	glm::vec3 max;
};

struct Triangle{
	
	Triangle();
	Triangle(glm::vec3 _A, glm::vec3 _B, glm::vec3 _C);
	
	
	glm::vec3 A, B, C;
	unsigned int id = 0;
	KDBoundingBox getBoundingBox();
	glm::vec3 getMidPoint();
	
};

class KDNode
{
	public:
		KDNode(int polygons_limit = 50);
		KDNode * left;
		KDNode * right;
		
		
		KDNode * build(std::vector<Triangle*>& tris, int depth) const;
		
		
		int polygons_limit;
		
		KDBoundingBox bbox;
		std::vector<Triangle*> triangles;
		int depth = -1;
				
	private:
		/* add your private declarations */
};

#endif /* KDKDNODE2_H */ 
