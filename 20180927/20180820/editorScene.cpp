#include "stdafx.h"
#include "editorScene.h"
#include "image.h"


HRESULT editorScene::init()
{
	m_pImg_Box1 = IMAGEMANAGER->addImage("box1", "image/wook/white.bmp", (WINSIZEX / 3) * 2 - 20, (WINSIZEY / 8) * 7 - 20, true ,RGB(255,0,255));
	m_pImg_Box2 = IMAGEMANAGER->addImage("box2", "image/wook/white.bmp", (WINSIZEX / 3) * 1 - 20, (WINSIZEY / 8) * 2 - 20, true, RGB(255, 0, 255));
	m_pImg_Box3 = IMAGEMANAGER->addImage("box3", "image/wook/white.bmp", (WINSIZEX / 3) * 1 - 20, (WINSIZEY / 8) * 5 - 20, true, RGB(255, 0, 255));
	m_pImg_Box4 = IMAGEMANAGER->addImage("box4", "image/wook/white.bmp", (WINSIZEX) * 1 - 20, (WINSIZEY / 8) * 1 - 20, true, RGB(255, 0, 255));
	m_pImg_BG = IMAGEMANAGER->addImage("BG", "image/wook/BG.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
	
	m_pTileSet;

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
	IMAGEMANAGER->findImage("BG")->render(hdc, 0, 0);
	IMAGEMANAGER->findImage("white")->render(hdc, (WINSIZEX / 3) * 1, WINSIZEY - ((WINSIZEY / 5) * 4));
	IMAGEMANAGER->findImage("white2")->render(hdc, 10, WINSIZEY - ((WINSIZEY / 5) * 4));

}

editorScene::editorScene()
{
}


editorScene::~editorScene()
{
}

