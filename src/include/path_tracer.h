#ifndef PATHTRACER_H_
#define PATHTRACER_H_

#include <sstream>
#include <iostream>
#include <iomanip>
#include <random>

#include "camera.h"
#include "scene.h"
#include "buffer.h"
#include "ray.h"
#include "intersection_record.h"

#define PI_FLOAT 3.14159265358979f
#define MAX_DEPTH 5

class PathTracer
{
public:

    PathTracer( Camera &camera,
                const Scene &scene,
                const glm::vec3 background_color,
                Buffer &buffer,
                int num_samples );

    void integrate( void );

    void rayCast( void );

private:

    const Camera &camera_;

    const Scene &scene_;

    glm::dvec3 background_color_;

    Buffer &buffer_;

    int num_samples_;

    std::mt19937 generator_;

    std::uniform_real_distribution<float> dist_;

    glm::vec3 rayRadiance( const Ray &ray, int current_depth );

    Ray getRayInHemisphere( const IntersectionRecord &record );

    Ray getReflectedRay( const Ray &ray, const IntersectionRecord &record ) const;

    float random( void );

};

#endif /* PATHTRACER_H_ */

