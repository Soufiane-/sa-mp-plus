#include <SAMP+/client/CLocalPlayer.h>
#include <SAMP+/client/CRPCCallback.h>
#include <SAMP+/client/Network.h>
#include <SAMP+/client/CGame.h>

DWORD CLocalPlayer::m_actionMemory[ePlayerAction::COUNT - 1] =
{
	0xB7CE20,
	0xB73571,
	0xB73572,
	0xB73573,
	0xB73574,
	0xB73575,
	0xB73576
};

int CLocalPlayer::m_newkeys;
int CLocalPlayer::m_oldkeys;
POINT CLocalPlayer::m_oldcurs;
POINT CLocalPlayer::m_newcurs;
RECT CLocalPlayer::m_screen;

void CLocalPlayer::SetActionEnabled(unsigned char action, bool bEnabled)
{
	if (action >= ePlayerAction::COUNT)
		return;

	if (action == ePlayerAction::ALL)
	{
		for (unsigned char i = 1; i < ePlayerAction::COUNT; ++i)
			SetActionEnabled(i, bEnabled);

	}
	else
		CMem::PutSingle<BYTE>(m_actionMemory[action-1], !bEnabled);

}

// TODO: make cancellable
void CLocalPlayer::OnDriveByShot()
{
	Network::SendRPC(eRPC::ON_DRIVE_BY_SHOT);
}

void CLocalPlayer::OnStuntBonus(sStuntDetails* pStuntDetails)
{
	RakNet::BitStream bitStream;
	bitStream.Write(*pStuntDetails);

	Network::SendRPC(eRPC::ON_STUNT_BONUS, &bitStream);
}


void CLocalPlayer::OnVKeyStateChange(int newkeys, int oldkeys)
{
	RakNet::BitStream bitStream;
	bitStream.Write(newkeys);
	bitStream.Write(oldkeys);
	Network::SendRPC(eRPC::ON_VKEY_STATE_CHANGE, &bitStream);
}

void CLocalPlayer::OnMousePosChange(POINT newcurs, POINT oldcurs)
{
	RakNet::BitStream bitStream;
	bitStream.Write(newcurs);
	bitStream.Write(oldcurs);
	Network::SendRPC(eRPC::ON_MOUSE_POS_CHANGE, &bitStream);
}

void CLocalPlayer::GetVKeyState(int vkey)
{
	RakNet::BitStream bitStream;

	if (!CGame::Playing())
		return;

	CLocalPlayer::m_oldkeys = CLocalPlayer::m_newkeys;
	bool state = PRESSED(vkey);
	if (state && !(CLocalPlayer::m_oldkeys & vkey))
		CLocalPlayer::m_newkeys |= vkey;
	else if (!state && (CLocalPlayer::m_oldkeys & vkey))
		CLocalPlayer::m_newkeys &= vkey;

	if (m_newkeys != m_oldkeys)
		CLocalPlayer::OnVKeyStateChange(m_newkeys, m_oldkeys);
}


void CLocalPlayer::GetMousePos(int &x, int &y)
{
	if (!CGame::Playing())
		return;

	m_oldcurs = m_newcurs;
	GetCursorPos(&m_newcurs);

	if ((m_oldcurs.x != m_newcurs.x) || (m_oldcurs.y != m_newcurs.y))
		CLocalPlayer::OnMousePosChange(m_newcurs, m_oldcurs);

	x = m_newcurs.x;
	y = m_newcurs.y;

	RakNet::BitStream bitStream;
	bitStream.Write(x);
	bitStream.Write(y);
	Network::SendRPC(eRPC::GET_MOUSE_POS, &bitStream);
}
void CLocalPlayer::SetClipAmmo(BYTE bSlot, int bAmmo)
{
	if (bSlot < 50) {
		//DWORD address = ((*(int*)0xB6F5F0) + 0x588) + (0x28 * bSlot) + 0x8;
		//CMem::PutSingle<int>(address, bAmmo);
		CGame::ClipAmmo[bSlot] = bAmmo;
	}
}


void CLocalPlayer::SetNoReload(bool toggle) {
	if (toggle) 
	{
		CMem::PutSingle<BYTE>(0x07428AB, 0x90);
		CMem::PutSingle<BYTE>(0x07428AC, 0x90);
	}
	else
	{
		CMem::PutSingle<BYTE>(0x07428AB, 0x85); // test eax,eax
		CMem::PutSingle<BYTE>(0x07428AC, 0xC0);
	}
}

void CLocalPlayer::ToggleInfiniteRun(bool toggle)
{
	CMem::PutSingle<BYTE>(0xB7CEE4, toggle);
}
