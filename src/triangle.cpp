#include "include/triangle.h"

#ifndef MEMORY_LIMITATION
Triangle::Triangle( const glm::vec3 &v0,
                    const glm::vec3 &v1,
                    const glm::vec3 &v2,
					Material::MaterialSharedPtr material ) :
		Primitive::Primitive(material),
        v_{v0, v1, v2}
{
	const glm::vec3 edge[2] = {v_[1] - v_[0],
						       v_[2] - v_[0]};

	normal_ = glm::normalize(glm::cross(edge[0], edge[1]));
	
	// Getting the plane which the normal has its max absolute value to set up the projection axis
	// X = 0, Y = 1, Z= 2
	if(std::abs(normal_.x) > std::abs(normal_.y))
		if(std::abs(normal_.x) > std::abs(normal_.z))
			p_axis_ = 0;
		else
			p_axis_ = 2;
	else if(std::abs(normal_.y) > std::abs(normal_.z))
		p_axis_ = 1;
	else
		p_axis_ = 2;

	// Calculating the normals
	normal_u_ = normal_[pu] / normal_[p_axis_];					// n_u
	normal_v_ = normal_[pv] / normal_[p_axis_];					// n_v
	normal_d_ = glm::dot(normal_, v_[0]) / normal_[p_axis_];	// n_d

	const float denominator = (edge[1][pu]*edge[0][pv] - edge[1][pv]*edge[0][pu]);
    edge_[1].nu =  edge[1][pu]/denominator;
    edge_[1].nv = -edge[1][pv]/denominator;
    edge_[0].nu =  edge[0][pv]/denominator;
    edge_[0].nv = -edge[0][pu]/denominator;
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

	const float distance =   (1.0f/(ray.direction_[p_axis_] + normal_u_ 
						   * ray.direction_[pu] + normal_v_ * ray.direction_[pv]))
						   * (normal_d_ - ray.origin_[p_axis_] - normal_u_ 
						   * ray.origin_[pu] - normal_v_ * ray.origin_[pv]);
	
	if(distance < EPSILON)
		return false;

	// Computing hitpoint positions on the uv plane
	const float hit_u = (ray.origin_[pu] + distance * ray.direction_[pu] - v_[0][pu]);
	const float hit_v = (ray.origin_[pv] + distance * ray.direction_[pv] - v_[0][pv]);

	// Checking if the first barycentric coordinate is valid
	const float beta = (hit_v * edge_[1].nu + hit_u * edge_[1].nv);
	if(beta < 0.0f)
		return false;

	// Checking if the second barycentric coordinate is valid
	const float gamma = (hit_u * edge_[0].nu + hit_v * edge_[0].nv);
	if(gamma < 0.0f)
		return false;

	// Checking if the third barycentric coordinate (alpha) is valid
	if(beta+gamma > 1.0f)
		return false;

	// Setting up the intersection record
	record.t_ = distance;
	record.normal_ = normal_;
	record.point_ = ray.origin_ + record.t_ * ray.direction_;

	return true;
}
#else
Triangle::Triangle( const glm::vec3 &v0,
                    const glm::vec3 &v1,
                    const glm::vec3 &v2 ) :
        v_{v0, v1, v2},
		edge_{v_[1] - v_[0], v_[2] - v_[0]},
		normal_{glm::normalize(glm::cross(edge_[0], edge_[1]))}
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
	
	if(det > -EPSILON && det < EPSILON)	// Checking if the ray is parallel to the triangle, meaning that there is no intersection
		return false;

	double inv_det = 1/det;

	glm::vec3 t_vec = ray.origin_ - v_[0];
	record.u_ = glm::dot(t_vec, p_vec) * inv_det;
	if(record.u_ < EPSILON || record.u_ > 1.0f)
		return false;

	glm::vec3 q_vec = glm::cross(t_vec, edge_[0]);
	record.v_ = glm::dot(ray.direction_, q_vec) * inv_det;
	if(record.v_ < EPSILON || record.u_ + record.v_ > 1.0f)
		return false;

	record.t_ = glm::dot(edge_[1], q_vec) * inv_det;
	record.normal_ = normal_;

	return true;
}
#endif
