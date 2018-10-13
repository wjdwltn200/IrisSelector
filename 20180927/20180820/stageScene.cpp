#include "stdafx.h"
#include "stageScene.h"
#include "button.h"
#include "image.h"
#include "PlayerCharacter.h"

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

	m_pPlayer = new PlayerCharacter;
	m_pPlayer->init();
	
	CAMERA->init();
	return S_OK;
}

void stageScene::release()
{
}

void stageScene::update()
{
	if (buttonNum == 0)
	{
		m_pButton1->update();
		m_pButton2->update();
	}
	if (buttonNum == 1)
	{
		FixedLoadEvent(); // 시나리오의 맵 최대크기는 1600 1600
		g_saveData.gTileMaxCountX = 40;
		g_saveData.gTileMaxCountY = 40;
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
				m_pTiles[x * g_saveData.gTileMaxCountX + y].rc = RectMake(x * TILE_SIZEX , y * TILE_SIZEY , TILE_SIZEX, TILE_SIZEY);
				
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
				else
					m_pTiles[x * g_saveData.gTileMaxCountX + y].isMove = true; // 특정 타일의 이동불가// */
			}
		}
	

		buttonNum++;
	}
	if (buttonNum == 4)
	{
		
		m_pPlayer->update();
		CAMERA->update();
		for (int x = 0; x < g_saveData.gTileMaxCountX; x++)
		{
			for (int y = 0; y < g_saveData.gTileMaxCountY; y++)
			{
				m_pTiles[x * g_saveData.gTileMaxCountX + y].rc = RectMake(x * TILE_SIZEX - CAMERA->getCameraX() , y * TILE_SIZEY - CAMERA->getCameraY(), TILE_SIZEX, TILE_SIZEY);
			}
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
			}

		}
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

	/*Rectangle(hdc, m_pTiles[x * g_saveData.gTileMaxCountX + y].rc.left,
		m_pTiles[x * g_saveData.gTileMaxCountX + y].rc.top, m_pTiles[x * g_saveData.gTileMaxCountX + y].rc.right,
		m_pTiles[x * g_saveData.gTileMaxCountX + y].rc.bottom);*/






	m_pPlayer->render(hdc);

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
		TXTDATA->getSingleton()->mapLoad(szFileName1, m_pTiles, &MapSize);
	}
}

void stageScene::FixedLoadEvent()
{
	TXTDATA->getSingleton()->mapLoad("mainGame2.map", m_pTiles, &MapSize);
}

stageScene::stageScene()
{
}


stageScene::~stageScene()
{
}
