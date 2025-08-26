#include "pch.h"
#include "Fish.h"
#include <iostream>
#include <cassert>
#include <iomanip>
#include <sstream>

Fish::Fish() : m_CurrFrame{ 1 }, m_AnimTime{ 0.f }, m_NumFrames{ 2 }, m_FrameTime{ 0.5f }, m_Rarity{ GetWeightedRandomNumber() }
{
    LoadTextures();
}

Fish::~Fish()
{
	delete m_pTexture;
    m_pTexture = nullptr;
    delete m_pRarity;
    m_pRarity = nullptr;
}

void Fish::Draw(const Vector2f& pos) const
{
	float width = m_pTexture->GetWidth() / m_NumFrames;
	float height = m_pTexture->GetHeight();
	Rectf srcRect = Rectf{ m_CurrFrame * width, 0.f, width, height };
	glPushMatrix();
    glTranslatef(pos.x, pos.y, 0.f);
    m_pRarity->Draw(Vector2f{ -width - m_pRarity->GetWidth() / 2, -m_pRarity->GetHeight()});
    glScalef(3.f, 3.f, 1.f);
    m_pTexture->Draw(Vector2f{ -width / 2, 0.f }, srcRect);
	glPopMatrix();
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

float Fish::GetWeightPercentage() const
{
    int totalWeight = 0;
    for (int i = 0; i < totalFish; i++)
    {
        totalWeight += m_Weights[i];
    }

    float percentage = ((float)m_Weights[m_Rarity - 1] / totalWeight) * 100.0f;
    return std::round(percentage);
}

int Fish::GetWeightedRandomNumber()
{
    int weights[totalFish]{ 500, 240, 100, 60, 40, 30, 20, 10 };
    int totalWeight{ 0 };

    for (int i = 0; i < totalFish; i++) {
        totalWeight += weights[i];
        m_Weights[i] = weights[i];
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

void Fish::LoadTextures()
{
    const std::string font{ "Font.ttf" };
    const float weight{ GetWeightPercentage() };
    std::ostringstream ss;
    ss << std::fixed << std::setprecision(1) << weight;
    m_pTexture = new Texture{ "Objects/Catch/" + std::to_string(m_Rarity) + ".png" };
    switch (m_Rarity)
    {
    case 1:
        m_TxtColor = Color4f{ 0.5f, 0.5f, 0.5f, 1.f };
        m_pRarity = new Texture{ "Very Common " + ss.str() + "%", font, 15, m_TxtColor};
        break;
    case 2:
        m_TxtColor = Color4f{ 0.38f, 0.55f, 0.70f, 1.f };
        m_pRarity = new Texture{ "Common " + ss.str() + "%", font, 15, m_TxtColor };
        break;
    case 3:
        m_TxtColor = Color4f{ 0.0f, 0.0f, 1.f, 1.f };
        m_pRarity = new Texture{ "Uncommon " + ss.str() + "%", font, 15, m_TxtColor };
        break;
    case 4:
        m_TxtColor = Color4f{ 0.0f, 1.f, 0.0f, 1.f };
        m_pRarity = new Texture{ "Rare " + ss.str() + "%", font, 15, m_TxtColor };
        break;
    case 5:
        m_TxtColor = Color4f{ 1.f, 0.65f, 0.f, 1.f };
        m_pRarity = new Texture{ "Very Rare " + ss.str() + "%", font, 15, m_TxtColor };
        break;
    case 6:
        m_TxtColor = Color4f{ 0.5f, 0.f, 0.5f, 1.f };
        m_pRarity = new Texture{ "Epic " + ss.str() + "%", font, 15, m_TxtColor };
        break;
    case 7:
        m_TxtColor = Color4f{ 1.f, 0.84f, 0.f, 1.f };
        m_pRarity = new Texture{ "Legendary " + ss.str() + "%", font, 15, m_TxtColor };
        break;
    case 8:
        m_TxtColor = Color4f{ 1.f, 0.f, 0.f, 1.f };
        m_pRarity = new Texture{ "Mythical " + ss.str() + "%", font, 15, m_TxtColor };
        break;
    default:
        break;
    }
}
