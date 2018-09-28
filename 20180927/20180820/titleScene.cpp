#include "stdafx.h"
#include "titleScene.h"


HRESULT titleScene::init()
{

	//img_titleScene = IMAGEMANAGER->addImage("titleScene.bmp", WINSIZEX, WINSIZEY);
	//img_button = IMAGEMANAGER->addImage("button", "image/button.bmp", 135, 147, 2, 6, true, RGB(166, 166, 166));

	m_titleScene = IMAGEMANAGER->addImage("titleScene.bmp", WINSIZEX, WINSIZEY);
	m_button = IMAGEMANAGER->addImage("button", "image/button.bmp", 135, 147, 2, 6, true, RGB(166, 166, 166));

	m_titleScene = IMAGEMANAGER->addImage("titleImage", "image/resources/UI_image/title_image/titleScene.bmp", WINSIZEX, WINSIZEY);
	m_button = IMAGEMANAGER->addImage("buttonBase", "image/resources/UI_image/title_image/button_base.bmp", 162, 360, 1, 6, true, RGB(166, 166, 166));

	// 버튼 tag 초기화
	memset(&m_tButtonInfo, NULL, sizeof(m_tButtonInfo));

	// 최초 게임 시작 선택 상태
	m_tButtonInfo.carrFrameX = TITEL::GAME_START_SC;
	m_tButtonInfo.m_moveSpeed = 1.5f;


	return S_OK;
}

void titleScene::release()
{
}

void titleScene::update()
{
	if (KEYMANAGER->isOnceKeyDown(VK_LEFT))
	{
		if (m_tButtonInfo.carrFrameX == TITEL::GAME_START_SC) return;
		
		m_tButtonInfo.carrFrameX--;
	}
	if (KEYMANAGER->isOnceKeyDown(VK_RIGHT))
	{
		if (m_tButtonInfo.carrFrameX == TITEL::EXIT_SC) return;

		m_tButtonInfo.carrFrameX++;
	}

}

void titleScene::render(HDC hdc)
{

	/*if (img_titleScene)
	{
		img_titleScene->render(hdc,0,0);
	}*/

	if (m_titleScene)
	{
		m_titleScene->render(hdc,0,0);

		// 센터
		m_button->frameAlphaRender(hdc, (WINSIZEX / 2) - (m_button->getFrameWidth() / 2), (WINSIZEY / 2) + ((WINSIZEY / 2) / 2) - (m_button->getFrameHeight() / 2), 0, m_tButtonInfo.carrFrameX, 0, 1.0f);
		// 우측 대기
		if (!(m_tButtonInfo.carrFrameX == TITEL::GAME_START_SC))
			m_button->frameAlphaRender(hdc, (WINSIZEX / 2) - ((WINSIZEX / 2) / 2) - (m_button->getFrameWidth() / 2), (WINSIZEY / 2) + ((WINSIZEY / 2) / 2) - (m_button->getFrameHeight() / 2), 0, m_tButtonInfo.carrFrameX - 1, 150, 1.0f);
		// 좌측 대기
		if (!(m_tButtonInfo.carrFrameX == TITEL::EXIT_SC))
			m_button->frameAlphaRender(hdc, (WINSIZEX / 2) + ((WINSIZEX / 2) / 2) - (m_button->getFrameWidth() / 2), (WINSIZEY / 2) + ((WINSIZEY / 2) / 2) - (m_button->getFrameHeight() / 2), 0, m_tButtonInfo.carrFrameX + 1, 150, 1.0f);
	}

}

titleScene::titleScene()
{
}


titleScene::~titleScene()
{
}
