#include <Muscle.h>

const int frequency = 100; // frequency of calls for data in miliseconds
const int valLen = 10;

int PinkieP = 27;
int RingP = 26;
int MiddleP = 29;
int PointerP = 28;
int ThumbP = 25;

int PinkieA = 34;
int RingA = 35;
int MiddleA = 36;
int PointerA = 37;
int ThumbA = 32;

int ProMusclePins[] = {PinkieP, RingP, MiddleP, PointerP, ThumbP};
Muscle ProMuscles[valLen/2];

int AntiMusclePins[] = {PinkieA, RingA, MiddleA, PointerA, ThumbA};
Muscle AntiMuscles[valLen/2];

void setup() {
  Serial.begin(9600);
  delay(200);
  
  pinSetUp();
  //fullValveTest();

  for(int i = 0; i < valLen/2; i++){
    ProMuscles[i] = Muscle(ProMusclePins[i]);
    AntiMuscles[i] = Muscle(AntiMusclePins[i]);
  }//end of for loop

  clearBuffer();
  
  //while(Serial.available() == 0){}//end wait for java input
  //clearBuffer();
}//end of set up

void loop() {

Serial.write('#'); //requests data
while(Serial.available() == 0){}//end wait for java input
delay(50);


for (int i = 0; i<valLen/2; i++){
      int input = Serial.read();
      if(input == '1'){
        AntiMuscles[i].Release();
        ProMuscles[i].Hold();
      }//end of if contracting
      else if(input == '0'){
        ProMuscles[i].Release();
        AntiMuscles[i].Hold();
      }//end of else if opening
      else{
        for(int j = 0; i < 5; i++){
          ProMuscles[i].Release();
          AntiMuscles[i].Release();
        }//end of for every finger
      }//end of else ending
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
    delay(1000);
  digitalWrite(pin, HIGH);
}//end of blinkValve

void clearBuffer(){
  int n;
  
  while(Serial.available() > 0){
    n = Serial.read();
  }//end of while
}//end of clear buffer
