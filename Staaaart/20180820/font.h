#pragma once
class font
{

private:
	//SYNTHESIZE(float, m_fX, posX);
	//SYNTHESIZE(float, m_fY, posY);

	struct tagFontStyle
	{
		int m_nHeight = 0; // 높이
		int m_nWidth = 0; // 너비
		int m_Escapement = 0; // 글자방향 벡터와 X축사이 각도
		int m_Orientation = 0; // 문자 기준선과 X축사이 각도
		int m_Weight = 0; // 굵기
		DWORD m_Italic = 0; // 기울여진 정도
		DWORD m_Underline = 0; // 밑줄
		DWORD m_StrikeOut = 0; // 취소선
		DWORD m_CharSet = 0;
		LPCSTR m_Style = 0;
		
	};

	tagFontStyle Font;
	
	float m_fX;
	float m_fY;
	string m_text;
	//LOGFONT m_fontStyle;
	bool	m_isAlive;
	float	m_fElapsedTime;
	HFONT   m_font, m_oldfont;
	

public:
	HRESULT init(float X, float Y, string text, int nHeight,
		int nWidth, int Escapement, int Orientation,
		int Weight, DWORD Italic, DWORD Underline, DWORD StrikeOut,
		DWORD CharSet, LPCSTR Style);
	void release();
	void update();
	void render(HDC hdc);

	void startFont();
	void endFont();

	bool getIsAlive() { return m_isAlive; }

	font();
	~font();
};

