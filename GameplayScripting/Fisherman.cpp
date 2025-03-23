#include "pch.h"
#include "Fisherman.h"
#include "Texture.h"

Fisherman::Fisherman(const Vector2f& pos)
	: m_Pos{ pos }, m_State{ State::idle }, m_pTexture{ new Texture("Fisherman/Fisherman_idle.png") },
	m_CurrFrame{ 0 }, m_Cols{ 4 }, m_AnimTime{ 0.f }
{
}

Fisherman::~Fisherman()
{
	delete m_pTexture;
}

Fisherman::Fisherman(const Fisherman& other)
	: m_Pos(other.m_Pos), m_State(other.m_State), m_pTexture(other.m_pTexture),
	m_CurrFrame{ other.m_CurrFrame }, m_Cols{ other.m_Cols }, m_AnimTime{ other.m_AnimTime }
{
}

Fisherman& Fisherman::operator=(const Fisherman& other) {
    if (this == &other) return *this;

    delete m_pTexture;

    m_Pos = other.m_Pos;
    m_State = other.m_State;
    m_pTexture = other.m_pTexture;
	m_CurrFrame = other.m_CurrFrame;
	m_Cols = other.m_Cols;
	m_AnimTime = other.m_AnimTime;

    return *this;
}

void Fisherman::Draw() const
{
	Rectf srcRect{};
	float width{ 0.f };
	float height{ m_pTexture->GetHeight() };

	switch (m_State)
	{
	case Fisherman::State::idle:
		width = m_pTexture->GetWidth() / 4;
		srcRect = Rectf{ m_CurrFrame * width, 0.f, width, height };
		break;
	case Fisherman::State::hook:
		width = m_pTexture->GetWidth() / 6;
		srcRect = Rectf{ m_CurrFrame * width, 0.f, width, height };
		break;
	case Fisherman::State::fishing:
		width = m_pTexture->GetWidth() / 4;
		srcRect = Rectf{ m_CurrFrame * width, 0.f, width, height };
		break;
	default:
		break;
	}

	Rectf dstRect{ m_Pos.x, m_Pos.y, width, height };
	m_pTexture->Draw(dstRect, srcRect);
}

void Fisherman::Update(float elapsedSec)
{
	const float m_FrameDuration{ 0.3f };

	switch (m_State)
	{
	case Fisherman::State::idle:
		m_Cols = 4;
		m_pTexture = new Texture("Fisherman/Fisherman_idle.png");
		break;
	case Fisherman::State::hook:
		m_Cols = 6;
		m_pTexture = new Texture("Fisherman/Fisherman_hook.png");
		break;
	case Fisherman::State::fishing:
		m_Cols = 4;
		m_pTexture = new Texture("Fisherman/Fisherman_fish.png");
		break;
	default:
		m_Cols = 4;
		m_pTexture = new Texture("Fisherman/Fisherman_idle.png");
		break;
	}

	m_AnimTime += elapsedSec;

	if (m_AnimTime >= m_FrameDuration)
	{
		m_AnimTime -= m_FrameDuration;

		if (m_State == Fisherman::State::hook)
		{
			if (m_CurrFrame < m_Cols - 1)
			{
				m_CurrFrame++;
			}
			else {
				m_State = Fisherman::State::idle;
			}
		}
		else
		{
			m_CurrFrame = (m_CurrFrame + 1) % m_Cols;
		}
	}
}
