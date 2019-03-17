/*
  Muscle.cpp - Library for controlling hydraulic muscles.
  Created by Shae McFadden, January 6th, 2019.
  Released into the public domain.
*/

#include "Arduino.h"
#include "Muscle.h"

Muscle::Muscle(){

}//end of default constructor

Muscle::Muscle(int pin){
    musclePin = pin;
    interval = 0;
    delayInterval = 0;

    muscleState = HIGH;
    previousMillis = 0;
    delayed = false;
}//end of constructor

void Muscle::Update() {
      currentMillis = millis();

      if((delayed) && (currentMillis - previousMillis >= delayInterval)){
	previousMillis = currentMillis;
        delayed = false;
        Hold();
      }//end of delay check if

      else if((!delayed) && (currentMillis - previousMillis >= interval)){
        previousMillis = currentMillis;
        if(holding){
	  Hold();
	}//end of if holding
	else{
	Release();
	}//end of else
      }//end of contraction state if
}//end of Update

void Muscle::Contract(int t) {
      interval = t;
      delayInterval = 0;
      delayed = false;
      holding = false;
      previousMillis = millis();
      Hold();

      Update();
}//end of contract

void Muscle::Contract(int dt, int t) {
     interval = t;
     delayInterval = dt;
     delayed = true;
     holding = false;   
     previousMillis = millis();

     Update();
}//end of delayed contract delayed

void Muscle::ContractAndHold(int t){
     interval = t;
     delayInterval = 0;
     delayed = false;
     holding = true;
     previousMillis = millis();
     Hold();

     Update();
}//end of contract and hold

void Muscle::ContractAndHold(int dt, int t){
     interval = t;
     delayInterval = dt;
     delayed = true;
     holding = true;
     previousMillis = millis();

     Update();
}//end of contract and hold


void Muscle::Hold(){
     muscleState = LOW;
     digitalWrite(musclePin, muscleState);
}//end of hold

void Muscle::Release(){
     muscleState = HIGH;
     digitalWrite(musclePin, muscleState);
}//end of release