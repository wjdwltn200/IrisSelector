#include "stdafx.h"
#include "animation.h"
#include "monster.h"
#include "PlayerCharacter.h"
#include "bulletManger.h"
#include "PlayerCharacter.h"
#include "progressBar.h"


HRESULT monster::init(const char * strKey, tagMonInfo monInfo, bulletManger* bulletP, PlayerCharacter* playerPoint)
{
	//IMAGEMANAGER->addImage("BG_Beholder", "image/resources/monster_image/BG_Beholder_Run.bmp", 1860, 78, 12, 1, true, RGB(255, 0, 255),
	//	m_Mon.m_fX, m_Mon.m_fY);
	//IMAGEMANAGER->addImage("BG_Blue_Guardian", "image/resources/monster_image/BG_Blue_Guardian_Run.bmp", 930, 57, 6, 1, true, RGB(255, 0, 255),
	//	m_Mon.m_fX, m_Mon.m_fY);
	//IMAGEMANAGER->addImage("BG_Blue_Mindflayer","image/resources/monster_image/BG_Blue_Mindflayer_Run.bmp", 930, 54, 6, 1, true, RGB(255, 0, 255),
	//	m_Mon.m_fX, m_Mon.m_fY);
	//IMAGEMANAGER->addImage("BG_Bugman", "image/resources/monster_image/BG_Bugman_Run.bmp", 620, 61, 4, 1, true, RGB(255, 0, 255),
	//	m_Mon.m_fX, m_Mon.m_fY);
	//IMAGEMANAGER->addImage("BG_Cetus", "image/resources/monster_image/BG_Cetus_Run.bmp", 620, 37, 4, 1, true, RGB(255, 0, 255),
	//	m_Mon.m_fX, m_Mon.m_fY);
	//IMAGEMANAGER->addImage("BG_Coven", "image/resources/monster_image/BG_Coven_Run.bmp", 620, 33, 4, 1, true, RGB(255, 0, 255),
	//	m_Mon.m_fX, m_Mon.m_fY);
	//IMAGEMANAGER->addImage("BG_Cow", "image/resources/monster_image/BG_Cow.bmp", 620, 28, 4, 1, true, RGB(255, 0, 255),
	//	m_Mon.m_fX, m_Mon.m_fY);
	//IMAGEMANAGER->addImage("BG_Cyclops", "image/resources/monster_image/BG_Cyclops.bmp", 930, 46, 6, 1, true, RGB(255, 0, 255),
	//	m_Mon.m_fX, m_Mon.m_fY);
	//IMAGEMANAGER->addImage("BG_Dark_Lord", "image/resources/monster_image/BG_Dark_Lord.bmp", 620, 78, 4, 1, true, RGB(255, 0, 255),
	//	m_Mon.m_fX, m_Mon.m_fY);
	//IMAGEMANAGER->addImage("BG_Dog", "image/resources/monster_image/BG_Dog.bmp", 465, 37, 3, 1, true, RGB(255, 0, 255),
	//	m_Mon.m_fX, m_Mon.m_fY);
	//IMAGEMANAGER->addImage("BG_Eye_Slime", "image/resources/monster_image/BG_Eye_Slime_Run.bmp", 465, 39, 3, 1, true, RGB(255, 0, 255),
	//	m_Mon.m_fX, m_Mon.m_fY);
	//IMAGEMANAGER->addImage("BG_Faun_Archer", "image/resources/monster_image/BG_Faun_Archer_Run.bmp", 930, 46, 6, 1, true, RGB(255, 0, 255),
	//	m_Mon.m_fX, m_Mon.m_fY);
	//IMAGEMANAGER->addImage("BG_Firewolf", "image/resources/monster_image/BG_Firewolf.bmp", 620, 46, 4, 1, true, RGB(255, 0, 255),
	//	m_Mon.m_fX, m_Mon.m_fY);
	//IMAGEMANAGER->addImage("BG_Gargoyle", "image/resources/monster_image/BG_Gargoyle.bmp", 620, 65, 4, 1, true, RGB(255, 0, 255),
	//	m_Mon.m_fX, m_Mon.m_fY);
	//IMAGEMANAGER->addImage("BG_Giant_Run", "image/resources/monster_image/BG_Giant_Run.bmp", 930, 63, 6, 1, true, RGB(255, 0, 255),
	//	m_Mon.m_fX, m_Mon.m_fY);
	//IMAGEMANAGER->addImage("BG_Gnome_Run", "image/resources/monster_image/BG_Gnome_Run.bmp", 930, 26, 6, 1, true, RGB(255, 0, 255),
	//	m_Mon.m_fX, m_Mon.m_fY);
	//IMAGEMANAGER->addImage("BG_Igor", "image/resources/monster_image/BG_Igor.bmp", 930, 44, 6, 1, true, RGB(255, 0, 255),
	//	m_Mon.m_fX, m_Mon.m_fY);
	//IMAGEMANAGER->addImage("BG_Itchy", "image/resources/monster_image/BG_Itchy.bmp", 930, 37, 6, 1, true, RGB(255, 0, 255),
	//	m_Mon.m_fX, m_Mon.m_fY);
	//IMAGEMANAGER->addImage("BG_Knife_dude", "image/resources/monster_image/BG_Knife_dude.bmp", 930, 60, 6, 1, true, RGB(255, 0, 255),
	//	m_Mon.m_fX, m_Mon.m_fY);

	m_pBulletMag = bulletP;
	m_PlayerCharPoint = playerPoint;

	// Monster Bullet 기본 셋팅 (메인)
	memset(&m_tBulletInfo, 0, sizeof(m_tBulletInfo));

	m_tBulletInfo.tIsAlive = true;
	m_tBulletInfo.tBulletSetNum = 1;
	m_tBulletInfo.tScale = 2.0f;
	m_tBulletInfo.tScaleMax = m_tBulletInfo.tScale * 2.0f;
	m_tBulletInfo.tRadius = 0.5f;
	m_tBulletInfo.tExpRadius = 0.5f;
	m_tBulletInfo.tRange = 200.0f;
	m_tBulletInfo.tBulletBoom = true;

	m_tBulletInfo.tDmage = 1.0f + m_tMonInfo.tDamageSub;
	m_tBulletInfo.tKnokBack = 0.0f;
	m_tBulletInfo.tMoveSpeed = 5.0f;

	m_tBulletInfo.tBoomType = BULLET_BOOM_TYPE::ANGLE_LINE;
	m_tBulletInfo.tShootType = BULLET_SHOOT_TYPE::ONE_SHOOT;
	m_tBulletInfo.tMasterType = BULLET_MASTER_TYPE::MONSTER;
	m_tBulletInfo.tMoveActType = BULLET_MOVE_ACT_TYPE::BULLET_MOVE_ACT_NUM;
	m_tBulletInfo.tImageType = BULLET_IMAGE_TYPE::COLOR_R;
	m_tBulletInfo.tMoveType = BULLET_MOVE_TYPE::ONE_LINE;

	// 서브 탄환 (이중 폭발)

	memset(&m_tBulletInfoSub, 0, sizeof(m_tBulletInfoSub));

	m_tBulletInfoSub.tIsAlive = true;
	m_tBulletInfoSub.tBulletSetNum = 2;
	m_tBulletInfoSub.tScale = 1.0f;
	m_tBulletInfoSub.tScaleMax = m_tBulletInfo.tScale * 2.0f;
	m_tBulletInfoSub.tRadius = 0.5f;
	m_tBulletInfoSub.tExpRadius = 0.5f;
	m_tBulletInfoSub.tRange = 200.0f;
	m_tBulletInfoSub.tBulletBoom = false;

	m_tBulletInfoSub.tDmage = 1.0f + m_tMonInfo.tDamageSub;
	m_tBulletInfoSub.tKnokBack = 5.0f;
	m_tBulletInfoSub.tMoveSpeed = 5.0f;

	m_tBulletInfoSub.tBoomType = BULLET_BOOM_TYPE::ANGLE_LINE;
	m_tBulletInfoSub.tShootType = BULLET_SHOOT_TYPE::ONE_SHOOT;
	m_tBulletInfoSub.tMasterType = BULLET_MASTER_TYPE::MONSTER;
	m_tBulletInfoSub.tMoveActType = BULLET_MOVE_ACT_TYPE::BULLET_MOVE_ACT_NUM;
	m_tBulletInfoSub.tImageType = BULLET_IMAGE_TYPE::COLOR_R;
	m_tBulletInfoSub.tMoveType = BULLET_MOVE_TYPE::ONE_LINE;

	m_tBulletInfoSubPoint = &m_tBulletInfoSub;

	m_monsterType = IMAGEMANAGER->findImage(strKey);
	m_monsterMove = new animation;
	m_monsterMove->init(m_monsterType->getWidth(), m_monsterType->getHeight(),
		m_monsterType->getFrameWidth(), m_monsterType->getFrameHeight());

	// 몬스터 정보 초기화
	memset(&m_tMonInfo.m_rc, 0, sizeof(m_tMonInfo.m_rc));
	memset(&m_tMonInfo, 0, sizeof(m_tMonInfo));
	m_tMonInfo.m_rc = RectMakeCenter(m_tMonInfo.tPosX, m_tMonInfo.tPosY, 100, 100);
	m_tMonInfo.tIsAlive = monInfo.tIsAlive;
	m_tMonInfo.tHp = monInfo.tHp;
	m_tMonInfo.tHpMax= monInfo.tHpMax = 100.0f;
	m_tMonInfo.tPosX = monInfo.tPosX;
	m_tMonInfo.tPosY = monInfo.tPosY;
	m_tMonInfo.tFireCount = monInfo.tFireCount;
	m_tMonInfo.tFireDelay = monInfo.tFireDelay;
	m_tMonInfo.tFireAngle = monInfo.tFireAngle;
	m_tMonInfo.tMoveAngle = monInfo.tMoveAngle;
	m_tMonInfo.tRadius = 50.0f;//monInfo.tRadius;
	m_tMonInfo.tScale = monInfo.tScale;
	m_tMonInfo.tScaleMax = monInfo.tScaleMax;
	m_tMonInfo.tUnKnokBack = monInfo.tUnKnokBack;
	m_tMonInfo.tMoveSpeed = monInfo.tMoveSpeed;

	m_tMonInfo.tHealingCount = monInfo.tHealingCount = 1;
	m_tMonInfo.tWidth = monInfo.tWidth;
	m_tMonInfo.tHeight = monInfo.tHeight;
	m_tMonInfo.tHp = monInfo.tHp;
	m_tMonInfo.tIsBoom = monInfo.tIsBoom;
	m_tMonInfo.tDamageSub = monInfo.tDamageSub;
	m_tMonInfo.tDef = monInfo.tDef = 0.0f;
	m_tMonInfo.tHealing = monInfo.tHealing;
	m_tMonInfo.tMoveType = monInfo.tMoveType;
	
	m_monsterMove->setDefPlayFrame(false, true);
	m_monsterMove->setFPS(10);
	m_monsterMove->start();

	m_HealingCount = 0;
	m_count = 0;
	m_isHealing = false;
	m_isMove = false;
	m_SubDamgeAdd = 5.0f;

	
	return S_OK;
}

void monster::release()
{
}

void monster::Move(int m_moveTypeNum)//int m_moveTypeNum)
{
	if (!m_tMonInfo.tIsAlive) return;
			m_tMonInfo.m_rc = RectMakeCenter(m_tMonInfo.tPosX, m_tMonInfo.tPosY, m_tMonInfo.tRadius * 2.0f, m_tMonInfo.tRadius * 2.0f);
			m_tMonInfo.tMoveAngle = MY_UTIL::getAngle(m_tMonInfo.tPosX, m_tMonInfo.tPosY, m_PlayerCharPoint->getX(), m_PlayerCharPoint->getY());
	switch (m_moveTypeNum)
	{
	case MONSTER_MOVE::MONSTER_CRAWL :
		if (m_tMonInfo.m_rc.left + 150 < m_PlayerCharPoint->getRect().left
			|| m_tMonInfo.m_rc.right - 150 > m_PlayerCharPoint->getRect().right
			|| m_tMonInfo.m_rc.bottom + 150 < m_PlayerCharPoint->getRect().bottom
			|| m_tMonInfo.m_rc.top - 150 > m_PlayerCharPoint->getRect().top)
		{
			if (m_isMove)
			{
				m_tMonInfo.tPosX += cosf(m_tMonInfo.tMoveAngle) * (m_tMonInfo.tMoveSpeed * 2);
				m_tMonInfo.tPosY += -sinf(m_tMonInfo.tMoveAngle) * (m_tMonInfo.tMoveSpeed * 2);
				m_monsterMove->setFPS(10);
			}
			m_count++;
			if (m_count >= 20)
			{
				m_count = 0;
				m_isMove = RANDOM->getInt(2);
				m_monsterMove->setFPS(0);
				//m_monsterMove->getFramePos();
			}
		}
		break;
	case MONSTER_MOVE::MONSTER_FLY :
			if (m_tMonInfo.m_rc.left + 150 < m_PlayerCharPoint->getRect().left
				|| m_tMonInfo.m_rc.right - 150 > m_PlayerCharPoint->getRect().right
				|| m_tMonInfo.m_rc.bottom + 150 < m_PlayerCharPoint->getRect().bottom
				|| m_tMonInfo.m_rc.top - 150 > m_PlayerCharPoint->getRect().top)
			{
				if (m_Follow)
				{
					m_tMonInfo.tPosX += cosf(m_tMonInfo.tMoveAngle) * (m_tMonInfo.tMoveSpeed + RANDOM->getFromFloatTo(0, 5));
					m_tMonInfo.tPosY += -sinf(m_tMonInfo.tMoveAngle) * (m_tMonInfo.tMoveSpeed + RANDOM->getFromFloatTo(0, 5));
				}
			}
			else 
			{
				m_Follow = false;
			}
			if (!(m_tMonInfo.m_rc.left + 300 < m_PlayerCharPoint->getRect().left
				|| m_tMonInfo.m_rc.right - 300 > m_PlayerCharPoint->getRect().right
				|| m_tMonInfo.m_rc.bottom + 300 < m_PlayerCharPoint->getRect().bottom
				|| m_tMonInfo.m_rc.top - 300 > m_PlayerCharPoint->getRect().top) && !m_Follow)
			{
				m_tMonInfo.tPosX -= cosf(m_tMonInfo.tMoveAngle) * (m_tMonInfo.tMoveSpeed + RANDOM->getFromFloatTo(0, 5));
				m_tMonInfo.tPosY -= -sinf(m_tMonInfo.tMoveAngle) * (m_tMonInfo.tMoveSpeed + RANDOM->getFromFloatTo(0, 5));
			}
			else
			{
				m_Follow = true;
			}
		break;
	case MONSTER_MOVE::MONSTER_RUN :

		break;
	case MONSTER_MOVE::MONSTER_WALK :

		break;
	}
}

void monster::fireAtk()
{
	if (!m_tMonInfo.tIsAlive) return;

	if (m_tMonInfo.tFireCount == 0)
	{
		m_pBulletMag->fire("임시",
			m_tMonInfo.tPosX,
			m_tMonInfo.tPosY,
			m_tMonInfo.tFireAngle,
			&m_tBulletInfo,
			&m_tBulletInfoSub);
		m_tMonInfo.tFireCount = m_tMonInfo.tFireDelay;
	}
	m_tMonInfo.tFireCount--;

}

void monster::knokback(float playerkuokback, float monsterHitRecovery)
{
	playerkuokback -= monsterHitRecovery;
		if (playerkuokback > 0.0f)
		{
			m_Follow = false;
			m_tMonInfo.tPosX -= cosf(m_tMonInfo.tMoveAngle) * (m_tMonInfo.tMoveSpeed) + playerkuokback;
			m_tMonInfo.tPosY -= -sinf(m_tMonInfo.tMoveAngle) * (m_tMonInfo.tMoveSpeed) + playerkuokback;
			m_Follow = true;
		}

}

void monster::Damge(float dam)
{
	// 데미지가 받을때 방어력 적용

	dam -= m_tMonInfo.tDef;
	if (m_isHealing)
	{
		m_SubDamgeAdd += dam;
	}
	else
	{
		m_SubDamgeAdd = 0.0f;
	}
	m_tMonInfo.tHp -= dam;

	if (m_tMonInfo.tHp < 0.0f) // 사망처리
	{
		m_tMonInfo.tIsAlive = false;
		m_tMonInfo.tDef = 5.0f;
	}
}

void monster::TypeSub(float minGague, float maxGauge, int minSubInfo, int maxSubInfo, bool isTrance, int life)
{
	m_tMonInfo.tTrance = isTrance;
	m_tMonInfo.tIslife = life;
	m_tMonInfo.tminGaugeSub = minGague;
	m_tMonInfo.tmaxGaugeSub = maxGauge;
	m_tMonInfo.tminGaugeInfo = minSubInfo;
	m_tMonInfo.tmaxGaugeInfo = maxSubInfo;
	if (m_isHealing && m_HealingCount <= m_tMonInfo.tHealingCount)
	{
		if (m_tMonInfo.tHp <= m_tMonInfo.tHpMax)
		{
		m_count++;
			if (m_count >= 10)
			{
				m_count = 0;
				m_tMonInfo.tHealing = 5.0f;
				if (!(m_tMonInfo.tHp > m_tMonInfo.tHpMax - m_SubDamgeAdd))
				{
					m_tMonInfo.tHp += m_tMonInfo.tHealing;
				}
				else
				{
				m_isHealing = false;
				m_HealingCount++;
				}
			}
		}
	}
	if (m_tMonInfo.tHp <= m_tMonInfo.tminGaugeSub)
	{
		switch (minSubInfo)
		{
		case MONSTER_SUB::MONSTER_ATT_UP:
			m_tMonInfo.tDamageSub = 10.0f;
			break;
		case MONSTER_SUB::MONSTER_DEF_UP:
			m_tMonInfo.tDef = 4.0f;
			break;
		case MONSTER_SUB::MONSTER_SPEED_UP:
			m_tMonInfo.tMoveSpeed = 10.0f;
			break;
		case MONSTER_SUB::MONSTER_POWER_UP:
			m_tMonInfo.tDamageSub += 10.0f;
			m_tMonInfo.tHp -= 5.0f;
			break;
		}
	}
	if (m_tMonInfo.tHp <= m_tMonInfo.tmaxGaugeSub)
	{
		switch (maxSubInfo)
		{
		case MONSTER_SUB::MONSTER_HP_HEALING:
			m_isHealing = true;
			break;
		case MONSTER_SUB::MONSTER_RESURRECTION:
			if (m_tMonInfo.tTrance == true)
			{
				if (m_tMonInfo.tIsAlive == false && m_lifeCount == 0)
				{
					m_lifeCount++;
					m_tMonInfo.tIsAlive = true;
					m_tMonInfo.tHp = 100.0f;
				}
				else
					m_tMonInfo.tIsAlive = false;
			}
			else if (m_tMonInfo.tIsAlive == false && m_lifeCount <= m_tMonInfo.tIslife)
			{
				m_lifeCount++;
				m_tMonInfo.tIsAlive = true;
				m_tMonInfo.tHp = 100.0f;
			}
			break;
		case MONSTER_SUB::MONSTER_BOOM:
			if (m_tMonInfo.tIsAlive == false)
			{
				m_tMonInfo.tIsBoom = true;
			}
			break;
		}
	}
}

void monster::update()
{	

	if (!m_tMonInfo.tIsAlive) return;

	m_tMonInfo.tFireAngle = MY_UTIL::getAngle(m_tMonInfo.tPosX, m_tMonInfo.tPosY, m_PlayerCharPoint->getX(), m_PlayerCharPoint->getY());
	Move(m_tMonInfo.tMoveType);
	fireAtk();
	m_monsterMove->frameUpdate();
}

void monster::render(HDC hdc)
{
	//Ellipse(hdc, m_tMonInfo.m_rc.left, m_tMonInfo.m_rc.top, m_tMonInfo.m_rc.right, m_tMonInfo.m_rc.bottom);
	EllipseMakeCenter(hdc, m_tMonInfo.tPosX, m_tMonInfo.tPosY, 10, 10);

	m_monsterType->aniRender(hdc,
		m_tMonInfo.tPosX - (m_monsterType->getFrameWidth() / 2) * m_tMonInfo.tScale,
		m_tMonInfo.tPosY - (m_monsterType->getFrameHeight() / 2) * m_tMonInfo.tScale,
		m_monsterMove, m_tMonInfo.tScale, true, 255);
	
}

monster::monster()
{
}


monster::~monster()
{
}
