#include "stdafx.h"
#include "editorScene.h"
#include "image.h"
#include "button.h"

int editorScene::isClick_left = 0;
int editorScene::isClick_right = 0;

static void SpaceFunc_left(void)
{

}

static void SpaceFunc_right(void)
{

}


HRESULT editorScene::init()
{
	m_pImg_Box1 = IMAGEMANAGER->addImage("box1", "image/wook/white.bmp", (WINSIZEX / 3) * 2 - 15, (WINSIZEY / 8) * 7 - 15, true ,RGB(255,0,255));
	m_pImg_Box2 = IMAGEMANAGER->addImage("box2", "image/wook/white.bmp", (WINSIZEX / 3) * 1 - 10, (WINSIZEY / 8) * 2 - 10, true, RGB(255, 0, 255));
	m_pImg_Box3 = IMAGEMANAGER->addImage("box3", "image/wook/white.bmp", (WINSIZEX / 3) * 1 - 10, (WINSIZEY / 8) * 5 - 15, true, RGB(255, 0, 255));
	m_pImg_Box4 = IMAGEMANAGER->addImage("box4", "image/wook/white.bmp", (WINSIZEX) * 1 - 15, (WINSIZEY / 8) * 1 - 10, true, RGB(255, 0, 255));
	m_pImg_BG = IMAGEMANAGER->addImage("BG", "image/wook/BG.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
	
	IMAGEMANAGER->addImage("space_left", "image/wook/space_left.bmp", 36, 72,1,2, true, RGB(255, 255, 255));
	IMAGEMANAGER->addImage("space_right", "image/wook/space_right.bmp", 36, 72,1,2, true, RGB(255, 255, 255));

	m_pBtnLspace = new button;
	m_pBtnLspace->init("space_left", IMAGEMANAGER->findImage("space_left")->getWidth()/2 + 10, 530, PointMake(0, 1), PointMake(0, 0), SpaceFunc_left);

	m_pBtnRspace = new button;
	m_pBtnRspace->init("space_right", IMAGEMANAGER->findImage("space_right")->getWidth() / 2 + (WINSIZEX / 3) -36, 530, PointMake(0, 1), PointMake(0, 0), SpaceFunc_right);


	return S_OK;

}

void editorScene::release()
{
	SAFE_DELETE(m_pBtnLspace);
	SAFE_DELETE(m_pBtnRspace);

}

void editorScene::update()
{
	if (m_pBtnLspace)
		m_pBtnLspace->update();
	if (m_pBtnRspace)
		m_pBtnRspace->update();

}

void editorScene::render(HDC hdc)
{
	m_pImg_BG->render(hdc, 0, 0);
	m_pImg_Box1->render(hdc, (WINSIZEX / 3) * 1 + 10, (WINSIZEY / 8) * 1 + 10);
	m_pImg_Box2->render(hdc, 10, (WINSIZEY / 8) * 1 + 10);
	m_pImg_Box3->render(hdc, 10, (WINSIZEY / 8) * 3 + 10);
	m_pImg_Box4->render(hdc, 10, 10);

	m_pBtnLspace->render(hdc);
	m_pBtnRspace->render(hdc);

	

}

editorScene::editorScene()
{
}


editorScene::~editorScene()
{
}


