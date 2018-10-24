#include "stdafx.h"
#include "CreatorScene.h"
#include "image.h"
#include "button.h"


bool CreatorScene::buttonInput = false;

static void Func_button1(void)
{
	CreatorScene::buttonInput = true; // �ó����� ����
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
	// TRANSPARENT : ����, OPAQUE : ������
	SetBkMode(hdc, TRANSPARENT);
	SetTextColor(hdc, RGB(255, 240, 200));
	MY_UTIL::FontOption(hdc, 42, 0);
	sprintf_s(SzText1, "%s : ", "�� �� �� ��");
	TextOut(hdc, WINSIZEX / 2 - 110, 340, SzText1, strlen(SzText1));
	MY_UTIL::FontDelete(hdc);

	char SzText2[256];
	// TRANSPARENT : ����, OPAQUE : ������
	SetBkMode(hdc, TRANSPARENT);
	SetTextColor(hdc, RGB(255, 240, 200));
	MY_UTIL::FontOption(hdc, 42, 0);
	sprintf_s(SzText2, "%s  ", "������" );
	TextOut(hdc, WINSIZEX / 2 - 70 , 400, SzText2, strlen(SzText2));

	sprintf_s(SzText2, "%s  ", "���ο�");
	TextOut(hdc, WINSIZEX / 2 - 70, 480, SzText2, strlen(SzText2));

	sprintf_s(SzText2, "%s  ", "�̼���");
	TextOut(hdc, WINSIZEX / 2 - 70, 560, SzText2, strlen(SzText2));
	MY_UTIL::FontDelete(hdc);
}




CreatorScene::CreatorScene()
{
}


CreatorScene::~CreatorScene()
{
}
