// ===========================================================
// Lang: C
// -----------------------------------------------------------
// File Name   : led.c
// Description : LED点滅用
// -----------------------------------------------------------
// History :
// Rev.01 2024/08/25 J.Sakuragami First Release
// -----------------------------------------------------------
// Copyright (C) 2024 J.Sakuragami
// ===========================================================

#include <stdio.h>
#include <pigpio.h>

#define PIN   21
#define SLEEP_SEC 1000000

// 初期設定関数
void Initialize ( void );
// 終了処理関数
void Terminate ( void );

int main( int argc, char **argv) {
    Initialize();
    while(1) {
        gpioWrite(PIN, 1); // High
        gpioDelay(SLEEP_SEC); // 1 sec delay
        gpioWrite(PIN, 0); // High
        gpioDelay(SLEEP_SEC); // 1 sec delay

    }
    Terminate();
    return 0;
}

void Initialize ( void ) {
    gpioInitialise(); // GPIOの初期化
    gpioSetMode(PIN, PI_OUTPUT); // GPIO 入出力設定
}
void Terminate ( void ) { gpioTerminate(); }