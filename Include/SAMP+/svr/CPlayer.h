#pragma once

#include <SAMP+/svr/CClientSocketInfo.h>
#include <map>

class CPlayer
{
public:
	CPlayer(CClientSocketInfo* socketInfo);
	~CPlayer();

	CClientSocketInfo* GetConnectionInfo();
	void SetInPauseMenu(bool bInPauseMenu);
	bool IsInPauseMenu();
	void SetCurrentMenuId(unsigned char ucMenuId);
	unsigned char GetCurrentMenuId();
	int GetResolutionX();
	int GetResolutionY();
	void SetResolution(int X, int Y);
	float GetAircraftHeight();
	float GetJetpackHeight();
	int GetNewkeys();
	void SetKeys(int newkeys);
	void GetMousePos(int &x, int &y);
	void SetMousePos(POINT cursor);
	void SetAircraftHeight(float height);
	void SetJetpackHeight(float height);



private:
	CClientSocketInfo* m_pSockInfo;
	bool m_bInPauseMenu;
	unsigned char m_ucMenuId;
	int m_iResolutionX;
	int m_iResolutionY;
	float m_fAircraftHeight;
	float m_fJetpackHeight;
	int m_newkeys;
	int m_oldkeys;
	POINT m_oldcurs;
	POINT m_newcurs;
};