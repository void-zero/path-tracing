#ifndef PERFECT_MIRROR_H_
#define PERFECT_MIRROR_H_

#include "material.h"

class PerfectMirror : public Material
{
public:

    PerfectMirror( float R,
                   float G,
                   float B );

    PerfectMirror ( void );

    virtual ~PerfectMirror( void );
};

#endif /* PERFECT_MIRROR_H_ */

