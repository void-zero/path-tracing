#ifndef TRIANGLE_H_
#define TRIANGLE_H_

#include <glm/glm.hpp>
#include <cmath>

#include "primitive.h"

#ifndef MEMORY_LIMITATION
    #define pu mod3_[p_axis_+1] // Projection U axis
    #define pv mod3_[p_axis_+2] // Projection V axis

    struct edge{
        float nu;
        float nv;
    };
#endif

class Triangle : public Primitive
{
    public:
        glm::vec3 v_[3];   //Triangle vertices
        glm::vec3 normal_;

        #ifndef MEMORY_LIMITATION
            float normal_u_;
            float normal_v_;
            float normal_d_;

            char p_axis_; // Projection Axis

            edge edge_[2]; 
            
            const char mod3_[5] = {0, 1, 2, 0, 1};
        #else
            glm::vec3 edge_[2];
        #endif

        bool intersect( const Ray &ray,
                        IntersectionRecord &intersection_record ) const;

        Triangle( const glm::vec3 &v0,
                  const glm::vec3 &v1,
                  const glm::vec3 &v2,
                  Material::MaterialSharedPtr material );
        
};

#endif /* TRIANGLE_H_ */