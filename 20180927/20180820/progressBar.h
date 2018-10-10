#pragma once
class progressBar
{
private:
	RECT	m_rc;
	float	m_fX, m_fY;
	float	m_fWidth;
	float	m_fHeight;

	float	m_fCurrGauge;

	image*	m_imgTop;
	image*	m_imgBottom;

public:
	HRESULT init(float x, float y, float width, float height);
	void release();
	void update();
	void render(HDC hdc);

	void setGauge(float currGauge, float maxGauge);

	inline void setX(float x) { m_fX = x; }
	inline void setY(float y) { m_fY = y; }

	inline void setWidth(float widht) { m_fWidth = widht; }
	inline void setHeight(float height) { m_fHeight = height; }
	inline void setCurrGauge(float currGauge) { m_fCurrGauge = currGauge; }

	progressBar();
	~progressBar();
};

