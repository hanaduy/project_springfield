#ifndef MY_PID_h
#define MY_PID_h
#define LIBRARY_VERSION	1.2.1
#define USER_CUSTOMIZED_MOVE_STYLE 255
#define MOTOR_REVERSE 0
#define MOTOR_FORWARD 1

class PID 
{
public:
    PID(float*, float*, float*, float*, float, float, float, int, unsigned long);
    void SetOutputLimits(float, float); 
    void ResetOutputSum(); 
    bool Compute(); 
    void ChangeMoveStyle(int, float, float, float);
    void SetSampleTime(int);



private:
    int move_style; 
    float kp, ki, kd; 
    float *input_ptr, *output_PWM_ptr, *output_direction_ptr, *target_ptr; 
    float out_min, out_max; 
    unsigned long last_time;
    unsigned long sample_time;
    float output_sum, last_input;
    float kp_style[8];
    float ki_style[8];
    float kd_style[8];
};
#endif 