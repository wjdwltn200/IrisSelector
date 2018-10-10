#pragma once
class progressBar
{
private:
	RECT	m_rc;
	float	m_fX, m_fY;
	float	m_fWidth;
	float	m_fHeight;

	float	m_fCurrGauge;
	float	m_fGaugeSub;
	float	m_fMaxGaugeSub;
	bool	m_isBoom;

	image*	m_imgTop;
	image*	m_imgBottom;
	tagMonInfo m_tMonInfo;
	tagBulletInfo m_tBulletInfo;

public:
	HRESULT init(float x, float y, float width, float height);
	void release();
	void update();
	void render(HDC hdc);

	void setGauge(float currGauge, float maxGauge);

	inline void setX(float x) { m_fX = x; }
	inline void setY(float y) { m_fY = y; }

	void monHpSub(float minGaugeSub, float maxGaugeSub, int minGaugeInfo, int maxGaugeInfo);

	inline void setWidth(float widht) { m_fWidth = widht; }
	inline void setHeight(float height) { m_fHeight = height; }
	inline void setCurrGauge(float currGauge) { m_fCurrGauge = currGauge; }

	progressBar();
	~progressBar();
};

