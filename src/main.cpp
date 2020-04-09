#include <chrono>

#include "include/camera.h"
#include "include/orthographic_camera.h"
#include "include/perspective_camera.h"
#include "include/scene.h"
#include "include/buffer.h"
#include "include/path_tracer.h"

int main(int argc, char** argv)
{

    unsigned x_resolution = 1024;
    unsigned y_resolution = 768;

    std::chrono::high_resolution_clock::time_point t0, t1; // Time points used to measure the render time
    
    PerspectiveCamera camera{ -2.0f, 
                               2.0f, 
                              -1.125f, 
                               1.125f,
                               3.0f,
                               glm::ivec2{ x_resolution, y_resolution }, 
                               glm::vec3{ 8.43f, -13.84f, 20.0f },     // position
                               glm::vec3{ 0.0f, 1.0f,  0.0f },     // up
                               glm::vec3{ -7.0f, 0.0f, -12.0f } };   // look at
    
    std::string arg;

    switch (argc)
    {
    case 1:
        break;

    case 2:
        arg = argv[1];
        break;  

    default:
        std::cerr << "Too many parameters!\n"
                  << "./ptracer [number of samples]\n";
        return EXIT_FAILURE;
    }

    Scene scene{};
    scene.load();

    std::cout << "Number of primitives: " << scene.primitives_.size();

    Buffer rendering_buffer{ x_resolution, y_resolution };
    glm::vec3 background_color{ 0.0f, 0.0f, 0.0f };

    // Set up the renderer.
    PathTracer pt( camera,
                   scene,
                   background_color,
                   rendering_buffer,
                   arg.empty()? 0 : std::stoi(arg) );

    t0 = std::chrono::high_resolution_clock::now();

    if( arg.empty() )
        pt.rayCast();
    else
        pt.integrate(); // Renders the final image.

    t1 = std::chrono::high_resolution_clock::now();
    std::cout << "\nRender time: " << (double) std::chrono::duration_cast<std::chrono::nanoseconds>(t1 - t0).count()/1000000000 << " (s)\n";

    // Save the rendered image to a .ppm file.
    rendering_buffer.save( "renders/output.ppm" );

    return EXIT_SUCCESS;
}

