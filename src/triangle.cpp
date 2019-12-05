#include "include/triangle.h"

Triangle::Triangle(){}

Triangle::Triangle( const glm::vec3 &v0,
                    const glm::vec3 &v1,
                    const glm::vec3 &v2) :
        v{v0, v1, v2}
{}

bool Triangle::intersect( const Ray &ray,
                        IntersectionRecord &intersection_record ) const{
    /* Ray-Triangle intersection test adapted from the very efficient algorithm presented in the article:
     *
     *     "Fast, Minimum Storage Ray-Triangle Intersection".
     *     Tomas Möller & Ben Trumbore.
     *     Journal of Graphics Tools.
     *     Academic Press.
     *     1997.
     */


}

