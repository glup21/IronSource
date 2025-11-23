#include "headers/core/Application.hpp"
#include "iostream"
#include <spdlog/spdlog.h>

int main()
{
    spdlog::set_level(spdlog::level::debug); 

    Application app;
    app.Run();

    return 0;
}

