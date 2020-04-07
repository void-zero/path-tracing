#ifndef PRIMITIVE_H_
#define PRIMITIVE_H_

#include <memory>

#include "ray.h"
#include "intersection_record.h"
#include "material.h"

class Primitive
{
public:

    typedef std::unique_ptr< Primitive > PrimitiveUniquePtr;

    Material::MaterialSharedPtr material_;

    Primitive( Material::MaterialSharedPtr material );

    virtual ~Primitive( void );

    virtual bool intersect( const Ray &ray,
                            IntersectionRecord &intersection_record ) const = 0;
};

#endif /* PRIMITIVE_H_ */

