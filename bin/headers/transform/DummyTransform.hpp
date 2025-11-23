#pragma once
#include "headers/transform/Translation.hpp"
#include "headers/pch.hpp"


class DummyTransform : public Translation
{
private:

public:
    DummyTransform();

    glm::mat4 GetTransformMatrix() override;
};
