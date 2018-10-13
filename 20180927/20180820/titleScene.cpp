#include "stdafx.h"
#include "titleScene.h"
#include "PlayerCharacter.h"
#include "bulletManger.h"
#include "effectManager.h"
#include "PlayerCharacter.h"
#include "itemManager.h"
#include "monsterManger.h"
#include "animation.h"

HRESULT titleScene::init()
{
	AddFontResourceA("BMHANNAAir_ttf.ttf");

	IMAGEMANAGER->addImage("BG_Beholder", "image/resources/monster_image/BG_Beholder_Run.bmp", 1860, 78, 12, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("BG_Blue_Guardian", "image/resources/monster_image/BG_Blue_Guardian_Run.bmp", 930, 57, 6, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("BG_Blue_Mindflayer", "image/resources/monster_image/BG_Blue_Mindflayer_Run.bmp", 930, 54, 6, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("BG_Bugman", "image/resources/monster_image/BG_Bugman_Run.bmp", 620, 61, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("BG_Cetus", "image/resources/monster_image/BG_Cetus_Run.bmp", 620, 37, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("BG_Coven", "image/resources/monster_image/BG_Coven_Run.bmp", 620, 33, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("BG_Cow", "image/resources/monster_image/BG_Cow.bmp", 620, 28, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("BG_Cyclops", "image/resources/monster_image/BG_Cyclops.bmp", 930, 46, 6, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("BG_Dark_Lord", "image/resources/monster_image/BG_Dark_Lord.bmp", 620, 78, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("BG_Dog", "image/resources/monster_image/BG_Dog.bmp", 465, 37, 3, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("BG_Eye_Slime", "image/resources/monster_image/BG_Eye_Slime_Run.bmp", 465, 39, 3, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("BG_Faun_Archer", "image/resources/monster_image/BG_Faun_Archer_Run.bmp", 930, 46, 6, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("BG_Firewolf", "image/resources/monster_image/BG_Firewolf.bmp", 620, 46, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("BG_Gargoyle", "image/resources/monster_image/BG_Gargoyle.bmp", 620, 65, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("BG_Giant_Run", "image/resources/monster_image/BG_Giant_Run.bmp", 930, 63, 6, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("BG_Gnome_Run", "image/resources/monster_image/BG_Gnome_Run.bmp", 930, 26, 6, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("BG_Igor", "image/resources/monster_image/BG_Igor.bmp", 930, 44, 6, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("BG_Itchy", "image/resources/monster_image/BG_Itchy.bmp", 930, 37, 6, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("BG_Knife_dude", "image/resources/monster_image/BG_Knife_dude.bmp", 930, 60, 6, 1, true, RGB(255, 0, 255));

	IMAGEMANAGER->addImage("Bullet_Y", "image/resources/bullet_image/Bullet_Y.bmp", 108, 27, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Bullet_B", "image/resources/bullet_image/Bullet_B.bmp", 108, 27, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Bullet_P", "image/resources/bullet_image/Bullet_P.bmp", 108, 27, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Bullet_G", "image/resources/bullet_image/Bullet_G.bmp", 108, 27, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Bullet_R", "image/resources/bullet_image/Bullet_R.bmp", 108, 27, 4, 1, true, RGB(255, 0, 255));

	
	IMAGEMANAGER->addImage("Player_ItemUI", "image/resources/UI_image/player_Ui/Player_Item_Ui.bmp", 449, 550, 1, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Player_InfoIcon", "image/resources/UI_image/player_Ui/BG_Player_Icon.bmp", 37 * 2, 43 * 2, 1, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Player_ItemPopupUI", "image/resources/UI_image/player_Ui/Player_Item_PopupUI.bmp", 307, 126, 1, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Player_HP_Point", "image/resources/UI_image/player_Ui/Player_Hp_Point.bmp", 27 * 5, 7 * 5, 3, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Player_UI_BG", "image/resources/UI_image/player_Ui/Player_UI_BG.bmp", WINSIZEX, WINSIZEY);

	////// 맵에디터 소스//////////////////////////////
	IMAGEMANAGER->addImage("black", "image/wook/black.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("space_left", "image/wook/space_left.bmp", 36, 72, 1, 2, true, RGB(255, 255, 255));
	IMAGEMANAGER->addImage("space_right", "image/wook/space_right.bmp", 36, 72, 1, 2, true, RGB(255, 255, 255));

	IMAGEMANAGER->addImage("box", "image/wook/white.bmp", WINSIZEX, 250, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("tileset1", "image/wook/tileset1.bmp", 256, 192, 8, 6, true, RGB(255, 255, 255));
	IMAGEMANAGER->addImage("tileset2", "image/wook/tileset2.bmp", 256, 192, 8, 6, true, RGB(255, 255, 255));
	IMAGEMANAGER->addImage("tileset3", "image/wook/tileset3.bmp", 256, 192, 8, 6, true, RGB(255, 255, 255));
	IMAGEMANAGER->addImage("tileset4", "image/wook/tileset4.bmp", 256, 192, 8, 6, true, RGB(255, 255, 255));
	IMAGEMANAGER->addImage("Cursor", "image/wook/Cursor.bmp", 30, 48, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("800x", "image/wook/800x.bmp", 320, 168, 1, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("size_box", "image/wook/size_box.bmp", 640, 640, true, RGB(255, 0, 255));

	IMAGEMANAGER->addImage("ItemObject", "image/resources/item_image/Item_set.bmp", 682, 614, 20, 18, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("ItemShadow", "image/resources/item_image/Item_shadow.bmp", 32, 9, 1, 1, true, RGB(255, 0, 255));

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
}

void titleScene::update()
{
	if (KEYMANAGER->isOnceKeyDown(VK_F2))
		SCENEMANAGER->changeScene("editor");



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

	

	TIMEMANAGER->render(hdc);
}



titleScene::titleScene()
{
}


titleScene::~titleScene()
{
}
