#include "stdafx.h"
#include "mainGame.h"
#include "titleScene.h"
#include "battleScene.h"
#include "loadingScene_1.h"
#include "uiTestScene.h"
#include "pixelCollision.h"

void mainGame::setBackBuffer()
{
	m_pBackBuffer = new image;
	m_pBackBuffer->init(WINSIZEX, WINSIZEY);
}

HRESULT mainGame::init()
{
	hdc = GetDC(g_hWnd);

	//HANDLE hTimer = (HANDLE)SetTimer(g_hWnd, 1, 10, NULL);
	KEYMANAGER->init();
	IMAGEMANAGER->init();
	TIMEMANAGER->init();
	SCENEMANAGER->init();

	setBackBuffer();

	// �ʿ��� ���ҽ� �̸� �ε�

	// scene test
	m_pTitleScene = new titleScene;
	SCENEMANAGER->addScene("title", m_pTitleScene);

	m_pBattleScene = new battleScene;
	SCENEMANAGER->addScene("battle", m_pBattleScene);

	m_pLoadingScene = new loadingScene_1;
	SCENEMANAGER->addLoadingScene("loading_1", m_pLoadingScene);

	m_pUiTestScene = new uiTestScene;
	SCENEMANAGER->addScene("uiTest", m_pUiTestScene);

	m_pPixelCollisionScene = new pixelCollision;
	SCENEMANAGER->addScene("pixelCollision", m_pPixelCollisionScene);
	
	SCENEMANAGER->changeScene("pixelCollision");

	return S_OK;
}

void mainGame::release()
{
	// �� �Ŵ��� ����(SCENEMANAGER->release())���� ó���ϹǷ�
	// ���⼭�� ����
	//m_pBattleScene->release();
	//SAFE_DELETE(m_pBattleScene);

	//m_pTitleScene->release();
	//SAFE_DELETE(m_pTitleScene);

	SAFE_DELETE(m_pBackBuffer);

	//KillTimer(g_hWnd, 1);
	ReleaseDC(g_hWnd, hdc);

	TXTDATA->release();
	KEYMANAGER->release();
	IMAGEMANAGER->release();
	TIMEMANAGER->release();
	SCENEMANAGER->release();

	TXTDATA->releaseSingleton();
	KEYMANAGER->releaseSingleton();
	IMAGEMANAGER->releaseSingleton();
	TIMEMANAGER->releaseSingleton();
	SCENEMANAGER->releaseSingleton();

}

LRESULT mainGame::MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	switch (iMessage)
	{
	case WM_MOUSEMOVE:
		g_ptMouse.x = LOWORD(lParam);
		g_ptMouse.y = HIWORD(lParam);
		break;
	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_ESCAPE:
			PostQuitMessage(0);
			return 0;
		}
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}

	return DefWindowProc(hWnd, iMessage, wParam, lParam);
}

void mainGame::update()
{
	InvalidateRect(g_hWnd, NULL, false);

	// titleScene
	//m_pTitleScene->update();

	// battleScene
	//m_pBattleScene->update();

	SCENEMANAGER->update();
}

void mainGame::render()
{
	HDC backDC = m_pBackBuffer->getMemDC();

	// titleScene
	//m_pTitleScene->render(backDC);

	// battleScene
	//m_pBattleScene->render(backDC);

	SCENEMANAGER->render(backDC);

	m_pBackBuffer->render(hdc, 0, 0);
}

mainGame::mainGame()
{
}


mainGame::~mainGame()
{
}
