#pragma once
class image;
class animation;

class bullet
{
private:
	image * m_pImg;
	animation * m_pAni;

	float	m_fScale;
	float	m_fRadius;
	float	m_fSpeed;
	float	m_fX, m_fY;
	float	m_fRange, m_fExpRadius;
	float	m_fDmage;
	float	m_fKnockBack;
	float	m_fAngle;

public:
	HRESULT init(const char * imageName, float scale, float radius,
		float speed, float posX, float posY, float range, float expRadius, float dmage, float knokBack, float angle);
	void release();
	void update();
	void render(HDC hdc);

	bullet();
	~bullet();
};

