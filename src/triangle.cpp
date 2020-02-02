#include "include/triangle.h"

Triangle::Triangle(){}

Triangle::Triangle( const glm::vec3 &v0,
                    const glm::vec3 &v1,
                    const glm::vec3 &v2) :
        v_{v0, v1, v2},
		edge_{v_[1] - v_[0], v_[2] - v_[0]}
{}

bool Triangle::intersect( const Ray &ray,
                        IntersectionRecord &record ) const
{
    /* Ray-Triangle intersection test adapted from the very efficient algorithm presented in the article:
     *
     *     "Fast, Minimum Storage Ray-Triangle Intersection".
     *     Tomas Möller & Ben Trumbore.
     *     Journal of Graphics Tools.
     *     Academic Press.
     *     1997.
     */

	glm::vec3 pVec = glm::cross(ray.direction_, edge_[1]);
	double det = glm::dot(edge_[0], pVec);
	
	if(det > -DBL_EPSILON && det < DBL_EPSILON)	// Checking if the ray is parallel to the triangle, meaning that there is no intersection
		return false;

	double invDet = 1/det;

	glm::vec3 tVec = ray.origin_ - v_[0];
	record.u_ = glm::dot(tVec, pVec) * invDet;
	if(record.u_ < 0.0f || record.u_ > 1.0f)
		return false;

	glm::vec3 qVec = glm::cross(tVec, edge_[0]);
	record.v_ = glm::dot(ray.direction_, qVec) * invDet;
	if(record.v_ < 0.0f || record.u_ + record.v_ > 1.0f)
		return false;

	record.t_ = glm::dot(edge_[1], qVec) * invDet;

	return true;
}

