void setup()
{
 //set pin 8 and pin 9 as output channel
 pinMode(8,OUTPUT); //pulse
 pinMode(9,OUTPUT); //direction
 //set begining direction
}
int t=1;
int i;
void loop()
{
 if(t) //repeat only if t!=0
 {
   for(i=1;i<=50;i++) //rotate for 90 degrees (50 intervals)
   {
     // giving one pulse for every 20 microseconds
     analogWrite(9,0);
     digitalWrite(10,255);
     delay(10);
     analogWrite(9,0);
     analogWrite(10,0);
     delay(10);
   };
  
   analogWrite(9,0);
   delay(1000);
   analogWrite(10,0);
   delay(1000);
  
   for(i=1;i<=50;i++) //rotate for 90 degrees (50 intervals)
   {
     // giving one pulse for every 20 microseconds
     analogWrite(9,255);
     analogWrite(10,0);
     delay(10);
     analogWrite(9,0);
     analogWrite(10,0);
     delay(10);
   }

   analogWrite(9,0);
   delay(1000);
   analogWrite(10,0);
   delay(1000);
 }
}
