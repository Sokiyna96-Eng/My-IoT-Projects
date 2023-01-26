/*;----------------------
; Title: LED Blinking Class Functions
;----------------------
;Program Detail:
;----------------------
; Purpose: Class function declarations for the Blink class

; Date: November 2, 2022 at 12:00pm pst
; Compiler: Arduino IDE 2.0.0
; Author: Sokiyna Naser
; Versions:
;         V1- 
;----------------------
; File Dependencies:
; 
;----------------------
; ledblink.h
; Arduino.h
;
;----------------------
; Main Program
;----------------------
*/

#include "ledblink.h"
#include <Arduino.h>

Blink::Blink(int pinNumber)
{
    // Use 'this->' to make the difference between the
    // 'pin' attribute of the class and the
    // local variable 'pin' created from the parameter.

    this->_pinNumber = pinNumber;
    init();
}

void Blink::init()
{
    pinMode(_pinNumber, OUTPUT);
    // Always try to avoid duplicate code.
    // Instead of writing digitalWrite(pinNumber, LOW) here,
    // call the function off() which already does that
    off();
}
void Blink::on()
{
    digitalWrite(_pinNumber, HIGH);
}
void Blink::off()
{
    digitalWrite(_pinNumber, LOW);
}