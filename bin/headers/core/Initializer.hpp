#pragma once

#include "headers/interfaces/IRenderTarget.hpp"
#include "headers/core/AppContext.hpp"
#include <vector>
#include <memory>

using std::vector;
class Initializer
{
public:
    void InitApplication();

    Initializer(AppContext* appContext);
    ~Initializer() = default;

private:
    AppContext* appContext;

    void InitWindow();
    void InitServices();
};