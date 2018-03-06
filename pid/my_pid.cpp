#if ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif

#include <my_pid.h>


/*
    Right now the pid directly controls the distance. 
    Error (i.e. distance) = current position - target position
*/

PID::PID(float* input_ptr_, float* output_PWM_ptr_ , 
    float* output_direction_ptr_, float* target_ptr_, 
    float kp_, float ki_, float kd_, 
    int move_style_, unsigned long sample_time_) 
{
    input_ptr = input_ptr_;
    output_PWM_ptr = output_PWM_ptr_;
    output_direction_ptr = output_direction_ptr_; 
    target_ptr = target_ptr_;
    move_style = move_style_;
    PID::ChangeMoveStyle(move_style, kp_, ki_, kd_);
    PID::SetOutputLimits(0, 255); 
    PID::ResetOutputSum(); 
    if (sample_time_ == 0 ) PID::SetSampleTime(100); //value to be changed 
    else PID::SetSampleTime(sample_time_);
    last_time = millis() - sample_time; 
}


void PID::SetOutputLimits(float min_, float max_)
{
    out_min = min_; // min is dummy here
    out_max = max_; 
}


void PID::ResetOutputSum() // called every time target changes
{
    output_sum = 0;
}


bool PID::Compute()
{
    unsigned long now = millis(); //does the time have the risk of overflowing?
    unsigned long time_change = (now - last_time); 
    if (time_change > sample_time) return false;

    float input_val = *input_ptr;
    float error = *target_ptr - input_val; 
    float dInput = (input_val - last_input); 
    /* start of standard PID control */
    //integral_term += error;
    output_sum += ki * error; 
    if (output_sum > out_max) output_sum = out_max; 
    if (output_sum < out_min) output_sum = out_min; 

    Serial.print(output_sum); 
    Serial.print(", "); 
    
    float output = output_sum + kp * error - kd * dInput; 
    Serial.print(output); 
    if (output < 0) { 
        * output_direction_ptr = MOTOR_REVERSE; 
    } else {
        * output_direction_ptr = MOTOR_FORWARD; 
    }
    output = abs(output); 
    if (output > out_max) output = out_max; 
    * output_PWM_ptr = output; 
    /* end of standard PID control */

    /* 
        TODO: 
        other control/PID mechanism goes here. 
    */

    /* maybe you can have some different mechanism */
    last_input = input_val; 
    last_time = now;
    return true; 
}


void PID::ChangeMoveStyle(int move_style_, float kp_, float ki_, float kd_)
{
    if (move_style == USER_CUSTOMIZED_MOVE_STYLE) { 
        kp = kp_; 
        ki = ki_; 
        kd = kd_; 
    } else {
        kp = kp_style[move_style_]; 
        ki = ki_style[move_style_];
        kd = kd_style[move_style_]; 
    }
}


void PID::SetSampleTime(int sample_time_)
{
    sample_time = sample_time_;
}