#pragma once
class Texture;
class Boss
{
public:
	Boss(const Vector2f& pos);
	~Boss();
	void Draw() const;
	void Update(float elapsedSec);

private:
	Vector2f m_Position;
	int m_HitPoints;
	Texture* m_pTexture;
	float m_Speed;
	int m_NumFrames;
	int m_CurrFrame;
	float m_AnimTime;
	float m_FrameTime;

	int GetRandBoss();
};
