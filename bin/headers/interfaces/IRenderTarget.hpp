#pragma once

#include <string>

// I work with C#, so I am used to calling it interface :D
class IRenderTarget
{
public:
    // test only
    virtual void Render() = 0;
    
    virtual ~IRenderTarget() = default;

};