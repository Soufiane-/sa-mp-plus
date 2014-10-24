#pragma once

#include <SAMP+/Definitions.h>
#include <SAMP+/client/Client.h>

class CLocalPlayer
{
public:

	#define PRESSED(vkey) \
		(GetAsyncKeyState(vkey) & 0x8000) != 0

	#define KEY_STATE_PRESSED              (0x01) // The key detected is being pressed
	#define KEY_STATE_NOT_PRESSED          (0x02) // The key detected is not being pressed
	#define KEY_STATE_NOT_PLAYING          (0x03) // The player you want to detect the key on isn't playing GTA SA

	enum ePlayerAction : unsigned char
	{
		ALL,
		SPRINT,
		ENTER_CAR,
		CROUCH,
		FIRE_WEAPON,
		UNKNOWN,
		SWITCH_WEAPON,
		JUMP,
		COUNT
	};

	static void SetActionEnabled(unsigned char action, bool bEnabled);
	static void OnDriveByShot();
	static void OnStuntBonus(sStuntDetails* pStuntDetails);
	static void SetClipAmmo(BYTE bSlot, int bAmmo);
	static void SetNoReload(bool toggle);
	static void ToggleInfiniteRun(bool toggle);
	static void GetVKeyState(int vkey);
	static void GetMousePos(int &x, int &y);
	static void OnVKeyStateChange(int newkeys, int oldkeys);
	static void OnMousePosChange(POINT newcurs, POINT oldcurs);

	// Soufiane
	static int m_oldkeys;
	static int m_newkeys;
	static POINT m_oldcurs;
	static POINT m_newcurs;
	static RECT m_screen;

private:
	static DWORD m_actionMemory[ePlayerAction::COUNT-1];

};