#include "stdafx.h"
#include "titleScene.h"


HRESULT titleScene::init()
{
	img_titleScene = IMAGEMANAGER->addImage("titleScene.bmp", WINSIZEX, WINSIZEY);
	img_button = IMAGEMANAGER->addImage("button", "image/button.bmp", 135, 147, 2, 6, true, RGB(166, 166, 166));

	return S_OK;
}

void titleScene::release()
{
}

void titleScene::update()
{
	if (KEYMANAGER->isOnceKeyDown(VK_LEFT))
	{
		
	}

}

void titleScene::render(HDC hdc)
{
	if (img_titleScene)
	{
		img_titleScene->render(hdc,0,0);
	}
}

titleScene::titleScene()
{
}


titleScene::~titleScene()
{
}
