#include "include/camera.h"
#include "include/orthographic_camera.h"
#include "include/perspective_camera.h"
#include "include/scene.h"
#include "include/buffer.h"
#include "include/raytracer.h"
#include <chrono>

int main(int argc, char** argv)
{
    unsigned x_resolution = 1024;
    unsigned y_resolution = 1024;

    std::chrono::high_resolution_clock::time_point t0, t1; // Time points used to measure the render time
    
    PerspectiveCamera camera{ -1.25f, 
                               1.25f, 
                              -1.25f, 
                               1.25f,
                               3.0f,
                               glm::ivec2{ x_resolution, y_resolution }, 
                               glm::vec3{ 0.0f, 0.0f,  1.0f },     // position
                               glm::vec3{ 0.0f, 1.0f,  0.0f },     // up
                               glm::vec3{ 0.0f, 0.0f, -1.0f } };   // look at
    
    std::string img_dest;

    if(argc >= 2){
        img_dest = argv[1];
        if(argc == 3){
            img_dest += argv[2];
            img_dest += ".ppm";
        } 
        else
            img_dest += "out.ppm";
    }
    else
        img_dest = "renders/out.ppm";

    TriangleMesh model{"models/monkey.obj"};
    std::cout << "Number of primitives: " << model.triangles_.size() << "\n";

    Scene scene{};
    scene.addMesh(model);

    Buffer rendering_buffer{ x_resolution, y_resolution };
    glm::vec3 background_color{ 0.0f, 0.0f, 0.0f };

    t0 = std::chrono::high_resolution_clock::now();

    // Set up the renderer.
    RayTracer rt( camera,
                  scene,
                  background_color,
                  rendering_buffer );

    rt.integrate(); // Renders the final image.

    t1 = std::chrono::high_resolution_clock::now();
    std::cout << "\nRender time: " << (double) std::chrono::duration_cast<std::chrono::nanoseconds>(t1 - t0).count()/1000000000 << " (s)\n";

    // Save the rendered image to a .ppm file.
    rendering_buffer.save( img_dest );

    return EXIT_SUCCESS;
}

