#ifndef INTERSECTION_RECORD_H_
#define INTERSECTION_RECORD_H_

#include <glm/glm.hpp>

struct IntersectionRecord
{
    float t_;
    glm::vec3 normal_;
    glm::vec3 point_;

    // Index of the collided primitive in the scene primitives vector
    std::size_t id_;
};

#endif /* INTERSECTION_RECORD_H_ */

