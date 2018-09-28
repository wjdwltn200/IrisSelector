#include "stdafx.h"
#include "titleScene.h"


HRESULT titleScene::init()
{

	m_titleScene = IMAGEMANAGER->addImage("titleImage", "image/resources/UI_image/title_image/titleScene.bmp", WINSIZEX, WINSIZEY);
	m_button = IMAGEMANAGER->addImage("buttonBase", "image/resources/UI_image/title_image/button_base.bmp", 162, 62, 1, 1, true, RGB(166, 166, 166));

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
	if (m_titleScene)
	{
		m_titleScene->render(hdc,0,0);
		m_button->alphaRender(hdc, (WINSIZEX / 2) - (m_button->getFrameWidth() / 2), (WINSIZEY / 2) + ((WINSIZEY / 2) / 2) - (m_button->getFrameHeight() / 2), 255);
	}
}

titleScene::titleScene()
{
}


titleScene::~titleScene()
{
}
