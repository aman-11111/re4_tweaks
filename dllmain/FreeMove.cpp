#include "dllmain.h"
#include "Patches.h"
#include "Settings.h"
#include "input.hpp"

bool HandleStrafing(bool not_fwd_back = false)
{
	float speed = 20.0f;
	if (not_fwd_back)
		speed = 25.0f;

	bool bKeyDown = false;
	if (pInput->is_key_down(0x44))  // D
	{
		float angleRight = PlayerPtr()->ang_A0.y;
		Vec d;
		float dist = 10.0f;
		d.x = -cosf(angleRight) * speed;
		d.z = sinf(angleRight) * speed;

		PlayerPtr()->pos_94.x += d.x;
		PlayerPtr()->pos_94.z += d.z;
		bKeyDown = true;
	}
	else
		if (pInput->is_key_down(0x41)) // A
		{
			float angleRight = PlayerPtr()->ang_A0.y;
			float angleLeft = angleRight + M_PI;  //left is 180 degree from right
			Vec d;
			float dist = 10.0f;
			d.x = -cosf(angleLeft) * speed;
			d.z = sinf(angleLeft) * speed;

			PlayerPtr()->pos_94.x += d.x;
			PlayerPtr()->pos_94.z += d.z;
			bKeyDown = true;
		}
	return bKeyDown;
}

void HandleAimAndMove()
{
	float maxspeed = 30.0f;
	float max_strafe_speed = maxspeed * 0.8f;
	float acceleration = 3.0f;
	float deceleration = 3.0f;
	float minspeed = 5.0f;
	static float speed = minspeed;
	static float strafe_speed = minspeed;
	bool keyDown = false;
	static float bobbleTimer = 0.0;



	if (pInput->is_key_down(0x57))  // W
	{
		if (keyDown)  speed = max(speed, max_strafe_speed);  // if side stepping slow down forward motion
		Vec d;
		float angleRight = PlayerPtr()->ang_A0.y;
		float angleFwd = angleRight + (M_PI / 2.0f);  //forward is +90 degree from right
		d.x = -cosf(angleFwd) * speed;
		d.z = sinf(angleFwd) * speed;
		
		PlayerPtr()->pos_94.x += d.x;
		PlayerPtr()->pos_94.z += d.z;
		keyDown = true;
	}
	else
		if (pInput->is_key_down(0x53)) // S
		{
			float angleRight = PlayerPtr()->ang_A0.y;
			float angleBack = angleRight - (M_PI / 2.0f);  //back is -90 degree from right
			Vec d;
			d.x = -cosf(angleBack) * speed;
			d.z = sinf(angleBack) * speed;
			PlayerPtr()->pos_94.x += d.x;
			PlayerPtr()->pos_94.z += d.z;
			keyDown = true;
		}

	if (pInput->is_key_down(0x41))  // key A
	{
		Vec d;
		strafe_speed = speed;
		if (keyDown && (speed > max_strafe_speed))
			strafe_speed = max_strafe_speed;
		float angleRight = PlayerPtr()->ang_A0.y;
		float angleLeft = angleRight + M_PI;  //left is +180 degree from right
		float dist = 10.0f;
		d.x = -cosf(angleLeft) * strafe_speed;
		d.z = sinf(angleLeft) * strafe_speed;
		//d.y = 0;
		PlayerPtr()->pos_94.x += d.x;
		PlayerPtr()->pos_94.z += d.z;
		keyDown = true;
	}
	else
		if (pInput->is_key_down(0x44))  // D
		{
			strafe_speed = speed;
			if (keyDown && (speed > max_strafe_speed))
				strafe_speed = max_strafe_speed;

			float angleRight = PlayerPtr()->ang_A0.y;
			Vec d;
			d.x = -cosf(angleRight) * strafe_speed;
			d.z = sinf(angleRight) * strafe_speed;

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
		bobbleTimer += 0.25;
		if (bobbleTimer > 2 * M_PI) bobbleTimer = 0;
		float bobble_y = sin(bobbleTimer) * ((speed - minspeed) / minspeed) * bobble_scale_y;
		float bobble_x = sin(bobbleTimer + 2.0f) * ((speed - minspeed) / minspeed) * bobble_scale_x;
		PlayerPtr()->pos_94.y += bobble_x;
		//*fCameraPosY += bobble_x;
		//PlayerPtr()->pos_94.x += bobble_x;
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