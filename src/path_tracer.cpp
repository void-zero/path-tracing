#include "include/path_tracer.h"

PathTracer::PathTracer( Camera &camera,
                        const Scene &scene,
                        const glm::vec3 background_color,
                        Buffer &buffer,
                        int num_samples ) :
        camera_( camera ),
        scene_( scene ),
        background_color_{ background_color },
        buffer_( buffer ),
        num_samples_( num_samples ),
        generator_(std::random_device{}()),
        dist_(std::uniform_real_distribution<float>(0.0f, 1.0f))
{}

inline float PathTracer::random( void ){
    return dist_(generator_);
}

Ray PathTracer::getRayInHemisphere( const IntersectionRecord &record )
{
    ONB world_base;
    world_base.setFromV(record.normal_);

    float r1 = random();
    while(r1 == 1.0f)
        r1 = random();

    float r2 = random();
    while(r2 == 1.0f)
        r2 = random();
    
    float theta = glm::acos(1 - r1);
    float phi = 2 * PI_FLOAT * r2;

    return Ray
    { record.point_, 
      glm::vec3{ 
          glm::normalize( 
              glm::vec3{glm::sin(theta) * glm::cos(phi),  // X
                        glm::sin(theta) * glm::sin(phi),  // Y
                        glm::cos(theta)}                  // Z
              * world_base.getBasisMatrix()
          ) 
      }
    };        
}

inline Ray PathTracer::getReflectedRay( const Ray &ray, const IntersectionRecord &record ) const
{
    return Ray{ record.point_, ray.direction_ - 2.0f * record.normal_ * glm::dot(ray.direction_, record.normal_) };
}

glm::vec3 PathTracer::rayRadiance( const Ray &ray, int current_depth ){
    IntersectionRecord record{std::numeric_limits<float>::max()};
    glm::vec3 radiance_out{0.0f, 0.0f, 0.0f};
    Ray reflected_ray;
    float cos;

    if ( current_depth < MAX_DEPTH && scene_.intersect(ray, record) )
    {
        switch (scene_.primitives_[record.id_]->material_->type_)
        {
        case Material::Type::DIFFUSE:
            reflected_ray = getRayInHemisphere(record);

            cos =  glm::dot(record.normal_, reflected_ray.direction_);
            if(cos < 0.0f){
                reflected_ray.direction_ = -reflected_ray.direction_;
                cos = -cos;
            }

            radiance_out =  2.0f * scene_.primitives_[record.id_]->material_->reflectance_ * rayRadiance( reflected_ray, ++current_depth ) * cos;
            break;

        case Material::Type::MIRROR:
            radiance_out = scene_.primitives_[record.id_]->material_->reflectance_ * rayRadiance(getReflectedRay( ray, record ), ++current_depth);
            break;

        case Material::Type::EMMITER:
            radiance_out = scene_.primitives_[record.id_]->material_->emitance_;
            break;
        }
        
    }

    return radiance_out;
}

void PathTracer::integrate( void )
{
    // Image space origin (i.e. x = 0 and y = 0) at the top left corner.

    // Loops over image rows, in parallel
    #pragma omp parallel for schedule(dynamic, 1)
    for ( std::size_t y = 0; y < buffer_.v_resolution_; y++ )
    {
        std::stringstream progress_stream;
        progress_stream << "\r  progress .........................: "
                        << std::fixed << std::setw( 6 )
                        << std::setprecision( 2 )
                        << 100.0 * y / ( buffer_.v_resolution_ - 1 )
                        << "%";

        std::clog << progress_stream.str();

        // Loops over image columns
        for ( std::size_t x = 0; x < buffer_.h_resolution_; x++ )
        {
           for (std::size_t i = 0; i < num_samples_; i++)
            {
                Ray ray{camera_.getWorldSpaceRay( glm::vec2{ x, y } )};

                buffer_.buffer_data_[x][y] += rayRadiance(ray, 0);
            }
            buffer_.buffer_data_[x][y] /= num_samples_;
        }
    }

    std::clog << std::endl;
}

void PathTracer::rayCast( void )
{
    // Image space origin (i.e. x = 0 and y = 0) at the top left corner.

    // Loops over image rows
    #pragma omp parallel for schedule(dynamic, 1)
    for ( std::size_t y = 0; y < buffer_.v_resolution_; y++ )
    {
        std::stringstream progress_stream;
        progress_stream << "\r  progress .........................: "
                        << std::fixed << std::setw( 6 )
                        << std::setprecision( 2 )
                        << 100.0 * y / ( buffer_.v_resolution_ - 1 )
                        << "%";

        std::clog << progress_stream.str();

        IntersectionRecord record;
        // Loops over image columns
        for ( std::size_t x = 0; x < buffer_.h_resolution_; x++ )
        {
           record.t_ = std::numeric_limits< double >::max();

            Ray ray{ camera_.getWorldSpaceRay( glm::vec2{ x + 0.5f, y + 0.5f } ) };

            if ( scene_.intersect( ray, record ) )
                buffer_.buffer_data_[x][y] =  (1.5f/record.t_)*(scene_.primitives_[record.id_]->material_->reflectance_ 
                                             + scene_.primitives_[record.id_]->material_->emitance_) ;
                // buffer_.buffer_data_[x][y] = glm::vec3{ 1/record.t_ * 1.5};
        }
    }

    std::clog << std::endl;
}
