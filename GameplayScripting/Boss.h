#pragma once
class Texture;
class Animation;
class Boss final
{
public:
	enum class State {
		walk,
		hurt,
		dead,
	};

	Boss(const Vector2f& pos);
	~Boss();
	void Draw() const;
	void Update(float elapsedSec);
	float GetXPos() const;
	int TakeDamage(int damage);
	void Die();

private:
	int m_BossNr;
	const float m_InitPos;
	int m_HitPoints;
	float m_Speed;
	int m_Frames;
	Vector2f m_Position;
	Rectf m_HPBar;
	State m_State;

	Texture* m_pWalkTexture;
	Animation* m_pWalkAnimation;
	Texture* m_pHurtTexture;
	Animation* m_pHurtAnimation;
	Texture* m_pDamageTexture;

	void LoadTextures();
	int GetRandBoss();
	float GetWidth() const;
	float GetHeight() const;
};
