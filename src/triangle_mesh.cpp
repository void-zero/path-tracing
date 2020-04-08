#include "include/triangle_mesh.h"

TriangleMesh::TriangleMesh( const std::string &file_path, Material::MaterialSharedPtr material ) :
        material_{material}        
{
    Assimp::Importer importer;
    const aiScene *scene =  importer.ReadFile( file_path,
                                               aiProcess_Triangulate            |
                                               aiProcess_JoinIdenticalVertices  |
                                               aiProcess_SortByPType);

    if(!scene)
    {
        std::cerr << "Could not open file: " << file_path << "\n";
        std::exit(-1);
    }

    for(unsigned i = 0; i < scene->mNumMeshes; i++)
    {
        aiVector3D* vertices = scene->mMeshes[i]->mVertices;
        
        for(unsigned j = 0; j < scene->mMeshes[i]->mNumFaces; j++)
        { 
            aiFace face = scene->mMeshes[i]->mFaces[j];

            triangles_.push_back( new Triangle{ glm::vec3{vertices[face.mIndices[0]][0], vertices[face.mIndices[0]][1], vertices[face.mIndices[0]][2]},
                                                glm::vec3{vertices[face.mIndices[1]][0], vertices[face.mIndices[1]][1], vertices[face.mIndices[1]][2]},
                                                glm::vec3{vertices[face.mIndices[2]][0], vertices[face.mIndices[2]][1], vertices[face.mIndices[2]][2]},
                                                material_});
        }

    }
}