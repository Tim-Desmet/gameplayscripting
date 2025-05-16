#include "pch.h"
#include "Fish.h"
#include <iostream>
#include <cassert>

Fish::Fish() : m_CurrFrame{ 1 }, m_AnimTime{ 0.f }, m_NumFrames{ 2 }, m_FrameTime{ 0.5f }, m_Rarity{ GetWeightedRandomNumber() }
{
    m_pTexture = new Texture{ "Objects/Catch/" + std::to_string(m_Rarity) + ".png" };
}

Fish::~Fish()
{
	delete m_pTexture;
    m_pTexture = nullptr;
}

void Fish::Draw(const Vector2f& pos) const
{
    float width = m_pTexture->GetWidth() / m_NumFrames;
    float height = m_pTexture->GetHeight();
    Rectf srcRect = Rectf{ m_CurrFrame * width, 0.f, width, height };
	m_pTexture->Draw(pos, srcRect);
}

void Fish::Update(float elapsedSec)
{
    m_AnimTime += elapsedSec;

    if (m_AnimTime >= m_FrameTime)
    {
        m_AnimTime -= m_FrameTime;
        m_CurrFrame = (m_CurrFrame + 1) % m_NumFrames;
    }
}

float Fish::GetWidth() const
{
    return m_pTexture->GetWidth() / 2;
}

float Fish::GetHeight() const
{
    return m_pTexture->GetHeight();
}

void Fish::SetRarity(int rar)
{
    m_Rarity = rar;
}

int Fish::GetRarity() const
{
    return m_Rarity;
}

int Fish::GetWeightedRandomNumber() {
    int weights[totalFish]{ 500, 240, 100, 60, 40, 30, 20, 10 };
    int totalWeight{ 0 };

    for (int i = 0; i < totalFish; i++) {
        totalWeight += weights[i];
    }
    int rnd = rand() % totalWeight;

    for (int i = 0; i < totalFish; i++) {
        if (rnd < weights[i])
        {
            SetRarity(i + 1);
            return i + 1;
        }
        rnd -= weights[i];
    }
    return 1;
}
