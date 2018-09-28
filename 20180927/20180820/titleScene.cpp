#include "stdafx.h"
#include "titleScene.h"


HRESULT titleScene::init()
{
<<<<<<< HEAD
	//img_titleScene = IMAGEMANAGER->addImage("titleScene.bmp", WINSIZEX, WINSIZEY);
	//img_button = IMAGEMANAGER->addImage("button", "image/button.bmp", 135, 147, 2, 6, true, RGB(166, 166, 166));
=======
	m_titleScene = IMAGEMANAGER->addImage("titleScene.bmp", WINSIZEX, WINSIZEY);
	m_button = IMAGEMANAGER->addImage("button", "image/button.bmp", 135, 147, 2, 6, true, RGB(166, 166, 166));
>>>>>>> a1e74794aafc031a54f1f8d857cd3143a957c15e

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
<<<<<<< HEAD
	/*if (img_titleScene)
	{
		img_titleScene->render(hdc,0,0);
	}*/
=======
	if (m_titleScene)
	{
		m_titleScene->render(hdc,0,0);
	}
>>>>>>> a1e74794aafc031a54f1f8d857cd3143a957c15e
}

titleScene::titleScene()
{
}


titleScene::~titleScene()
{
}
