#ifndef PERSPECTIVE_CAMERA_H_
#define PERSPECTIVE_CAMERA_H_

#include "camera.h"

class PerspectiveCamera : public Camera
{
public:

    PerspectiveCamera( void );

    PerspectiveCamera( const float min_x,
                       const float max_x,
                       const float min_y,
                       const float max_y,
                       const float focal_distance,
                       const glm::ivec2 &resolution,
                       const glm::vec3 &position,
                       const glm::vec3 &up_vector,
                       const glm::vec3 &look_at );

    Ray getWorldSpaceRay( const glm::vec2 &pixel_coord ) const;

    float min_x_;

    float max_x_;

    float min_y_;

    float max_y_;

    float focal_distance_;

};

#endif /* PERSPECTIVE_CAMERA_H_ */

