#include "headers/transform/Translation.hpp"
#include <glm/gtc/matrix_transform.hpp>

Translation::Translation(glm::vec3 posistion) : position(posistion)
{

}

void Translation::SetPosition(glm::vec3 posistion)
{
    this->position = posistion;
}

glm::vec3 Translation::GetPosition() const
{
    return position;
}

glm::mat4 Translation::GetTransformMatrix() 
{
    return glm::translate(glm::mat4(1.0f), position);
}
