#include "include/diffuse.h"

Diffuse::Diffuse( float R,
                  float G,
                  float B ) :
        // color_{R, G, B},
        Material::Material( Material::Type::DIFFUSE, glm::vec3{R, G, B} ) {}

Diffuse::Diffuse( void ) :
        Material::Material( Material::Type::DIFFUSE, glm::vec3{1.0f, 1.0f, 1.0f} ) {}

Diffuse::~Diffuse( void ) {}