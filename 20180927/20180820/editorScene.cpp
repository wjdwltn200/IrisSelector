#include "stdafx.h"
#include "editorScene.h"
#include "image.h"


HRESULT editorScene::init()
{
	IMAGEMANAGER->addImage("white", "image/wook/white.bmp", (WINSIZEX / 3) * 2, (WINSIZEY / 5) * 4, true ,RGB(255,0,255));
	IMAGEMANAGER->addImage("white2", "image/wook/white.bmp", (WINSIZEX / 3) * 1 - 10, (WINSIZEY / 5) * 4, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("BG", "image/wook/BG.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));


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

