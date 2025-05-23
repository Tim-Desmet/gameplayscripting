#pragma once
class Texture;
class Animation;
class Boss
{
public:
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
	Vector2f m_Position;
	int m_HitPoints;
	Texture* m_pWalkTexture;
	Animation* m_pWalkAnimation;
	Texture* m_pHitTexture;
	Animation* m_pHitAnimation;
	float m_Speed;
	bool m_IsHurt;

	int GetRandBoss();
};
