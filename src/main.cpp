#include "include/camera.h"
#include "include/orthographic_camera.h"
#include "include/scene.h"
#include "include/buffer.h"
#include "include/raytracer.h"
#include <chrono>

int main( void )
{
    unsigned int x_resolution = 512;
    unsigned int y_resolution = 512;
    std::chrono::high_resolution_clock::time_point t0, t1; // Time points used to measure the render time

    OrthographicCamera camera{ -1.25f, 
                                1.25f, 
                               -1.25f, 
                                1.25f,
                                glm::ivec2{ x_resolution, y_resolution }, 
                                glm::vec3{ 0.0f, 0.0f,  1.0f },     // position
                                glm::vec3{ 0.0f, 1.0f,  0.0f },     // up
                                glm::vec3{ 0.0f, 0.0f, -1.0f } };   // look at
    Scene scene{};
    
    t0 = std::chrono::high_resolution_clock::now();

    scene.load();

    Buffer rendering_buffer{ x_resolution, y_resolution };
    glm::vec3 background_color{ 0.0f, 0.0f, 0.0f };

    // Set up the renderer.
    RayTracer rt( camera,
                  scene,
                  background_color,
                  rendering_buffer );

    rt.integrate(); // Renders the final image.

    t1 = std::chrono::high_resolution_clock::now();

    std::cout << "\nRender time: " << (double) std::chrono::duration_cast<std::chrono::nanoseconds>(t1 - t0).count()/1000000000 << " (s)\n";

    // Save the rendered image to a .ppm file.
    rendering_buffer.save( "renders/Assignment 2/triangle.ppm" );

    return EXIT_SUCCESS;
}

