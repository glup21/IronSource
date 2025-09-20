#pragma once

#include "headers/interfaces/IRenderTarget.hpp"
#include "headers/core/AppContext.hpp"
#include <vector>
#include <memory>

using std::vector;
class Initializer
{
public:
    vector<std::shared_ptr<IRenderTarget>> InitApplication();

    Initializer(AppContext* appContext);
    ~Initializer() = default;

private:
    AppContext* appContext;

    void InitWindow();
    vector<std::shared_ptr<IRenderTarget>> InitGameObjects();
};