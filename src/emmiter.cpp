#include "include/emmiter.h"

Emmiter::Emmiter( float R,
                  float G,
                  float B ) :
        // color_{R, G, B},
        Material::Material( Material::Type::EMMITER, glm::vec3{R, G, B}, glm::vec3{0.0f, 0.0f, 0.0f} ) {}

Emmiter::Emmiter( void ) :
        Material::Material( Material::Type::EMMITER, glm::vec3{10.0f, 10.0f, 10.0f}, glm::vec3{0.0f, 0.0f, 0.0f} ) {}

Emmiter::~Emmiter( void ) {}