#include "stdafx.h"
#include "editorScene.h"
#include "image.h"
#include "button.h"
#include "uiObject.h"
#include "uiButton.h"
#include "uiImageView.h"

char szFileName[512];

int editorScene::m_nMapSize = 800;
int editorScene::m_nPreviewNum = 0;
bool editorScene::m_bIsSizeCheck = false;

static void SpaceFunc_left(void)
{
	if((editorScene::m_nPreviewNum) > 0)
		editorScene::m_nPreviewNum -= 1;
}

static void SpaceFunc_right(void)
{
	if((editorScene::m_nPreviewNum) < 3)
		editorScene::m_nPreviewNum += 1;
}


static void Func_MapSize1(void)
{
	editorScene::m_nMapSize = 800;
}

static void Func_MapSize2(void)
{
	editorScene::m_nMapSize = 1600;
}

static void Func_MapSize3(void)
{
	editorScene::m_nMapSize = 2000;
}

static void Func_MapSize4(void)
{
	editorScene::m_nMapSize = 2400;
}

static void Func_MapCheck(void)
{
	editorScene::m_bIsSizeCheck = true;
}

void editorScene::ButtonEvent(HWND hWnd, UINT iMessage, WPARAM wParam)
{
	if (editorScene::m_bIsSizeCheck == true)
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
}

void editorScene::MouseEvent()
{
	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		btnState = BUTTONSTATE::BUTTON_DOWN;
	}
	else if (KEYMANAGER->isOnceKeyUp(VK_LBUTTON) && btnState == BUTTONSTATE::BUTTON_DOWN)
	{
		for (int i = 0; i < SAMPLE_X * SAMPLE_Y; ++i)
		{
			if (PtInRect(&m_pSampleTiles[i].rc, g_ptMouse))
			{
				btnState = BUTTONSTATE::BUTTON_UP;
				m_rcSelectedTile.left = m_pSampleTiles[i].frameX;
				m_rcSelectedTile.top = m_pSampleTiles[i].frameY;
				m_isSel = true; 
			}
			else
			{
				btnState = BUTTONSTATE::BUTTON_IDLE;
			}
		}
	}

	if (KEYMANAGER->isStayKeyDown(VK_LBUTTON) && m_isSel == true)
	{
		for (int i = 0; i < m_nTile_MaxCountX * m_nTile_MaxCountY; ++i)
		{
			if (PtInRect(&m_pTiles[i].rc, g_ptMouse))
			{
				m_pTiles[i].terrainFrameX = m_rcSelectedTile.left;
				m_pTiles[i].terrainFrameY = m_rcSelectedTile.top;
			}

		}
	}

	if (KEYMANAGER->isOnceKeyDown(VK_SPACE) && g_ptMouse.x < (WINSIZEX / 3) * 2)
	{
		m_isSel = false;
	}

}

void editorScene::SaveEvent()
{
}

void editorScene::LoadEvent()
{
}

void editorScene::TileSetting()
{
	// 기본 타일 정보 셋팅
	for (int x = 0; x < m_nTile_MaxCountX; x++)
	{
		for (int y = 0; y < m_nTile_MaxCountY; y++)
		{
			m_pTiles[x * m_nTile_MaxCountX + y].rc = RectMake(WINSIZEX/3 * 1 +  x * TILE_SIZE_Map, 140 +  y * TILE_SIZE_Map, TILE_SIZE_Map, TILE_SIZE_Map);
			m_pTiles[x * m_nTile_MaxCountX + y].terrainFrameX = 2;
			m_pTiles[x * m_nTile_MaxCountY + y].terrainFrameY = 0;  // 29
		}
	}

}


HRESULT editorScene::init()
{
	m_bWindowPrint = false;
	m_nMapSize = 800;

	m_pImg_SizeBox = IMAGEMANAGER->addImage("size_box","image/wook/size_box.bmp", 640, 640);
	IMAGEMANAGER->addImage("800x", "image/wook/800x.bmp", 320, 168,1,2,true,RGB(255,0,255));
	IMAGEMANAGER->addImage("1600x", "image/wook/1600x.bmp", 320, 168, 1, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("2000x", "image/wook/2000x.bmp", 320, 168, 1, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("2400x", "image/wook/2400x.bmp", 320, 168, 1, 2, true, RGB(255, 0, 255));
	m_pCheckSize = IMAGEMANAGER->addImage("size_check", "image/wook/size_check.bmp", 84, 84,1,1, true, RGB(255, 255, 255));
	
	m_pImg_Box1 = IMAGEMANAGER->addImage("box1", "image/wook/white.bmp", (WINSIZEX / 3) * 2 - 15, (WINSIZEY / 8) * 7 - 15, true ,RGB(255,0,255));
	m_pImg_Box2 = IMAGEMANAGER->addImage("box2", "image/wook/white.bmp", (WINSIZEX / 3) * 1 - 10, (WINSIZEY / 8) * 2 - 10, true, RGB(255, 0, 255));
	m_pImg_Box3 = IMAGEMANAGER->addImage("box3", "image/wook/white.bmp", (WINSIZEX / 3) * 1 - 10, (WINSIZEY / 8) * 5 - 15, true, RGB(255, 0, 255));
	m_pImg_Box4 = IMAGEMANAGER->addImage("box4", "image/wook/white.bmp", (WINSIZEX) * 1 - 15, (WINSIZEY / 8) * 1 - 10, true, RGB(255, 0, 255));
	m_pImg_BG = IMAGEMANAGER->addImage("BG", "image/wook/BG.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
	m_pTileSet1 = IMAGEMANAGER->addImage("tiles1", "image/wook/tiles1.bmp", 200, 360, 20, 9,true,RGB(255,0,255));
	m_pTileSet2 = IMAGEMANAGER->addImage("tiles2", "image/wook/tiles2.bmp", 200, 360, 20, 9, true, RGB(255, 0, 255));
	m_pTileSet3 = IMAGEMANAGER->addImage("tiles3", "image/wook/tiles3.bmp", 200, 360, 20, 9, true, RGB(255, 0, 255));
	m_pTileSet4 = IMAGEMANAGER->addImage("tiles4", "image/wook/tiles4.bmp", 200, 360, 20, 9, true, RGB(255, 0, 255));

	m_pImg_HorizontalBar = IMAGEMANAGER->addImage("horizontal_bar", "image/wook/width_bar.bmp", WINSIZEX, 15, true, RGB(255,0,255));
	m_pImg_VerticalBar = IMAGEMANAGER->addImage("vertical_bar", "image/wook/height_bar.bmp", 15, WINSIZEY, true, RGB(255, 0, 255));



	
	IMAGEMANAGER->addImage("space_left", "image/wook/space_left.bmp", 36, 72,1,2, true, RGB(255, 255, 255));
	IMAGEMANAGER->addImage("space_right", "image/wook/space_right.bmp", 36, 72,1,2, true, RGB(255, 255, 255));

	m_pBtnLspace = new button;
	m_pBtnLspace->init("space_left", IMAGEMANAGER->findImage("space_left")->getWidth()/2 + 10, 530, PointMake(0, 1), PointMake(0, 0), SpaceFunc_left);

	m_pBtnRspace = new button;
	m_pBtnRspace->init("space_right", IMAGEMANAGER->findImage("space_right")->getWidth() / 2 + (WINSIZEX / 3) -36, 530, PointMake(0, 1), PointMake(0, 0), SpaceFunc_right);


	for (int j = 0; j < SAMPLE_Y; ++j)
	{
		for (int i = 0; i < SAMPLE_X; ++i)
		{
			m_pSampleTiles[j * SAMPLE_X + i].rc = RectMake(WINSIZEX - m_pTileSet1->getWidth() + i * TILE_SIZE_Preview,
			j * TILE_SIZE_Preview, TILE_SIZE_Preview, TILE_SIZE_Preview);
			m_pSampleTiles[j * SAMPLE_X + i].frameX = i;
			m_pSampleTiles[j * SAMPLE_X + i].frameY = j;
		}
	}

	SetSize();

	return S_OK;

}

void editorScene::SetSize()
{
	m_pImg_Box5 = IMAGEMANAGER->addImage("box5", "image/wook/white.bmp", 320,84, true, RGB(255, 0, 255));

	m_pBtn800x = new button;
	m_pBtn800x->init("800x", WINSIZEX / 2, 80, PointMake(0, 1), PointMake(0, 0), Func_MapSize1);
	
	m_pBtn1600x = new button;
	m_pBtn1600x->init("1600x", WINSIZEX / 2 , 180, PointMake(0, 1), PointMake(0, 0), Func_MapSize2);

	m_pBtn2000x = new button;
	m_pBtn2000x->init("2000x", WINSIZEX / 2, 280, PointMake(0, 1), PointMake(0, 0), Func_MapSize3);

	m_pBtn2400x = new button;
	m_pBtn2400x->init("2400x", WINSIZEX / 2 , 380, PointMake(0, 1), PointMake(0, 0), Func_MapSize4);

	m_pBtnSizeCheck = new button;
	m_pBtnSizeCheck->init("size_check", WINSIZEX/ 2  + m_pImg_SizeBox->getWidth()/2 - IMAGEMANAGER->findImage("size_check")->getWidth()/ 2, WINSIZEY / 2 + m_pImg_SizeBox->getHeight() / 2 - (IMAGEMANAGER->findImage("size_check")->getHeight() / 2 + 84), PointMake(0, 1), PointMake(0, 0), Func_MapCheck);
}


void editorScene::release()
{
	SAFE_DELETE(m_pBtnLspace);
	SAFE_DELETE(m_pBtnRspace);
}

void editorScene::update()
{



	if (KEYMANAGER->isOnceKeyDown(0x71))
		SCENEMANAGER->changeScene("title");

	if (editorScene::m_bIsSizeCheck == true)
	{
		if (m_pBtnLspace)
			m_pBtnLspace->update();
		if (m_pBtnRspace)
			m_pBtnRspace->update();


		if (m_bWindowPrint == false)
		{
			m_hBtnSave = CreateWindow("button", "Save", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
				WINSIZEY - 264, 60, 74, 40, g_hWnd, HMENU(0), g_hInstance, NULL);

			m_hBtnLoad = CreateWindow("button", "Load", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
				WINSIZEY - 176, 60, 74, 40, g_hWnd, HMENU(1), g_hInstance, NULL);

			m_hBtnEraser = CreateWindow("button", "Erase", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
				WINSIZEY - 88, 60, 74, 40, g_hWnd, HMENU(2), g_hInstance, NULL);
		
			m_nTile_MaxCountX = editorScene::m_nMapSize / TILE_SIZE_Map;
			m_nTile_MaxCountY = editorScene::m_nMapSize / TILE_SIZE_Map;
			//tagTile * m_pTiles = new tagTile; // 입력된 수만큼 배열생성 (최대 맵 사이즈 설정된다.)
			TileSetting();



			m_bWindowPrint = true;
		}
		
	}

	if (editorScene::m_bIsSizeCheck == false)
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
	}
	

	MouseEvent();
}




void editorScene::render(HDC hdc)
{
	m_pImg_BG->render(hdc, 0, 0);
	m_pImg_Box1->render(hdc, (WINSIZEX / 3) * 1 + 10, (WINSIZEY / 8) * 1 + 10);
	m_pImg_Box2->render(hdc, 10, (WINSIZEY / 8) * 1 + 10);
	m_pImg_Box3->render(hdc, 10, (WINSIZEY / 8) * 3 + 10);
	m_pImg_Box4->render(hdc, 10, 10);


	if (editorScene::m_bIsSizeCheck == true)
	{
		if (m_pTileSet1 && editorScene::m_nPreviewNum == 0)
			m_pTileSet1->render(hdc, 40, (WINSIZEY / 8) * 3 + 10);
		if (m_pTileSet2 && editorScene::m_nPreviewNum == 1)
			m_pTileSet2->render(hdc, 40, (WINSIZEY / 8) * 3 + 10);
		if (m_pTileSet3 && editorScene::m_nPreviewNum == 2)
			m_pTileSet3->render(hdc, 40, (WINSIZEY / 8) * 3 + 10);
		if (m_pTileSet4 && editorScene::m_nPreviewNum == 3)
			m_pTileSet4->render(hdc, 40, (WINSIZEY / 8) * 3 + 10);
		m_pBtnLspace->render(hdc);
		m_pBtnRspace->render(hdc);
	

		for (int x = 0; x < m_nTile_MaxCountX; ++x)
		{
			for (int y = 0; y < m_nTile_MaxCountY; ++y)
			{
				m_pTileSet1->frameRender(hdc,
					m_pTiles[x * m_nTile_MaxCountX + y].rc.left,
					m_pTiles[x * m_nTile_MaxCountX + y].rc.top,
					m_pTiles[x * m_nTile_MaxCountX + y].terrainFrameX,
					m_pTiles[x * m_nTile_MaxCountX + y].terrainFrameY);

				m_pTileSet2->frameRender(hdc,
					m_pTiles[x * m_nTile_MaxCountX + y].rc.left,
					m_pTiles[x * m_nTile_MaxCountX + y].rc.top,
					m_pTiles[x * m_nTile_MaxCountX + y].terrainFrameX,
					m_pTiles[x * m_nTile_MaxCountX + y].terrainFrameY);

				m_pTileSet3->frameRender(hdc,
					m_pTiles[x * m_nTile_MaxCountX + y].rc.left,
					m_pTiles[x * m_nTile_MaxCountX + y].rc.top,
					m_pTiles[x * m_nTile_MaxCountX + y].terrainFrameX,
					m_pTiles[x * m_nTile_MaxCountX + y].terrainFrameY);

				m_pTileSet4->frameRender(hdc,
					m_pTiles[x * m_nTile_MaxCountX + y].rc.left,
					m_pTiles[x * m_nTile_MaxCountX + y].rc.top,
					m_pTiles[x * m_nTile_MaxCountX + y].terrainFrameX,
					m_pTiles[x * m_nTile_MaxCountX + y].terrainFrameY);
			}
		}

	
		if (m_isSel == true)
		{
			m_pTileSet1->frameRender(hdc,
				g_ptMouse.x,
				g_ptMouse.y,
				m_rcSelectedTile.left,
				m_rcSelectedTile.top);
			m_pTileSet2->frameRender(hdc,
				g_ptMouse.x,
				g_ptMouse.y,
				m_rcSelectedTile.left,
				m_rcSelectedTile.top);
			m_pTileSet3->frameRender(hdc,
				g_ptMouse.x,
				g_ptMouse.y,
				m_rcSelectedTile.left,
				m_rcSelectedTile.top);
			m_pTileSet4->frameRender(hdc,
				g_ptMouse.x,
				g_ptMouse.y,
				m_rcSelectedTile.left,
				m_rcSelectedTile.top);
		}
	}


	if (editorScene::m_bIsSizeCheck == false)
	{
		m_pImg_SizeBox->render(hdc, WINSIZEX / 2 - IMAGEMANAGER->findImage("size_box")->getWidth() / 2, 0);
		m_pBtn800x->render(hdc);
		m_pBtn1600x->render(hdc);
		m_pBtn2000x->render(hdc);
		m_pBtn2400x->render(hdc);
		m_pBtnSizeCheck->render(hdc);

		m_pImg_Box5->render(hdc, WINSIZEX / 2 - m_pImg_Box5->getWidth() / 2, 440);
	}

	m_pImg_HorizontalBar->render(hdc, 0, WINSIZEY - 15);
	m_pImg_VerticalBar->render(hdc, WINSIZEX - 15, 0);

}

editorScene::editorScene()
{
}


editorScene::~editorScene()
{
}


