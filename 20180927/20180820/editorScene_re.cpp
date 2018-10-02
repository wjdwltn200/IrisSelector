#include "stdafx.h"
#include "editorScene_re.h"
#include "button.h"
#include "image.h"

char szFileName[512];
bool editorScene_re::m_bIsSizeCheck = false;
int editorScene_re::m_nMapSize = 0;
int editorScene_re::m_nPreviewNum = 0;


static void SpaceFunc_left(void)
{
	if ((editorScene_re::m_nPreviewNum) > 0)
		editorScene_re::m_nPreviewNum -= 1;
}

static void SpaceFunc_right(void)
{
	if ((editorScene_re::m_nPreviewNum) < 3)
		editorScene_re::m_nPreviewNum += 1;
}

static void Func_MapSize1(void)
{
	editorScene_re::m_nMapSize = 800;
}

static void Func_MapSize2(void)
{
	editorScene_re::m_nMapSize = 1600;
}

static void Func_MapSize3(void)
{
	editorScene_re::m_nMapSize = 2000;
}

static void Func_MapSize4(void)
{
	editorScene_re::m_nMapSize = 2400;
}

static void Func_MapCheck(void)
{
	editorScene_re::m_bIsSizeCheck = true;
}

void editorScene_re::SetSize()
{
	m_pImg_SizeBox = IMAGEMANAGER->addImage("size_box", "image/wook/size_box.bmp", 640, 640);
	IMAGEMANAGER->addImage("800x", "image/wook/800x.bmp", 320, 168, 1, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("1600x", "image/wook/1600x.bmp", 320, 168, 1, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("2000x", "image/wook/2000x.bmp", 320, 168, 1, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("2400x", "image/wook/2400x.bmp", 320, 168, 1, 2, true, RGB(255, 0, 255));
	m_pCheckSize = IMAGEMANAGER->addImage("size_check", "image/wook/size_check.bmp", 84, 84, 1, 1, true, RGB(255, 255, 255));
	m_pImg_Box5 = IMAGEMANAGER->addImage("box5", "image/wook/white.bmp", 320, 84, true, RGB(255, 0, 255));

	m_pBtn800x = new button;
	m_pBtn800x->init("800x", WINSIZEX / 2, 80, PointMake(0, 1), PointMake(0, 0), Func_MapSize1);

	m_pBtn1600x = new button;
	m_pBtn1600x->init("1600x", WINSIZEX / 2, 180, PointMake(0, 1), PointMake(0, 0), Func_MapSize2);

	m_pBtn2000x = new button;
	m_pBtn2000x->init("2000x", WINSIZEX / 2, 280, PointMake(0, 1), PointMake(0, 0), Func_MapSize3);

	m_pBtn2400x = new button;
	m_pBtn2400x->init("2400x", WINSIZEX / 2, 380, PointMake(0, 1), PointMake(0, 0), Func_MapSize4);

	m_pBtnSizeCheck = new button;
	m_pBtnSizeCheck->init("size_check", WINSIZEX / 2 + m_pImg_SizeBox->getWidth() / 2 - IMAGEMANAGER->findImage("size_check")->getWidth() / 2, WINSIZEY / 2 + m_pImg_SizeBox->getHeight() / 2 - (IMAGEMANAGER->findImage("size_check")->getHeight() / 2 + 84), PointMake(0, 1), PointMake(0, 0), Func_MapCheck);

	m_bWindowPrint = false;
}

void editorScene_re::init_Setting()
{
	m_pImg_Box1 = IMAGEMANAGER->addImage("box1", "image/wook/white.bmp", (WINSIZEX / 3) * 2 - 15, (WINSIZEY / 8) * 7 - 15, true, RGB(255, 0, 255));
	m_pImg_Box2 = IMAGEMANAGER->addImage("box2", "image/wook/white.bmp", (WINSIZEX / 3) * 1 - 10, (WINSIZEY / 8) * 2 - 10, true, RGB(255, 0, 255));
	m_pImg_Box3 = IMAGEMANAGER->addImage("box3", "image/wook/white.bmp", (WINSIZEX / 3) * 1 - 10, (WINSIZEY / 8) * 5 - 15, true, RGB(255, 0, 255));
	m_pImg_Box4 = IMAGEMANAGER->addImage("box4", "image/wook/white.bmp", (WINSIZEX) * 1 - 15, (WINSIZEY / 8) * 1 - 10, true, RGB(255, 0, 255));
	m_pImg_BG = IMAGEMANAGER->addImage("BG", "image/wook/BG.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
	m_pTileSet[0] = IMAGEMANAGER->addImage("tiles1", "image/wook/tiles1.bmp", 200, 360, 5, 9, true, RGB(255, 0, 255));
	m_pTileSet[1] = IMAGEMANAGER->addImage("tiles2", "image/wook/tiles2.bmp", 200, 360, 5, 9, true, RGB(255, 0, 255));
	m_pTileSet[2] = IMAGEMANAGER->addImage("tiles3", "image/wook/tiles3.bmp", 200, 360, 5, 9, true, RGB(255, 0, 255));
	m_pTileSet[3] = IMAGEMANAGER->addImage("tiles4", "image/wook/tiles4.bmp", 200, 360, 5, 9, true, RGB(255, 0, 255));

	IMAGEMANAGER->addImage("space_left", "image/wook/space_left.bmp", 36, 72, 1, 2, true, RGB(255, 255, 255));
	IMAGEMANAGER->addImage("space_right", "image/wook/space_right.bmp", 36, 72, 1, 2, true, RGB(255, 255, 255));

	m_pBtnLspace = new button;
	m_pBtnLspace->init("space_left", IMAGEMANAGER->findImage("space_left")->getWidth() / 2 + 10, 530, PointMake(0, 1), PointMake(0, 0), SpaceFunc_left);

	m_pBtnRspace = new button;
	m_pBtnRspace->init("space_right", IMAGEMANAGER->findImage("space_right")->getWidth() / 2 + (WINSIZEX / 3) - 36, 530, PointMake(0, 1), PointMake(0, 0), SpaceFunc_right);

	for (int j = 0; j < SAMPLE_COUNTY; ++j)
	{
		for (int i = 0; i < SAMPLE_COUNTX; ++i)
		{
			m_pSampleTiles[j * SAMPLE_COUNTX + i].rc = RectMake((40 + m_pTileSet[0]->getWidth()) - (m_pTileSet[0]->getWidth()) + i * TILE_SIZEX,
				(WINSIZEY / 8) * 3 + 10 + j * TILE_SIZEY, TILE_SIZEX, TILE_SIZEY);
			m_pSampleTiles[j * SAMPLE_COUNTX + i].frameX = i;
			m_pSampleTiles[j * SAMPLE_COUNTX + i].frameY = j;
		}
	}

}







void editorScene_re::ButtonEvent(HWND hWnd, UINT iMessage, WPARAM wParam)
{
	switch (LOWORD(wParam))
	{
	case 0:
		MessageBox(hWnd, "Save Button Clicked", "Button", MB_OK);
		SaveEvent();
		break;
	case 1:
		MessageBox(hWnd, "Load Button Clicked", "Button", MB_OK);
		LoadEvent();
		break;
	case 2:
		MessageBox(hWnd, "Eraser Button Clicked", "Button", MB_OK);
		break;
	}
}

void editorScene_re::SaveEvent()
{
}

void editorScene_re::LoadEvent()
{
}

HRESULT editorScene_re::init()
{
	m_editSt = STATE_SETSIZE;
	SetSize();
	init_Setting();


	return S_OK;
}

void editorScene_re::release()
{
}

void editorScene_re::update()
{
	if (KEYMANAGER->isOnceKeyDown(0x71))
		SCENEMANAGER->changeScene("title");

	if (m_editSt != STATE_SETSIZE && m_bWindowPrint == false)
	{
		m_hBtnSave = CreateWindow("button", "Save", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			WINSIZEY - 234, 60, 74, 40, g_hWnd, HMENU(0), g_hInstance, NULL);

		m_hBtnLoad = CreateWindow("button", "Load", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			WINSIZEY - 156, 60, 74, 40, g_hWnd, HMENU(1), g_hInstance, NULL);

		m_hBtnEraser = CreateWindow("button", "Erase", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			WINSIZEY - 78, 60, 74, 40, g_hWnd, HMENU(2), g_hInstance, NULL);
		m_bWindowPrint = true;
	}

	if (m_editSt == STATE_SETSIZE)
	{
		if (m_pBtn800x)
			m_pBtn800x->update();
		if (m_pBtn1600x)
			m_pBtn1600x->update();
		if (m_pBtn2000x)
			m_pBtn2000x->update();
		if (m_pBtn2400x)
			m_pBtn2400x->update();
		if (m_pBtnSizeCheck)
			m_pBtnSizeCheck->update();

		if (m_bIsSizeCheck == true)
		{
			m_nTileMaxCountX = editorScene_re::m_nMapSize / 40;
			m_nTileMaxCountY = editorScene_re::m_nMapSize / 40;

			// 기본 타일 정보 셋팅
			for (int x = 0; x < m_nTileMaxCountX; x++)
			{
				for (int y = 0; y < m_nTileMaxCountY; y++)
				{
					m_pTiles[x * m_nTileMaxCountX + y].rc = RectMake((WINSIZEX / 3) * 1 + 10 + x * TILE_SIZEX, (WINSIZEY / 8) * 1 + 10 +  y * TILE_SIZEY, TILE_SIZEX, TILE_SIZEY);
					m_pTiles[x * m_nTileMaxCountX + y].terrainFrameX = 1;
					m_pTiles[x * m_nTileMaxCountX + y].terrainFrameY = 0;  // 29
				}
			}

			m_editSt = STATE_MAP1;
		}
	}
	else
	{
		if(m_pBtnLspace)
			m_pBtnLspace->update();
		if(m_pBtnRspace)
			m_pBtnRspace->update();

	}


}

void editorScene_re::render(HDC hdc)
{
	if (m_editSt == STATE_SETSIZE)
	{
		m_pImg_SizeBox->render(hdc, WINSIZEX / 2 - IMAGEMANAGER->findImage("size_box")->getWidth() / 2, 0);
		m_pBtn800x->render(hdc);
		m_pBtn1600x->render(hdc);
		m_pBtn2000x->render(hdc);
		m_pBtn2400x->render(hdc);
		m_pBtnSizeCheck->render(hdc);
		m_pImg_Box5->render(hdc, WINSIZEX / 2 - m_pImg_Box5->getWidth() / 2, 440);
	}
	else
	{
		m_pImg_BG->render(hdc, 0, 0);
		m_pImg_Box1->render(hdc, (WINSIZEX / 3) * 1 + 10, (WINSIZEY / 8) * 1 + 10);
		m_pImg_Box2->render(hdc, 10, (WINSIZEY / 8) * 1 + 10);
		m_pImg_Box3->render(hdc, 10, (WINSIZEY / 8) * 3 + 10);
		m_pImg_Box4->render(hdc, 10, 10);

		m_pBtnLspace->render(hdc);
		m_pBtnRspace->render(hdc);

		if (m_pTileSet[0] && editorScene_re::m_nPreviewNum == 0)
			m_pTileSet[0]->render(hdc, 40, (WINSIZEY / 8) * 3 + 10);
		if (m_pTileSet[1] && editorScene_re::m_nPreviewNum == 1)
			m_pTileSet[1]->render(hdc, 40, (WINSIZEY / 8) * 3 + 10);
		if (m_pTileSet[2] && editorScene_re::m_nPreviewNum == 2)
			m_pTileSet[2]->render(hdc, 40, (WINSIZEY / 8) * 3 + 10);
		if (m_pTileSet[3] && editorScene_re::m_nPreviewNum == 3)
			m_pTileSet[3]->render(hdc, 40, (WINSIZEY / 8) * 3 + 10);


		for (int i = 0; i < 4; ++i)
		{
			m_pTileSet[i]->frameRender(hdc,
				g_ptMouse.x,
				g_ptMouse.y,
				m_rcSelectedTile.left,
				m_rcSelectedTile.top);
		}

		for (int x = 0; x < SAMPLE_COUNTX; x++)
		{
			for (int y = 0; y < SAMPLE_COUNTY; y++)
			{
				for (int x = 0; x < 4; ++x)
				{
					m_pTileSet[x]->frameRender(hdc,
						m_pTiles[x * SAMPLE_COUNTX + y].rc.left,
						m_pTiles[x * SAMPLE_COUNTX + y].rc.top,
						m_pTiles[x * SAMPLE_COUNTX + y].terrainFrameX,
						m_pTiles[x * SAMPLE_COUNTX + y].terrainFrameY);
				}
			}
		}


	}
}


editorScene_re::editorScene_re()
{
}

editorScene_re::~editorScene_re()
{
}

