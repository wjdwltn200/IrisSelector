#include "stdafx.h"
#include "stageScene.h"
#include "button.h"
#include "image.h"

char szFileName[512];

int stageScene::buttonNum = 0;

static void Func_button1(void)
{
	stageScene::buttonNum = 1; // 시나리오 게임
}

static void Func_button2(void)
{
	stageScene::buttonNum = 2; // 사용자 지정 게임
}






HRESULT stageScene::init()
{
	m_pImage_BG1 = IMAGEMANAGER->findImage("black");
	m_pImage_checkBox = IMAGEMANAGER->findImage("size_box");

	m_pButton1 = new button;
	m_pButton1->init("800x", WINSIZEX / 2, 80, PointMake(0, 1), PointMake(0, 0), Func_button1); // 시나리오

	m_pButton2 = new button;
	m_pButton2->init("800x", WINSIZEX / 2, 180, PointMake(0, 1), PointMake(0, 0), Func_button2); // 사용자 지정게임

	return S_OK;
}

void stageScene::release()
{
}

void stageScene::update()
{
	if (buttonNum == 0)
	{
		m_pButton1->update();
		m_pButton2->update();
	}
	if (buttonNum == 1)
	{

		buttonNum = 3;
	}
	if (buttonNum == 2)
	{
		LoadEvent();
		buttonNum = 3;
	}

		

}

void stageScene::render(HDC hdc)
{
	m_pImage_BG1->render(hdc,0,0);
	if (buttonNum == 0)
	{
		m_pImage_checkBox->render(hdc, WINSIZEX / 2 - IMAGEMANAGER->findImage("size_box")->getWidth() / 2, 0);
		m_pButton1->render(hdc);
		m_pButton2->render(hdc);
	}
}

void stageScene::LoadEvent()
{
	OPENFILENAME ofn;
	HWND hEditFileToBeOpened = NULL;

	ZeroMemory(&ofn, sizeof(OPENFILENAME));
	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = g_hWnd;
	ofn.lpstrFilter = "txt Files(*.txt)\0*.txt\0All Files (*.*)\0*.*\0"; //"All Files(*.*)\0*.*\0";
	ofn.lpstrFile = szFileName;
	ofn.nMaxFile = 512;

	if (0 != GetOpenFileName(&ofn))
	{
		SetWindowText(hEditFileToBeOpened, ofn.lpstrFile);
		TXTDATA->getSingleton()->mapLoad(szFileName, m_pTiles, &m_rcSelectedTile);
	}

}

stageScene::stageScene()
{
}


stageScene::~stageScene()
{
}
