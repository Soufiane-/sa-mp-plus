#include <SAMP+/svr/CPlayer.h>

CPlayer::CPlayer(CClientSocketInfo* socketInfo)
{
	m_pSockInfo = socketInfo;
	m_bInPauseMenu = false;
	m_ucMenuId = 42;
	m_fAircraftHeight = 800.0f;
	m_fJetpackHeight = 100.0f;
	m_oldkeys = m_newkeys = 0;
	m_oldcurs.x = m_oldcurs.y = m_newcurs.x = m_newcurs.y = 0;
}

CPlayer::~CPlayer()
{
	delete m_pSockInfo;
}

CClientSocketInfo* CPlayer::GetConnectionInfo()
{
	return m_pSockInfo;
}

void CPlayer::SetInPauseMenu(bool bInPauseMenu)
{
	m_bInPauseMenu = bInPauseMenu;
}

bool CPlayer::IsInPauseMenu()
{
	return m_bInPauseMenu;
}

int CPlayer::GetResolutionX()
{
	return m_iResolutionX;
}

int CPlayer::GetResolutionY()
{
	return m_iResolutionY;
}

void CPlayer::SetResolution(int X, int Y)
{
	m_iResolutionX = X;
	m_iResolutionY = Y;
}

float CPlayer::GetAircraftHeight()
{
	return m_fAircraftHeight;
}

float CPlayer::GetJetpackHeight()
{
	return m_fJetpackHeight;
}

void CPlayer::SetAircraftHeight(float height)
{
	m_fAircraftHeight = height;
}

void CPlayer::SetJetpackHeight(float height)
{
	m_fJetpackHeight = height;
}

void CPlayer::SetCurrentMenuId(unsigned char ucMenuId)
{
	m_ucMenuId = ucMenuId;
}

unsigned char CPlayer::GetCurrentMenuId()
{
	return m_ucMenuId;
}

void CPlayer::GetMousePos(int &x, int &y)
{
	x = m_newcurs.x;
	y = m_newcurs.y;
}

int CPlayer::GetNewkeys()
{
	return m_newkeys;
}

void CPlayer::SetKeys(int newkeys)
{
	m_oldkeys = m_newkeys;
	m_newkeys = newkeys;
}

void CPlayer::SetMousePos(POINT cursor)
{
	m_newcurs = cursor;
}