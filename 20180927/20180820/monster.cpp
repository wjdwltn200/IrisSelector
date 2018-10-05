#include "stdafx.h"
#include "animation.h"
#include "monster.h"


HRESULT monster::init()
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

	for (int i = 0; i < 4; i++)
	{
	ani_monsterMove = new animation;
	}

	ani_monsterMove->init(IMAGEMANAGER->findImage("BG_Beholder")->getWidth(),IMAGEMANAGER->findImage("BG_Beholder")->getHeight(), 155, 78);
	ani_monsterMove->init(IMAGEMANAGER->findImage("BG_Blue_Guardian")->getWidth(),IMAGEMANAGER->findImage("BG_Blue_Guardian")->getHeight(), 155, 57);
	ani_monsterMove->init(IMAGEMANAGER->findImage("BG_Blue_Guardian")->getWidth(), IMAGEMANAGER->findImage("BG_Blue_Guardian")->getHeight(), 155, 57);
	ani_monsterMove->init(IMAGEMANAGER->findImage("BG_Bugman")->getWidth(), IMAGEMANAGER->findImage("BG_Bugman")->getHeight(), 155, 57);

	ani_monsterMove->setDefPlayFrame(false, true);
	ani_monsterMove->setFPS(10);
	ani_monsterMove->start();
	m_Mon.m_fX = WINSIZEX / 2;
	m_Mon.m_fY = WINSIZEY / 2;

	


	return S_OK;
}

void monster::release()
{
}

void monster::update()
{
	ani_monsterMove->frameUpdate();
}

void monster::render(HDC hdc)
{
	IMAGEMANAGER->findImage("BG_Bugman")->aniRender(hdc, m_Mon.m_fX, m_Mon.m_fY, ani_monsterMove, 1.0f, true, 255);
	IMAGEMANAGER->findImage("BG_Blue_Guardian")->aniRender(hdc, m_Mon.m_fX-100, m_Mon.m_fY, ani_monsterMove, 1.0f, true, 255);

}

void monster::Move()
{
}

monster::monster()
{
}


monster::~monster()
{
}
