#include "headers/transform/DummyTransform.hpp"

DummyTransform::DummyTransform()
    : Translation(glm::vec3(0.0f))
{

}


glm::mat4 DummyTransform::GetTransformMatrix()
{
    auto res = glm::mat4(1.0f);
    res[3][3] = 20.0f;

    return res;
}