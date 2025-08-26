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
	void SetRarity(int rar);
	int GetRarity() const;
	float GetWeightPercentage() const;
	int GetWeightedRandomNumber();

private:
	int m_CurrFrame;
	const int m_NumFrames;
	float m_AnimTime;
	const float m_FrameTime;
	int m_Rarity;
	int m_Weights[8];

	Color4f m_TxtColor;
	Texture* m_pTexture;
	Texture* m_pRarity;

	void LoadTextures();
};

