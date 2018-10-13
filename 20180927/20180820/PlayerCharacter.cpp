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

	for (int i = 0; i < 10; i++)
	{
		img_HpPoint[i] = IMAGEMANAGER->findImage("Player_HP_Point");
	}

	m_vecItem.reserve(30); // ���� ������


	m_currHp = BAES_HP;
	m_currHpMax = m_currHp;
	m_isAlive = true;
	m_isItemUi = false;

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

	// ������ ����
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

	// ������ ��

	// Player �⺻ ���� (����)
	memset(&m_tBulletInfo, 0, sizeof(m_tBulletInfo));

	m_tBulletInfo.tIsAlive = true;
	m_tBulletInfo.tBulletSetNum = 3;
	m_tBulletInfo.tScale = 1.0f;
	m_tBulletInfo.tScaleMax = m_tBulletInfo.tScale * 2.0f;
	m_tBulletInfo.tRadius = 0.5f;
	m_tBulletInfo.tExpRadius = 0.5f;
	m_tBulletInfo.tRange = 200.0f;
	m_tBulletInfo.tBulletBoom = true;

	m_tBulletInfo.tDmage = 10.0f;
	m_tBulletInfo.tKnokBack = 5.0f;
	m_tBulletInfo.tMoveSpeed = 20.0f;
	m_tBulletInfo.tScatter = m_fCrossHairScale * 10.0f;

	m_tBulletInfo.tBoomType = BULLET_BOOM_TYPE::ANGLE_LINE;
	m_tBulletInfo.tShootType = BULLET_SHOOT_TYPE::CUFF_SHOOT;
	m_tBulletInfo.tMasterType = BULLET_MASTER_TYPE::PLAYER;
	m_tBulletInfo.tMoveActType = BULLET_MOVE_ACT_TYPE::BULLET_MOVE_ACT_NUM;
	m_tBulletInfo.tImageType = BULLET_IMAGE_TYPE::COLOR_Y;
	m_tBulletInfo.tMoveType = BULLET_MOVE_TYPE::CENTER_CENTRIFUGAL;
	
	m_tBulletInfoPoint = &m_tBulletInfo;

	// ���� źȯ (���� ����)
	memset(&m_tBulletInfoSub, 0, sizeof(m_tBulletInfoSub));

	m_tBulletInfoSub.tIsAlive = true;
	m_tBulletInfoSub.tBulletSetNum = 1;
	m_tBulletInfoSub.tScale = 1.0f;
	m_tBulletInfoSub.tScaleMax = m_tBulletInfo.tScale * 2.0f;
	m_tBulletInfoSub.tRadius = 0.5f;
	m_tBulletInfoSub.tExpRadius = 0.5f;
	m_tBulletInfoSub.tRange = 300.0f;
	m_tBulletInfoSub.tBulletBoom = true;

	m_tBulletInfoSub.tDmage = 5.0f;
	m_tBulletInfoSub.tKnokBack = 5.0f;
	m_tBulletInfoSub.tMoveSpeed = 10.0f;
	m_tBulletInfoSub.tScatter = 0.0f;

	m_tBulletInfoSub.tBoomType = BULLET_BOOM_TYPE::MOUSE_POINT;
	m_tBulletInfoSub.tShootType = BULLET_SHOOT_TYPE::LINE_SHOOT;
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
	// �Ѿ� �߻�
	if (KEYMANAGER->isOnceKeyDown(VK_RBUTTON)) // �׽�Ʈ ��
	{
		//m_fCrossHairScaleMin += 0.1f;
		//m_currHpMax += 2;
		//m_currHp++;
		//m_currHp--;
	}

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
					(*m_pBulletMag)->fire("�ӽ�", m_fX, m_fY, MY_UTIL::getMouseAngle(m_fX, m_fY), m_tBulletInfoPoint, m_tBulletInfoSubPoint);
				}
				else // �Ѿ� ���� ��ŭ ������ �и�
				{
					for (int i = 0; i < m_tBulletInfo.tBulletSetNum; i++)
					{
						(*m_pBulletMag)->fire("�ӽ�", m_fX, m_fY, MY_UTIL::getMouseAngle(m_fX, m_fY) - (i * (PI / 180.0f * (30.0f))) - ((PI / 180.0f) * MY_UTIL::getMouseAngle(m_fX, m_fY) - ((m_tBulletInfo.tBulletSetNum - 1) * (PI / 180.0f * (30.0f)))) / 2, m_tBulletInfoPoint, m_tBulletInfoSubPoint);
					}
				}
			}
			else if (m_tBulletInfo.tShootType == BULLET_SHOOT_TYPE::CUFF_SHOOT)
			{
				if (m_tBulletInfo.tBulletSetNum == 1)
				{
					(*m_pBulletMag)->fire("�ӽ�", m_fX, m_fY, MY_UTIL::getMouseAngle(m_fX, m_fY), m_tBulletInfoPoint, m_tBulletInfoSubPoint);
				}
				else // �Ѿ� ���� ��ŭ ������ �и�
				{
					for (int i = 0; i < m_tBulletInfo.tBulletSetNum; i++)
					{
						(*m_pBulletMag)->fire("�ӽ�", m_fX, m_fY, MY_UTIL::getMouseAngle(m_fX, m_fY) + (i * (PI / 180.0f * (360.0f / m_tBulletInfo.tBulletSetNum))), m_tBulletInfoPoint, m_tBulletInfoSubPoint);
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
		if (m_isRunStart) // �޸��� �ִٸ�
		{
			m_fX -= m_fSpeed * 1.5f;
			ani_left_Run->setFPS(30);
		}
		else // �޸��� �ʰ� �ִٸ�
		{
			ani_left_Run->setFPS(10);
			m_fX -= m_fSpeed;
		}
	}
	if (KEYMANAGER->isStayKeyDown('D'))
	{
		if (m_isRunStart) // �޸��� �ִٸ�
		{
			m_fX += m_fSpeed * 1.5f;
			ani_right_Run->setFPS(30);

		}
		else // �޸��� �ʰ� �ִٸ�
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

	m_rc = RectMakeCenter(m_fX, m_fY, img_player->getFrameWidth(), img_player->getFrameHeight());

	MoveActKeyInput();

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
		(KEYMANAGER->isStayKeyDown('A') && (KEYMANAGER->isStayKeyDown('W') || KEYMANAGER->isStayKeyDown('S'))))) // ���� �밢��
	{
		m_Direction = true;
		img_left_Run->aniRender(hdc, m_fX - (img_left_Run->getFrameWidth() / 2), m_fY - (img_left_Run->getFrameHeight() / 2), ani_left_Run, 1.0f, true, 255);
	}
	else if (KEYMANAGER->isStayKeyDown('D') ||
		(KEYMANAGER->isStayKeyDown('D') && (KEYMANAGER->isStayKeyDown('W') || KEYMANAGER->isStayKeyDown('S')))) // ������ �밢��
	{
		m_Direction = false;
		img_right_Run->aniRender(hdc, m_fX - (img_right_Run->getFrameWidth() / 2), m_fY - (img_right_Run->getFrameHeight() / 2), ani_right_Run, 1.0f, true, 255);
	}
	else if (m_Direction && ((KEYMANAGER->isStayKeyDown('W')) || (KEYMANAGER->isStayKeyDown('S')))) // ���� ��
	{
		m_Direction = true;
		img_left_Run->aniRender(hdc, m_fX - (img_left_Run->getFrameWidth() / 2), m_fY - (img_left_Run->getFrameHeight() / 2), ani_left_Run, 1.0f, true, 255);
	}
	else if (!m_Direction && ((KEYMANAGER->isStayKeyDown('W')) || (KEYMANAGER->isStayKeyDown('S')))) // ������ �Ʒ�
	{
		m_Direction = false;
		img_right_Run->aniRender(hdc, m_fX - (img_right_Run->getFrameWidth() / 2), m_fY - (img_right_Run->getFrameHeight() / 2), ani_right_Run, 1.0f, true, 255);
	}
	else if (m_Direction) // ���̵�
	{
		img_player->aniRender(hdc, m_fX - (img_player->getFrameWidth() / 2), m_fY - (img_player->getFrameHeight() / 2), ani_left_stay, 1.0f, true, 255);
	}
	else
	{
		img_player->aniRender(hdc, m_fX - (img_player->getFrameWidth() / 2), m_fY - (img_player->getFrameHeight() / 2), ani_right_stay, 1.0f, true, 255);

	}

	//Rectangle(hdc, m_rc.left, m_rc.top, m_rc.right, m_rc.bottom);

	if (m_isItemUi) // ���� ����
	{
		img_ItemUiBg->render(hdc, (WINSIZEX / 2) - (img_ItemUiBg->getFrameWidth() / 2), (WINSIZEX / 2) - (img_ItemUiBg->getFrameHeight() / 2));
		itemUi(hdc);
		PlayerInfoUi(hdc);
	}

	img_CrossHair->aniRender(hdc, g_ptMouse.x - (img_CrossHair->getFrameWidth() / 2) * m_fCrossHairScale, g_ptMouse.y - (img_CrossHair->getFrameHeight() / 2) * m_fCrossHairScale, ani_CrossHair, m_fCrossHairScale);


}

void PlayerCharacter::getItem(tagItemInfo itemInfo)
{
	if (itemInfo.tBulletSetNum < 0.0f)
	{
		m_tBulletInfo.tBulletSetNum += itemInfo.tBulletSetNum;
	}
	else
	{
		m_tBulletInfo.tBulletSetNum += itemInfo.tBulletSetNum;
	}

	if (itemInfo.tRange < 0.0f)
	{
		m_tBulletInfo.tRange += itemInfo.tRange;
	}
	else
	{
		m_tBulletInfo.tRange += itemInfo.tRange;
	}

	if (itemInfo.tDmage < 0.0f)
	{
		m_tBulletInfo.tDmage += itemInfo.tDmage;
	}
	else
	{
		m_tBulletInfo.tDmage += itemInfo.tDmage;
	}

	if (itemInfo.tKnokBack < 0.0f)
	{
		m_tBulletInfo.tKnokBack += itemInfo.tKnokBack;
	}
	else
	{
		m_tBulletInfo.tKnokBack += itemInfo.tKnokBack;
	}

	if (itemInfo.tMoveSpeed < 0.0f)
	{
		m_tBulletInfo.tMoveSpeed += itemInfo.tMoveSpeed;
	}
	else
	{
		m_tBulletInfo.tMoveSpeed += itemInfo.tMoveSpeed;
	}

	if (itemInfo.tBulletBoom != 3)
		m_tBulletInfo.tBulletBoom = itemInfo.tBulletBoom;

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

	if (itemInfo.tPlayerSpeed < 0.0f)
	{
		m_fSpeed += itemInfo.tPlayerSpeed;
		if (m_fSpeed < 0.0f)
		{
			m_fSpeed = 0.3f;
		}
	}
	else
	{
		m_fSpeed += itemInfo.tPlayerSpeed;
	}

	if (itemInfo.tBulletDelayCountMax < 0.0f)
	{
		m_bulletDelayCountMax += itemInfo.tBulletDelayCountMax;
	}
	else
	{
		m_bulletDelayCountMax += itemInfo.tBulletDelayCountMax;
	}

	if (itemInfo.tCrossHairScaleMax < 0.0f)
	{
		m_fCrossHairScaleMax += itemInfo.tCrossHairScaleMax;
	}
	else
	{
		m_fCrossHairScaleMax += itemInfo.tCrossHairScaleMax;
	}

	if (itemInfo.tPlayerHpMax < 0.0f)
	{
		m_currHpMax += itemInfo.tPlayerHpMax;
		m_currHp += itemInfo.tPlayerHpMax;
	}
	else
	{
		m_currHpMax += itemInfo.tPlayerHpMax;
		m_currHp += itemInfo.tPlayerHpMax;
	}

	m_pItemInfo = new item;
	itemInfo.tIsGet = true;
	
	m_itemNum++; // ������ ���� �߰�
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

	/*switch (itemInfo)
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
	}*/
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
	if (KEYMANAGER->isStayKeyDown('A'))
	{
		if (m_isRunStart) // �޸��� �ִٸ�
		{
			m_fX -= m_fSpeed * 1.5f;
			ani_left_Run->setFPS(20);
		}
		else // �޸��� �ʰ� �ִٸ�
		{
			ani_left_Run->setFPS(10);
			m_fX -= m_fSpeed;
		}
	}
	if (KEYMANAGER->isStayKeyDown('D'))
	{
		if (m_isRunStart) // �޸��� �ִٸ�
		{
			m_fX += m_fSpeed * 1.5f;
			ani_right_Run->setFPS(20);

		}
		else // �޸��� �ʰ� �ִٸ�
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
	char szText[256];

	// TRANSPARENT : ����, OPAQUE : ������
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

PlayerCharacter::PlayerCharacter()
{
}


PlayerCharacter::~PlayerCharacter()
{
}
