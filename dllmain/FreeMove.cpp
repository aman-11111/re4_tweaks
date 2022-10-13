#include "dllmain.h"
#include "Patches.h"
#include "Settings.h"
#include "input.hpp"
#include "FreeMove.h"
#define DEAD_ZONE_X   1
void HandlePadRightStickTurn(int8_t AnalogRX)
{
	pInput->RightStickTurning = 0;
	if (AnalogRX < -DEAD_ZONE_X || AnalogRX > DEAD_ZONE_X)
	{
		float deltaTime = GlobalPtr()->deltaTime_70;
		float SpeedMulti = 900.0f;

		// not sure what to use here
		// "Classic" aiming mode (0x00) needs lower sensitivity here.
		//if (GetMouseAimingMode() == MouseAimingModes::Classic)
			//SpeedMulti = 1300.0f;

		PlayerPtr()->ang_A0.y += (-AnalogRX / SpeedMulti) * pConfig->fTurnTypeBSensitivity * deltaTime ;

		// use this to trigger turning animation
		if (*AnalogRX_8 > DEAD_ZONE_X)
			pInput->RightStickTurning = 0x4;
		if (*AnalogRX_8 < -DEAD_ZONE_X)
			pInput->RightStickTurning = 0x8;

		// save player angle for pl_R1_TurnLeft/Right to pickup, this allow strafing pick up turning at the same time
		pInput->cached_player_ang_y = PlayerPtr()->ang_A0.y;
	}
}

bool HandleStrafing(bool not_fwd_back)
{
	bool bGamePad = isController();
	float deltaTime = GlobalPtr()->deltaTime_70;
	float speed = 40.0f;
	if (not_fwd_back)
		speed = 60.0f;
	bool bKeyDown = false;
	if (game_KeyOnCheck_0(KEY_BTN::KEY_RIGHT))
	{
		float angleRight = PlayerPtr()->ang_A0.y;
		Vec d;
		float dist = 10.0f;
		d.x = -cosf(angleRight) * speed * deltaTime;
		d.z = sinf(angleRight) * speed * deltaTime; 

		PlayerPtr()->pos_94.x += d.x;
		PlayerPtr()->pos_94.z += d.z;
		bKeyDown = true;
	}
	if (game_KeyOnCheck_0(KEY_BTN::KEY_LEFT))
	{
		float angleRight = PlayerPtr()->ang_A0.y;
		float angleLeft = angleRight + M_PI;  //left is 180 degree from right
		Vec d;
		float dist = 10.0f;
		d.x = -cosf(angleLeft) * speed * deltaTime;
		d.z = sinf(angleLeft) * speed * deltaTime;

		PlayerPtr()->pos_94.x += d.x;
		PlayerPtr()->pos_94.z += d.z;
		bKeyDown = true;
	}
	return bKeyDown;
}

void HandleAimAndMove()
{
	float maxspeed = 60.0f;
	float max_strafe_speed = maxspeed * 0.8f;
	float acceleration = 6.0f;
	float deceleration = 6.0f;
	float minspeed = 10.0f;
	static float speed = minspeed;
	static float strafe_speed = minspeed;
	bool keyDown = false;
	static float bobbleTimer = 0.0;
	float deltaTime = GlobalPtr()->deltaTime_70;
	bool bGamePad = false;

	bGamePad = isController();

	// For some reason leftStick changes AnalogRX,Y, rightStick changes AnalogLX,Y 
	// Both Stick trigger KEY_FORWARD,BACK,LEFT, RIGHT. cannot tell which stick was pushed.
	
	// leftSTick and AWSD keys control player movement
	// only read stick position if gamepad is used. otherwise mouse up/down motion also change the stick poistion, don't know why  
	if  ((bGamePad && *AnalogRY_9 > DEAD_ZONE_X) || pInput->is_key_down(0x57))  // W
	{
		if (keyDown)  speed = max(speed, max_strafe_speed);  // if side stepping slow down forward motion
		Vec d;
		float angleRight = PlayerPtr()->ang_A0.y;
		float angleFwd = angleRight + (M_PI / 2.0f);  //forward is +90 degree from right
		d.x = -cosf(angleFwd) * speed * deltaTime;
		d.z = sinf(angleFwd) * speed * deltaTime;
		
		PlayerPtr()->pos_94.x += d.x;
		PlayerPtr()->pos_94.z += d.z;
		keyDown = true;
	}

	if ((bGamePad && *AnalogRY_9 < -DEAD_ZONE_X) || pInput->is_key_down(0x53)) // S
	{
		float angleRight = PlayerPtr()->ang_A0.y;
		float angleBack = angleRight - (M_PI / 2.0f);  //back is -90 degree from right
		Vec d;
		d.x = -cosf(angleBack) * speed * deltaTime;
		d.z = sinf(angleBack) * speed * deltaTime;
		PlayerPtr()->pos_94.x += d.x;
		PlayerPtr()->pos_94.z += d.z;
		keyDown = true;
	}

	if ((bGamePad && *AnalogRX_8 < -DEAD_ZONE_X) || pInput->is_key_down(0x41))
	{
		Vec d;
		strafe_speed = speed;
		if (keyDown && (speed > max_strafe_speed))
			strafe_speed = max_strafe_speed;
		float angleRight = PlayerPtr()->ang_A0.y;
		float angleLeft = angleRight + M_PI;  //left is +180 degree from right
		float dist = 10.0f;
		d.x = -cosf(angleLeft) * strafe_speed * deltaTime;
		d.z = sinf(angleLeft) * strafe_speed * deltaTime;
		//d.y = 0;
		PlayerPtr()->pos_94.x += d.x;
		PlayerPtr()->pos_94.z += d.z;
		keyDown = true;
	}

	if ((bGamePad && *AnalogRX_8 > DEAD_ZONE_X)|| pInput->is_key_down(0x44))  // D
	{
		strafe_speed = speed;
		if (keyDown && (speed > max_strafe_speed))
			strafe_speed = max_strafe_speed;

		float angleRight = PlayerPtr()->ang_A0.y;
		Vec d;
		d.x = -cosf(angleRight) * strafe_speed * deltaTime;
		d.z = sinf(angleRight) * strafe_speed * deltaTime;

		PlayerPtr()->pos_94.x += d.x;
		PlayerPtr()->pos_94.z += d.z;
		keyDown = true;
	}

	if (keyDown)
		speed += acceleration;

	if (speed > minspeed) // simulate walking bobble
	{
		float bobble_scale_x = 1.5f;
		float bobble_scale_y = 1.5f;
		bobbleTimer += 0.5 * deltaTime;
		if (bobbleTimer > 2 * M_PI) bobbleTimer = 0;
		//float bobble_y = sin(bobbleTimer) * ((speed - minspeed) / minspeed) * bobble_scale_y;
		float bobble_y = sin(bobbleTimer + 2.0f) * ((speed - minspeed) / minspeed) * bobble_scale_y;
		PlayerPtr()->pos_94.y += bobble_y;
	}

	if (!keyDown)
	{
		if (speed > minspeed)
			speed -= deceleration;
	}
	else
	{
		if (speed > maxspeed) speed = maxspeed;
	}
}