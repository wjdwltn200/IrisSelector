#include "stdafx.h"
#include "animation.h"
#include "monster.h"
#include "PlayerCharacter.h"


HRESULT monster::init(const char * strKey, int fX, int fY, float speed)
{
	IMAGEMANAGER->addImage("BG_Beholder", "image/resources/monster_image/BG_Beholder_Run.bmp", 1860, 78, 12, 1, true, RGB(255, 0, 255),
		m_Mon.m_fX, m_Mon.m_fY);
	IMAGEMANAGER->addImage("BG_Blue_Guardian", "image/resources/monster_image/BG_Blue_Guardian_Run.bmp", 930, 57, 6, 1, true, RGB(255, 0, 255),
		m_Mon.m_fX, m_Mon.m_fY);
	IMAGEMANAGER->addImage("BG_Blue_Mindflayer","image/resources/monster_image/BG_Blue_Mindflayer_Run.bmp", 930, 54, 6, 1, true, RGB(255, 0, 255),
		m_Mon.m_fX, m_Mon.m_fY);
	IMAGEMANAGER->addImage("BG_Bugman", "image/resources/monster_image/BG_Bugman_Run.bmp", 620, 61, 4, 1, true, RGB(255, 0, 255),
		m_Mon.m_fX, m_Mon.m_fY);
	IMAGEMANAGER->addImage("BG_Cetus", "image/resources/monster_image/BG_Cetus_Run.bmp", 620, 37, 4, 1, true, RGB(255, 0, 255),
		m_Mon.m_fX, m_Mon.m_fY);
	IMAGEMANAGER->addImage("BG_Coven", "image/resources/monster_image/BG_Coven_Run.bmp", 620, 33, 4, 1, true, RGB(255, 0, 255),
		m_Mon.m_fX, m_Mon.m_fY);
	IMAGEMANAGER->addImage("BG_Cow", "image/resources/monster_image/BG_Cow.bmp", 620, 28, 4, 1, true, RGB(255, 0, 255),
		m_Mon.m_fX, m_Mon.m_fY);
	IMAGEMANAGER->addImage("BG_Cyclops", "image/resources/monster_image/BG_Cyclops.bmp", 930, 46, 6, 1, true, RGB(255, 0, 255),
		m_Mon.m_fX, m_Mon.m_fY);
	IMAGEMANAGER->addImage("BG_Dark_Lord", "image/resources/monster_image/BG_Dark_Lord.bmp", 620, 78, 4, 1, true, RGB(255, 0, 255),
		m_Mon.m_fX, m_Mon.m_fY);
	IMAGEMANAGER->addImage("BG_Dog", "image/resources/monster_image/BG_Dog.bmp", 465, 37, 3, 1, true, RGB(255, 0, 255),
		m_Mon.m_fX, m_Mon.m_fY);
	IMAGEMANAGER->addImage("BG_Eye_Slime", "image/resources/monster_image/BG_Eye_Slime_Run.bmp", 465, 39, 3, 1, true, RGB(255, 0, 255),
		m_Mon.m_fX, m_Mon.m_fY);
	IMAGEMANAGER->addImage("BG_Faun_Archer", "image/resources/monster_image/BG_Faun_Archer_Run.bmp", 930, 46, 6, 1, true, RGB(255, 0, 255),
		m_Mon.m_fX, m_Mon.m_fY);
	IMAGEMANAGER->addImage("BG_Firewolf", "image/resources/monster_image/BG_Firewolf.bmp", 620, 46, 4, 1, true, RGB(255, 0, 255),
		m_Mon.m_fX, m_Mon.m_fY);
	IMAGEMANAGER->addImage("BG_Gargoyle", "image/resources/monster_image/BG_Gargoyle.bmp", 620, 65, 4, 1, true, RGB(255, 0, 255),
		m_Mon.m_fX, m_Mon.m_fY);
	IMAGEMANAGER->addImage("BG_Giant_Run", "image/resources/monster_image/BG_Giant_Run.bmp", 930, 63, 6, 1, true, RGB(255, 0, 255),
		m_Mon.m_fX, m_Mon.m_fY);
	IMAGEMANAGER->addImage("BG_Gnome_Run", "image/resources/monster_image/BG_Gnome_Run.bmp", 930, 26, 6, 1, true, RGB(255, 0, 255),
		m_Mon.m_fX, m_Mon.m_fY);
	IMAGEMANAGER->addImage("BG_Igor", "image/resources/monster_image/BG_Igor.bmp", 930, 44, 6, 1, true, RGB(255, 0, 255),
		m_Mon.m_fX, m_Mon.m_fY);
	IMAGEMANAGER->addImage("BG_Itchy", "image/resources/monster_image/BG_Itchy.bmp", 930, 37, 6, 1, true, RGB(255, 0, 255),
		m_Mon.m_fX, m_Mon.m_fY);
	IMAGEMANAGER->addImage("BG_Knife_dude", "image/resources/monster_image/BG_Knife_dude.bmp", 930, 60, 6, 1, true, RGB(255, 0, 255),
		m_Mon.m_fX, m_Mon.m_fY);

	m_player = new PlayerCharacter;

	m_monsterType = IMAGEMANAGER->findImage(strKey);
	m_monsterMove = new animation;
	m_monsterMove->init(m_monsterType->getWidth(), m_monsterType->getHeight(),
		m_monsterType->getFrameWidth(), m_monsterType->getFrameHeight());

	isAlive = true;
	
	m_monsterMove->setDefPlayFrame(false, true);
	m_monsterMove->setFPS(10);
	m_monsterMove->start();



	m_Mon.m_CurrHpX = 0.0f;
	m_Mon.m_CurrHpY = 0.0f;
	m_Mon.m_fX = fX;
	m_Mon.m_fY = fY;
	m_Mon.m_MaxHp = 0.0f;
	m_Mon.m_Speed = speed;
	

	
	


	return S_OK;
}

void monster::release()
{
}
void monster::Move()
{
	if (isAlive == true)
	{
		m_Mon.m_Angle = MY_UTIL::getAngle(m_Mon.m_fX, m_Mon.m_fY, m_player->getX(), m_player->getY());
		m_Mon.m_fX += cosf(m_Mon.m_Angle)*m_Mon.m_Speed;
		m_Mon.m_fY += -sinf(m_Mon.m_Angle)*m_Mon.m_Speed;	
	}
}

void monster::update()
{
	m_monsterMove->frameUpdate();
	Move();
}

void monster::render(HDC hdc)
{
	m_monsterType->aniRender(hdc, m_Mon.m_fX, m_Mon.m_fY, m_monsterMove, 1.0f, true, 255);
}

monster::monster()
{
}


monster::~monster()
{
}
