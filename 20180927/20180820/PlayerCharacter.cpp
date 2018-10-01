#include "stdafx.h"
#include "animation.h"
#include "PlayerCharacter.h"


HRESULT PlayerCharacter::init()
{
	img_player = IMAGEMANAGER->addImage("player", "image/resources/player_image/BG_Player_idle_0.bmp", 128, 54, 4, 1, true, RGB(255, 0, 255), m_fX, m_fY);
	img_leftRun = IMAGEMANAGER->addImage("player_Left_Run", "image/resources/player_image/BG_Player_L_Run.bmp", 342, 54, 6, 1, true, RGB(255, 0, 255), m_fX, m_fY);
	img_rightRun = IMAGEMANAGER->addImage("player_Right_Run", "image/resources/player_image/BG_Player_R_Run.bmp", 342, 54, 6, 1, true, RGB(255, 0, 255), m_fX, m_fY);
	
	return S_OK;
}

void PlayerCharacter::release()
{

}

void PlayerCharacter::update()
{
	
	if (KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
		m_fX -= m_pSpeed;
	}
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		m_fX += m_pSpeed;
	}
	if (KEYMANAGER->isStayKeyDown(VK_UP))
	{
		m_fY -= m_pSpeed;
	}
	if (KEYMANAGER->isStayKeyDown(VK_DOWN))
	{
		m_fY += m_pSpeed;
	}
}

void PlayerCharacter::render(HDC hdc)
{
	img_player->frameRender(hdc, m_fX, m_fY, 1, 1);
}

PlayerCharacter::PlayerCharacter()
{
}


PlayerCharacter::~PlayerCharacter()
{
}
