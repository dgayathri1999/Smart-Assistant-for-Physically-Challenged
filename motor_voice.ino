String voice;
int m1 = 8; //Connect LED 1 To Pin 
int m2 = 9; //Connect LED 2 To Pin #3
int m3 = 10; //Connect LED 3 To Pin #4
int m4 = 11; //Connect LED 4 To Pin #5
//--------------------------Call A Function-------------------------------// 
void forward(){
     digitalWrite(m1, HIGH);
     digitalWrite(m2, LOW);
     digitalWrite(m3, HIGH);
     digitalWrite(m4, LOW);
}
void stopit(){
     digitalWrite(m1, LOW);
     digitalWrite(m2, LOW);
     digitalWrite(m3, LOW);
     digitalWrite(m4, LOW);
}
void left(){
     digitalWrite(m1, LOW);
     digitalWrite(m2, LOW);
     digitalWrite(m3, HIGH);
     digitalWrite(m4, LOW);
}
void right(){
     digitalWrite(m1, HIGH);
     digitalWrite(m2, LOW);
     digitalWrite(m3, LOW);
     digitalWrite(m4, LOW);
}
void backward(){
     digitalWrite(m1, LOW);
     digitalWrite(m2, HIGH);
     digitalWrite(m3, LOW);
     digitalWrite(m4, HIGH);
}
//-----------------------------------------------------------------------// 
void setup() {
  Serial.begin(9600);
  pinMode(m1, OUTPUT);
  pinMode(m2, OUTPUT);
  pinMode(m3, OUTPUT);
  pinMode(m4, OUTPUT);
}
//-----------------------------------------------------------------------// 
void loop() {
  while (Serial.available()){  //Check if there is an available byte to read
  delay(10); //Delay added to make thing stable
  char c = Serial.read(); //Conduct a serial read
  if (c == '#') {break;} //Exit the loop when the # is detected after the word
  voice += c; //Shorthand for voice = voice + c
  } 
  if (voice.length() > 0) {
    Serial.println(voice);
       if(voice == "forward") {forward();}  //Turn Off All Pins (Call Function)
       else if(voice == "backward"){backward();} //Turn On  All Pins (Call Function)
       else if(voice == "right"){right();}
       else if(voice == "left"){left();}
       else if(voice == "stop it"){stopit();}
voice="";}} //Reset the variable after initiating
