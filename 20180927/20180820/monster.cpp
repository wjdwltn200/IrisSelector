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
	m_tBulletInfo.tScale = 1.0f;
	m_tBulletInfo.tScaleMax = m_tBulletInfo.tScale * 2.0f;
	m_tBulletInfo.tRadius = 0.5f;
	m_tBulletInfo.tExpRadius = 0.5f;
	m_tBulletInfo.tRange = 200.0f;
	m_tBulletInfo.tBulletBoom = true;

	m_tBulletInfo.tDmage = 10.0f + m_tMonInfo.tDamageSub;
	m_tBulletInfo.tKnokBack = 5.0f;
	m_tBulletInfo.tMoveSpeed = 5.0f;

	m_tBulletInfo.tBoomType = BULLET_BOOM_TYPE::ANGLE_LINE;
	m_tBulletInfo.tShootType = BULLET_SHOOT_TYPE::ONE_SHOOT;
	m_tBulletInfo.tMasterType = BULLET_MASTER_TYPE::MONSTER;
	m_tBulletInfo.tMoveActType = BULLET_MOVE_ACT_TYPE::BULLET_MOVE_ACT_NUM;
	m_tBulletInfo.tImageType = BULLET_IMAGE_TYPE::COLOR_Y;
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

	m_tBulletInfoSub.tDmage = 10.0f + m_tMonInfo.tDamageSub;
	m_tBulletInfoSub.tKnokBack = 5.0f;
	m_tBulletInfoSub.tMoveSpeed = 5.0f;

	m_tBulletInfoSub.tBoomType = BULLET_BOOM_TYPE::ANGLE_LINE;
	m_tBulletInfoSub.tShootType = BULLET_SHOOT_TYPE::ONE_SHOOT;
	m_tBulletInfoSub.tMasterType = BULLET_MASTER_TYPE::MONSTER;
	m_tBulletInfoSub.tMoveActType = BULLET_MOVE_ACT_TYPE::BULLET_MOVE_ACT_NUM;
	m_tBulletInfoSub.tImageType = BULLET_IMAGE_TYPE::COLOR_B;
	m_tBulletInfoSub.tMoveType = BULLET_MOVE_TYPE::ONE_LINE;

	m_tBulletInfoSubPoint = &m_tBulletInfoSub;

	m_player = new PlayerCharacter;

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
	m_tMonInfo.tIsType = monInfo.tIsType;
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

void monster::Move()
{
	if (!m_tMonInfo.tIsAlive) return;

	m_tMonInfo.m_rc = RectMakeCenter(m_tMonInfo.tPosX, m_tMonInfo.tPosY, m_tMonInfo.tRadius * 2.0f, m_tMonInfo.tRadius * 2.0f);
	m_tMonInfo.tMoveAngle = MY_UTIL::getAngle(m_tMonInfo.tPosX, m_tMonInfo.tPosY, m_PlayerCharPoint->getX(), m_PlayerCharPoint->getY());
	m_tMonInfo.tPosX += cosf(m_tMonInfo.tMoveAngle) * m_tMonInfo.tMoveSpeed;
	m_tMonInfo.tPosY += -sinf(m_tMonInfo.tMoveAngle) * m_tMonInfo.tMoveSpeed;
	m_progressBar->init(m_tMonInfo.tPosX - 50, m_tMonInfo.tPosY + 50,
		m_tMonInfo.tHp, 10.0f);

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

void monster::Damge(float dam)
{
	m_tMonInfo.tHp -= dam;

	if (m_tMonInfo.tHp < 0.0f) // 사망처리
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
	m_progressBar->monHpSub(minGague, maxGauge, minSubInfo, maxSubInfo, isTrance, life);
}

void monster::update()
{	

	if (!m_tMonInfo.tIsAlive) return;

	m_tMonInfo.tFireAngle = MY_UTIL::getAngle(m_tMonInfo.tPosX, m_tMonInfo.tPosY, m_PlayerCharPoint->getX(), m_PlayerCharPoint->getY());

	Move();
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
