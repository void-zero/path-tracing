#include "include/triangle.h"

Triangle::Triangle(){}

#ifndef MEMORY_LIMITATION
Triangle::Triangle( const glm::vec3 &v0,
                    const glm::vec3 &v1,
                    const glm::vec3 &v2 ) :
        v_{v0, v1, v2}
{
	const glm::vec3 edge[2] = {v_[1] - v_[0],
						 v_[2] - v_[0]};

	const glm::vec3 normal = glm::normalize(glm::cross(edge[0], edge[1]));
	
	// Getting the plane which the normal has its max absolute value to set up the projection axis
	// X = 0, Y = 1, Z= 2
	if(abs(normal.x) > abs(normal.y))
		if(abs(normal.x) > abs(normal.z))
			tas_.p_axis = 0;
		else
			tas_.p_axis = 2;
	else if(abs(normal.y) > abs(normal.z))
		tas_.p_axis = 1;
	else
		tas_.p_axis = 2;

	// Calculating the normals
 	tas_.n_v = normal[pv] / normal[tas_.p_axis];
	tas_.n_u = normal[pu] / normal[tas_.p_axis];
	tas_.n_d = glm::dot(normal, v_[0]) / normal[tas_.p_axis];

	const float denominator = (edge[1][pu]*edge[0][pv] - edge[1][pv]*edge[0][pu]);
    tas_.e1_nu =  edge[1][pu]/denominator;
    tas_.e1_nv = -edge[1][pv]/denominator;
    tas_.e0_nu =  edge[0][pv]/denominator;
    tas_.e0_nv = -edge[0][pu]/denominator;
}

bool Triangle::intersect( const Ray &ray,
                                 IntersectionRecord &record ) const
{
	 /* Ray-Triangle intersection test adapted from the algorithm proposed by Ingo Wald and modified by Jacco Bikker:
     *
     *     "Fast Triangle Intersection in RTRT".
     *     Ingo Wald, in his PhD paper(Section 7.1).
	 * 
     *     "Raytracing: Theory & Implementation Part 7, Kd-Trees and More Speed"
	 *	   Jacco Bikker, DevMaster.net
     */

	const float distance =   (1.0f/(ray.direction_[tas_.p_axis] + tas_.n_u 
						   * ray.direction_[pu] + tas_.n_v * ray.direction_[pv]))
						   * (tas_.n_d - ray.origin_[tas_.p_axis] - tas_.n_u 
						   * ray.origin_[pu] - tas_.n_v * ray.origin_[pv]);

	// Computing hitpoint positions on the uv plane
	const float hit_u = (ray.origin_[pu] + distance * ray.direction_[pu] - v_[0][pu]);
	const float hit_v = (ray.origin_[pv] + distance * ray.direction_[pv] - v_[0][pv]);

	// Checking if the first barycentric coordinate is valid
	const float beta = (hit_v * tas_.e1_nu + hit_u * tas_.e1_nv);
	if(beta < 0.0f)
		return false;

	// Checking if the second barycentric coordinate is valid
	const float gamma = (hit_u * tas_.e0_nu + hit_v * tas_.e0_nv);
	if(gamma < 0.0f)
		return false;

	// Checking if the third barycentric coordinate (alpha) is valid
	if(beta+gamma > 1.0f)
		return false;

	record.t_ = distance;
	record.u_ = beta;
	record.v_ = gamma;

	return true;
}
#else
Triangle::Triangle( const glm::vec3 &v0,
                    const glm::vec3 &v1,
                    const glm::vec3 &v2 ) :
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

	glm::vec3 p_vec = glm::cross(ray.direction_, edge_[1]);
	double det = glm::dot(edge_[0], p_vec);
	
	if(det > -DBL_EPSILON && det < DBL_EPSILON)	// Checking if the ray is parallel to the triangle, meaning that there is no intersection
		return false;

	double inv_det = 1/det;

	glm::vec3 t_vec = ray.origin_ - v_[0];
	record.u_ = glm::dot(t_vec, p_vec) * inv_det;
	if(record.u_ < 0.0f || record.u_ > 1.0f)
		return false;

	glm::vec3 q_vec = glm::cross(t_vec, edge_[0]);
	record.v_ = glm::dot(ray.direction_, q_vec) * inv_det;
	if(record.v_ < 0.0f || record.u_ + record.v_ > 1.0f)
		return false;

	record.t_ = glm::dot(edge_[1], q_vec) * inv_det;

	return true;
}
#endif
