#include "include/perspective_camera.h"

PerspectiveCamera::PerspectiveCamera( void )
{}

PerspectiveCamera::PerspectiveCamera( const float min_x,
                                      const float max_x,
                                      const float min_y,
                                      const float max_y,
                                      const float focal_distance,
                                      const glm::ivec2 &resolution,
                                      const glm::vec3 &position,
                                      const glm::vec3 &up_vector,
                                      const glm::vec3 &look_at ) :
        Camera::Camera{ resolution, 
                        position,
                        up_vector,
                        look_at },
        min_x_{ min_x },
        max_x_{ max_x },
        min_y_{ min_y },
        max_y_{ max_y },
        focal_distance_{focal_distance}
{}

Ray PerspectiveCamera::getWorldSpaceRay( const glm::vec2 &pixel_coord ) const
{
    float width = max_x_ - min_x_;
    float height = max_y_ - min_y_;

    glm::vec3 ray_direction{ pixel_coord[0] / static_cast< float >( resolution_[0] ) * width + min_x_,
                             pixel_coord[1] / static_cast< float >( resolution_[1] ) * height + min_y_,
                             -focal_distance_ };

    return Ray{ position_, 
                glm::normalize( onb_.getBasisMatrix() * ray_direction ) };
}

