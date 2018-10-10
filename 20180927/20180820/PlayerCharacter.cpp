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
	img_CrossHair = IMAGEMANAGER->addImage("CrossHair", "image/resources/bullet_image/crossHair.bmp", 207, 69, 3, 1, true, RGB(255, 0, 255), m_fX, m_fY);
	ani_CrossHair = new animation;
	ani_CrossHair->init(img_CrossHair->getWidth(), img_CrossHair->getFrameHeight(), 69, 69);
	ani_CrossHair->setDefPlayFrame(true, false);
	ani_CrossHair->setFPS(30);

	ani_right_stay = new animation;
	ani_right_stay->init(IMAGEMANAGER->findImage("player")->getWidth(), IMAGEMANAGER->findImage("player")->getHeight(), 32, 54);
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

	m_fRadius = img_player->getFrameWidth() / 2;
	m_fSpeed = 1.0f;

	bulletManger m_pBulletMag;
	m_bulletDelayCount = 0;
	m_bulletDelayCountMax = BULLET_FIRST_DELAY;

	m_fCrossHairScale = CROSSHAIR_MIN_SCALE;
	m_fCrossHairScaleMax = CROSSHAIR_MAX_SCALE;

	// 정지수 끝

	// Player 기본 셋팅 (메인)
	memset(&m_tBulletInfo, 0, sizeof(m_tBulletInfo));

	m_tBulletInfo.tIsAlive = true;
	m_tBulletInfo.tBulletSetNum = 1;
	m_tBulletInfo.tScale = 1.0f;
	m_tBulletInfo.tScaleMax = m_tBulletInfo.tScale * 2.0f;
	m_tBulletInfo.tRadius = 0.5f;
	m_tBulletInfo.tExpRadius = 0.5f;
	m_tBulletInfo.tRange = 300.0f;
	m_tBulletInfo.tBulletBoom = false;

	m_tBulletInfo.tDmage = 10.0f;
	m_tBulletInfo.tKnokBack = 5.0f;
	m_tBulletInfo.tMoveSpeed = 20.0f;
	m_tBulletInfo.tScatter = 10.0f;

	m_tBulletInfo.tBoomType = BULLET_BOOM_TYPE::ANGLE_LINE;
	m_tBulletInfo.tShootType = BULLET_SHOOT_TYPE::ONE_SHOOT;
	m_tBulletInfo.tMasterType = BULLET_MASTER_TYPE::PLAYER;
	m_tBulletInfo.tMoveActType = BULLET_MOVE_ACT_TYPE::BULLET_MOVE_ACT_NUM;
	m_tBulletInfo.tImageType = BULLET_IMAGE_TYPE::COLOR_Y;
	m_tBulletInfo.tMoveType = BULLET_MOVE_TYPE::ONE_LINE;
	
	m_tBulletInfoPoint = &m_tBulletInfo;

	// 서브 탄환 (이중 폭발)
	memset(&m_tBulletInfoSub, 0, sizeof(m_tBulletInfoSub));

	m_tBulletInfoSub.tIsAlive = true;
	m_tBulletInfoSub.tBulletSetNum = 3;
	m_tBulletInfoSub.tScale = 1.0f;
	m_tBulletInfoSub.tScaleMax = m_tBulletInfo.tScale * 2.0f;
	m_tBulletInfoSub.tRadius = 0.5f;
	m_tBulletInfoSub.tExpRadius = 0.5f;
	m_tBulletInfoSub.tRange = 300.0f;
	m_tBulletInfoSub.tBulletBoom = false;

	m_tBulletInfoSub.tDmage = 10.0f;
	m_tBulletInfoSub.tKnokBack = 5.0f;
	m_tBulletInfoSub.tMoveSpeed = 10.0f;
	m_tBulletInfoSub.tScatter = 0.0f;

	m_tBulletInfoSub.tBoomType = BULLET_BOOM_TYPE::ANGLE_RANDOM;
	m_tBulletInfoSub.tShootType = BULLET_SHOOT_TYPE::CUFF_SHOOT;
	m_tBulletInfoSub.tMasterType = BULLET_MASTER_TYPE::PLAYER;
	m_tBulletInfoSub.tMoveActType = BULLET_MOVE_ACT_TYPE::BULLET_MOVE_ACT_NUM;
	m_tBulletInfoSub.tImageType = BULLET_IMAGE_TYPE::COLOR_P;
	m_tBulletInfoSub.tMoveType = BULLET_MOVE_TYPE::ONE_LINE;

	m_tBulletInfoSubPoint = &m_tBulletInfoSub;

	return S_OK;
}

void PlayerCharacter::release()
{

}

void PlayerCharacter::update()
{
	if (m_fCrossHairScale > CROSSHAIR_MIN_SCALE)
	{
		if (m_fCrossHairScale < CROSSHAIR_MIN_SCALE)
			m_fCrossHairScale = CROSSHAIR_MIN_SCALE;

		m_fCrossHairScale -= 0.1f;
	}

	// 총알 발사
	if (0)
	{

		if (m_bulletDelayCount == NULL)
		{
			if (m_fCrossHairScale < m_fCrossHairScaleMax)
			{
				m_fCrossHairScale += 0.1f;
				if (m_fCrossHairScale > m_fCrossHairScaleMax)
					m_fCrossHairScale = m_fCrossHairScaleMax;
			}
			ani_CrossHair->start();

			if (m_tBulletInfo.tShootType == BULLET_SHOOT_TYPE::ONE_SHOOT)
			{
				if (m_tBulletInfo.tBulletSetNum == 1)
				{
					(*m_pBulletMag)->fire("임시", m_fX, m_fY, MY_UTIL::getMouseAngle(m_fX, m_fY), m_tBulletInfoPoint, m_tBulletInfoSubPoint);
				}
				else // 총알 개수 만큼 방향을 분리
				{
					for (int i = 0; i < m_tBulletInfo.tBulletSetNum; i++)
					{
						(*m_pBulletMag)->fire("임시", m_fX, m_fY, MY_UTIL::getMouseAngle(m_fX, m_fY) - (i * (PI / 180.0f * (30.0f))) - ((PI / 180.0f) * MY_UTIL::getMouseAngle(m_fX, m_fY) - ((m_tBulletInfo.tBulletSetNum - 1) * (PI / 180.0f * (30.0f)))) / 2, m_tBulletInfoPoint, m_tBulletInfoSubPoint);
					}
				}
			}
			else if (m_tBulletInfo.tShootType == BULLET_SHOOT_TYPE::CUFF_SHOOT)
			{
				if (m_tBulletInfo.tBulletSetNum == 1)
				{
					(*m_pBulletMag)->fire("임시", m_fX, m_fY, MY_UTIL::getMouseAngle(m_fX, m_fY), m_tBulletInfoPoint, m_tBulletInfoSubPoint);
				}
				else // 총알 개수 만큼 방향을 분리
				{
					for (int i = 0; i < m_tBulletInfo.tBulletSetNum; i++)
					{
						(*m_pBulletMag)->fire("임시", m_fX, m_fY, MY_UTIL::getMouseAngle(m_fX, m_fY) + (i * (PI / 180.0f * (360.0f / m_tBulletInfo.tBulletSetNum))), m_tBulletInfoPoint, m_tBulletInfoSubPoint);
					}
				}
			}
			m_bulletDelayCount = m_bulletDelayCountMax;
		}
	}
	if (m_bulletDelayCount > 0)
	{
		m_bulletDelayCount--;
		// 크로스 헤어 Act

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

	ani_CrossHair->frameUpdate();
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

	img_CrossHair->aniRender(hdc, g_ptMouse.x - (img_CrossHair->getFrameWidth() / 2) * m_fCrossHairScale, g_ptMouse.y - (img_CrossHair->getFrameHeight() / 2) * m_fCrossHairScale, ani_CrossHair, m_fCrossHairScale);


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
		m_tBulletInfo.tBulletSetNum);
	TextOut(hdc, m_fX + 100, m_fY + 120, szText, strlen(szText));

	sprintf_s(szText, "m_fCrossHairScale : %f",
		m_fCrossHairScale);
	TextOut(hdc, m_fX + 100, m_fY + 140, szText, strlen(szText));

	sprintf_s(szText, "m_fCrossHairScaleMax : %f",
		m_fCrossHairScaleMax);
	TextOut(hdc, m_fX + 100, m_fY + 160, szText, strlen(szText));
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
		m_tBulletInfo.tBulletSetNum += 1;
		break;

	case ITEM_SKILL_TYPE::BULLET_SCALE_SIZE_UP:
		m_tBulletInfo.tMoveActType = BULLET_MOVE_ACT_TYPE::SCALE_SIZE_UP;
		m_tBulletInfo.tScaleMax += 0.5f;
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
