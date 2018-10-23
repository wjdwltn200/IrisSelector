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
#include "uiManager.h"

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
	DWORD dwRemove = WS_CAPTION | WS_BORDER | WS_SYSMENU | WS_THICKFRAME | WS_MINIMIZEBOX | WS_MAXIMIZEBOX;
	// This should be kept for reverse operation
	DWORD dwStyle = ::GetWindowLong(g_hWnd, GWL_STYLE);
	HMENU hMenu = ::GetMenu(g_hWnd);
	WINDOWPLACEMENT wp = { sizeof WINDOWPLACEMENT };
	::GetWindowPlacement(g_hWnd, &wp);

	::LockWindowUpdate(g_hWnd); // prevent intermediate redrawing
	::SetMenu(g_hWnd, NULL);
	::SetWindowLong(g_hWnd, GWL_STYLE, dwStyle & ~dwRemove);
	HDC hDC = ::GetWindowDC(NULL);
	::LockWindowUpdate(NULL); // allow redrawing
	::SetWindowPos(g_hWnd, NULL, 100, 100, 800, 800, SWP_FRAMECHANGED);



	m_soundMag.init();
	m_soundMag.addSound("sound/sound_StageBGM.wav", true, true);
	m_soundMag.addSound("sound/EnemyDead0.wav", false, false);
	m_soundMag.addSound("sound/EnemyDead1.wav", false, false);
	m_soundMag.addSound("sound/EnemyDead2.wav", false, false);
	m_soundMag.addSound("sound/EnemyDead3.wav", false, false);
	m_soundMag.addSound("sound/EnemyDead4.wav", false, false);
	m_soundMag.addSound("sound/EnemyDead5.wav", false, false);
	m_soundMag.addSound("sound/EnemyDead6.wav", false, false);

	m_soundMag.addSound("sound/sound_MonsterHit.wav", false, false);

	m_soundMag.addSound("sound/sound_itemGet.wav", false, false);
	m_soundMag.addSound("sound/sound_playerHit.wav", false, false);
	m_soundMag.addSound("sound/sound_playerAtt.wav", false, false);


	//tagTile * m_pTiles = new tagTile[g_saveData.gTileMaxCountX * g_saveData.gTileMaxCountY];
	m_pTileSet[0] = IMAGEMANAGER->findImage("tileset1");
	m_pTileSet[1] = IMAGEMANAGER->findImage("tileset2");
	m_pTileSet[2] = IMAGEMANAGER->findImage("tileset3");
	m_pTileSet[3] = IMAGEMANAGER->findImage("tileset4");

	//m_pImg_Black = IMAGEMANAGER->findImage("black_big");
	m_pImg_rad[0] = IMAGEMANAGER->findImage("rad1");
	m_pImg_rad[1] = IMAGEMANAGER->findImage("rad2");
	m_pImg_rad[2] = IMAGEMANAGER->findImage("rad3");
	m_pImg_rad[3] = IMAGEMANAGER->findImage("rad4");

	m_bIsMiniMapOn = false;
	m_bIsCameraTextOn = false;
	MiniMap_Ratio = 8;

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

	m_pEffMagr->addEffect("Monster_die", "image/resources/monster_image/Monster_Die_Eff.bmp", 512, 384, 512 / 4, 384 / 3, 15, 10);

	m_pEffMagr->addEffect("Item_Get1", "image/resources/item_image/Item_Get.bmp", 320, 31, (320 / 4), 31, 15, 5);
	m_pEffMagr->addEffect("Item_Get2", "image/resources/item_image/Item_Get2.bmp", 230, 70, (230 / 5), 70, 15, 5);

	m_pUiMag = new uiManager;
	m_pUiMag->init(100);

	m_player = new PlayerCharacter;
	m_player->init(&m_soundMag);
	m_player->setBulletMagPointer(&m_pBulletMag);

	m_pBulletMag = new bulletManger;
	m_pBulletMag->init(100, m_pEffMagr);

	m_pBulletMagMons = new bulletManger;
	m_pBulletMagMons->init(100, m_pEffMagr);

	m_pMonsterMag = new monsterManger;
	m_pMonsterMag->setEffMagPoint(m_pEffMagr);
	m_pMonsterMag->init(50);

	m_pItemMag = new itemManager;
	m_pItemMag = m_pItemMag;
	m_pItemMag->init(10);
	m_isSpawnCycle = false;
	m_GateNum = 0;
	m_GateMonsterIndex = 0;
	m_GateMonsterNum = 0;
	m_stageNum = 0;
	m_MaxSpawnNum = 0;
	m_ClearScore = 0;



	m_isTest = false; // 정지수 : 테스트용으로 만듦

	//CAMERA->init();
	return S_OK;
}

void stageScene::release()
{
	m_pUiMag->release();
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
		g_saveData.gTileMaxCountX = m_pTiles[0].terrain;
		g_saveData.gTileMaxCountY = m_pTiles[0].terrain;
	}
	if (buttonNum == 3)
	{
		// 최초 한번만 실행되는 부분
		ShowCursor(FALSE);

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

		if (!m_BGMreSet)
		{
			m_BGMreSet = true;
			m_soundMag.play("sound/sound_StageBGM.wav", g_saveData.gMainBGMValue);
		}


		SpawnGateTime();

		
		m_pMonsterMag->update();
		m_player->update();

		//m_pItemMag->update();
		m_pBulletMag->update();

		m_pBulletMagMons->update();
		m_pEffMagr->update();
		m_pUiMag->update();

		ColRc();

		for (int x = 0; x < g_saveData.gTileMaxCountX; x++)
		{
			for (int y = 0; y < g_saveData.gTileMaxCountY; y++)
			{
				m_pTiles[x * g_saveData.gTileMaxCountX + y].rc = RectMake(x * TILE_SIZEX - SCROLL->GetX(), y * TILE_SIZEY - SCROLL->GetY(), TILE_SIZEX, TILE_SIZEY);
			}
		}

		SCROLL->update(m_player->getX(), m_player->getY());
		//CAMERA->update();

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
	if (KEYMANAGER->isOnceKeyDown('T'))
	{
		if (m_isTest)
			m_isTest = false;
		else
			m_isTest = true;
	}
	if (KEYMANAGER->isOnceKeyDown('L'))
	{
		if (m_bIsFireOn)
			m_bIsFireOn = false;
		else
			m_bIsFireOn = true;
	}
	if (KEYMANAGER->isOnceKeyDown('P'))
	{
		if (m_bIsScoreOn)
			m_bIsScoreOn = false;
		else
			m_bIsScoreOn = true;
	}
	if (KEYMANAGER->isOnceKeyDown(VK_F6))
	{
		if (m_bIsCameraTextOn)
			m_bIsCameraTextOn = false;
		else
			m_bIsCameraTextOn = true;
	}
	//CAMERA->keyUpdate();
	/////////////////////////////

}




void stageScene::MouseEvent()
{
}




void stageScene::render(HDC hdc)
{
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

		m_pMonsterMag->render(hdc);
		m_pItemMag->render(hdc);
		m_pBulletMag->render(hdc);
		m_pBulletMagMons->render(hdc);
		m_pMonsterMag->render(hdc);
		m_pItemMag->render(hdc);
		m_player->render(hdc);
		m_pUiMag->render(hdc);

		ClearEvent();
		//TIMEMANAGER->render(hdc);
	}


	//미니맵//
	if (m_bIsMiniMapOn)
	{
		for (int x = 0; x < g_saveData.gTileMaxCountX; x++)
		{
			for (int y = 0; y < g_saveData.gTileMaxCountY; y++)
			{
				m_pTileSet[m_pTiles[x *  g_saveData.gTileMaxCountX + y].SampleNum]->RatioRender(hdc,
					649 + m_pTiles[x *  g_saveData.gTileMaxCountX + y].rc.left / MiniMap_Ratio + (SCROLL->GetX() / MiniMap_Ratio),
					11 + m_pTiles[x *  g_saveData.gTileMaxCountX + y].rc.top / MiniMap_Ratio + (SCROLL->GetY() / MiniMap_Ratio),
					m_pTiles[x *  g_saveData.gTileMaxCountX + y].terrainFrameX,
					m_pTiles[x *  g_saveData.gTileMaxCountX + y].terrainFrameY,
					MiniMap_Ratio,
					TILE_SIZEX,
					TILE_SIZEY);
			}
		}
	}
	//////////

	if (m_bIsCameraTextOn)
	{
		char szText[256];

		// TRANSPARENT : 투명, OPAQUE : 불투명
		SetBkMode(hdc, TRANSPARENT);

		SetTextColor(hdc, RGB(255, 0, 255));

		sprintf_s(szText, "화면시작좌표X : %f / 화면시작좌표Y : %f",
			SCROLL->GetX(), SCROLL->GetY());
		TextOut(hdc, 400, 0, szText, strlen(szText));

		sprintf_s(szText, "캐릭터좌표 : %f / 캐릭터좌표Y : %f",
			m_player->getX(), m_player->getY());
		TextOut(hdc, 400, 100, szText, strlen(szText));
	}

	if (m_bIsScoreOn)
	{
		char szTextStage[128];
		// TRANSPARENT : 투명, OPAQUE : 불투명
		SetBkMode(hdc, TRANSPARENT);
		SetTextColor(hdc, RGB(150, 0, 100));
		MY_UTIL::FontOption(hdc, 25, 0);
		sprintf_s(szTextStage, "%s : %d", "스테이지", m_stageNum);
		TextOut(hdc, 320, 42, szTextStage, strlen(szTextStage));
		MY_UTIL::FontDelete(hdc);


		char szTextScore[128];
		// TRANSPARENT : 투명, OPAQUE : 불투명
		SetBkMode(hdc, TRANSPARENT);
		SetTextColor(hdc, RGB(150, 0, 100));
		MY_UTIL::FontOption(hdc, 25, 0);
		sprintf_s(szTextScore, "%s : %d", "점수", m_ClearScore);
		TextOut(hdc, 320, 15, szTextScore, strlen(szTextScore));
		MY_UTIL::FontDelete(hdc);

	}

	if (m_bIsFireOn)
	{
		//m_pImg_Black->alphaRender(hdc, 240);
		m_pImg_rad[0]->alphaRender(hdc, m_player->getX() - m_pImg_rad[0]->getWidth() / 2 - SCROLL->GetX(), m_player->getY() - m_pImg_rad[0]->getHeight() / 2 - SCROLL->GetY(), 1, 190); // 450
		m_pImg_rad[1]->alphaRender(hdc, m_player->getX() - m_pImg_rad[1]->getWidth() / 2 - SCROLL->GetX(), m_player->getY() - m_pImg_rad[1]->getHeight() / 2 - SCROLL->GetY(), 1, 170); // 450
		m_pImg_rad[2]->alphaRender(hdc, m_player->getX() - m_pImg_rad[2]->getWidth() / 2 - SCROLL->GetX(), m_player->getY() - m_pImg_rad[2]->getHeight() / 2 - SCROLL->GetY(), 1, 150); // 450
		//m_pImg_rad[3]->alphaRender(hdc, m_player->getX() - m_pImg_rad[3]->getWidth() / 2, m_player->getY() - m_pImg_rad[3]->getHeight() / 2, 1, 50); // 450

		

	}
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
}

void stageScene::FixedLoadEvent()
{
	int tempX = 0;
	int tempY = 0;
	TXTDATA->getSingleton()->mapLoad("SaveFile/mainGame7.map", m_pTiles);

}

void stageScene::MonSpawnCycle(int SpawnOfNumber, int MonNumber)
{
	SpawnTile.nSpawnOfNumber = SpawnOfNumber;
	SpawnTile.nSPawnNumber = MonNumber;
	for (int i = 0; i < SpawnTile.nSpawnOfNumber; i++)
	{
		switch (SpawnTile.nSPawnNumber)
		{
		case 0:
			Moninfo.tHpMax = Moninfo.tHp;
			m_pMonsterMag->Regeneration("BG_Beholder",1, Moninfo, m_pBulletMagMons, m_player);
			break;
		case 1:
			Moninfo.tHpMax = Moninfo.tHp;
			m_pMonsterMag->Regeneration("BG_Blue_Guardian",2, Moninfo, m_pBulletMagMons, m_player);
			break;
		case 2:
			Moninfo.tHpMax = Moninfo.tHp;
			m_pMonsterMag->Regeneration("BG_Blue_Mindflayer",3, Moninfo, m_pBulletMagMons, m_player);
			break;
		case 3:
			Moninfo.tHpMax = Moninfo.tHp;
			m_pMonsterMag->Regeneration("BG_Bugman",4, Moninfo, m_pBulletMagMons, m_player);
			break;
		case 4:
			Moninfo.tHpMax = Moninfo.tHp;
			m_pMonsterMag->Regeneration("BG_Cetus",5, Moninfo, m_pBulletMagMons, m_player);
			break;
		case 5:

			Moninfo.tHpMax = Moninfo.tHp;
			m_pMonsterMag->Regeneration("BG_Coven",6, Moninfo, m_pBulletMagMons, m_player);
			break;
		case 6:
			Moninfo.tHpMax = Moninfo.tHp;
			m_pMonsterMag->Regeneration("BG_Cow",7, Moninfo, m_pBulletMagMons, m_player);
			break;
		case 7:
			Moninfo.tHpMax = Moninfo.tHp;
			m_pMonsterMag->Regeneration("BG_Cyclops",8, Moninfo, m_pBulletMagMons, m_player);
			break;
		case 8:
			Moninfo.tHpMax = Moninfo.tHp;
			m_pMonsterMag->Regeneration("BG_Dark_Lord",9, Moninfo, m_pBulletMagMons, m_player);
			break;
		case 9:
			Moninfo.tHpMax = Moninfo.tHp;
			m_pMonsterMag->Regeneration("BG_Dog",10, Moninfo, m_pBulletMagMons, m_player);
			break;
		case 10:
			Moninfo.tHpMax = Moninfo.tHp;
			m_pMonsterMag->Regeneration("BG_Eye_Slime",11, Moninfo, m_pBulletMagMons, m_player);
			break;
		case 11:
			Moninfo.tHpMax = Moninfo.tHp;
			m_pMonsterMag->Regeneration("BG_Faun_Archer",12, Moninfo, m_pBulletMagMons, m_player);
			break;
		case 12:
			Moninfo.tHpMax = Moninfo.tHp;
			m_pMonsterMag->Regeneration("BG_Firewolf",13, Moninfo, m_pBulletMagMons, m_player);
			break;
		case 13:
			Moninfo.tHpMax = Moninfo.tHp;
			m_pMonsterMag->Regeneration("BG_Gargoyle",14, Moninfo, m_pBulletMagMons, m_player);
			break;
		case 14:
			Moninfo.tHpMax = Moninfo.tHp;
			m_pMonsterMag->Regeneration("BG_Giant_Run",15, Moninfo, m_pBulletMagMons, m_player);
			break;
		case 15:
			Moninfo.tHpMax = Moninfo.tHp;
			m_pMonsterMag->Regeneration("BG_Gnome_Run",16, Moninfo, m_pBulletMagMons, m_player);
			break;
		case 16:
			Moninfo.tHpMax = Moninfo.tHp;
			m_pMonsterMag->Regeneration("BG_Igor",17, Moninfo, m_pBulletMagMons, m_player);
			break;
		case 17:
			Moninfo.tHpMax = Moninfo.tHp;
			m_pMonsterMag->Regeneration("BG_Itchy",18, Moninfo, m_pBulletMagMons, m_player);
			break;
		case 18:
			Moninfo.tHpMax = Moninfo.tHp;
			m_pMonsterMag->Regeneration("BG_Knife_dude",19, Moninfo, m_pBulletMagMons, m_player);
			break;
		}
	}
	m_SpawnCount++;
	m_isSpawnCycle = false;
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

		for (int i = 0; i < TILE_MAXCOUNTX * TILE_MAXCOUNTY; i++)
		{
			if (m_pTiles[i].isMove) continue;

			if (m_isTest && !m_pTiles[i].isMove && IntersectRect(&temp_rc, &m_pTiles[i].rc, &(*MonsterBulletIter)->getRect()))
			{
				(*MonsterBulletIter)->HitEff();
			}
		}

		if ((*MonsterBulletIter)->getIsAlive() &&
			(*MonsterBulletIter)->getTagBulletInfo().tRadius + m_player->getRadius() >
			(MY_UTIL::getDistance(
			(*MonsterBulletIter)->getTagBulletInfo().tPosX,
				(*MonsterBulletIter)->getTagBulletInfo().tPosY,
				m_player->getX(),
				m_player->getY()))
			)
		{
			// 플레이어 피격 처리
			if (!m_player->getHitState())
			{
				m_player->PlayerDamage((*MonsterBulletIter)->getTagBulletInfo().tDmage);
				(*MonsterBulletIter)->HitEff();
				m_soundMag.play("sound/sound_playerHit.wav", g_saveData.gSeValue);
			}
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
					// 몬스터 피격 처리
					(*MonsIter)->Damge((*PlayerBulletIter)->getTagBulletInfo().tDmage, &m_soundMag, m_pItemMag);
					(*MonsIter)->knokback((*PlayerBulletIter)->getTagBulletInfo().tKnokBack, (*MonsIter)->getMonInfo().tUnKnokBack);
					(*PlayerBulletIter)->HitEff();
					m_pUiMag->addHitTxt((*PlayerBulletIter)->getTagBulletInfo().tDmage, (*MonsIter)->getMonInfo().tPosX, (*MonsIter)->getMonInfo().tPosY);
					m_soundMag.play("sound/sound_MonsterHit.wav", g_saveData.gSeValue);
				}
			}
		}
	}
	for (MonsIter = vMonster.begin(); MonsIter != vMonster.end(); MonsIter++)
	{
		(*MonsIter)->TypeSub(Moninfo.tminGaugeSub, Moninfo.tmaxGaugeSub, Moninfo.tminGaugeInfo, Moninfo.tmaxGaugeInfo, true, 1);
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
			m_soundMag.play("sound/sound_itemGet.wav", g_saveData.gSeValue);

		}
	}

}

void stageScene::SpawnGateTime()
{
	m_isCount++; // 스폰되는 주기 카운트
	if (m_isCount > 200.0f /*&& (MAX_SPAWN_NUMBER >= m_MaxSpawnNum)*/)
	{
		m_isSpawnCycle = true;
		m_GateNum++;
		m_MaxSpawnNum++;
		m_isCount = 0;
		if (m_GateNum > 19)
		{
			m_GateNum = 0;
		}
	}
	if (m_isSpawnCycle/* && MAX_SPAWN_NUMBER >= m_MaxSpawnNum*/)
	{
		for (int x = 0; x < g_saveData.gTileMaxCountX; x++)
		{
			for (int y = 0; y < g_saveData.gTileMaxCountX; y++)
			{
				if (m_pTiles[x * g_saveData.gTileMaxCountX + y].MonsterNumber == 20) continue;
				{
					Moninfo.tPosX = m_pTiles[x * g_saveData.gTileMaxCountX + y].rc.left;
					Moninfo.tPosY = m_pTiles[x * g_saveData.gTileMaxCountX + y].rc.top;
					if (m_pTiles[x * g_saveData.gTileMaxCountX + y].MonsterNumber == m_GateNum)
					{
						MonSpawnCycle(m_GateMonsterNum, m_GateMonsterIndex); // (몬스터 한번에 생성 마리, 몬스터 ID)
					}
				}

			}
		}
	}
	//else if (MAX_SPAWN_NUMBER < m_MaxSpawnNum)
	//{
	//	m_stageNum++;
	//}

	switch (m_stageNum)
	{
	case GATE_1 :
		m_GateMonsterNum = 1;
		m_GateMonsterIndex = RANDOM->getFromIntTo(1, 18); 
		break;
	case GATE_2:
		m_GateMonsterNum = 1;
		m_GateMonsterIndex = RANDOM->getFromIntTo(4, 6);
		break;
	case GATE_3:
		m_GateMonsterNum = 1;
		m_GateMonsterIndex = RANDOM->getFromIntTo(7, 9);
		break;
	case GATE_4:
		m_GateMonsterNum = 1;
		m_GateMonsterIndex = RANDOM->getFromIntTo(10, 13);
		break;
	case GATE_5:
		m_GateMonsterNum = 1;
		m_GateMonsterIndex = RANDOM->getFromIntTo(14, 16);
		break;
	case GATE_6:
		m_GateMonsterNum = 1;
		m_GateMonsterIndex = RANDOM->getFromIntTo(17, 18);
		break;
	case GATE_7:
		m_GateMonsterNum = 2;
		m_GateMonsterIndex = RANDOM->getFromIntTo(1, 6);
		break;
	case GATE_8:
		m_GateMonsterNum = 2;
		m_GateMonsterIndex = RANDOM->getFromIntTo(7, 13);
		break;
	case GATE_9:
		m_GateMonsterNum = 3;
		m_GateMonsterIndex = RANDOM->getFromIntTo(14, 18);
		break;
	case GATE_10:
		m_GateMonsterNum = 3;
		m_GateMonsterIndex = RANDOM->getFromIntTo(1, 10);
		break;
	case GATE_11:
		m_GateMonsterNum = 3;
		m_GateMonsterIndex = RANDOM->getFromIntTo(11, 18);
		break;
	case GATE_12:
		m_GateMonsterNum = 3;
		m_GateMonsterIndex = RANDOM->getFromIntTo(1, 18);
		break;
	case GATE_13:
		m_GateMonsterNum = 3;
		m_GateMonsterIndex = RANDOM->getFromIntTo(1, 18);
		break;
	case GATE_14:
		m_GateMonsterNum = 3;
		m_GateMonsterIndex = RANDOM->getFromIntTo(1, 18);
		break;
	case GATE_15:
		m_GateMonsterNum = 3;
		m_GateMonsterIndex = RANDOM->getFromIntTo(1, 18);
		break;
	case GATE_16:
		m_GateMonsterNum = 3;
		m_GateMonsterIndex = RANDOM->getFromIntTo(1, 18);
		break;
	case GATE_17:
		m_GateMonsterNum = 4;
		m_GateMonsterIndex = RANDOM->getFromIntTo(1, 18);
		break;
	case GATE_18:
		m_GateMonsterNum = 4;
		m_GateMonsterIndex = RANDOM->getFromIntTo(1, 18);
		break;
	}

}

void stageScene::ClearEvent()
{
	if (m_stageNum >= 18 && m_ClearScore >= 500)
		SCENEMANAGER->changeScene("ending");
	
	

}

stageScene::stageScene()
{
}


stageScene::~stageScene()
{
}