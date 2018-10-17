#include "stdafx.h"
#include "stageScene.h"
#include "button.h"
#include "image.h"
#include "PlayerCharacter.h"
#include "bulletManger.h"
#include "effectManager.h"
#include "PlayerCharacter.h"
#include "itemManager.h"
#include "monsterManger.h"
#include "animation.h"

char szFileName1[512];

int stageScene::buttonNum = 0;

static void Func_button1(void)
{
	stageScene::buttonNum = 1; // 시나리오 게임
}

static void Func_button2(void)
{
	stageScene::buttonNum = 2; // 사용자 지정 게임
}

HRESULT stageScene::init()
{
	//tagTile * m_pTiles = new tagTile[g_saveData.gTileMaxCountX * g_saveData.gTileMaxCountY];
	m_pTileSet[0] = IMAGEMANAGER->findImage("tileset1");
	m_pTileSet[1] = IMAGEMANAGER->findImage("tileset2");
	m_pTileSet[2] = IMAGEMANAGER->findImage("tileset3");
	m_pTileSet[3] = IMAGEMANAGER->findImage("tileset4");
	m_bIsMiniMapOn = false;
	MiniMap_Ratio = 8;

	m_pImage_BG1 = IMAGEMANAGER->findImage("black");
	m_pImage_checkBox = IMAGEMANAGER->findImage("size_box");

	m_pButton1 = new button;
	m_pButton1->init("800x", WINSIZEX / 2, 80, PointMake(0, 1), PointMake(0, 0), Func_button1); // 시나리오

	m_pButton2 = new button;
	m_pButton2->init("800x", WINSIZEX / 2, 180, PointMake(0, 1), PointMake(0, 0), Func_button2); // 사용자 지정게임

	// 타이틀 CPP 이동

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
	m_pBulletMag->init(100, m_pEffMagr);

	m_pBulletMagMons = new bulletManger;
	m_pBulletMagMons->init(100, m_pEffMagr);

	m_pMonsterMag = new monsterManger;
	m_pMonsterMag->init(50);
	isCount = 0;
	//m_pMonsterMag->Regeneration("BG_Beholder", Moninfo, m_pBulletMagMons, m_player);

	m_pItemMag = new itemManager;
	m_pItemMag->init(10);

	m_isTest = false; // 정지수 : 테스트용으로 만듦




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




	CAMERA->init();
	return S_OK;
}

void stageScene::release()
{
	m_pBulletMag->release();
	m_pBulletMagMons->release();
	m_pEffMagr->release();
	m_pItemMag->release();
}

void stageScene::update()
{
	KeyEvent();

	if (buttonNum == 0)
	{
		m_pButton1->update();
		m_pButton2->update();
	}
	if (buttonNum == 1)
	{
		g_saveData.gTileMaxCountX = 35;
		g_saveData.gTileMaxCountY = 35;
		FixedLoadEvent(); // 시나리오의 맵 최대크기는 1600 1600
		buttonNum = 3;
	}
	if (buttonNum == 2)
	{
		LoadEvent();
		buttonNum++;
	}
	if (buttonNum == 3)
	{
		// 최초 한번만 실행되는 부분







		for (int x = 0; x < g_saveData.gTileMaxCountX; x++)
		{
			for (int y = 0; y < g_saveData.gTileMaxCountX; y++)
			{
				m_pTiles[x * g_saveData.gTileMaxCountX + y].rc = RectMake(x * TILE_SIZEX, y * TILE_SIZEY, TILE_SIZEX, TILE_SIZEY);

				m_pTiles[x * g_saveData.gTileMaxCountX + y].isMove = true; // 특정 타일의 이동불가// */

				if (m_pTiles[x * g_saveData.gTileMaxCountX + y].SampleNum == 1)
				{
					if (m_pTiles[x * g_saveData.gTileMaxCountX + y].terrainFrameX == 6 && m_pTiles[x * g_saveData.gTileMaxCountX + y].terrainFrameY == 3)
						m_pTiles[x * g_saveData.gTileMaxCountX + y].isMove = false;
					if (m_pTiles[x * g_saveData.gTileMaxCountX + y].terrainFrameX == 6 && m_pTiles[x * g_saveData.gTileMaxCountX + y].terrainFrameY == 4)
						m_pTiles[x * g_saveData.gTileMaxCountX + y].isMove = false;
					if (m_pTiles[x * g_saveData.gTileMaxCountX + y].terrainFrameX == 6 && m_pTiles[x * g_saveData.gTileMaxCountX + y].terrainFrameY == 5)
						m_pTiles[x * g_saveData.gTileMaxCountX + y].isMove = false;
					if (m_pTiles[x * g_saveData.gTileMaxCountX + y].terrainFrameX == 7 && m_pTiles[x * g_saveData.gTileMaxCountX + y].terrainFrameY == 4)
						m_pTiles[x * g_saveData.gTileMaxCountX + y].isMove = false;
					if (m_pTiles[x * g_saveData.gTileMaxCountX + y].terrainFrameX == 7 && m_pTiles[x * g_saveData.gTileMaxCountX + y].terrainFrameY == 5)
						m_pTiles[x * g_saveData.gTileMaxCountX + y].isMove = false;
				}
				if (m_pTiles[x * g_saveData.gTileMaxCountX + y].MonsterNumber == 20) continue;
				Moninfo.tPosX = m_pTiles[x * g_saveData.gTileMaxCountX + y].rc.left;
				Moninfo.tPosY = m_pTiles[x * g_saveData.gTileMaxCountX + y].rc.top;
				MonSpawnCycle(50, 2, 0, 0, 0, 0, 0); // ( 몬스터 생성 사이클, 몬스터 한번에 생성 마리, 몬스터 ID)이후는 제작중

			}
		}


		buttonNum++;
	}



	if (buttonNum == 4)
	{
		KeyEvent();

		for (int i = 0; i < TILE_MAXCOUNTX * TILE_MAXCOUNTY; i++)
		{
			RECT m_rc;

			if (m_pTiles[i].isMove) continue;

			if (m_isTest && !m_pTiles[i].isMove && IntersectRect(&m_rc, &m_pTiles[i].rc, &m_player->getRect()))
			{
				m_player->setTileRc(m_pTiles[i].rc);
			}
		}

		m_pMonsterMag->update();
		m_player->update();

		m_pItemMag->update();
		m_pBulletMag->update();

		m_pBulletMagMons->update();
		m_pEffMagr->update();


		ColRc();



		CAMERA->update();
		for (int x = 0; x < g_saveData.gTileMaxCountX; x++)
		{
			for (int y = 0; y < g_saveData.gTileMaxCountY; y++)
			{
				m_pTiles[x * g_saveData.gTileMaxCountX + y].rc = RectMake(x * TILE_SIZEX - CAMERA->getCameraX(), y * TILE_SIZEY - CAMERA->getCameraY(), TILE_SIZEX, TILE_SIZEY);
			}
		}

	}
	//if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
	//{


	//}

	if (KEYMANAGER->isOnceKeyDown('T'))
	{
		if (m_isTest)
		{
			m_isTest = false;
		}
		else
		{
			m_isTest = true;
		}
	}

}




void stageScene::KeyEvent()
{
	// 단축키
	if (KEYMANAGER->isOnceKeyDown('M'))
	{
		if (m_bIsMiniMapOn == false)
			m_bIsMiniMapOn = true;
		else if (m_bIsMiniMapOn == true)
			m_bIsMiniMapOn = false;
	}
	CAMERA->keyUpdate();
	/////////////////////////////

}




void stageScene::MouseEvent()
{
}




void stageScene::render(HDC hdc)
{
	m_pImage_BG1->render(hdc, 0, 0);
	if (buttonNum == 0)
	{
		m_pImage_checkBox->render(hdc, WINSIZEX / 2 - IMAGEMANAGER->findImage("size_box")->getWidth() / 2, 0);
		m_pButton1->render(hdc);
		m_pButton2->render(hdc);
	}
	if (buttonNum == 3)
	{

	}
	if (buttonNum == 4)
	{
		for (int x = 0; x < g_saveData.gTileMaxCountX; x++)
		{
			for (int y = 0; y < g_saveData.gTileMaxCountY; y++)
			{
				m_pTileSet[m_pTiles[x * g_saveData.gTileMaxCountX + y].SampleNum]->frameRender(hdc,
					m_pTiles[x * g_saveData.gTileMaxCountX + y].rc.left,
					m_pTiles[x * g_saveData.gTileMaxCountX + y].rc.top,
					m_pTiles[x * g_saveData.gTileMaxCountX + y].terrainFrameX,
					m_pTiles[x * g_saveData.gTileMaxCountX + y].terrainFrameY);


				if (!m_pTiles[x * g_saveData.gTileMaxCountX + y].isMove)
				{
					Rectangle(hdc, m_pTiles[x * g_saveData.gTileMaxCountX + y].rc.left,
						m_pTiles[x * g_saveData.gTileMaxCountX + y].rc.top, m_pTiles[x * g_saveData.gTileMaxCountX + y].rc.right,
						m_pTiles[x * g_saveData.gTileMaxCountX + y].rc.bottom);
				}
			}

		}

		char szText[256];

		// TRANSPARENT : 투명, OPAQUE : 불투명
		SetBkMode(hdc, TRANSPARENT);

		SetTextColor(hdc, RGB(255, 0, 255));

		sprintf_s(szText, "BulletSetNum : %d",
			m_pBulletMag->getIter());
		TextOut(hdc, 10, WINSIZEY - 20, szText, strlen(szText));

		m_pEffMagr->render(hdc);
		m_pBulletMag->render(hdc);
		m_pBulletMagMons->render(hdc);
		m_pMonsterMag->render(hdc);
		m_player->render(hdc);
		m_pItemMag->render(hdc);

		TIMEMANAGER->render(hdc);

	}


	//미니맵//
	if (m_bIsMiniMapOn)
	{
		for (int x = 0; x < g_saveData.gTileMaxCountX; x++)
		{
			for (int y = 0; y < g_saveData.gTileMaxCountY; y++)
			{
				m_pTileSet[m_pTiles[x *  g_saveData.gTileMaxCountX + y].SampleNum]->RatioRender(hdc,
					550 + m_pTiles[x *  g_saveData.gTileMaxCountX + y].rc.left / MiniMap_Ratio + (CAMERA->getCameraX() / MiniMap_Ratio),
					15 + m_pTiles[x *  g_saveData.gTileMaxCountX + y].rc.top / MiniMap_Ratio + (CAMERA->getCameraY() / MiniMap_Ratio),
					m_pTiles[x *  g_saveData.gTileMaxCountX + y].terrainFrameX,
					m_pTiles[x *  g_saveData.gTileMaxCountX + y].terrainFrameY,
					MiniMap_Ratio,
					TILE_SIZEX,
					TILE_SIZEY);
			}
		}
	}
	//////////

	char szText[256];

	// TRANSPARENT : 투명, OPAQUE : 불투명
	SetBkMode(hdc, TRANSPARENT);

	SetTextColor(hdc, RGB(255, 0, 255));

	sprintf_s(szText, "m_ptMoveCameraX : %f / m_ptMoveCameraY : %f",
		CAMERA->getfocusCameraX(), CAMERA->getfocusCameraY());
	TextOut(hdc, 400, 0, szText, strlen(szText));

	sprintf_s(szText, "m_ptCameraX : %f / m_ptCameraY : %f",
		CAMERA->getCameraX(), CAMERA->getCameraY());
	TextOut(hdc, 400, 100, szText, strlen(szText));

}

void stageScene::LoadEvent()
{

	OPENFILENAME ofn;
	HWND hEditFileToBeOpened = NULL;

	ZeroMemory(&ofn, sizeof(OPENFILENAME));
	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = g_hWnd;
	ofn.lpstrFilter = "txt Files(*.txt)\0*.txt\0All Files (*.*)\0*.*\0"; //"All Files(*.*)\0*.*\0";
	ofn.lpstrFile = szFileName1;
	ofn.nMaxFile = 512;

	if (0 != GetOpenFileName(&ofn))
	{
		SetWindowText(hEditFileToBeOpened, ofn.lpstrFile);
		TXTDATA->getSingleton()->mapLoad(szFileName1, m_pTiles);
	}
	g_saveData.gTileMaxCountX = m_pTiles[0].terrain;
	g_saveData.gTileMaxCountY = m_pTiles[0].terrain;
}

void stageScene::FixedLoadEvent()
{
	int tempX = 0;
	int tempY = 0;
	TXTDATA->getSingleton()->mapLoad("mainGame6.map", m_pTiles);

}

void stageScene::MonSpawnCycle(int SpawnCycle,int SpawnOfNumber, int MonNumber, int CycleDecreaseNum,
	int TimetoComplete, int AbilityType, int AbilityCycle)
{
	SpawnTile.isActive = true;
	if (SpawnTile.isActive)
	{
		SpawnTile.nSpawnOfNumber = SpawnOfNumber;
		SpawnTile.nSPawnNumber = MonNumber;
		for (int i = 0; i < SpawnTile.nSpawnOfNumber; i++)
		{
			switch (SpawnTile.nSPawnNumber)
			{
			case 0:
				Moninfo.tFireDelay = 120;
				Moninfo.tMoveSpeed = 0.5f;
				Moninfo.tMoveType = MONSTER_MOVE::MONSTER_FLY;
				Moninfo.tUnKnokBack = 0.0f;
				Moninfo.tHp = 400.0f;
				Moninfo.tHpMax = 400.0f;
				m_pMonsterMag->Regeneration("BG_Beholder", Moninfo, m_pBulletMagMons, m_player);
				break;
			case 1:
				Moninfo.tFireDelay = 120;
				Moninfo.tMoveSpeed = 0.5f;
				Moninfo.tMoveType = MONSTER_MOVE::MONSTER_WALK;
				Moninfo.tUnKnokBack = 0.0f;
				Moninfo.tHp = 100.0f;
				Moninfo.tHpMax = 100.0f;
				m_pMonsterMag->Regeneration("BG_Blue_Guardian", Moninfo, m_pBulletMagMons, m_player);
				break;
			case 2:
				Moninfo.tFireDelay = 120;
				Moninfo.tMoveSpeed = 0.5f;
				Moninfo.tMoveType = MONSTER_MOVE::MONSTER_WALK;
				Moninfo.tUnKnokBack = 0.0f;
				Moninfo.tHp = 100.0f;
				m_pMonsterMag->Regeneration("BG_Blue_Mindflayer", Moninfo, m_pBulletMagMons, m_player);
				break;
			case 3:
				Moninfo.tFireDelay = 120;
				Moninfo.tMoveSpeed = 0.5f;
				Moninfo.tMoveType = MONSTER_MOVE::MONSTER_FLY;
				Moninfo.tUnKnokBack = 0.0f;
				Moninfo.tHp = 100.0f;
				Moninfo.tHpMax = 100.0f;
				m_pMonsterMag->Regeneration("BG_Bugman", Moninfo, m_pBulletMagMons, m_player);
				break;
			case 4:
				Moninfo.tFireDelay = 120;
				Moninfo.tMoveSpeed = 0.5f;
				Moninfo.tMoveType = MONSTER_MOVE::MONSTER_CRAWL;
				Moninfo.tUnKnokBack = 0.0f;
				Moninfo.tHp = 100.0f;
				m_pMonsterMag->Regeneration("BG_Cetus", Moninfo, m_pBulletMagMons, m_player);
				break;
			case 5:
				Moninfo.tFireDelay = 120;
				Moninfo.tMoveSpeed = 0.5f;
				Moninfo.tMoveType = MONSTER_MOVE::MONSTER_RUN;
				Moninfo.tUnKnokBack = 0.0f;
				Moninfo.tHp = 100.0f;
				Moninfo.tHpMax = 100.0f;
				m_pMonsterMag->Regeneration("BG_Coven", Moninfo, m_pBulletMagMons, m_player);
				break;
			case 6:
				Moninfo.tFireDelay = 120;
				Moninfo.tMoveSpeed = 0.5f;
				Moninfo.tMoveType = MONSTER_MOVE::MONSTER_WALK;
				Moninfo.tUnKnokBack = 0.0f;
				Moninfo.tHp = 100.0f;
				Moninfo.tHpMax = 100.0f;
				m_pMonsterMag->Regeneration("BG_Cow", Moninfo, m_pBulletMagMons, m_player);
				break;
			case 7:
				Moninfo.tFireDelay = 120;
				Moninfo.tMoveSpeed = 0.5f;
				Moninfo.tMoveType = MONSTER_MOVE::MONSTER_WALK;
				Moninfo.tUnKnokBack = 0.0f;
				Moninfo.tHp = 100.0f;
				Moninfo.tHpMax = 100.0f;
				m_pMonsterMag->Regeneration("BG_Cyclops", Moninfo, m_pBulletMagMons, m_player);
				break;
			case 8:
				Moninfo.tFireDelay = 120;
				Moninfo.tMoveSpeed = 0.5f;
				Moninfo.tMoveType = MONSTER_MOVE::MONSTER_RUN;
				Moninfo.tUnKnokBack = 0.0f;
				Moninfo.tHp = 100.0f;
				Moninfo.tHpMax = 100.0f;
				m_pMonsterMag->Regeneration("BG_Dark_Lord", Moninfo, m_pBulletMagMons, m_player);
				break;
			case 9:
				Moninfo.tFireDelay = 120;
				Moninfo.tMoveSpeed = 0.5f;
				Moninfo.tMoveType = MONSTER_MOVE::MONSTER_RUN;
				Moninfo.tUnKnokBack = 0.0f;
				Moninfo.tHp = 100.0f;
				Moninfo.tHpMax = 100.0f;
				m_pMonsterMag->Regeneration("BG_Dog", Moninfo, m_pBulletMagMons, m_player);
				break;
			case 10:
				Moninfo.tFireDelay = 120;
				Moninfo.tMoveSpeed = 0.5f;
				Moninfo.tMoveType = MONSTER_MOVE::MONSTER_CRAWL;
				Moninfo.tUnKnokBack = 0.0f;
				Moninfo.tHp = 100.0f;
				Moninfo.tHpMax = 100.0f;
				m_pMonsterMag->Regeneration("BG_Eye_Slime", Moninfo, m_pBulletMagMons, m_player);
				break;
			case 11:
				Moninfo.tFireDelay = 120;
				Moninfo.tMoveSpeed = 0.5f;
				Moninfo.tMoveType = MONSTER_MOVE::MONSTER_RUN;
				Moninfo.tUnKnokBack = 0.0f;
				Moninfo.tHp = 100.0f;
				Moninfo.tHpMax = 100.0f;
				m_pMonsterMag->Regeneration("BG_Faun_Archer", Moninfo, m_pBulletMagMons, m_player);
				break;
			case 12:
				Moninfo.tFireDelay = 120;
				Moninfo.tMoveSpeed = 0.5f;
				Moninfo.tMoveType = MONSTER_MOVE::MONSTER_RUN;
				Moninfo.tUnKnokBack = 0.0f;
				Moninfo.tHp = 100.0f;
				Moninfo.tHpMax = 100.0f;
				m_pMonsterMag->Regeneration("BG_Firewolf", Moninfo, m_pBulletMagMons, m_player);
				break;
			case 13:
				Moninfo.tFireDelay = 120;
				Moninfo.tMoveSpeed = 0.5f;
				Moninfo.tMoveType = MONSTER_MOVE::MONSTER_FLY;
				Moninfo.tUnKnokBack = 0.0f;
				Moninfo.tHp = 100.0f;
				Moninfo.tHpMax = 100.0f;
				m_pMonsterMag->Regeneration("BG_Gargoyle", Moninfo, m_pBulletMagMons, m_player);
				break;
			case 14:
				Moninfo.tFireDelay = 120;
				Moninfo.tMoveSpeed = 0.5f;
				Moninfo.tMoveType = MONSTER_MOVE::MONSTER_WALK;
				Moninfo.tUnKnokBack = 0.0f;
				Moninfo.tHp = 100.0f;
				Moninfo.tHpMax = 100.0f;
				m_pMonsterMag->Regeneration("BG_Giant_Run", Moninfo, m_pBulletMagMons, m_player);
				break;
			case 15:
				Moninfo.tFireDelay = 120;
				Moninfo.tMoveSpeed = 0.5f;
				Moninfo.tMoveType = MONSTER_MOVE::MONSTER_RUN;
				Moninfo.tUnKnokBack = 0.0f;
				Moninfo.tHp = 100.0f;
				Moninfo.tHpMax = 100.0f;
				m_pMonsterMag->Regeneration("BG_Gnome_Run", Moninfo, m_pBulletMagMons, m_player);
				break;
			case 16:
				Moninfo.tFireDelay = 120;
				Moninfo.tMoveSpeed = 0.5f;
				Moninfo.tMoveType = MONSTER_MOVE::MONSTER_WALK;
				Moninfo.tUnKnokBack = 0.0f;
				Moninfo.tHp = 100.0f;
				Moninfo.tHpMax = 100.0f;
				m_pMonsterMag->Regeneration("BG_Igor", Moninfo, m_pBulletMagMons, m_player);
				break;
			case 17:
				Moninfo.tFireDelay = 120;
				Moninfo.tMoveSpeed = 0.5f;
				Moninfo.tMoveType = MONSTER_MOVE::MONSTER_RUN;
				Moninfo.tUnKnokBack = 0.0f;
				Moninfo.tHp = 100.0f;
				Moninfo.tHpMax = 100.0f;
				m_pMonsterMag->Regeneration("BG_Itchy", Moninfo, m_pBulletMagMons, m_player);
				break;
			case 18:
				Moninfo.tFireDelay = 120;
				Moninfo.tMoveSpeed = 0.5f;
				Moninfo.tMoveType = MONSTER_MOVE::MONSTER_RUN;
				Moninfo.tUnKnokBack = 0.0f;
				Moninfo.tHp = 100.0f;
				Moninfo.tHpMax = 100.0f;
				m_pMonsterMag->Regeneration("BG_Knife_dude", Moninfo, m_pBulletMagMons, m_player);
				break;
			}
		}
			SpawnTile.isActive = false;
	}
	isCount++;
		if (isCount == SpawnTile.nSPawnCycle)
		{
			SpawnTile.isActive = true;
			isCount = 0;
		}

}

void stageScene::ColRc()
{
	RECT temp_rc;

	// 몬스터 매니저 정보
	std::vector<monster*> vMonster = m_pMonsterMag->getVecMons();
	std::vector<monster*>::iterator MonsIter;
	// 몬스터 총알 충돌
	std::vector<bullet*> vMonsterBullet = m_pBulletMagMons->getVecBullet();
	std::vector<bullet*>::iterator MonsterBulletIter;
	for (MonsterBulletIter = vMonsterBullet.begin(); MonsterBulletIter != vMonsterBullet.end(); MonsterBulletIter++) // 플레이어 총알 백터
	{
		if (!(*MonsterBulletIter)->getIsAlive()) continue;

		if ((*MonsterBulletIter)->getIsAlive() &&
			(*MonsterBulletIter)->getTagBulletInfo().tRadius + m_player->getRadius() >
			(MY_UTIL::getDistance(
			(*MonsterBulletIter)->getTagBulletInfo().tPosX,
				(*MonsterBulletIter)->getTagBulletInfo().tPosY,
				m_player->getX(),
				m_player->getY()))
			)
		{
			m_player->PlayerDamage((*MonsterBulletIter)->getTagBulletInfo().tDmage);
			(*MonsterBulletIter)->HitEff();
		}
	}

	// 플레이어 총알 충돌
	std::vector<bullet*> vPlayerBullet = m_pBulletMag->getVecBullet();
	std::vector<bullet*>::iterator PlayerBulletIter;
	for (PlayerBulletIter = vPlayerBullet.begin(); PlayerBulletIter != vPlayerBullet.end(); PlayerBulletIter++) // 플레이어 총알 백터
	{
		if (!(*PlayerBulletIter)->getIsAlive()) continue;

		for (int i = 0; i < TILE_MAXCOUNTX * TILE_MAXCOUNTY; i++)
		{
			if (m_pTiles[i].isMove) continue;

			if (m_isTest && !m_pTiles[i].isMove && IntersectRect(&temp_rc, &m_pTiles[i].rc, &(*PlayerBulletIter)->getRect()))
			{
				(*PlayerBulletIter)->HitEff();
			}
		}

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
					(*PlayerBulletIter)->HitEff();
				}
			}
		}
	}
	for (MonsIter = vMonster.begin(); MonsIter != vMonster.end(); MonsIter++)
	{
		(*MonsIter)->TypeSub(50.0f, 10.0f, MONSTER_ATT_UP, MONSTER_HP_HEALING, true, 1);
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

stageScene::stageScene()
{
}


stageScene::~stageScene()
{
}
