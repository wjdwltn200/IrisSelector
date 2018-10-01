#include "stdafx.h"
#include "animation.h"
#include "PlayerCharacter.h"


HRESULT PlayerCharacter::init()
{
	img_player = IMAGEMANAGER->addImage("player", "image/resources/player_image/BG_Player_idle_0.bmp", 256, 54, 8, 1, true, RGB(255, 0, 255), m_fX, m_fY);
	img_leftRun = IMAGEMANAGER->addImage("player_Left_Run", "image/resources/player_image/BG_Player_L_Run.bmp", 342, 54, 6, 1, true, RGB(255, 0, 255), m_fX, m_fY);
	img_rightRun = IMAGEMANAGER->addImage("player_Right_Run", "image/resources/player_image/BG_Player_R_Run.bmp", 342, 54, 6, 1, true, RGB(255, 0, 255), m_fX, m_fY);

	ani_stay = new animation;
	ani_stay->init(IMAGEMANAGER->findImage("player")->getWidth(), IMAGEMANAGER->findImage("player")->getHeight(),32, 54);
	ani_stay->setPlayFrame(4, 7, false, true);
	ani_stay->setFPS(10);
	ani_stay->start();

	ani_leftRun = new animation;
	ani_leftRun->init(IMAGEMANAGER->findImage("player_Left_Run")->getWidth(), IMAGEMANAGER->findImage("player_Left_Run")->getHeight(), 57, 54);
	ani_leftRun->setDefPlayFrame(false, true);
	ani_leftRun->setFPS(10);
	ani_leftRun->start();

	ani_rightRun = new animation;
	ani_rightRun->init(IMAGEMANAGER->findImage("player_Right_Run")->getWidth(), IMAGEMANAGER->findImage("player_Right_Run")->getHeight(), 57, 54);
	ani_rightRun->setDefPlayFrame(false, true);
	ani_rightRun->setFPS(10);
	ani_rightRun->start();

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

	ani_stay->frameUpdate();
	ani_leftRun->frameUpdate();
	ani_rightRun->frameUpdate();
}

void PlayerCharacter::render(HDC hdc)
{
	if (KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
		img_leftRun->aniRender(hdc, m_fX, m_fY, ani_leftRun, 1.0f, true, 255);
	}
	else if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		img_rightRun->aniRender(hdc, m_fX, m_fY, ani_rightRun, 1.0f, true, 255);
	}
	else
	{
		img_player->aniRender(hdc, m_fX, m_fY, ani_stay, 1.0f, true, 255);
	}
}

PlayerCharacter::PlayerCharacter()
{
}


PlayerCharacter::~PlayerCharacter()
{
}
