#pragma once
class animation;
class monster
{
private:
	int ani_stay_Curr[6];
	image * img_monsterType;
	animation * ani_monsterMove;


	int img_fX;
	int img_fY;
	struct monsterKinds
	{
		float m_fX;
		float m_fY;
		RECT m_rc;
		float m_CurrHpX;
		float m_CurrHpY;
		float m_MaxHp;
		float m_Speed;
	};
	struct bossMonster
	{
		RECT m_rc;
		float m_fX;
		float m_fY;
		float m_CurrHpX;
		float m_CurrHpY;
		float m_MaxHp;
		float m_Speed;
	};

	monsterKinds m_Mon;
	bossMonster m_Boss;

	
public:
	HRESULT init();
	void release();
	void update();
	void render(HDC hdc);
	void Move();

	monster();
	~monster();
};

