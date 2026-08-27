#ifndef __MY_TIME_H__
#define __MY_TIME_H__

#include "common.h"

class MyTime {
public:
    static MyTime& Get();
    void Update();
    float GetDeltaTime();

private:
    double m_time{};
    double m_prevTime{};
    double m_deltaTime;
};

#endif // __MY_TIME_H__