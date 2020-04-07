#ifndef SPHERE_H_
#define SPHERE_H_

#include <glm/glm.hpp>

#include "primitive.h"

class Sphere : public Primitive
{
public:

    Sphere( void );

    Sphere( const glm::vec3 &center,
            float radius,
            Material::MaterialSharedPtr material );

    bool intersect( const Ray &ray,
                    IntersectionRecord &intersection_record ) const;

    glm::vec3 center_;

    float radius_;

private:

    static const float kIntersectionTestEpsilon_;
};

#endif /* SPHERE_H_ */

