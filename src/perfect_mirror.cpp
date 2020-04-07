#include "include/perfect_mirror.h"

PerfectMirror::PerfectMirror( float R,
                              float G,
                              float B ) :
        Material::Material( Material::Type::MIRROR, glm::vec3{R, G, B} ) {}

PerfectMirror::PerfectMirror( void ) :
        Material::Material( Material::Type::MIRROR, glm::vec3{1.0f, 1.0f, 1.0f} ) {}

PerfectMirror::~PerfectMirror( void ) {}