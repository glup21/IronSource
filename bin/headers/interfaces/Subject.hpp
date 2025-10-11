#pragma once
#include <vector>

class Observer;
class Subject
{
protected:
    std::vector<Observer*> observers;

public:
    virtual void NotifyAll() = 0;
    void Attach(Observer* observer)
    {
        this->observers.push_back(observer);
    }

};