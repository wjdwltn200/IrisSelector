#include "stdafx.h"
#include "font.h"


font::font()
{
}
font::~font()
{
}





HRESULT font::init(float X, float Y, string text, int nHeight,
	int nWidth, int Escapement, int Orientation,
	int Weight, DWORD Italic, DWORD Underline, DWORD StrikeOut,
	DWORD CharSet, LPCSTR Style)
{
	m_fX = X;
	m_fY = Y;
	m_text = text;
	m_isAlive = true;
	Font.m_nHeight = nHeight;
	Font.m_nWidth = nWidth;
	Font.m_Escapement = Escapement;
	Font.m_Orientation = Orientation;
	if (Weight == 0)
	{
		Font.m_Weight = FW_DONTCARE;
	}
	else if (Weight == 1)
	{
		Font.m_Weight = FW_THIN;
	}
	else if (Weight == 2)
	{
		Font.m_Weight = FW_NORMAL;
	}
	else if (Weight == 3)
	{
		Font.m_Weight = FW_BOLD;
	}
	else if (Weight == 4)
	{
		Font.m_Weight = FW_HEAVY;
	}
	Font.m_Italic = Italic;
	Font.m_Underline = Underline;
	Font.m_StrikeOut = StrikeOut;
	if (CharSet == 0)
	{
		Font.m_CharSet = DEFAULT_CHARSET;
	}
	else if (CharSet == 1)
	{
		Font.m_CharSet = HANGEUL_CHARSET;
	}
	Font.m_Style = Style;
	

	return S_OK;
}

void font::release()
{
}

void font::update()
{
	if (!m_isAlive) return;

	
}

void font::render(HDC hdc)
{
	if (!m_isAlive) return;

	m_font = CreateFont(Font.m_nHeight, Font.m_nWidth, Font.m_Escapement,
		Font.m_Orientation, Font.m_Weight, Font.m_Italic, Font.m_Underline,
		Font.m_StrikeOut, Font.m_CharSet, 0, 0, 0, 0, Font.m_Style);
	m_oldfont = (HFONT)SelectObject(hdc, m_font);
	TextOut(hdc, m_fX, m_fY, m_text.c_str(), strlen(m_text.c_str()));
	SelectObject(hdc, m_oldfont);
	DeleteObject(m_font);
}

void font::startFont()
{
}

void font::endFont()
{
}
