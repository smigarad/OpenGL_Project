#include "subject.h"

Subject::Subject()
{
    this->observers = std::vector<Observer *>();
}

void Subject::addObserver(Observer *observer)
{
    this->observers.push_back(observer);
}

void Subject::removeObserver(Observer *observer)
{
    this->observers.erase(std::remove(this->observers.begin(), this->observers.end(), observer), this->observers.end());
}

std::vector<Observer *> Subject::getObservers()
{
    return this->observers;
}

void Subject::notifyObservers()
{
    for (auto observer : this->observers)
    {
        observer->notify(this);
    }
}
Subject::~Subject()
{
}
