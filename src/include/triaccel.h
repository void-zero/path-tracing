#ifndef TRIACCEL_H_
#define TRIACCEL_H_

/*
    Triangle acceleration structure adapted from the data layout proposed by
    Ingo Wald in his PhD dissertation,
    section 7.1, named "Fast Triangle Intersection in RTRT"
*/

struct TriAccel
{
    // plane:
    float n_u; //!< == normal.u / normal.k
    float n_v; //!< == normal.v / normal.k
    float n_d; //!< constant of plane equation
    int p_axis; // projection axis

    // line equation for line ac
    float e1_nu;
    float e1_nv;

    // line equation for line ab
    float e0_nu;
    float e0_nv;
};

#endif // TRIACCEL_H_