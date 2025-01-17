#include "include/sphere.h"

Sphere::Sphere( const glm::vec3 &center,
                float radius,
                Material::MaterialSharedPtr material ) :
        Primitive::Primitive(material),
        center_{ center },
        radius_{ radius }
{}

bool Sphere::intersect( const Ray &ray,
                        IntersectionRecord &record ) const
{
    /* Ray-sphere intersection test adapted from the very efficient algorithm presented in the article:
     *
     *     "Intersection of a Ray with a Sphere".
     *     Jeff Hultquist.
     *     Graphics Gems.
     *     Academic Press.
     *     1990.
     */

    float t1;
    float t2;

    glm::vec3 eo = center_ - ray.origin_;
    float v = glm::dot( eo, ray.direction_ );
    float disc = ( radius_ * radius_ ) - ( glm::dot( eo, eo ) - ( v * v ) );

    if ( disc < EPSILON )
        return false;                           // no intersection
    else
    {
        float d = sqrt( disc );
        t1 = v - d;                             // first intersection point
        t2 = v + d;                             // second intersection point
    }

    // Set the intersection record
    record.t_ =  ( t1 > EPSILON ) ? t1 : t2;
    record.point_ = ray.origin_ + record.t_ * ray.direction_;
    record.normal_ = glm::normalize( record.point_ - center_ );

    return true;
}

