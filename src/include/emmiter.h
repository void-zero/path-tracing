#ifndef EMMITER_H_
#define EMMITER_H_

#include "material.h"

class Emmiter : public Material
{
public:

    Emmiter( float R,
             float G,
             float B );

    Emmiter ( void );

    virtual ~Emmiter( void );
};

#endif /* EMMITER_H_ */

