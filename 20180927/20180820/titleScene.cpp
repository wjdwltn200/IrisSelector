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

	/////////////////////////////////////////////




	m_pEffMagr = new effectManager;
	m_pEffMagr->addEffect("Bullet_End_0", "image/resources/bullet_image/Bullet_End_0.bmp", 238, 30, 34, 30, 15, 50);
	m_pEffMagr->addEffect("Bullet_End_1", "image/resources/bullet_image/Bullet_End_1.bmp", 238, 34, 34, 34, 15, 50);
	m_pEffMagr->addEffect("Bullet_End_2", "image/resources/bullet_image/Bullet_End_2.bmp", 224, 32, 32, 32, 15, 50);
	m_pEffMagr->addEffect("Bullet_End_3", "image/resources/bullet_image/Bullet_End_3.bmp", 210, 24, 30, 24, 15, 50);

	m_pEffMagr->addEffect("Item_Get1", "image/resources/item_image/Item_Get.bmp", 320, 31, (320 / 4), 31, 15, 5);
	m_pEffMagr->addEffect("Item_Get2", "image/resources/item_image/Item_Get2.bmp", 230, 70, (230 / 5), 70, 15, 5);

	ShowCursor(FALSE);

	m_player = new PlayerCharacter;
	m_player->init();
	m_player->setBulletMagPointer(&m_pBulletMag);
	
	m_pBulletMag = new bulletManger;
	m_pBulletMag->init(500, m_pEffMagr);

	m_pBulletMagMons = new bulletManger;
	m_pBulletMagMons->init(100, m_pEffMagr);

	m_pMonsterMag = new monsterManger;
	m_pMonsterMag->init(50);
	//m_pMonsterMag->Regeneration("BG_Beholder", Moninfo, m_pBulletMagMons, m_player);

	m_pItemMag = new itemManager;
	m_pItemMag->init(10);

	//m_pProgressBar = new progressBar;
	
	

	IMAGEMANAGER->addImage("ItemObject", "image/resources/item_image/Item_set.bmp", 682, 614, 20, 18, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("ItemShadow", "image/resources/item_image/Item_shadow.bmp", 32, 9, 1, 1, true, RGB(255, 0, 255));

	//for (int i = 0; i < ITEM_SKILL_TYPE::ITEM_SKILL_NUM; i++)
	//{
		tagItemInfo ItemInfo;
		ItemInfo.tScale = 1.0f;
		ItemInfo.tTimer = 1000;
		ItemInfo.tRadius = 1.5f;
		ItemInfo.tSkillType = 1;
		ItemInfo.posX = 300;
		ItemInfo.posY = 100;
		m_pItemMag->itemDrop("ItemObject", 2, ItemInfo, m_pEffMagr);
		ItemInfo.posY += 100;

		m_pItemMag->itemDrop("ItemObject", 1, ItemInfo, m_pEffMagr);

		ItemInfo.posY += 100;

		m_pItemMag->itemDrop("ItemObject", 3, ItemInfo, m_pEffMagr);
		ItemInfo.posY += 100;

		m_pItemMag->itemDrop("ItemObject", 4, ItemInfo, m_pEffMagr);
		ItemInfo.posY += 100;

		m_pItemMag->itemDrop("ItemObject", 5, ItemInfo, m_pEffMagr);
		ItemInfo.posY += 100;

		m_pItemMag->itemDrop("ItemObject", 6, ItemInfo, m_pEffMagr);

	//}

	



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
	m_pBulletMagMons->release();
	m_pEffMagr->release();
	m_pItemMag->release();

}

void titleScene::update()
{
	if (KEYMANAGER->isOnceKeyDown(VK_F2))
		SCENEMANAGER->changeScene("editor");

	if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
	{

		tagMonInfo Moninfo;
		Moninfo.tFireDelay = 120;
		Moninfo.tMoveSpeed = 0.5f;
		Moninfo.tMoveType = MONSTER_MOVE::MONSTER_CRAWL;
		Moninfo.tUnKnokBack = 0.0f;
		Moninfo.tHp = 100.0f;
		m_pMonsterMag->Regeneration("BG_Cetus", Moninfo, m_pBulletMagMons, m_player);
	}

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
	m_pMonsterMag->update();
	m_player->update();
	m_pItemMag->update();
	m_pBulletMag->update();
	m_player->update();
	m_pBulletMagMons->update();
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
	m_pMonsterMag->render(hdc);
	m_pItemMag->render(hdc);
	m_player->render(hdc);
	m_player->render(hdc);
	m_pEffMagr->render(hdc);
	m_pBulletMag->render(hdc);
	m_pBulletMagMons->render(hdc);
	TIMEMANAGER->render(hdc);
}

void titleScene::ColRc()
{
	// 몬스터 매니저 정보
	std::vector<monster*> vMonster = m_pMonsterMag->getVecMons();
	std::vector<monster*>::iterator MonsIter;
	// 플레이어 총알 충돌
	std::vector<bullet*> vPlayerBullet = m_pBulletMag->getVecBullet();
	std::vector<bullet*>::iterator PlayerBulletIter;
	for (PlayerBulletIter = vPlayerBullet.begin(); PlayerBulletIter != vPlayerBullet.end(); PlayerBulletIter++) // 플레이어 총알 백터
	{
		if (!(*PlayerBulletIter)->getIsAlive()) continue;

		for (MonsIter = vMonster.begin(); MonsIter != vMonster.end(); MonsIter++) // 몬스터 백터
		{
			if (!(*MonsIter)->getMonInfo().tIsAlive) continue;
			{
				if ((*PlayerBulletIter)->getIsAlive() &&
					(*PlayerBulletIter)->getTagBulletInfo().tRadius + (*MonsIter)->getMonInfo().tRadius >
					(MY_UTIL::getDistance(
					(*PlayerBulletIter)->getTagBulletInfo().tPosX,
						(*PlayerBulletIter)->getTagBulletInfo().tPosY,
						(*MonsIter)->getMonInfo().tPosX,
						(*MonsIter)->getMonInfo().tPosY))
					)
				{
					(*MonsIter)->Damge((*PlayerBulletIter)->getTagBulletInfo().tDmage);
					(*MonsIter)->knokback((*PlayerBulletIter)->getTagBulletInfo().tKnokBack, (*MonsIter)->getMonInfo().tUnKnokBack);
					(*PlayerBulletIter)->setIsAlive(false);
				}
			}
		}
	}
	for (MonsIter = vMonster.begin(); MonsIter != vMonster.end(); MonsIter++)
	{
		(*MonsIter)->TypeSub(50.0f, 10.0f, MONSTER_DEF_UP, MONSTER_HP_HEALING, true, 4);
	}

	// 아이템 획득
	std::vector<item*> vItem = m_pItemMag->getVecItem();
	std::vector<item*>::iterator ItemIter;
	for (ItemIter = vItem.begin(); ItemIter != vItem.end(); ItemIter++)
	{

		if ((*ItemIter)->getIsAlive() && m_player->getRadius() + (*ItemIter)->getItemRadius() > (MY_UTIL::getDistance(m_player->getX(), m_player->getY(), (*ItemIter)->getItemInfo().posX, (*ItemIter)->getItemInfo().posY)))
		{
			m_pEffMagr->play("Item_Get1", m_player->getX() - (320 / 4) / 2, m_player->getY());
			m_pEffMagr->play("Item_Get2", m_player->getX() - (230 / 5) / 2, m_player->getY() - (70) / 2);

			(*ItemIter)->setIsAlive(false);
			m_player->getItem((*ItemIter)->getItemInfo());
		}
	}

}

titleScene::titleScene()
{
}


titleScene::~titleScene()
{
}
