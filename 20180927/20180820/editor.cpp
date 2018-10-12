
#include "resource.h"
#include "stdafx.h"
#include "editor.h"
#include "button.h"
#include "image.h"


char szFileName_1[512];
int editor::m_nPreviewNum = 0;


static void SpaceFunc_left(void)
{
	if ((editor::m_nPreviewNum) > 0)
		editor::m_nPreviewNum -= 1;
}

static void SpaceFunc_right(void)
{
	if ((editor::m_nPreviewNum) < 3)
		editor::m_nPreviewNum += 1;
}

void editor::ButtonEvent(HWND hWnd, UINT iMessage, WPARAM wParam)
{
	switch (LOWORD(wParam))
	{
	case 32788: //Save
		MessageBox(hWnd, "Save Button Clicked", "Button", MB_OK);
		SaveEvent();
		break;
	case 32791: // Load
		MessageBox(hWnd, "Load Button Clicked", "Button", MB_OK);
		LoadEvent();
		break;
	case 32781: // Save and Start
		MessageBox(hWnd, "Eraser Button Clicked", "Button", MB_OK);
		break;
	case 32801: // Exit
		PostQuitMessage(0);
		break;

	case 32773: // Terrains 
		st_obj = isTerrain;
		break;
	case 32774: // Units
		st_obj = isUnit;
		break;

	case 32783: // 사이즈체크
		st_selSize = x800;
		m_bIsSelectSize = true;
		break;
	case 32784:
		st_selSize = x1600;
		m_bIsSelectSize = true;
		break;
	case 32785:
		st_selSize = x2000;
		m_bIsSelectSize = true;
		break;
	case 32786:
		st_selSize = x2400;
		m_bIsSelectSize = true;
		break;

		//case IDM_NOTICE_HELP: // 32772
		//	DialogBox(g_hInstance, MAKEINTRESOURCE(ID_NOTICE_HELP), hWnd, NULL);
		//	break;
	}

	// aboutBox 여는법
	// 윈도우 MessageBox처럼 기본 함수가 있다.
}







HRESULT editor::init()
{
	init_image();
	st_selSize = x1600;
	st_selTile = tileset1;
	st_view = x1;
	m_bIsSelectSize = true; // 메뉴에서 사이즈체크시 초기화되고 사이즈 다시측정된다.
	m_bIsUnfold = true;
	m_isSel = false;
	m_bIsMiniMapOn = true;
	m_bIsTextOn = false;
	MiniMap_Ratio = 8;
	MAPCAMERA->init();

	tileReset();
	return S_OK;
}

void editor::init_image()
{
	m_pBG = IMAGEMANAGER->addImage("black", "image/wook/black.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("space_left", "image/wook/space_left.bmp", 36, 72, 1, 2, true, RGB(255, 255, 255));
	IMAGEMANAGER->addImage("space_right", "image/wook/space_right.bmp", 36, 72, 1, 2, true, RGB(255, 255, 255));

	m_pBox = IMAGEMANAGER->addImage("box", "image/wook/white.bmp", WINSIZEX, 250, true, RGB(255, 0, 255));
	m_pTileSet[0] = IMAGEMANAGER->addImage("tileset1", "image/wook/tileset1.bmp", 256, 192, 8, 6, true, RGB(255, 255, 255));
	m_pTileSet[1] = IMAGEMANAGER->addImage("tileset2", "image/wook/tileset2.bmp", 256, 192, 8, 6, true, RGB(255, 255, 255));
	m_pTileSet[2] = IMAGEMANAGER->addImage("tileset3", "image/wook/tileset3.bmp", 256, 192, 8, 6, true, RGB(255, 255, 255));
	m_pTileSet[3] = IMAGEMANAGER->addImage("tileset4", "image/wook/tileset4.bmp", 256, 192, 8, 6, true, RGB(255, 255, 255));


	m_pBtnLspace = new button;
	m_pBtnLspace->init("space_left", IMAGEMANAGER->findImage("space_left")->getWidth() / 2 + 0, WINSIZEY - 150, PointMake(0, 1), PointMake(0, 0), SpaceFunc_left);

	m_pBtnRspace = new button;
	m_pBtnRspace->init("space_right", IMAGEMANAGER->findImage("space_right")->getWidth() / 2 + 301, WINSIZEY - 150, PointMake(0, 1), PointMake(0, 0), SpaceFunc_right);

}

void editor::tileReset()
{
	// 기본 타일 정보 셋팅
	for (int x = 0; x < g_saveData.gTileMaxCountX; x++)
	{
		for (int y = 0; y < g_saveData.gTileMaxCountY; y++)
		{
			m_pTiles[x * g_saveData.gTileMaxCountX + y].rc = RectMake(0 + x * TILE_SIZEX, 0 + y * TILE_SIZEY, TILE_SIZEX, TILE_SIZEY);
			m_pTiles[x * g_saveData.gTileMaxCountX + y].terrainFrameX = 6;
			m_pTiles[x * g_saveData.gTileMaxCountX + y].terrainFrameY = 3;  // 29
			m_pTiles[x * g_saveData.gTileMaxCountX + y].SampleNum = 1;
		}
	}
}

void editor::release()
{
}

void editor::update()
{
	MAPCAMERA->update();
	SizeUpdate();
	KeyEvent();
	if (m_pBtnLspace && m_bIsUnfold)
		m_pBtnLspace->update();
	if (m_pBtnRspace && m_bIsUnfold)
		m_pBtnRspace->update();

	MouseEvent();

	if (m_pTileSet[0] && editor::m_nPreviewNum == 0)
		st_selTile = tileset1;
	if (m_pTileSet[1] && editor::m_nPreviewNum == 1)
		st_selTile = tileset2;
	if (m_pTileSet[2] && editor::m_nPreviewNum == 2)
		st_selTile = tileset3;
	if (m_pTileSet[3] && editor::m_nPreviewNum == 3)
		st_selTile = tileset4;


	if (m_bIsUnfold)
	{

		for (int j = 0; j < SAMPLE_COUNTY; ++j)
		{
			for (int i = 0; i < SAMPLE_COUNTX; ++i)
			{
				m_pSampleTiles[j * SAMPLE_COUNTX + i].rc = RectMake(40 + i * TILE_SIZEX,
					(WINSIZEY - 240) + j * TILE_SIZEY, TILE_SIZEX, TILE_SIZEY);
				m_pSampleTiles[j * SAMPLE_COUNTX + i].frameX = i; //8까지
				m_pSampleTiles[j * SAMPLE_COUNTX + i].frameY = j; //6까지
				m_pSampleTiles[j * SAMPLE_COUNTX + i].SampleNum = (int)st_selTile;
				// 샘플넘은 계속 바뀔것이다. 최초에는 1
			}
		}
	}

	for (int x = 0; x < g_saveData.gTileMaxCountX; x++)
	{
		for (int y = 0; y < g_saveData.gTileMaxCountY; y++)
		{
			m_pTiles[x * g_saveData.gTileMaxCountX + y].rc = RectMake(x * TILE_SIZEX - MAPCAMERA->getCameraX(), y * TILE_SIZEY - MAPCAMERA->getCameraY(), TILE_SIZEX, TILE_SIZEY);
		}
	}

}

void editor::SizeUpdate()
{
	if (m_bIsSelectSize == true)
	{
		g_saveData.gTileMaxCountX = st_selSize / TILE_SIZEX;
		g_saveData.gTileMaxCountY = st_selSize / TILE_SIZEY;
		//tagTile * m_pTiles = new tagTile[g_saveData.gTileMaxCountX * g_saveData.gTileMaxCountY];
		tileReset();
		m_bIsSelectSize = false;
	}
}

void editor::KeyEvent()
{
	MAPCAMERA->keyUpdate();

	if (KEYMANAGER->isOnceKeyDown(VK_PRIOR))
	{
		switch (st_view)
		{
		case x1:
			st_view = x2;
			break;
		case x2:
			st_view = x3;
			break;
		case x3:
			st_view = x1;
			break;
		}
	}
	if (KEYMANAGER->isOnceKeyDown(0x55)) // 'U'
	{
		if (m_bIsUnfold == true) // 이미 펼쳐져있다면
			m_bIsUnfold = false;
		else
			m_bIsUnfold = true;
	}
	if (KEYMANAGER->isOnceKeyDown(VK_F2))
		SCENEMANAGER->changeScene("stage");
	if (KEYMANAGER->isOnceKeyDown(VK_SPACE) && m_isSel == true)
		m_isSel = false; // 선택해제 단축키
	if (KEYMANAGER->isOnceKeyDown(VK_DELETE))
	{
		m_isSel = false;
		tileReset();  //초기화 단축키
	}
	if (KEYMANAGER->isOnceKeyDown('M') && m_bIsUnfold == true)
	{
		if (m_bIsMiniMapOn)
			m_bIsMiniMapOn = false;
		else
			m_bIsMiniMapOn = true;
	}
	if (KEYMANAGER->isOnceKeyDown(VK_F6))
	{
		if (m_bIsTextOn)
			m_bIsTextOn = false;
		else
			m_bIsTextOn = true;
	}

}

void editor::MouseEvent()
{
	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		st_mouse = tagMOUSE_STATE::MOUSE_DOWN1;
	}
	else if (KEYMANAGER->isOnceKeyUp(VK_LBUTTON) && st_mouse == tagMOUSE_STATE::MOUSE_DOWN1)
	{
		for (int i = 0; i < SAMPLE_COUNTX * SAMPLE_COUNTY; ++i)
		{
			if (PtInRect(&m_pSampleTiles[i].rc, g_ptMouse))
			{
				st_mouse = tagMOUSE_STATE::MOUSE_UP1;
				m_rcSelectedTile.left = m_pSampleTiles[i].frameX;
				m_rcSelectedTile.top = m_pSampleTiles[i].frameY;
				m_rcSelectedTileSampleNum = m_pSampleTiles[i].SampleNum;
				m_isSel = true;
			}
			else
			{
				st_mouse = tagMOUSE_STATE::MOUSE_IDLE1;
			}
		}
	}


	if (KEYMANAGER->isStayKeyDown(VK_LBUTTON) && m_isSel == true)
	{
		for (int i = 0; i < g_saveData.gTileMaxCountX * g_saveData.gTileMaxCountY; ++i)
		{
			if (m_bIsUnfold == true && g_ptMouse.y >= 542) continue;

			if (PtInRect(&m_pTiles[i].rc, g_ptMouse))
			{
				m_pTiles[i].terrainFrameX = m_rcSelectedTile.left;
				m_pTiles[i].terrainFrameY = m_rcSelectedTile.top;
				m_pTiles[i].SampleNum = m_rcSelectedTileSampleNum;
			}

		}
	}


}

void editor::render(HDC hdc)
{
	m_pBG->render(hdc, 0, 0);

	// 실제 뿌려지는 맵//
	render_mapTile(hdc);
	/////////////////////


	////////////////// 펼쳤을때의 이벤트 렌더링/////////////////
	if (m_bIsUnfold)
	{
		m_pBox->render(hdc, 0, WINSIZEY - 250);

		// 왼쪽에 나타나는 타일 미리보기 렌더링//
		if (m_pTileSet[0] && editor::m_nPreviewNum == 0)
			m_pTileSet[0]->render(hdc, 40, WINSIZEY - 240);
		if (m_pTileSet[1] && editor::m_nPreviewNum == 1)
			m_pTileSet[1]->render(hdc, 40, WINSIZEY - 240);
		if (m_pTileSet[2] && editor::m_nPreviewNum == 2)
			m_pTileSet[2]->render(hdc, 40, WINSIZEY - 240);
		if (m_pTileSet[3] && editor::m_nPreviewNum == 3)
			m_pTileSet[3]->render(hdc, 40, WINSIZEY - 240);
		///////////////////////////////////

		//미니맵//
		if (m_bIsMiniMapOn)
		{
			for (int x = 0; x < g_saveData.gTileMaxCountX; x++)
			{
				for (int y = 0; y < g_saveData.gTileMaxCountY; y++)
				{
					m_pTileSet[m_pTiles[x *  g_saveData.gTileMaxCountX + y].SampleNum]->RatioRender(hdc,
						550 + m_pTiles[x *  g_saveData.gTileMaxCountX + y].rc.left / MiniMap_Ratio,
						560 + m_pTiles[x *  g_saveData.gTileMaxCountX + y].rc.top / MiniMap_Ratio,
						m_pTiles[x *  g_saveData.gTileMaxCountX + y].terrainFrameX,
						m_pTiles[x *  g_saveData.gTileMaxCountX + y].terrainFrameY,
						MiniMap_Ratio,
						TILE_SIZEX,
						TILE_SIZEY);
				}
			}
		}
		//////////

		m_pBtnLspace->render(hdc);
		m_pBtnRspace->render(hdc);
	}
	////////////////////////////////////////////////////////////

	if (m_isSel == true)
	{
		m_pTileSet[m_rcSelectedTileSampleNum]->frameRender(hdc,
			g_ptMouse.x,
			g_ptMouse.y,
			m_rcSelectedTile.left,
			m_rcSelectedTile.top);
	}


	if (m_bIsTextOn)
	{
		char szText[256];

		// TRANSPARENT : 투명, OPAQUE : 불투명
		SetBkMode(hdc, TRANSPARENT);

		SetTextColor(hdc, RGB(255, 0, 255));

		sprintf_s(szText, "m_ptMoveCameraX : %f / m_ptMoveCameraY : %f",
			MAPCAMERA->getfocusCameraX(), MAPCAMERA->getfocusCameraY());
		TextOut(hdc, 400, 0, szText, strlen(szText));

		sprintf_s(szText, "m_ptCameraX : %f / m_ptCameraY : %f",
			MAPCAMERA->getCameraX(), MAPCAMERA->getCameraY());
		TextOut(hdc, 400, 100, szText, strlen(szText));
	}

	/*Rectangle(hdc, m_pTiles[x * g_saveData.gTileMaxCountX + y].rc.left,
		m_pTiles[x * g_saveData.gTileMaxCountX + y].rc.top, m_pTiles[x * g_saveData.gTileMaxCountX + y].rc.right,
		m_pTiles[x * g_saveData.gTileMaxCountX + y].rc.bottom);*/


}

void editor::render_mapTile(HDC hdc)
{

	for (int x = 0; x < g_saveData.gTileMaxCountX; x++)
	{
		for (int y = 0; y < g_saveData.gTileMaxCountY; y++)
		{
			m_pTileSet[m_pTiles[x *  g_saveData.gTileMaxCountX + y].SampleNum]->frameRender(hdc,
				m_pTiles[x *  g_saveData.gTileMaxCountX + y].rc.left,
				m_pTiles[x *  g_saveData.gTileMaxCountX + y].rc.top,
				m_pTiles[x *  g_saveData.gTileMaxCountX + y].terrainFrameX,
				m_pTiles[x *  g_saveData.gTileMaxCountX + y].terrainFrameY);
		}
	}

}









void editor::SaveEvent()
{
	int mapSize = (int)st_selSize;

	OPENFILENAME ofn;
	ZeroMemory(&ofn, sizeof(OPENFILENAME));
	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = g_hWnd;
	ofn.lpstrFilter = _T("txt Files(*.txt)\0*.txt\0All Files (*.*)\0*.*\0");
	ofn.lpstrFile = szFileName_1;
	ofn.nMaxFile = 512;
	//ofn.nFilterIndex = 1;
	//ofn.lpstrFileTitle = szFileName;
	//ofn.nMaxFileTitle = 0;
	//ofn.lpstrInitialDir = NULL;
	ofn.Flags = OFN_OVERWRITEPROMPT;
	GetSaveFileName(&ofn);

	TXTDATA->mapSave(szFileName_1, m_pTiles, &mapSize);

}

void editor::LoadEvent()
{
	int mapSize = (int)st_selSize;

	OPENFILENAME ofn;
	HWND hEditFileToBeOpened = NULL;

	ZeroMemory(&ofn, sizeof(OPENFILENAME));
	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = g_hWnd;
	ofn.lpstrFilter = "txt Files(*.txt)\0*.txt\0All Files (*.*)\0*.*\0"; //"All Files(*.*)\0*.*\0";
	ofn.lpstrFile = szFileName_1;
	ofn.nMaxFile = 512;

	if (0 != GetOpenFileName(&ofn))
	{
		SetWindowText(hEditFileToBeOpened, ofn.lpstrFile);
		TXTDATA->getSingleton()->mapLoad(szFileName_1, m_pTiles, &mapSize);
	}

}


editor::editor()
{
}


editor::~editor()
{
}
