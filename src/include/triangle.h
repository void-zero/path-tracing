#ifndef TRIANGLE_H_
#define TRIANGLE_H_

#include <glm/glm.hpp>
#include "primitive.h"

class Triangle : public Primitive{
    public:
        glm::vec3 v[3] = {{0.0f, 0.0f, 0.0f},
                          {0.0f, 0.0f, 0.0f},
                          {0.0f, 0.0f, 0.0f}};

        bool intersect( const Ray &ray,
                        IntersectionRecord &intersection_record ) const;

        Triangle();
        Triangle(const glm::vec3 &v0,
                 const glm::vec3 &v1,
                 const glm::vec3 &v2);
        
};

#endif /* TRIANGLE_H_ */