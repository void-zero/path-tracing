#include "include/primitive.h"

Primitive::Primitive( Material::MaterialSharedPtr material ) : 
        material_{material} {}

Primitive::~Primitive( void ) {}