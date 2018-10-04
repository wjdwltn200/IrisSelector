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
	memset(&m_rc, 0, sizeof(m_rc));

	m_bulletSetMax = 1;
	m_fRadius = img_player->getFrameWidth() / 2;
	m_fSpeed = 1.0f;

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
	if (KEYMANAGER->isStayKeyDown(VK_LBUTTON))
	{
		if (m_bulletDelayCount == NULL)
		{
			if (m_bulletSetMax == 1)
			{
				(*m_pBulletMag)->fire("임시", m_fX, m_fY, MY_UTIL::getMouseAngle(m_fX, m_fY), m_tBulletInfo);
			}
			else
			{
				for (int i = 0; i < m_bulletSetMax; i++)
				{
					float a = (i * (PI / 180.0f * (360.0f / m_bulletSetMax)));
					float b = MY_UTIL::getMouseAngle(m_fX, m_fY);
					float c = a + b;
					float d = 0.0f;
					(*m_pBulletMag)->fire("임시", m_fX, m_fY, b + a, m_tBulletInfo);
				}
			}


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
			m_fX -= m_fSpeed * 1.5f;
			ani_left_Run->setFPS(30);
		}
		else // 달리지 않고 있다면
		{
			ani_left_Run->setFPS(10);
			m_fX -= m_fSpeed;
		}
	}
	if (KEYMANAGER->isStayKeyDown('D'))
	{
		if (m_isRunStart) // 달리고 있다면
		{
			m_fX += m_fSpeed * 1.5f;
			ani_right_Run->setFPS(30);

		}
		else // 달리지 않고 있다면
		{
			m_fX += m_fSpeed;
			ani_right_Run->setFPS(10);
		}
	}
	if (KEYMANAGER->isStayKeyDown('W'))
	{
		m_fY -= m_fSpeed;
	}
	if (KEYMANAGER->isStayKeyDown('S'))
	{
		m_fY += m_fSpeed;
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

	m_rc = RectMakeCenter(m_fX, m_fY, img_player->getFrameWidth(), img_player->getFrameHeight());

	ani_right_stay->frameUpdate();
	ani_left_stay->frameUpdate();
	ani_left_Run->frameUpdate();
	ani_right_Run->frameUpdate();
}

void PlayerCharacter::render(HDC hdc)
{
	EllipseMakeCenter(hdc, m_fX, m_fY, img_player->getFrameWidth(), img_player->getFrameHeight());
	//Ellipse(hdc, m_rc.left, m_rc.top, m_rc.right, m_rc.bottom);


	if (KEYMANAGER->isStayKeyDown('A') || KEYMANAGER->isStayKeyDown('W') && m_Direction && !(KEYMANAGER->isStayKeyDown('D')
		|| KEYMANAGER->isStayKeyDown('S') && m_Direction && !(KEYMANAGER->isStayKeyDown('D'))))
	{
		m_Direction = true;
		img_left_Run->aniRender(hdc, m_fX - (img_left_Run->getFrameWidth() / 2), m_fY - (img_left_Run->getFrameHeight() / 2), ani_left_Run, 1.0f, true, 255);
	}
	
	if (KEYMANAGER->isStayKeyDown('D') || KEYMANAGER->isStayKeyDown('W') && !m_Direction && !(KEYMANAGER->isStayKeyDown('A')
		|| KEYMANAGER->isStayKeyDown('S') && !m_Direction && !(KEYMANAGER->isStayKeyDown('A'))))
	{
		m_Direction = false;
		img_right_Run->aniRender(hdc, m_fX - (img_right_Run->getFrameWidth() / 2), m_fY - (img_right_Run->getFrameHeight() / 2), ani_right_Run, 1.0f, true, 255);
	}
	if (m_Direction && !(KEYMANAGER->isStayKeyDown('A') || KEYMANAGER->isStayKeyDown('W') && m_Direction
		|| KEYMANAGER->isStayKeyDown('S') && m_Direction))
	{
		img_player->aniRender(hdc, m_fX - (img_player->getFrameWidth() / 2), m_fY - (img_player->getFrameHeight() / 2), ani_left_stay, 1.0f, true, 255);
	}

	if (!m_Direction && !(KEYMANAGER->isStayKeyDown('D') || KEYMANAGER->isStayKeyDown('W') && !m_Direction 
		|| KEYMANAGER->isStayKeyDown('S') && !m_Direction))
	{
		img_player->aniRender(hdc, m_fX - (img_player->getFrameWidth() / 2), m_fY - (img_player->getFrameHeight() / 2), ani_right_stay, 1.0f, true, 255);
	}

	//Rectangle(hdc, m_rc.left, m_rc.top, m_rc.right, m_rc.bottom);


	char szText[256];

	// TRANSPARENT : 투명, OPAQUE : 불투명
	SetBkMode(hdc, TRANSPARENT);

	SetTextColor(hdc, RGB(255, 0, 255));

	sprintf_s(szText, "m_fX : %f / m_fY : %f",
		m_fX, m_fY);
	TextOut(hdc, m_fX + 100, m_fY, szText, strlen(szText));

	sprintf_s(szText, "tMoveSpeed : %f",
		m_tBulletInfo.tMoveSpeed);
	TextOut(hdc, m_fX + 100, m_fY + 20, szText, strlen(szText));

	sprintf_s(szText, "tDmage : %f",
		m_tBulletInfo.tDmage);
	TextOut(hdc, m_fX + 100, m_fY + 40, szText, strlen(szText));

	sprintf_s(szText, "tRange : %f",
		m_tBulletInfo.tRange);
	TextOut(hdc, m_fX + 100, m_fY + 60, szText, strlen(szText));

	sprintf_s(szText, "m_bulletDelayCountMax : %d",
		m_bulletDelayCountMax);
	TextOut(hdc, m_fX + 100, m_fY + 80, szText, strlen(szText));

	sprintf_s(szText, "m_fSpeed : %f",
		m_fSpeed);
	TextOut(hdc, m_fX + 100, m_fY + 100, szText, strlen(szText));

	sprintf_s(szText, "m_bulletSetMax : %d",
		m_bulletSetMax);
	TextOut(hdc, m_fX + 100, m_fY + 120, szText, strlen(szText));
}

void PlayerCharacter::getItem(int itemInfo)
{
	switch (itemInfo)
	{
	case ITEM_SKILL_TYPE::BULLET_SPEED_UP:
		m_tBulletInfo.tMoveSpeed += 1.0f;
		break;
	case ITEM_SKILL_TYPE::BULLET_POWER_UP:
		m_tBulletInfo.tDmage += 1.0f;
		break;
	case ITEM_SKILL_TYPE::BULLET_RANGE_UP:
		m_tBulletInfo.tRange += 10.0f;
		break;
	case ITEM_SKILL_TYPE::BULLET_SIZE_UP:
		m_tBulletInfo.tScale += 1.0f;
		break;
	case ITEM_SKILL_TYPE::BULLET_DELAY_DOWN:
		m_bulletDelayCountMax -= 30;
		break;
	case ITEM_SKILL_TYPE::BULLET_SET_MAX_UP:
		m_bulletSetMax += 6;
		break;

	case ITEM_SKILL_TYPE::BULLET_CENTER_CENTRIFUGAL:
		m_tBulletInfo.tMoveType = BULLET_MOVE_TYPE::CENTER_CENTRIFUGAL;
		break;
	case ITEM_SKILL_TYPE::BULLET_MOVE_CENTRIFUGAL:
		m_tBulletInfo.tMoveType = BULLET_MOVE_TYPE::MOVE_CENTRIFUGAL;
		break;
	case ITEM_SKILL_TYPE::BULLET_ONE_LINE:
		m_tBulletInfo.tMoveType = BULLET_MOVE_TYPE::ONE_LINE;
		break;

	case ITEM_SKILL_TYPE::PLAYER_MOVE_SPEED_UP:
		m_fSpeed += 1.0f;
		break;

	case ITEM_SKILL_TYPE::BULLET_COLOR_B:
		m_tBulletInfo.tImageType = BULLET_IMAGE_TYPE::COLOR_B;
		break;
	case ITEM_SKILL_TYPE::BULLET_COLOR_G:
		m_tBulletInfo.tImageType = BULLET_IMAGE_TYPE::COLOR_G;
		break;
	case ITEM_SKILL_TYPE::BULLET_COLOR_P:
		m_tBulletInfo.tImageType = BULLET_IMAGE_TYPE::COLOR_P;
		break;
	case ITEM_SKILL_TYPE::BULLET_COLOR_Y:
		m_tBulletInfo.tImageType = BULLET_IMAGE_TYPE::COLOR_Y;
		break;
	}
}

PlayerCharacter::PlayerCharacter()
{
}


PlayerCharacter::~PlayerCharacter()
{
}
