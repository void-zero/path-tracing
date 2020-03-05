#ifndef TRIANGLE_MESH_
#define TRIANGLE_MESH_

#include <iostream>
#include <vector>
#include "triangle.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

class TriangleMesh{
    public:
        std::vector<Triangle*> triangles_;

        TriangleMesh();
        TriangleMesh(const char* file_path);

        void load(const char* file_path);
};

#endif  // TRIANGLE_MESH_