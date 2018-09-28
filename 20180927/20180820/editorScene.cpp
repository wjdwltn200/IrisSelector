#include "stdafx.h"
#include "editorScene.h"
#include "image.h"


HRESULT editorScene::init()
{
	m_pImg_Box1 = IMAGEMANAGER->addImage("box1", "image/wook/white.bmp", (WINSIZEX / 3) * 2 - 15, (WINSIZEY / 8) * 7 - 15, true ,RGB(255,0,255));
	m_pImg_Box2 = IMAGEMANAGER->addImage("box2", "image/wook/white.bmp", (WINSIZEX / 3) * 1 - 10, (WINSIZEY / 8) * 2 - 10, true, RGB(255, 0, 255));
	m_pImg_Box3 = IMAGEMANAGER->addImage("box3", "image/wook/white.bmp", (WINSIZEX / 3) * 1 - 10, (WINSIZEY / 8) * 5 - 15, true, RGB(255, 0, 255));
	m_pImg_Box4 = IMAGEMANAGER->addImage("box4", "image/wook/white.bmp", (WINSIZEX) * 1 - 15, (WINSIZEY / 8) * 1 - 10, true, RGB(255, 0, 255));
	m_pImg_BG = IMAGEMANAGER->addImage("BG", "image/wook/BG.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
	
	m_pImg_Lspace = IMAGEMANAGER->addImage("space_left", "image/wook/space_left.bmp", 42, 42, true, RGB(255, 0, 255));
	m_pImg_Rspace = IMAGEMANAGER->addImage("space_right", "image/wook/space_right.bmp", 42, 42, true, RGB(255, 0, 255));


	return S_OK;

}

void editorScene::release()
{
}

void editorScene::update()
{
}

void editorScene::render(HDC hdc)
{
	m_pImg_BG->render(hdc, 0, 0);
	m_pImg_Box1->render(hdc, (WINSIZEX / 3) * 1 + 10, (WINSIZEY / 8) * 1 + 10);
	m_pImg_Box2->render(hdc, 10, (WINSIZEY / 8) * 1 + 10);
	m_pImg_Box3->render(hdc, 10, (WINSIZEY / 8) * 3 + 10);
	m_pImg_Box4->render(hdc, 10, 10);

	m_pImg_Lspace->alphaRender(hdc, 10, 530,95);
	m_pImg_Rspace->alphaRender(hdc, (WINSIZEX/3) - m_pImg_Rspace->getWidth(), 530, 95);


	

}

editorScene::editorScene()
{
}


editorScene::~editorScene()
{
}

