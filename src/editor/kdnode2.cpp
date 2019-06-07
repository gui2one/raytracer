#include "kdnode2.h"

// implement KDBoundingBox
void KDBoundingBox::expand(KDBoundingBox other)
{
	if(other.min.x < min.x)
		min.x = other.min.x;
	if(other.min.y < min.y)
		min.y = other.min.y;		
	if(other.min.z < min.z)
		min.z = other.min.z;		
		
	if(other.max.x > max.x)
		max.x = other.max.x;
	if(other.max.y > max.y)
		max.y = other.max.y;		
	if(other.max.z > max.z)
		max.z = other.max.z;				
}

int KDBoundingBox::getLongestAxis()
{
	float sx = max.x - min.x;
	float sy = max.y - min.y;
	float sz = max.z - min.z;
	
	if( sx > sy && sx > sz) return 0;
	else if( sy > sx && sy > sz) return 1;
	else if( sz > sx && sz > sy) return 2;
	else return 0;
	
	
	
}

bool KDBoundingBox::intersect(const Ray &r)
{ 
    float tmin = (min.x - r.origin.x) / r.direction.x; 
    float tmax = (max.x - r.origin.x) / r.direction.x; 
 
    if (tmin > tmax) std::swap(tmin, tmax); 
 
    float tymin = (min.y - r.origin.y) / r.direction.y; 
    float tymax = (max.y - r.origin.y) / r.direction.y; 
 
    if (tymin > tymax) std::swap(tymin, tymax); 
 
    if ((tmin > tymax) || (tymin > tmax)) 
        return false; 
 
    if (tymin > tmin) 
        tmin = tymin; 
 
    if (tymax < tmax) 
        tmax = tymax; 
 
    float tzmin = (min.z - r.origin.z) / r.direction.z; 
    float tzmax = (max.z - r.origin.z) / r.direction.z; 
 
    if (tzmin > tzmax) std::swap(tzmin, tzmax); 
 
    if ((tmin > tzmax) || (tzmin > tmax)) 
        return false; 
 
    if (tzmin > tmin) 
        tmin = tzmin; 
 
    if (tzmax < tmax) 
        tmax = tzmax; 
 
    return true; 
} 


void KDBoundingBox::print()
{
	printf("KD Bbox Value :\n");
	printf("\tMin Values --> %.3f %.3f %.3f\n", min.x, min.y, min.z);
	printf("\tMax Values --> %.3f %.3f %.3f\n", max.x, max.y, max.z);
}
//// end KDBoundingBox implementation


// implementing Triangle
Triangle::Triangle(glm::vec3 _A, glm::vec3 _B, glm::vec3 _C)
{
	A = _A;
	B = _B;
	C = _C;		
}

Triangle::Triangle(const Triangle& other) // copy constructor
{
	printf("COPY TRIANGLE\n");
}
KDBoundingBox Triangle::getBoundingBox()
{
	glm::vec3 max = glm::vec3(-1000000000.0, -1000000000.0, -1000000000.0);
	glm::vec3 min = glm::vec3(1000000000.0, 1000000000.0, 1000000000.0);


//// check min values
	if(A.x < min.x)
		min.x = A.x;
		
	if(A.y < min.y)
		min.y = A.y;
		
	if(A.z < min.z)
		min.z = A.z;

	
	if(B.x < min.x)
		min.x = B.x;
		
	if(B.y < min.y)
		min.y = B.y;
		
	if(B.z < min.z)
		min.z = B.z;
				
		
	if(C.x < min.x)
		min.x = C.x;
		
	if(C.y < min.y)
		min.y = C.y;
		
	if(C.z < min.z)
		min.z = C.z;		
		
//// check MAX values
	if(A.x > max.x)
		max.x = A.x;
		
	if(A.y > max.y)
		max.y = A.y;
		
	if(A.z > max.z)
		max.z = A.z;

	
	if(B.x > max.x)
		max.x = B.x;
		
	if(B.y > max.y)
		max.y = B.y;
		
	if(B.z > max.z)
		max.z = B.z;
				
		
	if(C.x > max.x)
		max.x = C.x;
		
	if(C.y > max.y)
		max.y = C.y;
		
	if(C.z > max.z)
		max.z = C.z;
		
	KDBoundingBox bbox;
	bbox.min = min;					
	bbox.max = max;					
	
	return bbox;
}

glm::vec3 Triangle::getMidPoint()
{
	
	glm::vec3 mid_point = A + B + C;
	return (mid_point / 3.0f);
}

Triangle::~Triangle()
{
	//~ printf("\tdelete Triangle --\n");
}
//// end Triangle implementation

//// Implementing KD Node

KDNode::KDNode(int limit)
{
	polygons_limit = limit;
}

std::shared_ptr<KDNode> KDNode::build(std::vector<std::shared_ptr<Triangle> >& tris, int _depth) const
{
	
	//~ printf("-- Building KDNode. Depth : %d\n", depth);
	//~ printf("\tNum Triangles : %d\n", tris.size());
	
	
	std::shared_ptr<KDNode> node = std::make_shared<KDNode>();
	node->depth = _depth;
	node->triangles = tris;
	node->left = NULL;
	node->right = NULL;
	//~ node->bbox = KDBoundingBox();
	
	if(tris.size() == 0)
		return node;
		
	if(tris.size() == 1)
	{
		node->bbox = tris[0]->getBoundingBox();
		node->left  = std::make_shared<KDNode>();
		node->right = std::make_shared<KDNode>();
		node->left->triangles  = std::vector<std::shared_ptr<Triangle> >();
		node->right->triangles = std::vector<std::shared_ptr<Triangle> >();
		
		return node;
	}
	
	
	
	
	// get bounding box of all triangles
	node->bbox = tris[0]->getBoundingBox();
	
	for (size_t i = 1; i < tris.size(); i++)
	{
		node->bbox.expand(tris[i]->getBoundingBox());
	}
	
	
	//~ node->bbox.print();
	
	//find mid point of all triangles
	glm::vec3 mid_point = glm::vec3(0.0, 0.0, 0.0);
	
	for (size_t i = 0; i < tris.size(); i++)
	{
		mid_point = mid_point + tris[i]->getMidPoint();
	}
	
	mid_point = mid_point / (float)tris.size();
	
	
	
	std::vector<std::shared_ptr<Triangle> > left_tris;
	std::vector<std::shared_ptr<Triangle> > right_tris;
	int axis = node->bbox.getLongestAxis();
	

	for (size_t i = 0; i < tris.size(); i++)
	{
		switch(axis){
			case 0:
				mid_point.x >= tris[i]->getMidPoint().x ? right_tris.push_back(tris[i]) : left_tris.push_back(tris[i]);
				break;
			case 1:
				mid_point.y >= tris[i]->getMidPoint().y ? right_tris.push_back(tris[i]) : left_tris.push_back(tris[i]);
				break;			
			case 2:
				mid_point.z >= tris[i]->getMidPoint().z ? right_tris.push_back(tris[i]) : left_tris.push_back(tris[i]);
				break;
			
		}
	}	

	if((int)left_tris.size() > polygons_limit && (int)right_tris.size() > polygons_limit)
	{
		// recurse left and right sides
		node->left = build(left_tris, _depth + 1);
		node->right = build(right_tris, _depth + 1);
		
	}else{
		
		//~ printf("reached polygon limit of %d!!\n", polygons_limit);
		node->left = std::make_shared<KDNode>();
		node->right = std::make_shared<KDNode>();
		node->left->triangles = std::vector<std::shared_ptr<Triangle> >();
		node->right->triangles = std::vector<std::shared_ptr<Triangle> >();
	}
	
	return node;
	
	
	
	
}

KDNode::~KDNode()
{

	
	//~ printf("KDNode Destructor\n");
	
	

}
