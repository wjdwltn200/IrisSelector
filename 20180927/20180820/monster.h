#pragma once
class animation;
class PlayerCharacter;
class monster
{
private:

	struct monsterKinds
	{
		float m_fX;
		float m_fY;
		RECT m_rc;
		float m_CurrHpX;
		float m_CurrHpY;
		float m_MaxHp;
		float m_Speed;
		float m_Angle;
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

	bool isAlive;

	image * m_monsterType;
	animation * m_monsterMove;

	
	PlayerCharacter * m_player;


	monsterKinds m_Mon;
	bossMonster m_Boss;

	
public:
	HRESULT init(const char * strKey, int fX, int fY, float speed);
	void release();
	void update();
	void Move();
	void render(HDC hdc);

	bool getAlive() { return isAlive; }
	void setAlive(bool Alive) { isAlive = Alive; };
	monster();
	~monster();
};

