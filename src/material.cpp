#include "include/material.h"

Material::Material( Type type, glm::vec3 reflectance ) :
        type_{type},
        emitance_{glm::vec3{0.0f, 0.0f, 0.0f}},
        reflectance_{reflectance} {}

Material::Material( Type type, glm::vec3 emitance, glm::vec3 reflectance ) :
        type_{type},
        emitance_{emitance},
        reflectance_{reflectance} {}

Material::~Material( void ) {}