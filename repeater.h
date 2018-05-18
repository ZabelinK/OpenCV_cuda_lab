#ifndef REPEATER_H
#define REPEATER_H

#include <cstdlib>

//Repeat action every N step

template <typename RunableObject>
class Repeater
{
public:
    Repeater(RunableObject& runableObject, size_t countEmptyStepBetweenRun);
    Repeater(Repeater&&) = default;
    Repeater& operator=(Repeater&&) = default;

    void takeStep();

    Repeater(const Repeater&) = delete;
    Repeater& operator=(const Repeater&) = delete;
private:
    RunableObject& runableObject_;
    const size_t times_;
    size_t nowTimes_;
};

template <typename RunableObject>
Repeater<RunableObject>::Repeater(RunableObject &object, size_t countEmptyStepBetweenRun):
    runableObject_(object),
    times_(countEmptyStepBetweenRun),
    nowTimes_(0)
{}

template <typename RunableObject>
void Repeater<RunableObject>::takeStep()
{
    if(nowTimes_ == times_)
    {
        runableObject_();
        nowTimes_ = 0;
    }
    else
    {
        ++nowTimes_;
    }
}


#endif // REPEATER_H
