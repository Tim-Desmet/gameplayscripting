#pragma once
#include "Texture.h"
#include <vector>

static const int totalFish{ 8 };

class Fish
{
public:
	Fish();
	~Fish();
	void Draw(const Vector2f& pos) const;
	void Update(float elapsedSec);
	float GetWidth() const;
	float GetHeight() const;
	int GetWeightedRandomNumber() const;

private:
	Texture* m_pTexture;
	int m_CurrFrame;
	const int m_NumFrames;
	float m_AnimTime;
	const float m_FrameTime;
	int m_Amount;
};

