#ifndef TRIANGLE_MESH_
#define TRIANGLE_MESH_

#include <iostream>
#include <vector>
#include "triangle.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

class TriangleMesh
{
    public:
        TriangleMesh( const std::string &file_path, Material::MaterialSharedPtr material );

        // void load(const std::string &file_path);

        std::vector<Triangle*> triangles_;

        Material::MaterialSharedPtr material_;
};

#endif  // TRIANGLE_MESH_