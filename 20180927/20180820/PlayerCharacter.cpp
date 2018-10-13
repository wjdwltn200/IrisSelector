#include "stdafx.h"
#include "animation.h"
#include "PlayerCharacter.h"
#include "bulletManger.h"
#include "item.h"

HRESULT PlayerCharacter::init()
{
	img_ItemUiBg = IMAGEMANAGER->findImage("Player_ItemUI");
	img_ItemUiBg->setX(WINSIZEX / 2 - img_ItemUiBg->getFrameWidth() / 2);
	img_ItemUiBg->setY(WINSIZEY / 2 - img_ItemUiBg->getFrameHeight() / 2);
	img_InfoIcon = IMAGEMANAGER->findImage("Player_InfoIcon");

	for (int i = 0; i < 10; i++)
	{
		img_HpPoint[i] = IMAGEMANAGER->findImage("Player_HP_Point");
	}

	m_vecItem.reserve(30); // 가방 사이즈

	m_currHp = BAES_HP;
	m_currHpMax = m_currHp;
	m_isAlive = true;
	m_isItemUi = false;
	m_fPlayerScale = 1.0f;
	m_isRectCol = false;

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

	m_bulletDelayCount = 0;
	m_bulletDelayCountMax = BULLET_FIRST_DELAY;

	m_fCrossHairScaleMin = CROSSHAIR_MIN_SCALE;
	m_fCrossHairScale = m_fCrossHairScaleMin;
	m_fCrossHairScaleMax = CROSSHAIR_MAX_SCALE;

	m_itemNum = 0;
	m_itemNumY = 0;

	// 정지수 끝

	// Player 기본 셋팅 (메인)
	memset(&m_tBulletInfo, 0, sizeof(m_tBulletInfo));

	m_tBulletInfo.tIsAlive = true;
	m_tBulletInfo.tBulletSetNum = 1;
	m_tBulletInfo.tScale = 1.0f;
	m_tBulletInfo.tScaleMax = m_tBulletInfo.tScale * 2.0f;
	m_tBulletInfo.tRadius = 0.5f;
	m_tBulletInfo.tExpRadius = 0.5f;
	m_tBulletInfo.tRange = 200.0f;
	m_tBulletInfo.tBulletBoom = false;

	m_tBulletInfo.tDmage = 5.0f;
	m_tBulletInfo.tKnokBack = 2.0f;
	m_tBulletInfo.tMoveSpeed = 10.0f;
	m_tBulletInfo.tScatter = m_fCrossHairScale * 10.0f;

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
	m_tBulletInfoSub.tBulletSetNum = 1;
	m_tBulletInfoSub.tScale = m_tBulletInfo.tScale / 2;
	m_tBulletInfoSub.tScaleMax = m_tBulletInfo.tScale * 2.0f;
	m_tBulletInfoSub.tRadius = m_tBulletInfo.tRadius / 2;
	m_tBulletInfoSub.tExpRadius = m_tBulletInfo.tExpRadius / 2;
	m_tBulletInfoSub.tRange = m_tBulletInfo.tRange / 2;
	m_tBulletInfoSub.tBulletBoom = false;

	m_tBulletInfoSub.tDmage = m_tBulletInfo.tDmage / 2;
	m_tBulletInfoSub.tKnokBack = m_tBulletInfo.tKnokBack / 2;
	m_tBulletInfoSub.tMoveSpeed = m_tBulletInfo.tMoveSpeed / 2;
	m_tBulletInfoSub.tScatter = m_tBulletInfo.tScatter / 2;

	m_tBulletInfoSub.tBoomType = BULLET_BOOM_TYPE::ANGLE_LINE;
	m_tBulletInfoSub.tShootType = BULLET_SHOOT_TYPE::ONE_SHOOT;
	m_tBulletInfoSub.tMasterType = BULLET_MASTER_TYPE::PLAYER;
	m_tBulletInfoSub.tMoveActType = BULLET_MOVE_ACT_TYPE::BULLET_MOVE_ACT_NUM;
	m_tBulletInfoSub.tImageType = BULLET_IMAGE_TYPE::COLOR_P;
	m_tBulletInfoSub.tMoveType = BULLET_MOVE_TYPE::ONE_LINE;

	m_tBulletInfoSubPoint = &m_tBulletInfoSub;

	return S_OK;
}

void PlayerCharacter::release()
{
	SAFE_DELETE(ani_CrossHair);
	SAFE_DELETE(ani_right_stay);
	SAFE_DELETE(ani_left_stay);
	SAFE_DELETE(ani_right_Run);
}

void PlayerCharacter::update()
{
	// 총알 발사
	if (KEYMANAGER->isOnceKeyDown(VK_RBUTTON)) // 테스트 용
	{
		//m_fCrossHairScaleMin += 0.1f;
		//m_currHpMax += 2;
		//m_currHp++;
		//m_currHp--;
	}

	movement();

	if (KEYMANAGER->isStayKeyDown(VK_LBUTTON))
	{
		if (m_bulletDelayCount == NULL)
		{
			if (m_fCrossHairScale < m_fCrossHairScaleMax)
			{
				m_fCrossHairScale += 0.1f;
				if (m_fCrossHairScale > m_fCrossHairScaleMax)
					m_fCrossHairScale = m_fCrossHairScaleMax;
				m_tBulletInfo.tScatter = m_fCrossHairScale * 10.0f;
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
		m_bulletDelayCount--;

	if (m_fCrossHairScale > CROSSHAIR_MAX_SCALE)
		m_fCrossHairScale = CROSSHAIR_MAX_SCALE;

	if (m_fCrossHairScale > m_fCrossHairScaleMin)
		m_fCrossHairScale -= 0.1f;

	if (!m_isRectCol)
	{
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
		if (KEYMANAGER->isOnceKeyDown(VK_TAB))
		{
			if (m_isItemUi)
			{
				m_isItemUi = false;
			}
			else if (!m_isItemUi)
			{
				m_isItemUi = true;
			}
		}
	}

	m_rc = RectMakeCenter(m_fX, m_fY, img_player->getFrameWidth() * m_fPlayerScale, img_player->getFrameHeight() * m_fPlayerScale);

	MoveActKeyInput();

	ani_CrossHair->frameUpdate();
	ani_right_stay->frameUpdate();
	ani_left_stay->frameUpdate();
	ani_left_Run->frameUpdate();
	ani_right_Run->frameUpdate();
}

void PlayerCharacter::render(HDC hdc)
{
	EllipseMakeCenter(hdc, m_fX, m_fY, img_player->getFrameWidth() * m_fPlayerScale, img_player->getFrameHeight() * m_fPlayerScale);
	//Ellipse(hdc, m_rc.left, m_rc.top, m_rc.right, m_rc.bottom);

	for (int i = 0; i < m_currHpMax / 2; i++)
	{
		if ((i+1) * 2 <= m_currHp)
		{
			img_HpPoint[i]->frameRender(hdc,
				10 + i * (img_HpPoint[0]->getFrameWidth() + 10),
				(img_HpPoint[0]->getFrameHeight() / 2),
				2,
				0
			);
		}
		else if (((i + 1) * 2) - 1 == m_currHp)
		{
			img_HpPoint[i]->frameRender(hdc,
				10 + i * (img_HpPoint[0]->getFrameWidth() + 10),
				(img_HpPoint[0]->getFrameHeight() / 2),
				1,
				0
			);
		}
		else
		{
			img_HpPoint[i]->frameRender(hdc,
				10 + i * (img_HpPoint[0]->getFrameWidth() + 10),
				(img_HpPoint[0]->getFrameHeight() / 2),
				0,
				0
			);
		}
	}

	if ((KEYMANAGER->isStayKeyDown('A') ||
		(KEYMANAGER->isStayKeyDown('A') && (KEYMANAGER->isStayKeyDown('W') || KEYMANAGER->isStayKeyDown('S'))))) // 왼쪽 대각선
	{
		m_Direction = true;
		img_left_Run->aniRender(hdc, m_fX - (img_left_Run->getFrameWidth() / 2) * m_fPlayerScale, m_fY - (img_left_Run->getFrameHeight() / 2) * m_fPlayerScale, ani_left_Run, m_fPlayerScale, true, 255);
	}
	else if (KEYMANAGER->isStayKeyDown('D') ||
		(KEYMANAGER->isStayKeyDown('D') && (KEYMANAGER->isStayKeyDown('W') || KEYMANAGER->isStayKeyDown('S')))) // 오른쪽 대각선
	{
		m_Direction = false;
		img_right_Run->aniRender(hdc, m_fX - (img_right_Run->getFrameWidth() / 2) * m_fPlayerScale, m_fY - (img_right_Run->getFrameHeight() / 2) * m_fPlayerScale, ani_right_Run, m_fPlayerScale, true, 255);
	}
	else if (m_Direction && ((KEYMANAGER->isStayKeyDown('W')) || (KEYMANAGER->isStayKeyDown('S')))) // 왼쪽 위
	{
		m_Direction = true;
		img_left_Run->aniRender(hdc, m_fX - (img_left_Run->getFrameWidth() / 2) * m_fPlayerScale, m_fY - (img_left_Run->getFrameHeight() / 2) * m_fPlayerScale, ani_left_Run, m_fPlayerScale, true, 255);
	}
	else if (!m_Direction && ((KEYMANAGER->isStayKeyDown('W')) || (KEYMANAGER->isStayKeyDown('S')))) // 오른쪽 아래
	{
		m_Direction = false;
		img_right_Run->aniRender(hdc, m_fX - (img_right_Run->getFrameWidth() / 2) * m_fPlayerScale, m_fY - (img_right_Run->getFrameHeight() / 2) * m_fPlayerScale, ani_right_Run, m_fPlayerScale, true, 255);
	}
	else if (m_Direction) // 아이들
	{
		img_player->aniRender(hdc, m_fX - (img_player->getFrameWidth() / 2) * m_fPlayerScale, m_fY - (img_player->getFrameHeight() / 2) * m_fPlayerScale, ani_left_stay, m_fPlayerScale, true, 255);
	}
	else
	{
		img_player->aniRender(hdc, m_fX - (img_player->getFrameWidth() / 2) * m_fPlayerScale, m_fY - (img_player->getFrameHeight() / 2) * m_fPlayerScale, ani_right_stay, m_fPlayerScale, true, 255);

	}

	//Rectangle(hdc, m_rc.left, m_rc.top, m_rc.right, m_rc.bottom);

	img_InfoIcon->render(hdc, PLAYER_ICON_X - (img_InfoIcon->getFrameWidth() / 2), PLAYER_ICON_Y - (img_InfoIcon->getFrameHeight() / 2));
	if (m_isItemUi) // 가방 열기
	{
		IMAGEMANAGER->findImage("Player_UI_BG")->alphaRender(hdc, 0, 0, 155);

		img_ItemUiBg->render(hdc, (WINSIZEX / 2) - (img_ItemUiBg->getFrameWidth() / 2), (WINSIZEX / 2) - (img_ItemUiBg->getFrameHeight() / 2));
		PlayerInfoUi(hdc);
		itemUi(hdc);
	}

	img_CrossHair->aniRender(hdc, g_ptMouse.x - (img_CrossHair->getFrameWidth() / 2) * m_fCrossHairScale, g_ptMouse.y - (img_CrossHair->getFrameHeight() / 2) * m_fCrossHairScale, ani_CrossHair, m_fCrossHairScale);


}

void PlayerCharacter::getItem(tagItemInfo itemInfo)
{
	if (!itemInfo.tBulletType)
	{
		m_tBulletInfo.tBulletSetNum += itemInfo.tBulletSetNum;
		m_tBulletInfo.tRange += itemInfo.tRange;
		m_tBulletInfo.tScale += itemInfo.tBulletScale;
		m_tBulletInfo.tDmage += itemInfo.tDmage;
		m_tBulletInfo.tKnokBack += itemInfo.tKnokBack;
		m_tBulletInfo.tMoveSpeed += itemInfo.tMoveSpeed;

		if (itemInfo.tBoomType != (BULLET_BOOM_TYPE::BULLET_BOOM_NUM))
			m_tBulletInfo.tBoomType = itemInfo.tBoomType;
		if (itemInfo.tShootType != (BULLET_SHOOT_TYPE::BULLET_SHOOT_NUM))
			m_tBulletInfo.tShootType = itemInfo.tShootType;
		if (itemInfo.tMasterType != (BULLET_MASTER_TYPE::BULLET_MASTER_NUM))
			m_tBulletInfo.tMasterType = itemInfo.tMasterType;
		if (itemInfo.tMoveActType != (BULLET_BOOM_TYPE::BULLET_BOOM_NUM))
			m_tBulletInfo.tMoveActType = itemInfo.tMoveActType;
		if (itemInfo.tMoveType != (BULLET_MOVE_ACT_TYPE::BULLET_MOVE_ACT_NUM))
			m_tBulletInfo.tMoveType = itemInfo.tMoveType;
		if (itemInfo.tImageType != BULLET_IMAGE_TYPE::BULLET_IMAGE_NUM)
			m_tBulletInfo.tImageType = itemInfo.tImageType;
	}
	else
	{
		m_tBulletInfoSub.tBulletSetNum += itemInfo.tBulletSetNum;
		m_tBulletInfoSub.tRange += itemInfo.tRange;
		m_tBulletInfoSub.tScale += itemInfo.tBulletScale;
		m_tBulletInfoSub.tDmage += itemInfo.tDmage;
		m_tBulletInfoSub.tKnokBack += itemInfo.tKnokBack;
		m_tBulletInfoSub.tMoveSpeed += itemInfo.tMoveSpeed;

		if (itemInfo.tBoomType != (BULLET_BOOM_TYPE::BULLET_BOOM_NUM))
			m_tBulletInfoSub.tBoomType = itemInfo.tBoomType;
		if (itemInfo.tShootType != (BULLET_SHOOT_TYPE::BULLET_SHOOT_NUM))
			m_tBulletInfoSub.tShootType = itemInfo.tShootType;
		if (itemInfo.tMasterType != (BULLET_MASTER_TYPE::BULLET_MASTER_NUM))
			m_tBulletInfoSub.tMasterType = itemInfo.tMasterType;
		if (itemInfo.tMoveActType != (BULLET_BOOM_TYPE::BULLET_BOOM_NUM))
			m_tBulletInfoSub.tMoveActType = itemInfo.tMoveActType;
		if (itemInfo.tMoveType != (BULLET_MOVE_ACT_TYPE::BULLET_MOVE_ACT_NUM))
			m_tBulletInfoSub.tMoveType = itemInfo.tMoveType;
		if (itemInfo.tImageType != BULLET_IMAGE_TYPE::BULLET_IMAGE_NUM)
			m_tBulletInfoSub.tImageType = itemInfo.tImageType;
	}
	
	// 2차 폭발 여부
	if (itemInfo.tBulletBoom != 3)
		m_tBulletInfo.tBulletBoom = itemInfo.tBulletBoom;

	m_fSpeed += itemInfo.tPlayerSpeed;
	if (m_fSpeed < 0.0f)
		m_fSpeed = 0.3f;

	m_bulletDelayCountMax += itemInfo.tBulletDelayCountMax;
	m_fCrossHairScaleMin += itemInfo.tCrossHairScaleMax;

	m_currHpMax += itemInfo.tPlayerHpMax;
	m_currHp += itemInfo.tPlayerHpMax;
	m_fPlayerScale += itemInfo.tPlayerScale;

	m_pItemInfo = new item;
	itemInfo.tIsGet = true;
	
	m_itemNum++; // 아이템 개수 추가
	if (m_itemNum > 4)
	{
		m_itemNumY++;
		m_itemNum = 1;
	}

	m_pItemInfo->init("ItemObject", itemInfo, NULL);
	m_pItemInfo->setItemIdleCurrY(img_ItemUiBg->getY() + (ITEM_BAG_Y) + (m_itemNumY * ITEM_BAG_Size_Y));
	m_pItemInfo->setItemIdleY(img_ItemUiBg->getY() + (ITEM_BAG_Y) + (m_itemNumY * ITEM_BAG_Size_Y));
	m_pItemInfo->setX(img_ItemUiBg->getX() + (ITEM_BAG_X) + ((m_itemNum - 1) * ITEM_BAG_Size_X));
	m_pItemInfo->setY(img_ItemUiBg->getY() + (ITEM_BAG_Y) + (m_itemNumY * ITEM_BAG_Size_Y));
	m_pItemInfo->ItemGetSetting();
	m_vecItem.push_back(m_pItemInfo);
}

void PlayerCharacter::PlayerDamage(int dam)
{
	m_currHp -= dam;
	if (m_currHp < 0)
	{
		m_isAlive = false;
	}
}

void PlayerCharacter::MoveActKeyInput()
{
	if (KEYMANAGER->isOnceKeyUp('A'))
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
	if (KEYMANAGER->isOnceKeyUp('D'))
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
	

	if (m_isRunState)
	{
		m_count++;
		if (m_count >= 20)
		{
			m_count = 0;
			m_isRunState = false;
		}
	}
}

void PlayerCharacter::itemUi(HDC hdc)
{
	for (m_iter = m_vecItem.begin(); m_iter != m_vecItem.end(); m_iter++)
	{
		if (!(*m_iter)->getIsAlive()) continue;

		(*m_iter)->render(hdc);
		(*m_iter)->update();
	}
}

void PlayerCharacter::PlayerInfoUi(HDC hdc)
{
	AddFontResourceA("BMHANNAAir_ttf.ttf");

	char szText[256];

	float TempYSize = 0.0f;
	// 이름 출력
	SetBkMode(hdc, TRANSPARENT);
	MY_UTIL::FontOption(hdc, 28, 0);
	SetTextColor(hdc, RGB(255, 255, 255));
	sprintf_s(szText, "[ 소녀 앨리스 ]");
	TextOut(hdc, img_ItemUiBg->getX() + PLAYER_STATE_X, img_ItemUiBg->getY() + PLAYER_STATE_Y, szText, strlen(szText));
	MY_UTIL::FontDelete(hdc);

	TempYSize = img_ItemUiBg->getY() + PLAYER_STATE_Y + 30.0f;

	// 캐릭터 능력치 출력
	MY_UTIL::FontOption(hdc, 18, 0);
	SetTextColor(hdc, RGB(255, 255, 255));
	sprintf_s(szText, "체력 : %d / %d", m_currHp, m_currHpMax);
	TextOut(hdc, img_ItemUiBg->getX() + PLAYER_STATE_X, TempYSize, szText, strlen(szText));

	TempYSize += 20.0f;
	sprintf_s(szText, "이동속도 : %.1f", m_fSpeed);
	TextOut(hdc, img_ItemUiBg->getX() + PLAYER_STATE_X, TempYSize, szText, strlen(szText));
	
	TempYSize += 20.0f;
	sprintf_s(szText, "크기 : %.1f", m_fPlayerScale);
	TextOut(hdc, img_ItemUiBg->getX() + PLAYER_STATE_X, TempYSize, szText, strlen(szText));

	// 블렛 능력치 출력
	sprintf_s(szText, "공격력 : %.1f", m_tBulletInfo.tDmage);
	TextOut(hdc, img_ItemUiBg->getX() + BULLET_STATE_X, img_ItemUiBg->getY() + BULLET_STATE_Y, szText, strlen(szText));
	TempYSize = img_ItemUiBg->getY() + BULLET_STATE_Y + 20.0f; // UI 위치 재정렬

	sprintf_s(szText, "발사개수 : %d", m_tBulletInfo.tBulletSetNum);
	TextOut(hdc, img_ItemUiBg->getX() + BULLET_STATE_X, TempYSize, szText, strlen(szText));
	TempYSize += 20.0f;

	sprintf_s(szText, "발사속도 : %d/s", m_bulletDelayCountMax);
	TextOut(hdc, img_ItemUiBg->getX() + BULLET_STATE_X, TempYSize, szText, strlen(szText));
	TempYSize += 20.0f;

	sprintf_s(szText, "마법속도 : %.1f", m_tBulletInfo.tMoveSpeed);
	TextOut(hdc, img_ItemUiBg->getX() + BULLET_STATE_X, TempYSize, szText, strlen(szText));
	TempYSize += 20.0f;

	sprintf_s(szText, "이동거리 : %.1f", m_tBulletInfo.tRange);
	TextOut(hdc, img_ItemUiBg->getX() + BULLET_STATE_X, TempYSize, szText, strlen(szText));
	TempYSize += 20.0f;

	sprintf_s(szText, "크기 : %.1f", m_tBulletInfo.tScale);
	TextOut(hdc, img_ItemUiBg->getX() + BULLET_STATE_X, TempYSize, szText, strlen(szText));
	TempYSize += 20.0f;

	sprintf_s(szText, "정확도 : %.1f", m_fCrossHairScaleMin);
	TextOut(hdc, img_ItemUiBg->getX() + BULLET_STATE_X, TempYSize, szText, strlen(szText));
	TempYSize += 20.0f;

	sprintf_s(szText, "넉백 : %.1f", m_tBulletInfo.tKnokBack);
	TextOut(hdc, img_ItemUiBg->getX() + BULLET_STATE_X, TempYSize, szText, strlen(szText));
	TempYSize += 20.0f;


	MY_UTIL::FontDelete(hdc);
}

void PlayerCharacter::movement()
{
	if (!m_isRectCol)
	{
		if (KEYMANAGER->isStayKeyDown('A'))
		{
			if (m_isRunStart) // 달리고 있다면
			{
				m_fX -= m_fSpeed * 1.5f;
				ani_left_Run->setFPS(20);
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
				ani_right_Run->setFPS(20);

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
	}
}

PlayerCharacter::PlayerCharacter()
{
}


PlayerCharacter::~PlayerCharacter()
{
}
