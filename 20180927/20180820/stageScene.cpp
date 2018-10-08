#include "stdafx.h"
#include "stageScene.h"
#include "button.h"
#include "image.h"

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
	m_pTileSet[0] = IMAGEMANAGER->findImage("tiles1");
	m_pTileSet[1] = IMAGEMANAGER->findImage("tiles2");
	m_pTileSet[2] = IMAGEMANAGER->findImage("tiles3");
	m_pTileSet[3] = IMAGEMANAGER->findImage("tiles4");



	m_pImage_BG1 = IMAGEMANAGER->findImage("black");
	m_pImage_checkBox = IMAGEMANAGER->findImage("size_box");

	m_pButton1 = new button;
	m_pButton1->init("800x", WINSIZEX / 2, 80, PointMake(0, 1), PointMake(0, 0), Func_button1); // 시나리오

	m_pButton2 = new button;
	m_pButton2->init("800x", WINSIZEX / 2, 180, PointMake(0, 1), PointMake(0, 0), Func_button2); // 사용자 지정게임

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
		buttonNum = 3;
	}
	if (buttonNum == 3)
	{
		for (int x = 0; x < g_saveData.gTileMaxCountX; x++)
		{
			for (int y = 0; y < g_saveData.gTileMaxCountX; y++)
			{
				m_pTiles[x * g_saveData.gTileMaxCountX + y].rc = RectMake(x * TILE_SIZEX , y * TILE_SIZEY , TILE_SIZEX, TILE_SIZEY);
				
				/*if (m_pTiles[x * g_saveData.gTileMaxCountX + y].terrainFrameX == 100 && m_pTiles[x * g_saveData.gTileMaxCountX + y].terrainFrameY == 100)
					m_pTiles[x * g_saveData.gTileMaxCountX + y].isMove = false;
				else
					m_pTiles[x * g_saveData.gTileMaxCountX + y].isMove = true; // 특정 타일의 이동불가// */
			}
		}
	


	}
	
		

}

void stageScene::render(HDC hdc)
{
	m_pImage_BG1->render(hdc,0,0);
	if (buttonNum == 0)
	{
		m_pImage_checkBox->render(hdc, WINSIZEX / 2 - IMAGEMANAGER->findImage("size_box")->getWidth() / 2, 0);
		m_pButton1->render(hdc);
		m_pButton2->render(hdc);
	}
	if (buttonNum == 3)
	{
		for (int x = 0; x < g_saveData.gTileMaxCountX; x++)
		{
			for (int y = 0; y < g_saveData.gTileMaxCountY; y++)
			{

				switch (m_pTiles[x * g_saveData.gTileMaxCountX + y].SampleNum )
				{
				case 1:
					m_pTileSet[0]->frameRender(hdc,
						m_pTiles[x * g_saveData.gTileMaxCountX + y].rc.left,
						m_pTiles[x * g_saveData.gTileMaxCountX + y].rc.top,
						m_pTiles[x * g_saveData.gTileMaxCountX + y].terrainFrameX,
						m_pTiles[x * g_saveData.gTileMaxCountX + y].terrainFrameY);
					break;
				case 2:
					m_pTileSet[1]->frameRender(hdc,
						m_pTiles[x * g_saveData.gTileMaxCountX + y].rc.left,
						m_pTiles[x * g_saveData.gTileMaxCountX + y].rc.top,
						m_pTiles[x * g_saveData.gTileMaxCountX + y].terrainFrameX,
						m_pTiles[x * g_saveData.gTileMaxCountX + y].terrainFrameY);
					break;
				case 3:
					m_pTileSet[2]->frameRender(hdc,
						m_pTiles[x * g_saveData.gTileMaxCountX + y].rc.left,
						m_pTiles[x * g_saveData.gTileMaxCountX + y].rc.top,
						m_pTiles[x * g_saveData.gTileMaxCountX + y].terrainFrameX,
						m_pTiles[x * g_saveData.gTileMaxCountX + y].terrainFrameY);
					break;
				case 4:
					m_pTileSet[3]->frameRender(hdc,
						m_pTiles[x * g_saveData.gTileMaxCountX + y].rc.left,
						m_pTiles[x * g_saveData.gTileMaxCountX + y].rc.top,
						m_pTiles[x * g_saveData.gTileMaxCountX + y].terrainFrameX,
						m_pTiles[x * g_saveData.gTileMaxCountX + y].terrainFrameY);
					break;
				}

				/*Rectangle(hdc, m_pTiles[x * g_saveData.gTileMaxCountX + y].rc.left,
					m_pTiles[x * g_saveData.gTileMaxCountX + y].rc.top, m_pTiles[x * g_saveData.gTileMaxCountX + y].rc.right,
					m_pTiles[x * g_saveData.gTileMaxCountX + y].rc.bottom);*/

			}
		}

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
		TXTDATA->getSingleton()->mapLoad(szFileName1, m_pTiles, &MapSize);
	}
}

void stageScene::FixedLoadEvent()
{
	TXTDATA->getSingleton()->mapLoad("mainGame.map", m_pTiles, &MapSize);
}

stageScene::stageScene()
{
}


stageScene::~stageScene()
{
}
