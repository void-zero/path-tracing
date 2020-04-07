#ifndef DIFFUSE_H_
#define DIFFUSE_H_

#include "material.h"
#include "ray.h"

class Diffuse : public Material
{
public:

    Diffuse( float R,
             float G,
             float B );

    Diffuse ( void );

    virtual ~Diffuse( void );
};

#endif /* DIFFUSE_H_ */

