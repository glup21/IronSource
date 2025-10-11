#pragma once
#include "headers/interfaces/Subject.hpp"

class Subject;
class Observer 
{
public:
    virtual void Update(Subject* caller) = 0;
    virtual ~Observer() = default;
};