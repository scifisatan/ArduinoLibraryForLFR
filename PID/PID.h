#ifndef PID_h
#define PID_h

#include <Arduino.h>

class PID
{
private:
    int _error;
    int _kp;
    int _ki;
    int _kd;
    int _previousError;
    int _P;
    int _I;
    int _D;
    int _PIDValue;

public:
    PID(int kp, int ki, int kd);
    int calcPID(int error);
};

#endif