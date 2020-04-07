#ifndef MATERIAL_H_
#define MATERIAL_H_

#include <glm/glm.hpp>
#include <memory>

#define PI_FLOAT 3.14159265358979f

class Material
{
public:

    typedef std::shared_ptr< Material > MaterialSharedPtr;

    enum class Type { EMMITER, DIFFUSE, MIRROR };

    Type type_;

    Material( Type type, glm::vec3 reflectance );

    Material( Type type, glm::vec3 emitance, glm::vec3 reflectance );

    virtual ~Material( void );

    glm::vec3 emitance_;

    glm::vec3 reflectance_;
};

#endif /* MATERIAL_H_ */

