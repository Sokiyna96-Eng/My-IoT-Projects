/*;----------------------
; Title: LED Blinking Main
;----------------------
;Program Detail:
;----------------------
; Date: November 1, 2022 at 11:59pm pst
; Compiler: Arduino IDE 2.0.0
; Author: Sokiyna Naser
; Versions:
;         V1-
;----------------------
; File Dependencies:
; 
;----------------------
;  Arduino.h
;  ledblink.h
;----------------------
; Main Program
;----------------------
*/

#include <Arduino.h>
#include <ledblink.h>
#include<ledblink.cpp>



#define pin LED_BUILTIN

Blink led(pin);

void setup() { 
    Serial.begin(9600);
}

void loop() {
    led.on();
    delay(5000);
    led.off();
    delay(500);
  }