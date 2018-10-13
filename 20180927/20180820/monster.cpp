#include "stdafx.h"
#include "animation.h"
#include "monster.h"
#include "PlayerCharacter.h"
#include "bulletManger.h"
#include "PlayerCharacter.h"
#include "progressBar.h"


HRESULT monster::init(const char * strKey, tagMonInfo monInfo, bulletManger* bulletP, PlayerCharacter* playerPoint)
{
	m_pBulletMag = bulletP;
	m_PlayerCharPoint = playerPoint;

	// Monster Bullet �⺻ ���� (����)
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
	m_tBulletInfo.tKnokBack = 5.0f;
	m_tBulletInfo.tMoveSpeed = 5.0f;

	m_tBulletInfo.tBoomType = BULLET_BOOM_TYPE::ANGLE_LINE;
	m_tBulletInfo.tShootType = BULLET_SHOOT_TYPE::ONE_SHOOT;
	m_tBulletInfo.tMasterType = BULLET_MASTER_TYPE::MONSTER;
	m_tBulletInfo.tMoveActType = BULLET_MOVE_ACT_TYPE::BULLET_MOVE_ACT_NUM;
	m_tBulletInfo.tImageType = BULLET_IMAGE_TYPE::COLOR_R;
	m_tBulletInfo.tMoveType = BULLET_MOVE_TYPE::ONE_LINE;

	// ���� źȯ (���� ����)

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

	m_player = new PlayerCharacter;

	m_monsterType = IMAGEMANAGER->findImage(strKey);
	m_monsterMove = new animation;
	m_monsterMove->init(m_monsterType->getWidth(), m_monsterType->getHeight(),
		m_monsterType->getFrameWidth(), m_monsterType->getFrameHeight());

	// ���� ���� �ʱ�ȭ
	memset(&m_tMonInfo.m_rc, 0, sizeof(m_tMonInfo.m_rc));
	memset(&m_tMonInfo, 0, sizeof(m_tMonInfo));
	m_tMonInfo.m_rc = RectMakeCenter(m_tMonInfo.tPosX, m_tMonInfo.tPosY, 100, 100);
	m_tMonInfo.tIsAlive = monInfo.tIsAlive;
	m_tMonInfo.tHp = monInfo.tHp;
	m_tMonInfo.tHpMax= monInfo.tHpMax;
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

	m_tMonInfo.tWidth = monInfo.tWidth;
	m_tMonInfo.tHeight = monInfo.tHeight;
	m_tMonInfo.tHp = monInfo.tHp;
	m_tMonInfo.tIsBoom = monInfo.tIsBoom;
	m_tMonInfo.tDamageSub = monInfo.tDamageSub;
	
	m_monsterMove->setDefPlayFrame(false, true);
	m_monsterMove->setFPS(10);
	m_monsterMove->start();


	m_progressBar = new progressBar;

	return S_OK;
}

void monster::release()
{
}

void monster::fireAtk()
{
	if (!m_tMonInfo.tIsAlive) return;

	if (m_tMonInfo.tFireCount == 0)
	{
		m_pBulletMag->fire("�ӽ�",
			m_tMonInfo.tPosX,
			m_tMonInfo.tPosY,
			m_tMonInfo.tFireAngle,
			&m_tBulletInfo,
			&m_tBulletInfoSub);
		m_tMonInfo.tFireCount = m_tMonInfo.tFireDelay;
	}
	m_tMonInfo.tFireCount--;

}

void monster::Damge(float dam)
{
	m_tMonInfo.tHp -= dam;

	if (m_tMonInfo.tHp < 0.0f) // ���ó��
	{
		m_tMonInfo.tIsAlive = false;
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
	if (m_tMonInfo.tHp <= m_tMonInfo.tminGaugeSub)
	{
		switch (minSubInfo)
		{
		case MONSTER_SUB::MONSTER_ATT_UP:
			m_tMonInfo.tDamageSub = 10.0f;
			break;
		case MONSTER_SUB::_MONSTER_DEF_UP:
			m_tMonInfo.tHp -= 5.0f;
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
	else if (m_tMonInfo.tHp <= m_tMonInfo.tmaxGaugeSub)
	{
		switch (maxSubInfo)
		{
		case MONSTER_SUB::MONSTER_HP_HEALING:
			m_tMonInfo.tHp += 5.0f;
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
	//Move();
	fireAtk();
	m_monsterMove->frameUpdate();
}

void monster::render(HDC hdc)
{
	Ellipse(hdc, m_tMonInfo.m_rc.left, m_tMonInfo.m_rc.top, m_tMonInfo.m_rc.right, m_tMonInfo.m_rc.bottom);
	//EllipseMakeCenter(hdc, m_tMonInfo.tPosX, m_tMonInfo.tPosY, 10, 10);

	m_monsterType->aniRender(hdc,
		m_tMonInfo.tPosX - (m_monsterType->getFrameWidth() / 2) * m_tMonInfo.tScale,
		m_tMonInfo.tPosY - (m_monsterType->getFrameHeight() / 2) * m_tMonInfo.tScale,
		m_monsterMove, m_tMonInfo.tScale, true, 255);
	m_progressBar->render(hdc);
	
}

monster::monster()
{
}


monster::~monster()
{
}
