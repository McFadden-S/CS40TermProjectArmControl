/*
  Muscle.h - Library for Hydraulic Muscle Control
  Created by Shae McFadden, January 6th, 2019.
  Released into the public domain.
*/

#ifndef Muscle_h
#define Muscle_h

#include "Arduino.h"

class Muscle{
  public:
    Muscle();
    Muscle(int pin);
    void Update();
    void Contract(int t);
    void Contract(int dt, int t);
    void ContractAndHold(int t);
    void ContractAndHold(int dt, int t);
    void Hold();
    void Release();
  private:
    int musclePin;
    int muscleState;
    long interval;
    long delayInterval;
    unsigned long previousMillis;
    unsigned long currentMillis;
    boolean delayed;
    boolean holding;
};

#endif