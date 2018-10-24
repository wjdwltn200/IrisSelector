#include "stdafx.h"
#include "CreatorScene.h"
#include "image.h"
#include "button.h"


bool CreatorScene::buttonInput = false;

static void Func_button1(void)
{
	CreatorScene::buttonInput = true; // 시나리오 게임
}



HRESULT CreatorScene::init()
{
	m_pImg_BG = IMAGEMANAGER->findImage("black");
	m_pButton1 = new button;
	//m_pButton1->init()


	return S_OK;
}

void CreatorScene::update()
{
}

void CreatorScene::release()
{
}

void CreatorScene::render(HDC hdc)
{
	m_pImg_BG->render(hdc, 0, 0);


	AddFontResourceA("BMHANNAAir_ttf.ttf");

	char SzText1[128];
	// TRANSPARENT : 투명, OPAQUE : 불투명
	SetBkMode(hdc, TRANSPARENT);
	SetTextColor(hdc, RGB(255, 240, 200));
	MY_UTIL::FontOption(hdc, 42, 0);
	sprintf_s(SzText1, "%s : ", "만 든 이 들");
	TextOut(hdc, WINSIZEX / 2 - 110, 340, SzText1, strlen(SzText1));
	MY_UTIL::FontDelete(hdc);

	char SzText2[256];
	// TRANSPARENT : 투명, OPAQUE : 불투명
	SetBkMode(hdc, TRANSPARENT);
	SetTextColor(hdc, RGB(255, 240, 200));
	MY_UTIL::FontOption(hdc, 42, 0);
	sprintf_s(SzText2, "%s  ", "정지수" );
	TextOut(hdc, WINSIZEX / 2 - 70 , 400, SzText2, strlen(SzText2));

	sprintf_s(SzText2, "%s  ", "정민욱");
	TextOut(hdc, WINSIZEX / 2 - 70, 480, SzText2, strlen(SzText2));

	sprintf_s(SzText2, "%s  ", "이순현");
	TextOut(hdc, WINSIZEX / 2 - 70, 560, SzText2, strlen(SzText2));
	MY_UTIL::FontDelete(hdc);
}




CreatorScene::CreatorScene()
{
}


CreatorScene::~CreatorScene()
{
}
