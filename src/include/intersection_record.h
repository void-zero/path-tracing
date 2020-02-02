#ifndef INTERSECTION_RECORD_H_
#define INTERSECTION_RECORD_H_

#include <glm/glm.hpp>

struct IntersectionRecord
{
    float t_;
    float u_;
    float v_;
    
    glm::vec3 position_;
    glm::vec3 normal_;
};

#endif /* INTERSECTION_RECORD_H_ */

