/*;----------------------
; Title: LED Blinking Class Header
;----------------------
;Program Detail:
;----------------------
; Purpose: Blink C++ class 
; Date: November 2, 2022 at 12:00pm pst
; Compiler: Arduino IDE 2.0.0
; Author: Sokiyna Naser
; Versions:
;         V1- Class and blink 
;----------------------
; File Dependencies:
; 
;----------------------
; Arduino.h
;----------------------
; Main Program
;----------------------
*/
#ifndef MY_LED_H
#define MY_LED_H 
#include <Arduino.h>
// define the Blink class
class Blink {
    
  
  private:
    int _pinNumber;
    int _BlinkRate;
    
  public:
    Blink(int pinNumber);
    void rate(int BlinkRate);
    void init();
    void on();
    void off();
   
};
#endif