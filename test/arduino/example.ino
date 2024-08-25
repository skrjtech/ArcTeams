// ===========================================================
// Lang: C/C++
// -----------------------------------------------------------
// File Name   : example.ino
// Description : 記述例サンプル
// -----------------------------------------------------------
// History :
// Rev.01 2024/08/25 J.Sakuragami First Release
// -----------------------------------------------------------
// Copyright (C) 2024 J.Sakuragami
// ===========================================================

#define PIN 8
#define DELAY 1000 // 1 Sec

void setup () {
    pinMode(PIN, OUTPUT);       
}

void loop () {
    digitalWrite(PIN, 1); // High
    delay(DELAY);
    digitalWrite(PIN, 0); // Low
    delay(DELAY);
}