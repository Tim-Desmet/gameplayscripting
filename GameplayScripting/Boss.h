#pragma once
class Texture;
class Boss
{
public:
	Boss();
	~Boss();
	void Draw() const;
	void Update(float elapsedSec);

private:
	int m_HitPoints;
	Texture* m_pTexture;
	float m_Speed;
};
