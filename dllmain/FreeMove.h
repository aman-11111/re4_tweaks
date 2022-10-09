#pragma once
#include <stdint.h>
bool HandleStrafing(bool strafing_only = false);
void HandleAimAndMove();
void HandlePadRightStickTurn(int8_t AnalogRX);

extern int8_t* AnalogLX_0;
extern int8_t* AnalogLY_4;
extern int8_t* AnalogRX_8;
extern int8_t* AnalogRY_9;