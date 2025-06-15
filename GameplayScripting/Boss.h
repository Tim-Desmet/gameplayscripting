#pragma once
class Texture;
class Animation;
class Boss
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
	void TakeDamage(int damage);
	void Die();

private:
	int m_BossNr;
	const float m_InitPos;
	int m_HitPoints;
	float m_Speed;
	Vector2f m_Position;
	State m_State;

	Texture* m_pWalkTexture;
	Animation* m_pWalkAnimation;
	Texture* m_pHurtTexture;
	Animation* m_pHurtAnimation;

	void LoadTextures();
	int GetRandBoss();
};
