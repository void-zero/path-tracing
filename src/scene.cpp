#include "include/scene.h"

Scene::Scene( void )
{}

Scene::~Scene( void )
{}

bool Scene::intersect( const Ray &ray,
                       IntersectionRecord &intersection_record ) const
{
    bool intersection_result = false;
    IntersectionRecord tmp_intersection_record;
    std::size_t num_primitives = primitives_.size();

    // Loops over the list of primitives, testing the intersection of each primitive against the given ray 
    for ( std::size_t primitive_id = 0; primitive_id < num_primitives; primitive_id++ )
        if ( primitives_[primitive_id]->intersect( ray, tmp_intersection_record ) )
            if ( ( tmp_intersection_record.t_ < intersection_record.t_ ) && ( tmp_intersection_record.t_ > 0.0 ) )
            {
                intersection_record = tmp_intersection_record;
                intersection_record.id_ = primitive_id;
                intersection_result = true; // the ray intersects a primitive!
            }

    return intersection_result;
}

void Scene::load( void ) 
{
    auto emmiter = Material::MaterialSharedPtr(new Emmiter{20.0f, 20.0f, 20.0f});
    auto red = Material::MaterialSharedPtr(new Diffuse{.75f, .25f, .25f});
    auto blue = Material::MaterialSharedPtr(new Diffuse{.25f, .25f, .75f});
    auto grey = Material::MaterialSharedPtr(new Diffuse{.25f, .25f, .25f});
    auto white = Material::MaterialSharedPtr(new Diffuse{.75f, .75f, .75f});
    auto perfect_mirror = Material::MaterialSharedPtr(new PerfectMirror);

    TriangleMesh human{"models/human.obj", Material::MaterialSharedPtr(grey)};
    addMesh(human);

    TriangleMesh walls{"models/walls.obj", Material::MaterialSharedPtr(white)};
    addMesh(walls);

    TriangleMesh left_wall{"models/left_wall.obj", Material::MaterialSharedPtr(red)};
    addMesh(left_wall);

    TriangleMesh right_wall{"models/right_wall.obj", Material::MaterialSharedPtr(blue)};
    addMesh(right_wall);

    TriangleMesh mirror{"models/mirror.obj", Material::MaterialSharedPtr(perfect_mirror)};
    addMesh(mirror);

    primitives_.push_back( Primitive::PrimitiveUniquePtr( new Sphere{glm::vec3(1.0f, -16.3f, -2.7f), 2.0f, emmiter} ) );
}

inline void Scene::addMesh(const TriangleMesh &mesh)
{
    for(unsigned i = 0; i < mesh.triangles_.size(); i++)
            primitives_.push_back(Primitive::PrimitiveUniquePtr(mesh.triangles_[i]));
}
