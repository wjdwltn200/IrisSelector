#include "stdafx.h"
#include "titleScene.h"
#include "PlayerCharacter.h"
#include "bulletManger.h"


HRESULT titleScene::init()
{
	m_player = new PlayerCharacter;
	m_player->init();
	m_titleScene = IMAGEMANAGER->addImage("titleImage", "image/resources/UI_image/title_image/titleScene.bmp", WINSIZEX, WINSIZEY);
	m_button = IMAGEMANAGER->addImage("buttonBase", "image/resources/UI_image/title_image/button_base.bmp", 162, 360, 1, 6, true, RGB(166, 166, 166));
	// 버튼 tag 초기화
	memset(&m_tButtonInfo, NULL, sizeof(m_tButtonInfo));

	// 최초 게임 시작 선택 상태
	m_tButtonInfo.carrFrameX = TITEL::GAME_START_SC;
	m_tButtonInfo.m_moveSpeed = 1.5f;
	m_tButtonInfo.m_isMovement = false;

	m_pBulletMag = new bulletManger;
	m_pBulletMag->init(10);

	IMAGEMANAGER->addImage("Bullet_Y", "image/resources/bullet_image/Bullet_Y.bmp", 108, 27, 4, 1, true, RGB(255, 0, 255));


	return S_OK;
}

void titleScene::release()
{
	m_pBulletMag->release();
}

void titleScene::update()
{
	if (KEYMANAGER->isOnceKeyDown(0x71))
		SCENEMANAGER->changeScene("editor");

	if (KEYMANAGER->isStayKeyDown('F'))
	{
		//m_pBulletMag->fire("Bullet_Y", 1.0f, 0.5f, 10.0f, WINSIZEX / 2, WINSIZEY / 2, 200.0f, 10.0f, 3.0f, 1.0f, MY_UTIL::getMouseAngle(WINSIZEX / 2, WINSIZEY / 2));


		for (int i = 0; i < 10; i++)
		{
			m_pBulletMag->fire("Bullet_Y", 1.0f, 0.5f, 3.5f, WINSIZEX / 2, WINSIZEY / 2, (i * 50.0f) + 100.0f, 10.0f, 3.0f, 1.0f, PI/180.0f - (i * 10.0f));
		}

	}

	if (!m_tButtonInfo.m_isMovement)
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
	
	m_pBulletMag->update();
	m_player->update();

}

void titleScene::render(HDC hdc)
{
	if (m_titleScene)
	{
		m_titleScene->render(hdc,0,0);

		// 센터
		m_button->frameAlphaRender(hdc, (WINSIZEX / 2) - (m_button->getFrameWidth() / 2) * 1.2f, (WINSIZEY / 2) + ((WINSIZEY / 2) / 2) - (m_button->getFrameHeight() / 2) * 1.2f, 0, m_tButtonInfo.carrFrameX, 1.2f, 0);
		// 우측 대기
		if (!(m_tButtonInfo.carrFrameX == TITEL::GAME_START_SC))
			m_button->frameAlphaRender(hdc, (WINSIZEX / 2) - ((WINSIZEX / 2) / 2) - (m_button->getFrameWidth() / 2) * 0.8f, (WINSIZEY / 2) + ((WINSIZEY / 2) / 2) - (m_button->getFrameHeight() / 2) * 0.8f, 0, m_tButtonInfo.carrFrameX - 1, 0.8f, 150);
		// 좌측 대기
		if (!(m_tButtonInfo.carrFrameX == TITEL::EXIT_SC))
			m_button->frameAlphaRender(hdc, (WINSIZEX / 2) + ((WINSIZEX / 2) / 2) - (m_button->getFrameWidth() / 2) * 0.8f, (WINSIZEY / 2) + ((WINSIZEY / 2) / 2) - (m_button->getFrameHeight() / 2) * 0.8f, 0, m_tButtonInfo.carrFrameX + 1, 0.8f ,150);
	}

	m_pBulletMag->render(hdc);
	TIMEMANAGER->render(hdc);
	m_player->render(hdc);
}

titleScene::titleScene()
{
}


titleScene::~titleScene()
{
}
