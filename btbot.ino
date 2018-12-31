#include<SoftwareSerial.h>
SoftwareSerial abc(0,1);
char motion;
void setup() {
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
    
  Serial.begin(9600);
  abc.begin(9600);
  motion=0;
}
void loop() {
  if (abc.available() > 0)
  {
     motion = abc.read();
       Serial.println(motion);
       if (motion =='F')
       {
        // forward motion
        
        digitalWrite(3, LOW);
        digitalWrite(4, HIGH);
        digitalWrite(5, LOW);
        digitalWrite(6, HIGH);
        }
          if (motion =='L')
       {
        // LEFT motion
        digitalWrite(3, LOW);
        digitalWrite(4, LOW);
        digitalWrite(5, LOW);
        digitalWrite(6, HIGH);
        }
          if (motion =='R')
       {
        // RIGHT motion
        digitalWrite(3, LOW);
        digitalWrite(4, HIGH);
        digitalWrite(5, LOW);
        digitalWrite(6, LOW );
        }
          if (motion =='B')
       {
        // BACK motion
        digitalWrite(3, HIGH);
        digitalWrite(4, LOW);
        digitalWrite(5, HIGH);
        digitalWrite(6, LOW);
        }
          if (motion =='S')
       {
        // TO STOP
        digitalWrite(3, LOW);
        digitalWrite(4, LOW);
        digitalWrite(5, LOW);
        digitalWrite(6, LOW);
        }
          if (motion =='C')
       {
        // SPIN CLOCK WISE motion
        digitalWrite(3, HIGH);
        digitalWrite(4, LOW);
        digitalWrite(5, LOW);
        digitalWrite(6, HIGH);
        }
          if (motion =='A')
       {
        // SPIN ANTI CLOCK WISE motion
        digitalWrite(3, LOW);
        digitalWrite(4, HIGH);
        digitalWrite(5, HIGH);
        digitalWrite(6, LOW);
        }
  }}
