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
	editorScene_re::m_nPreviewNum = 0;
}

void editorScene_re::SetSize()
{
	m_nMouseWheelState = 0;

	m_pImg_SizeBox = IMAGEMANAGER->addImage("size_box", "image/wook/size_box.bmp", 640, 640,true, RGB(255,0,255));
	IMAGEMANAGER->addImage("black", "image/wook/black.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));

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
	m_bTempTrigger = false;

	FixedCamera.left = CAMERA_destX;
	FixedCamera.right = CAMERA_destX + m_Camera.m_nWidth;
	FixedCamera.top = CAMERA_destY;
	FixedCamera.bottom = CAMERA_destY + m_Camera.m_nHeight;


	m_Camera.m_ninitX = 0;
	m_Camera.m_ninitY = 0;
	m_Camera.m_nHeight = CAMERA_HEIGHT;
	m_Camera.m_nWidth = CAMARA_WIDTH;
	m_Camera.m_rc.left = CAMERA_destX;
	m_Camera.m_rc.right = CAMERA_destX + m_Camera.m_nWidth;
	m_Camera.m_rc.top = CAMERA_destY;
	m_Camera.m_rc.bottom = CAMERA_destY + m_Camera.m_nHeight;
	m_Camera.m_nX = m_Camera.m_rc.left;
	m_Camera.m_nY = m_Camera.m_rc.right;

	m_MiniMap.m_nX = MINIMAP_destX;
	m_MiniMap.m_nY = MINIMAP_destY;
	m_MiniMap.m_rc.left =  MINIMAP_destX;
	m_MiniMap.m_rc.right = MINIMAP_destX + MINIMAP_WIDTH;
	m_MiniMap.m_rc.top = MINIMAP_destY;
	m_MiniMap.m_rc.bottom = MINIMAP_destY + MINIMAP_HEIGHT;


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

void editorScene_re::MouseEvent()
{
	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		m_mouseSt = MOUSE_STATE::MOUSE_DOWN;
	}
	else if (KEYMANAGER->isOnceKeyUp(VK_LBUTTON) && m_mouseSt == MOUSE_STATE::MOUSE_DOWN)
	{
		for (int i = 0; i < SAMPLE_COUNTX * SAMPLE_COUNTY; ++i)
		{
			if (PtInRect(&m_pSampleTiles[i].rc, g_ptMouse))
			{
				m_mouseSt = MOUSE_STATE::MOUSE_UP;
				m_rcSelectedTile.left = m_pSampleTiles[i].frameX;
				m_rcSelectedTile.top = m_pSampleTiles[i].frameY;
				m_rcSelectedTileSampleNum = m_pSampleTiles[i].SampleNum;
				m_isSel = true;
			}
			else
			{
				m_mouseSt = MOUSE_STATE::MOUSE_IDLE;
			}
		}
	}

	if (KEYMANAGER->isStayKeyDown(VK_LBUTTON) && m_isSel == true)
	{
		for (int i = 0; i < m_nTileMaxCountX * m_nTileMaxCountY; ++i)
		{
			if (PtInRect(&m_pTiles[i].rc, g_ptMouse))
			{
				m_pTiles[i].terrainFrameX = m_rcSelectedTile.left;
				m_pTiles[i].terrainFrameY = m_rcSelectedTile.top;
				m_pTiles[i].SampleNum = m_rcSelectedTileSampleNum;
			}

		}
	}

}

void editorScene_re::CameraUpdate()
{
	if (m_Camera.m_nX < 0) m_Camera.m_nX = 0;
	if (m_Camera.m_nX > (g_saveData.gTileMaxCountX * 40)) (g_saveData.gTileMaxCountX * 40 - m_Camera.m_nWidth);
	if (m_Camera.m_nY < 0) m_Camera.m_nY = 0;
	if (m_Camera.m_nY > (g_saveData.gTileMaxCountY * 40)) (g_saveData.gTileMaxCountY * 40 - m_Camera.m_nHeight);


	if (KEYMANAGER->isStayKeyDown(VK_LEFT) && m_Camera.m_rc.left > CAMERA_destX)
	{
		m_Camera.m_nX -= CAMERA_SPEED;
		m_Camera.m_ninitX -= CAMERA_SPEED;

		for (int x = 0; x < m_nTileMaxCountX; x++)
		{
			for (int y = 0; y < m_nTileMaxCountY; y++)
			{
				m_pTiles[x * m_nTileMaxCountX + y].rc.left += CAMERA_SPEED;
				m_pTiles[x * m_nTileMaxCountX + y].rc.right += CAMERA_SPEED;

			}
		}
	}
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT) && m_Camera.m_rc.right < CAMERA_destX + m_nMapSize)
	{
		m_Camera.m_ninitX += CAMERA_SPEED;
		m_Camera.m_nX += CAMERA_SPEED;

		for (int x = 0; x < m_nTileMaxCountX; x++)
		{
			for (int y = 0; y < m_nTileMaxCountY; y++)
			{
				m_pTiles[x * m_nTileMaxCountX + y].rc.left -= CAMERA_SPEED;
				m_pTiles[x * m_nTileMaxCountX + y].rc.right -= CAMERA_SPEED;
			}
		}
	}
	if (KEYMANAGER->isStayKeyDown(VK_UP) && m_Camera.m_rc.top > WINSIZEY)
	{
		m_Camera.m_nY -= CAMERA_SPEED;
		m_Camera.m_ninitY -= CAMERA_SPEED;
		for (int x = 0; x < m_nTileMaxCountX; x++)
		{
			for (int y = 0; y < m_nTileMaxCountY; y++)
			{
				if(m_pTiles[x * m_nTileMaxCountX + y].rc.top )

				m_pTiles[x * m_nTileMaxCountX + y].rc.bottom += CAMERA_SPEED;
				m_pTiles[x * m_nTileMaxCountX + y].rc.top += CAMERA_SPEED;
			}
		}
	}
	if (KEYMANAGER->isStayKeyDown(VK_DOWN) && m_Camera.m_rc.bottom < WINSIZEY + m_nMapSize)
	{
		m_Camera.m_nY += CAMERA_SPEED;
		m_Camera.m_ninitY += CAMERA_SPEED;
		for (int x = 0; x < m_nTileMaxCountX; x++)
		{
			for (int y = 0; y < m_nTileMaxCountY; y++)
			{
				m_pTiles[x * m_nTileMaxCountX + y].rc.bottom -= CAMERA_SPEED;
				m_pTiles[x * m_nTileMaxCountX + y].rc.top -= CAMERA_SPEED;

			}
		}
	}


	m_Camera.m_rc.left = m_Camera.m_nX;
	m_Camera.m_rc.right = m_Camera.m_rc.left + m_Camera.m_nWidth;
	m_Camera.m_rc.top = m_Camera.m_nY;
	m_Camera.m_rc.bottom = m_Camera.m_rc.top + m_Camera.m_nHeight;

	

	
}

void editorScene_re::SaveEvent()
{
	OPENFILENAME ofn;
	ZeroMemory(&ofn, sizeof(OPENFILENAME));
	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = g_hWnd;
	ofn.lpstrFilter = _T("txt Files(*.txt)\0*.txt\0All Files (*.*)\0*.*\0");
	ofn.lpstrFile = szFileName;
	ofn.nMaxFile = 512;
	//ofn.nFilterIndex = 1;
	//ofn.lpstrFileTitle = szFileName;
	//ofn.nMaxFileTitle = 0;
	//ofn.lpstrInitialDir = NULL;
	ofn.Flags = OFN_OVERWRITEPROMPT;
	GetSaveFileName(&ofn);

	TXTDATA->mapSave(szFileName, m_pTiles, &m_nMapSize);

}

void editorScene_re::LoadEvent()
{
	OPENFILENAME ofn;
	HWND hEditFileToBeOpened = NULL;

	ZeroMemory(&ofn, sizeof(OPENFILENAME));
	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = g_hWnd;
	ofn.lpstrFilter = "txt Files(*.txt)\0*.txt\0All Files (*.*)\0*.*\0"; //"All Files(*.*)\0*.*\0";
	ofn.lpstrFile = szFileName;
	ofn.nMaxFile = 512;

	if (0 != GetOpenFileName(&ofn))
	{
		SetWindowText(hEditFileToBeOpened, ofn.lpstrFile);
		TXTDATA->getSingleton()->mapLoad(szFileName, m_pTiles, &m_nLoadMapSIze);
	}

}

void editorScene_re::WheelEvent(int num, WPARAM wParam)
{
	/*m_nMouseWheelState += num;
	if (m_nMouseWheelState > 2)
		m_nMouseWheelState = 2;
	else if (m_nMouseWheelState < -2)
		m_nMouseWheelState = -2;*/



		m_nMouseWheelState += num;
		if (m_nMouseWheelState > 2)
			m_nMouseWheelState = 2;
		if (m_nMouseWheelState < -2)
			m_nMouseWheelState = -2;
	

}

HRESULT editorScene_re::init()
{
	m_editSt = STATE_SETSIZE;
	m_nPreviewNum = 100;
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
	{
		SCENEMANAGER->changeScene("title");
		DestroyWindow(m_hBtnLoad);
		DestroyWindow(m_hBtnSave);
		DestroyWindow(m_hBtnEraser);
	}
	if (KEYMANAGER->isOnceKeyDown(0x72))
	{
		SCENEMANAGER->changeScene("stage");
		DestroyWindow(m_hBtnLoad);
		DestroyWindow(m_hBtnSave);
		DestroyWindow(m_hBtnEraser);

	}



	if (m_editSt != STATE_SETSIZE && m_bWindowPrint == false )
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
			editorScene_re::m_editSt = STATE_MAP1;

	}
	else
	{

		if (m_pTileSet[0] && editorScene_re::m_nPreviewNum == 0)
			m_editSt = STATE_MAP1;
		if (m_pTileSet[1] && editorScene_re::m_nPreviewNum == 1)
			m_editSt = STATE_MAP2;
		if (m_pTileSet[2] && editorScene_re::m_nPreviewNum == 2)
			m_editSt = STATE_MAP3;
		if (m_pTileSet[3] && editorScene_re::m_nPreviewNum == 3)
			m_editSt = STATE_MAP4;

		for (int j = 0; j < SAMPLE_COUNTY; ++j)
		{
			for (int i = 0; i < SAMPLE_COUNTX; ++i)
			{
				m_pSampleTiles[j * SAMPLE_COUNTX + i].rc = RectMake((40 + m_pTileSet[0]->getWidth()) - (m_pTileSet[0]->getWidth()) + i * TILE_SIZEX,
					(WINSIZEY / 8) * 3 + 10 + j * TILE_SIZEY, TILE_SIZEX, TILE_SIZEY);
				m_pSampleTiles[j * SAMPLE_COUNTX + i].frameX = i; // 4까지
				m_pSampleTiles[j * SAMPLE_COUNTX + i].frameY = j; // 8까지
				m_pSampleTiles[j * SAMPLE_COUNTX + i].SampleNum = (int)m_editSt;
			}
		}


		if (m_bTempTrigger == false)
		{
			m_nTileMaxCountX = editorScene_re::m_nMapSize / 40;
			m_nTileMaxCountY = editorScene_re::m_nMapSize / 40;
			m_fCameraSizeRate = (float)editorScene_re::m_nMapSize / CAMARA_WIDTH; // or CAMERA_HEIGHT;
			m_fMiniMapSiteRate_Width = CAMARA_WIDTH / m_fCameraSizeRate;
			m_fMiniMapSiteRate_Height = CAMERA_HEIGHT / m_fCameraSizeRate;
			
			g_saveData.gTileMaxCountX = m_nTileMaxCountX;
			g_saveData.gTileMaxCountY = m_nTileMaxCountY;

			// 기본 타일 정보 초기화 /// terrainFrameX 와 terrainFrameY가 100일경우 안보이게된다.
			for (int x = 0; x < m_nTileMaxCountX; x++)
			{
				for (int y = 0; y < m_nTileMaxCountY; y++)
				{
					m_pTiles[x * m_nTileMaxCountX + y].rc = RectMake(((WINSIZEX / 3) * 1 + 10) + x * TILE_SIZEX, ((WINSIZEY / 8) * 1 + 10) + y * TILE_SIZEY, TILE_SIZEX, TILE_SIZEY);
					m_pTiles[x * m_nTileMaxCountX + y].terrainFrameX = 100;
					m_pTiles[x * m_nTileMaxCountX + y].terrainFrameY = 100;  // 29
					m_pTiles[x * m_nTileMaxCountX + y].SampleNum = 1;
				}
			}


			// 기본 타일 정보 셋팅
			for (int x = 0; x < m_nTileMaxCountX; x++)
			{
				for (int y = 0; y < m_nTileMaxCountY; y++)
				{
					m_pTiles[x * m_nTileMaxCountX + y].rc = RectMake(((WINSIZEX / 3) * 1 + 10) + x * TILE_SIZEX, ((WINSIZEY / 8) * 1 + 10) + y * TILE_SIZEY, TILE_SIZEX, TILE_SIZEY);
					m_pTiles[x * m_nTileMaxCountX + y].terrainFrameX = 2;
					m_pTiles[x * m_nTileMaxCountX + y].terrainFrameY = 2;  // 29
					m_pTiles[x * m_nTileMaxCountX + y].SampleNum = 1;
				}
			}
			m_pTiles[181].terrainFrameX = 4;
			m_bTempTrigger = true;
		}

		if (m_pBtnLspace)
			m_pBtnLspace->update();
		if (m_pBtnRspace)
			m_pBtnRspace->update();

		MouseEvent();
		CameraUpdate();
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

		// 왼쪽에 나타나는 타일 미리보기 렌더링//
		if (m_pTileSet[0] && editorScene_re::m_nPreviewNum == 0)
			m_pTileSet[0]->render(hdc, 40, (WINSIZEY / 8) * 3 + 10);
		if (m_pTileSet[1] && editorScene_re::m_nPreviewNum == 1)
			m_pTileSet[1]->render(hdc, 40, (WINSIZEY / 8) * 3 + 10);
		if (m_pTileSet[2] && editorScene_re::m_nPreviewNum == 2)
			m_pTileSet[2]->render(hdc, 40, (WINSIZEY / 8) * 3 + 10);
		if (m_pTileSet[3] && editorScene_re::m_nPreviewNum == 3)
			m_pTileSet[3]->render(hdc, 40, (WINSIZEY / 8) * 3 + 10);
		///////////////////////////////////

		for (int x = 0; x < m_nTileMaxCountX; x++)
		{
			for (int y = 0; y < m_nTileMaxCountY; y++)
			{
				if (m_pTiles[x * m_nTileMaxCountX + y].terrainFrameX != 100 &&
					m_pTiles[x * m_nTileMaxCountX + y].terrainFrameY != 100 
					)
					//IntersectRect(&rc, &(m_pTiles[x * m_nTileMaxCountX + y].rc), &(FixedCamera)))
				{
					/*RECT rc;
					if (IntersectRect(&rc, &(m_pTiles[x * m_nTileMaxCountX + y].rc), &(FixedCamera))) continue;*/

					if (m_pTiles[x * m_nTileMaxCountX + y].rc.left <= FixedCamera.left) continue;
					if (m_pTiles[x * m_nTileMaxCountX + y].rc.top <= FixedCamera.top) continue;

					switch (m_pTiles[x * m_nTileMaxCountX + y].SampleNum)
					{
					case 1:
						m_pTileSet[0]->frameRender(hdc,
							m_pTiles[x * m_nTileMaxCountX + y].rc.left ,
							m_pTiles[x * m_nTileMaxCountX + y].rc.top ,
							m_pTiles[x * m_nTileMaxCountX + y].terrainFrameX ,
							m_pTiles[x * m_nTileMaxCountX + y].terrainFrameY );
						break;
					case 2:
						m_pTileSet[1]->frameRender(hdc,
							m_pTiles[x * m_nTileMaxCountX + y].rc.left ,
							m_pTiles[x * m_nTileMaxCountX + y].rc.top ,
							m_pTiles[x * m_nTileMaxCountX + y].terrainFrameX ,
							m_pTiles[x * m_nTileMaxCountX + y].terrainFrameY );
						break;
					case 3:
						m_pTileSet[2]->frameRender(hdc,
							m_pTiles[x * m_nTileMaxCountX + y].rc.left ,
							m_pTiles[x * m_nTileMaxCountX + y].rc.top,
							m_pTiles[x * m_nTileMaxCountX + y].terrainFrameX ,
							m_pTiles[x * m_nTileMaxCountX + y].terrainFrameY );
						break;
					case 4:
						m_pTileSet[3]->frameRender(hdc,
							m_pTiles[x * m_nTileMaxCountX + y].rc.left,
							m_pTiles[x * m_nTileMaxCountX + y].rc.top ,
							m_pTiles[x * m_nTileMaxCountX + y].terrainFrameX ,
							m_pTiles[x * m_nTileMaxCountX + y].terrainFrameY );
						break;
					}
					
				}
			}
		}

		for (int i = 0; i < SAMPLE_COUNTX * SAMPLE_COUNTY; ++i)
		{
			switch (m_rcSelectedTileSampleNum)
			{
			case 1:
				m_pTileSet[0]->frameRender(hdc,
					g_ptMouse.x,
					g_ptMouse.y,
					m_rcSelectedTile.left,
					m_rcSelectedTile.top);
				break;
			case 2:
				m_pTileSet[1]->frameRender(hdc,
					g_ptMouse.x,
					g_ptMouse.y,
					m_rcSelectedTile.left,
					m_rcSelectedTile.top);
				break;
			case 3:
				m_pTileSet[2]->frameRender(hdc,
					g_ptMouse.x,
					g_ptMouse.y,
					m_rcSelectedTile.left,
					m_rcSelectedTile.top);
				break;
			case 4:
				m_pTileSet[3]->frameRender(hdc,
					g_ptMouse.x,
					g_ptMouse.y,
					m_rcSelectedTile.left,
					m_rcSelectedTile.top);
				break;
			}
			
		}


		char szText[256];

		// TRANSPARENT : 투명, OPAQUE : 불투명
		SetBkMode(hdc, TRANSPARENT);

		SetTextColor(hdc, RGB(255, 0, 255));

		sprintf_s(szText, "wheel : %d" ,
			(int)m_nMouseWheelState );
		TextOut(hdc, 400, 100, szText, strlen(szText));

	}
}


editorScene_re::editorScene_re()
{
}

editorScene_re::~editorScene_re()
{
}

