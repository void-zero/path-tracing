#ifndef TRIANGLE_H_
#define TRIANGLE_H_

#include <glm/glm.hpp>
#include <cmath>
#include "primitive.h"

#ifndef MEMORY_LIMITATION
    #include "triaccel.h"

    #define pu mod3_[tas_.p_axis+1] // Projection U axis
    #define pv mod3_[tas_.p_axis+2] // Projection V axis
#endif

class Triangle : public Primitive{
    public:
        glm::vec3 v_[3];   //Triangle vertices

        #ifndef MEMORY_LIMITATION
            TriAccel tas_; // Triangle Acceleration Structure
            char mod3_[5] = {0, 1, 2, 0, 1};
        #else
            glm::vec3 edge_[2];
        #endif

        bool intersect( const Ray &ray,
                        IntersectionRecord &intersection_record ) const;

        Triangle();
        Triangle(const glm::vec3 &v0,
                 const glm::vec3 &v1,
                 const glm::vec3 &v2);
        
};

#endif /* TRIANGLE_H_ */