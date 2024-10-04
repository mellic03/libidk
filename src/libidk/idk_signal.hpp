#pragma once


namespace idk
{
    class PID;
    class Kalman;
}


class idk::PID
{
private:
    float yt = 0.0;
    float P  = 0.0;
    float I  = 0.0;
    float D  = 0.0;

    float integral = 0.0;
    float error    = 0.0;

    float Kp, Kd, Ki;

public:
    PID( float _Kp, float _Kd, float _Ki )
    : Kp(_Kp), Kd(_Kd), Ki(_Ki)
    {
        
    }

    float iterate( float error, float dt )
    {
        float dError = error - error;

        integral += error * dt;
        error = error;

        P = Kp * error;
        I = Ki * integral;
        D = 0.99*D + 0.01*Kd * (dError / dt);

        if (isnanl(D))
        {
            D = 0.0;
        }

        yt = P + D + I;

        return yt;
    }
};



class idk::Kalman
{
private:

public:

};


