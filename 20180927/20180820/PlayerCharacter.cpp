#include "stdafx.h"
#include "animation.h"
#include "PlayerCharacter.h"
#include "bulletManger.h"


HRESULT PlayerCharacter::init()
{

	int ani_stay_Curr[] = { 0,1,2,3,4,5,6,7 };
	img_player = IMAGEMANAGER->addImage("player", "image/resources/player_image/BG_Player_idle_0.bmp", 256, 54, 8, 1, true, RGB(255, 0, 255), m_fX, m_fY);
	img_left_Run = IMAGEMANAGER->addImage("player_Left_Run", "image/resources/player_image/BG_Player_L_Run.bmp", 342, 54, 6, 1, true, RGB(255, 0, 255), m_fX, m_fY);
	img_right_Run = IMAGEMANAGER->addImage("player_Right_Run", "image/resources/player_image/BG_Player_R_Run.bmp", 342, 54, 6, 1, true, RGB(255, 0, 255), m_fX, m_fY);

	ani_right_stay = new animation;
	ani_right_stay->init(IMAGEMANAGER->findImage("player")->getWidth(), IMAGEMANAGER->findImage("player")->getHeight(),32, 54);
	ani_right_stay->setPlayFrame(ani_stay_Curr[3, 2, 1, 0], 4, false, true);
	ani_right_stay->setFPS(10);
	ani_right_stay->start();

	ani_left_stay = new animation;
	ani_left_stay->init(IMAGEMANAGER->findImage("player")->getWidth(), IMAGEMANAGER->findImage("player")->getHeight(), 32, 54);
	ani_left_stay->setPlayFrame(ani_stay_Curr[7, 6, 5, 4], 7, false, true);
	ani_left_stay->setFPS(10);
	ani_left_stay->start();

	ani_left_Run = new animation;
	ani_left_Run->init(IMAGEMANAGER->findImage("player_Left_Run")->getWidth(), IMAGEMANAGER->findImage("player_Left_Run")->getHeight(), 57, 54);
	ani_left_Run->setDefPlayFrame(false, true);
	ani_left_Run->start();

	ani_right_Run = new animation;
	ani_right_Run->init(IMAGEMANAGER->findImage("player_Right_Run")->getWidth(), IMAGEMANAGER->findImage("player_Right_Run")->getHeight(), 57, 54);
	ani_right_Run->setDefPlayFrame(false, true);
	ani_right_Run->start();

	m_isRunState = false;
	m_isRunStart = false;

	// 정지수 시작
	bulletManger m_pBulletMag;
	m_bulletDelayCount = 0;
	m_bulletDelayCountMax = BULLET_FIRST_DELAY;

	// 정지수 끝

	// Player 기본 셋팅
	memset(&m_tBulletInfo, 0, sizeof(m_tBulletInfo));

	m_tBulletInfo.tScale = 1.0f;
	m_tBulletInfo.tRadius = 0.5f;
	m_tBulletInfo.tExpRadius = 0.5f;
	m_tBulletInfo.tRange = 500.0f;

	m_tBulletInfo.tDmage = 10.0f;
	m_tBulletInfo.tKnokBack = 5.0f;
	m_tBulletInfo.tMoveSpeed = 10.0f;

	m_tBulletInfo.tMasterType = BULLET_MASTER_TYPE::PLAYER;
	m_tBulletInfo.tImageType = BULLET_IMAGE_TYPE::COLOR_Y;
	m_tBulletInfo.tMoveType = BULLET_MOVE_TYPE::ONE_LINE;
	return S_OK;
}

void PlayerCharacter::release()
{

}

void PlayerCharacter::update()
{
	// 총알 발사
	if (KEYMANAGER->isStayKeyDown(VK_SPACE))
	{
		if (m_bulletDelayCount == NULL)
		{
			(*m_pBulletMag)->fire("임시", m_fX, m_fY, MY_UTIL::getMouseAngle(m_fX, m_fY), m_tBulletInfo);
			m_bulletDelayCount = m_bulletDelayCountMax;
		}
	}
	if (m_bulletDelayCount > 0)
	{
		m_bulletDelayCount--;
	}

	if (KEYMANAGER->isOnceKeyUp('A') && !KEYMANAGER->isOnceKeyUp('D'))
	{
		if (!m_isRunState)
		{
			m_isRunState = true;
			m_isRunStart = false;
		}
		else if (m_isRunState)
		{
			m_isRunStart = true;
		}		
	}
	if (KEYMANAGER->isOnceKeyUp('D') && !KEYMANAGER->isOnceKeyUp('A'))
	{
		if (!m_isRunState)
		{
			m_isRunState = true;
			m_isRunStart = false;
		}
		else if (m_isRunState)
		{
			m_isRunStart = true;
		}
	}
	if (KEYMANAGER->isStayKeyDown('A'))
	{
		if (m_isRunStart) // 달리고 있다면
		{
			m_fX -= m_Speed * 1.5f;
			ani_left_Run->setFPS(30);
		}
		else // 달리지 않고 있다면
		{
			ani_left_Run->setFPS(10);
			m_fX -= m_Speed;
		}
	}
	if (KEYMANAGER->isStayKeyDown('D'))
	{
		if (m_isRunStart) // 달리고 있다면
		{
			m_fX += m_Speed * 1.5f;
			ani_right_Run->setFPS(30);

		}
		else // 달리지 않고 있다면
		{
			m_fX += m_Speed;
			ani_right_Run->setFPS(10);
		}
	}
	if (KEYMANAGER->isStayKeyDown('W'))
	{
		m_fY -= m_Speed;
	}
	if (KEYMANAGER->isStayKeyDown('S'))
	{
		m_fY += m_Speed;
	}

	if (m_isRunState)
	{
		m_count++;
		if (m_count >= 20)
		{
			m_count = 0;
			m_isRunState = false;
		}
	}

	ani_right_stay->frameUpdate();
	ani_left_stay->frameUpdate();
	ani_left_Run->frameUpdate();
	ani_right_Run->frameUpdate();
}

void PlayerCharacter::render(HDC hdc)
{
	if (KEYMANAGER->isStayKeyDown('A') || KEYMANAGER->isStayKeyDown('W') && m_Direction && !(KEYMANAGER->isStayKeyDown('D')
		|| KEYMANAGER->isStayKeyDown('S') && m_Direction && !(KEYMANAGER->isStayKeyDown('D'))))
	{
		m_Direction = true;
		img_left_Run->aniRender(hdc, m_fX, m_fY, ani_left_Run, 1.0f, true, 255);
	}
	
	if (KEYMANAGER->isStayKeyDown('D') || KEYMANAGER->isStayKeyDown('W') && !m_Direction && !(KEYMANAGER->isStayKeyDown('A')
		|| KEYMANAGER->isStayKeyDown('S') && !m_Direction && !(KEYMANAGER->isStayKeyDown('A'))))
	{
		m_Direction = false;
		img_right_Run->aniRender(hdc, m_fX, m_fY, ani_right_Run, 1.0f, true, 255);
	}
	if (m_Direction && !(KEYMANAGER->isStayKeyDown('A') || KEYMANAGER->isStayKeyDown('W') && m_Direction
		|| KEYMANAGER->isStayKeyDown('S') && m_Direction))
	{
		img_player->aniRender(hdc, m_fX, m_fY, ani_left_stay, 1.0f, true, 255);	
	}

	if (!m_Direction && !(KEYMANAGER->isStayKeyDown('D') || KEYMANAGER->isStayKeyDown('W') && !m_Direction 
		|| KEYMANAGER->isStayKeyDown('S') && !m_Direction))
	{
		img_player->aniRender(hdc, m_fX, m_fY, ani_right_stay, 1.0f, true, 255);
	}
}

PlayerCharacter::PlayerCharacter()
{
}


PlayerCharacter::~PlayerCharacter()
{
}
