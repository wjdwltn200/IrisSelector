#pragma once
class monster
{
private:
	image * monsterType;
	animation * monsterMove;


	struct monsterKinds
	{
		RECT m_rc;
		float m_fX;
		float m_fY;
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

	monster();
	~monster();
};

