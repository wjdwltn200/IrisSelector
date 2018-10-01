#include "stdafx.h"
#include "editorScene.h"
#include "image.h"
#include "button.h"
#include "uiObject.h"
#include "uiButton.h"
#include "uiImageView.h"

int editorScene::isClick_left = 0;
int editorScene::isClick_right = 0;
int editorScene::m_nPreviewNum = 0;

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

void editorScene::SetSize()
{
	m_pUiPopup = new uiObject;

	// 배경 이미지
	uiImageView* pImageView = new uiImageView;	// 왜 지역변수일까?
	pImageView->init("size_box", WINSIZEX - IMAGEMANAGER->findImage("sizebox")->getWidth() / 2, WINSIZEX - IMAGEMANAGER->findImage("sizebox")->getHeight() / 2);
	m_pUiPopup->addChild(pImageView);

	// 버튼 1
	uiButton* pButton1 = new uiButton;
	pButton1->init("800x", 300, 100,
		PointMake(0, 1), PointMake(0, 0));
	m_pUiPopup->addChild(pButton1);
	pButton1->setDelegate(m_pUiPopup);
	pButton1->setTag(1);

	uiButton* pButton2 = new uiButton;
	pButton2->init("1600x", 300, 200,
		PointMake(0, 1), PointMake(0, 0));
	m_pUiPopup->addChild(pButton2);
	pButton2->setDelegate(m_pUiPopup);
	pButton2->setTag(2);

	uiButton* pButton3 = new uiButton;
	pButton3->init("2000x", 300, 300,
		PointMake(0, 1), PointMake(0, 0));
	m_pUiPopup->addChild(pButton3);
	pButton3->setDelegate(m_pUiPopup);
	pButton3->setTag(3);

	uiButton* pButton4 = new uiButton;
	pButton4->init("2400x", 300, 400,
		PointMake(0, 1), PointMake(0, 0));
	m_pUiPopup->addChild(pButton4);
	pButton4->setDelegate(m_pUiPopup);
	pButton4->setTag(4);
	

}

HRESULT editorScene::init()
{
	IMAGEMANAGER->addImage("size_box","image/wook/size_box.bmp", 640, 640);
	IMAGEMANAGER->addImage("800x", "image/wook/800x.bmp", 320, 168);
	IMAGEMANAGER->addImage("1600x", "image/wook/1600x.bmp", 320, 168);
	IMAGEMANAGER->addImage("2000x", "image/wook/2000x.bmp", 320, 168);
	IMAGEMANAGER->addImage("2400x", "image/wook/2400x.bmp", 320, 168);


	m_pImg_Box1 = IMAGEMANAGER->addImage("box1", "image/wook/white.bmp", (WINSIZEX / 3) * 2 - 15, (WINSIZEY / 8) * 7 - 15, true ,RGB(255,0,255));
	m_pImg_Box2 = IMAGEMANAGER->addImage("box2", "image/wook/white.bmp", (WINSIZEX / 3) * 1 - 10, (WINSIZEY / 8) * 2 - 10, true, RGB(255, 0, 255));
	m_pImg_Box3 = IMAGEMANAGER->addImage("box3", "image/wook/white.bmp", (WINSIZEX / 3) * 1 - 10, (WINSIZEY / 8) * 5 - 15, true, RGB(255, 0, 255));
	m_pImg_Box4 = IMAGEMANAGER->addImage("box4", "image/wook/white.bmp", (WINSIZEX) * 1 - 15, (WINSIZEY / 8) * 1 - 10, true, RGB(255, 0, 255));
	m_pImg_BG = IMAGEMANAGER->addImage("BG", "image/wook/BG.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
	m_pTileSet1 = IMAGEMANAGER->addImage("tiles1", "image/wook/tiles1.bmp", 200, 360, 20, 9,true,RGB(255,0,255));
	m_pTileSet2 = IMAGEMANAGER->addImage("tiles2", "image/wook/tiles2.bmp", 200, 360, 20, 9, true, RGB(255, 0, 255));
	m_pTileSet3 = IMAGEMANAGER->addImage("tiles3", "image/wook/tiles3.bmp", 200, 360, 20, 9, true, RGB(255, 0, 255));
	m_pTileSet4 = IMAGEMANAGER->addImage("tiles4", "image/wook/tiles4.bmp", 200, 360, 20, 9, true, RGB(255, 0, 255));



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

void editorScene::release()
{
	SAFE_DELETE(m_pBtnLspace);
	SAFE_DELETE(m_pBtnRspace);
	m_pUiPopup->release();
}

void editorScene::update()
{
	if (KEYMANAGER->isOnceKeyDown(0x71))
		SCENEMANAGER->changeScene("title");

	if (m_pBtnLspace)
		m_pBtnLspace->update();
	if (m_pBtnRspace)
		m_pBtnRspace->update();
	
	m_pUiPopup->update();
	Preview();
}

void editorScene::Preview()
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
		for (int i = 0; i < TILE_X_MapCount * TILE_Y_MapCount; ++i)
		{
			if (PtInRect(&m_pTiles[i].rc, g_ptMouse))
			{
				m_pTiles[i].terrainFrameX = m_rcSelectedTile.left;
				m_pTiles[i].terrainFrameY = m_rcSelectedTile.top;
			}

		}
	}

}


void editorScene::render(HDC hdc)
{
	m_pImg_BG->render(hdc, 0, 0);
	m_pImg_Box1->render(hdc, (WINSIZEX / 3) * 1 + 10, (WINSIZEY / 8) * 1 + 10);
	m_pImg_Box2->render(hdc, 10, (WINSIZEY / 8) * 1 + 10);
	m_pImg_Box3->render(hdc, 10, (WINSIZEY / 8) * 3 + 10);
	m_pImg_Box4->render(hdc, 10, 10);

	m_pUiPopup->render(hdc);

	if(m_pTileSet1 && editorScene::m_nPreviewNum == 0 )
		m_pTileSet1->render(hdc, 40 , (WINSIZEY / 8) * 3 + 10);
	if (m_pTileSet2 && editorScene::m_nPreviewNum == 1)
		m_pTileSet2->render(hdc, 40, (WINSIZEY / 8) * 3 + 10);
	if (m_pTileSet3 && editorScene::m_nPreviewNum == 2)
		m_pTileSet3->render(hdc, 40, (WINSIZEY / 8) * 3 + 10);
	if (m_pTileSet4 && editorScene::m_nPreviewNum == 3)
		m_pTileSet4->render(hdc, 40, (WINSIZEY / 8) * 3 + 10);


	m_pBtnLspace->render(hdc);
	m_pBtnRspace->render(hdc);
	
	m_pTileSet1->frameRender(hdc,
		10,
		100,
		m_rcSelectedTile.left,
		m_rcSelectedTile.top);

}

editorScene::editorScene()
{
}


editorScene::~editorScene()
{
}


