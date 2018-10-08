#include "stdafx.h"
#include "titleScene.h"
#include "PlayerCharacter.h"
#include "bulletManger.h"
#include "effectManager.h"
#include "PlayerCharacter.h"
#include "itemManager.h"
#include "monster.h"

HRESULT titleScene::init()
{

	IMAGEMANAGER->addImage("Bullet_Y", "image/resources/bullet_image/Bullet_Y.bmp", 108, 27, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Bullet_B", "image/resources/bullet_image/Bullet_B.bmp", 108, 27, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Bullet_P", "image/resources/bullet_image/Bullet_P.bmp", 108, 27, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Bullet_G", "image/resources/bullet_image/Bullet_G.bmp", 108, 27, 4, 1, true, RGB(255, 0, 255));
	m_monster = new monster;
	m_monster->init("BG_Gargoyle",100,100, 1.0f);

	

	m_player = new PlayerCharacter;
	m_player->init();

	m_pBulletMag = new bulletManger;
	m_pBulletMag->init(500);

	m_pItemMag = new itemManager;
	m_pItemMag->init(10);
	IMAGEMANAGER->addImage("ItemObject", "image/resources/item_image/item_object.bmp", 105, 60, 7, 4, true, RGB(255, 0, 255));

	for (int i = 0; i < ITEM_SKILL_TYPE::ITEM_SKILL_NUM; i++)
	{
		tagItemInfo ItemInfo;
		ItemInfo.tImageCurrX = i;
		ItemInfo.tImageCurrY = i;
		ItemInfo.tScale = 1.0f;
		ItemInfo.tTimer = 1000;
		ItemInfo.tRadius = 1.5f;
		ItemInfo.tSkillType = i;
		m_pItemMag->itemDrop("ItemObject", 100 , 50 * (i + 1), ItemInfo);
	}

	m_pEffMagr = new effectManager;
	m_pEffMagr->init();
	m_pEffMagr->addEffect("Bullet_Y_End", "image/resources/bullet_image/Bullet_Y_End.bmp",297, 27, 27, 27, 30, 5);

	m_player = new PlayerCharacter;
	m_player->init();
	m_player->setBulletMagPointer(&m_pBulletMag);

	m_titleScene = IMAGEMANAGER->addImage("titleImage", "image/resources/UI_image/title_image/titleScene.bmp", WINSIZEX, WINSIZEY);
	m_button = IMAGEMANAGER->addImage("buttonBase", "image/resources/UI_image/title_image/button_base.bmp", 162, 360, 1, 6, true, RGB(166, 166, 166));
	// 버튼 tag 초기화
	memset(&m_tButtonInfo, NULL, sizeof(m_tButtonInfo));

	// 최초 게임 시작 선택 상태
	m_tButtonInfo.carrFrameX = TITEL::GAME_START_SC;
	m_tButtonInfo.m_moveSpeed = 1.5f;
	m_tButtonInfo.m_isMovement = false;

	

	return S_OK;
}

void titleScene::release()
{
	m_pBulletMag->release();
	m_pEffMagr->release();
	m_pItemMag->release();
}

void titleScene::update()
{
	if (KEYMANAGER->isOnceKeyDown(0x71))
		SCENEMANAGER->changeScene("editor_re");

	if (!m_tButtonInfo.m_isMovement)
	{
		if (KEYMANAGER->isOnceKeyDown(VK_LEFT))
		{
			if (m_tButtonInfo.carrFrameX == TITEL::GAME_START_SC) return;

			m_tButtonInfo.carrFrameX--;
		}
		if (KEYMANAGER->isOnceKeyDown(VK_RIGHT))
		{
			if (m_tButtonInfo.carrFrameX == TITEL::EXIT_SC) return;

			m_tButtonInfo.carrFrameX++;
		}
	}
	
	ColRc();
	m_monster->update();
	m_player->update();
	m_pItemMag->update();
	m_player->update();
	m_pBulletMag->update();
	m_pEffMagr->update();
}

void titleScene::render(HDC hdc)
{
	if (m_titleScene)
	{
		m_titleScene->render(hdc,0,0);

		// 센터
		m_button->frameAlphaRender(hdc, (WINSIZEX / 2) - (m_button->getFrameWidth() / 2) * 1.2f, (WINSIZEY / 2) + ((WINSIZEY / 2) / 2) - (m_button->getFrameHeight() / 2) * 1.2f, 0, m_tButtonInfo.carrFrameX, 1.2f, 0);
		// 우측 대기
		if (!(m_tButtonInfo.carrFrameX == TITEL::GAME_START_SC))
			m_button->frameAlphaRender(hdc, (WINSIZEX / 2) - ((WINSIZEX / 2) / 2) - (m_button->getFrameWidth() / 2) * 0.8f, (WINSIZEY / 2) + ((WINSIZEY / 2) / 2) - (m_button->getFrameHeight() / 2) * 0.8f, 0, m_tButtonInfo.carrFrameX - 1, 0.8f, 150);
		// 좌측 대기
		if (!(m_tButtonInfo.carrFrameX == TITEL::EXIT_SC))
			m_button->frameAlphaRender(hdc, (WINSIZEX / 2) + ((WINSIZEX / 2) / 2) - (m_button->getFrameWidth() / 2) * 0.8f, (WINSIZEY / 2) + ((WINSIZEY / 2) / 2) - (m_button->getFrameHeight() / 2) * 0.8f, 0, m_tButtonInfo.carrFrameX + 1, 0.8f ,150);
	}

	char szText[256];

	// TRANSPARENT : 투명, OPAQUE : 불투명
	SetBkMode(hdc, TRANSPARENT);

	SetTextColor(hdc, RGB(255, 0, 255));

	sprintf_s(szText, "BulletSetNum : %d",
		m_pBulletMag->getIter());
	TextOut(hdc, 10, WINSIZEY - 20, szText, strlen(szText));
	m_monster->render(hdc);
	m_pItemMag->render(hdc);
	m_player->render(hdc);
	m_pEffMagr->render(hdc);
	m_player->render(hdc);
	m_pBulletMag->render(hdc);
	TIMEMANAGER->render(hdc);
}

void titleScene::ColRc()
{
	//IntersectRect();

	std::vector<item*> vItem = m_pItemMag->getVecItem();
	std::vector<item*>::iterator iter;
	for (iter = vItem.begin(); iter != vItem.end(); iter++)
	{
		if ((*iter)->getIsAlive() && m_player->getRadius() + (*iter)->getItemRadius() > (MY_UTIL::getDistance(m_player->getX(), m_player->getY(), (*iter)->getX(), (*iter)->getY())))
		{
			(*iter)->setIsAlive(false);
			m_player->getItem((*iter)->getItemSkill());
		}
	}

}

titleScene::titleScene()
{
}


titleScene::~titleScene()
{
}
