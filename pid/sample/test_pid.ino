#include <my_pid.h>

const byte encoder0pinA = 2; 
const byte encoder0pinB = 3;
byte encoder0PinALast;
int motor_A = 5; 
int motor_B = 4; 

float duration, abs_duration, accumulated_circles; 
boolean direction_; 
boolean result; 
float val_output;
float output_direction;
float target; 
float kp = 3.2, ki = 3, kd = 1.0;
PID motor_pid_1(&accumulated_circles, &val_output, &output_direction, &target, kp, ki, kd, USER_CUSTOMIZED_MOVE_STYLE, 0);


void setup() {
  Serial.begin(9600);
  pinMode(motor_A, OUTPUT); 
  pinMode(motor_B, OUTPUT); 
  target = 4500; 
  accumulated_circles = 0; 
  duration = 0;
  direction_ = true; 
  pinMode(encoder0pinB,INPUT);  
  attachInterrupt(0, wheelSpeed, CHANGE);
}

void wheelSpeed()
{
  int Lstate = digitalRead(encoder0pinA);
  if((encoder0PinALast == LOW) && Lstate==HIGH)
  {
    int val = digitalRead(encoder0pinB);
    if(val == LOW && direction_)
    {
      direction_ = false; //Reverse
    }
    else if(val == HIGH && !direction_)
    {
      direction_ = true;  //Forward
    }
  }
  encoder0PinALast = Lstate;
 
  if(!direction_) {
    duration++;
    accumulated_circles++; 
  } else  {
    duration--;
    accumulated_circles--; 
  }
}



// the loop function runs over and over again forever
void loop() {
  control_motor(); 
  abs_duration=abs(duration);
  result = motor_pid_1.Compute();
  if (result) {
    Serial.print("Pulse: ");
    Serial.print(duration); 
    Serial.print(", accumulated_circles: ");
    Serial.println(accumulated_circles);
    duration = 0; //Count clear, wait for the next count
  }
}


void control_motor() 
{
  if (output_direction == MOTOR_REVERSE) {
    digitalWrite(motor_A,LOW);
    analogWrite(motor_B, val_output);
  } else {
    digitalWrite(motor_B,LOW);
    analogWrite(motor_A, val_output);
  }
}

