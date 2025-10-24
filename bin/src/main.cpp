#include "headers/core/Application.hpp"
#include "iostream"
#include <spdlog/spdlog.h>

int main()
{
    spdlog::set_level(spdlog::level::debug); 
    try
    {
        Application app;
        app.Run();
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        return -1;
    }

    return 0;
}

