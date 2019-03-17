#include <Muscle.h>

const int frequency = 50; // frequency of calls for data in miliseconds
const int valLen = 10;

int PinkieP = 23;
int RingP = 22;
int MiddleP = 25;
int PointerP = 24;
int ThumbP = 26;

int PinkieA = 30;
int RingA = 31;
int MiddleA = 32;
int PointerA = 33;
int ThumbA = 35;

int ProMusclePins[] = {PinkieP, RingP, MiddleP, PointerP, ThumbP};
Muscle ProMuscles[valLen/2];

int AntiMusclePins[] = {PinkieA, RingA, MiddleA, PointerA, ThumbA};
Muscle AntiMuscles[valLen/2];

void setup() {
  Serial.begin(9600);
  delay(200);
  
  pinSetUp();
  fullValveTest();

  for(int i = 0; i < valLen/2; i++){
    ProMuscles[i] = Muscle(ProMusclePins[i]);
    AntiMuscles[i] = Muscle(AntiMusclePins[i]);
  }//end of for loop

  clearBuffer();
  
  while(Serial.available() == 0){}//end wait for java input
  clearBuffer();
}//end of set up

void loop() {

Serial.write('#'); //requests data
while(Serial.available() == 0){}//end wait for java input
delay(50);

for (int i = 0; i<valLen/2; i++){
      int input = Serial.read();
      if(input == '1'){
        ProMuscles[i].Hold();
        AntiMuscles[i].Release();
      }//end of if contracting
      else{
        ProMuscles[i].Release();
        AntiMuscles[i].Hold();
      }//end of else opening
      Serial.read();
}//end of for each finger

delay(frequency); //waits set amount of time
}//end of main loop

void pinSetUp(){
  for(int i = 0; i<valLen/2; i++){
    pinMode(ProMusclePins[i], OUTPUT);
    digitalWrite(ProMusclePins[i], HIGH);
    pinMode(AntiMusclePins[i], OUTPUT);
    digitalWrite(AntiMusclePins[i], HIGH);
  } 
}//end of pinSetUp

void fullValveTest(){
  for (int i = 0; i < valLen/2; i++){
    blinkValve(ProMusclePins[i]);
    blinkValve(AntiMusclePins[i]);
  }//end of for loop
}//end of full valve test

void blinkValve(int pin){
  digitalWrite(pin, LOW);
    delay(100);
  digitalWrite(pin, HIGH);
}//end of blinkValve

void clearBuffer(){
  int n;
  
  while(Serial.available() > 0){
    n = Serial.read();
  }//end of while
}//end of clear buffer
