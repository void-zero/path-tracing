#ifndef SCENE_H_
#define SCENE_H_

#include <iostream>
#include <fstream>
#include <memory>
#include <vector>
#include <glm/glm.hpp>

#include "triangle.h"
#include "triangle_mesh.h"
#include "sphere.h" 

class Scene
{
    public:
        Scene( void );

        ~Scene( void );

        std::vector<Primitive::PrimitiveUniquePtr> primitives_;

        bool intersect( const Ray &ray,
                        IntersectionRecord &intersection_record ) const;

        void load( void );
        
        void addMesh(TriangleMesh &mesh);
};

#endif /* SCENE_H_ */