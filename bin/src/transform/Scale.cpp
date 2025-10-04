#include "headers/transform/Scale.hpp"

Scale::Scale(glm::vec3 scale) : scale(scale) 
{

}

void Scale::SetScale(glm::vec3 scale)
{ 
    scale = scale;
}

glm::vec3 Scale::GetScale() const 
{
    return scale;
}

glm::mat4 Scale::GetTransformMatrix() const 
{
    return glm::scale(glm::mat4(1.0f), scale);
}
