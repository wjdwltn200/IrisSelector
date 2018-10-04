#include "stdafx.h"
#include "titleScene.h"
#include "PlayerCharacter.h"
#include "bulletManger.h"
#include "effectManager.h"
#include "PlayerCharacter.h"

HRESULT titleScene::init()
{
	m_player = new PlayerCharacter;
	m_player->init();
	m_pBulletMag = new bulletManger;
	m_pBulletMag->init(10);

	m_pEffMagr = new effectManager;
	m_pEffMagr->init();
	m_pEffMagr->addEffect("Bullet_Y_End", "image/resources/bullet_image/Bullet_Y_End.bmp",297, 27, 27, 27, 30, 5);

	m_player = new PlayerCharacter;
	m_player->init();
	m_player->setBulletMagPointer(&m_pBulletMag);

	m_titleScene = IMAGEMANAGER->addImage("titleImage", "image/resources/UI_image/title_image/titleScene.bmp", WINSIZEX, WINSIZEY);
	m_button = IMAGEMANAGER->addImage("buttonBase", "image/resources/UI_image/title_image/button_base.bmp", 162, 360, 1, 6, true, RGB(166, 166, 166));
	// 버튼 tag 초기화
	memset(&m_tButtonInfo, NULL, sizeof(m_tButtonInfo));

	// 최초 게임 시작 선택 상태
	m_tButtonInfo.carrFrameX = TITEL::GAME_START_SC;
	m_tButtonInfo.m_moveSpeed = 1.5f;
	m_tButtonInfo.m_isMovement = false;

	IMAGEMANAGER->addImage("Bullet_Y", "image/resources/bullet_image/Bullet_Y.bmp", 108, 27, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Bullet_B", "image/resources/bullet_image/Bullet_B.bmp", 108, 27, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Bullet_P", "image/resources/bullet_image/Bullet_P.bmp", 108, 27, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Bullet_G", "image/resources/bullet_image/Bullet_G.bmp", 108, 27, 4, 1, true, RGB(255, 0, 255));

	return S_OK;
}

void titleScene::release()
{
	m_pBulletMag->release();
	m_pEffMagr->release();
}

void titleScene::update()
{
	if (KEYMANAGER->isOnceKeyDown(0x71))
		SCENEMANAGER->changeScene("editor");

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
	
	m_player->update();
	m_pBulletMag->update();
	m_player->update();
	m_pEffMagr->update();
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
	m_player->render(hdc);
	m_pEffMagr->render(hdc);
	TIMEMANAGER->render(hdc);
	m_player->render(hdc);
}

titleScene::titleScene()
{
}


titleScene::~titleScene()
{
}
