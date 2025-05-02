#include "pch.h"
#include "Fisherman.h"
#include "Texture.h"
#include "SkillCheck.h"

Fisherman::Fisherman(const Vector2f& pos)
	: m_Pos{ pos }, m_State{ State::idle }, m_CurrFrame{ 0 }, m_Cols{ 4 }, m_AnimTime{ 0.f },
	m_pSkillCheck{ new SkillCheck(pos, 20.f, 300.f) }
{
	InitTextures();
}

Fisherman::~Fisherman()
{
	delete m_pIdleTexture;
	m_pIdleTexture = nullptr;
	delete m_pHookTexture;
	m_pHookTexture = nullptr;
	delete m_pFishTexture;
	m_pFishTexture = nullptr;
	delete m_pSkillCheck;
	m_pSkillCheck = nullptr;
}

Fisherman::Fisherman(const Fisherman& other)
	: m_Pos(other.m_Pos), m_State(other.m_State), m_CurrFrame{ other.m_CurrFrame }, m_Cols{ other.m_Cols },
	m_AnimTime{ other.m_AnimTime }
{
	InitTextures();
}

Fisherman& Fisherman::operator=(const Fisherman& other) {
    if (this == &other) return *this;

    m_Pos = other.m_Pos;
    m_State = other.m_State;
	m_CurrFrame = other.m_CurrFrame;
	m_Cols = other.m_Cols;
	m_AnimTime = other.m_AnimTime;

    return *this;
}

void Fisherman::Draw() const
{
	Rectf srcRect{};
	float width{ 0.f };
	float height{ 0.f };
	Rectf dstRect{ m_Pos.x, m_Pos.y, width, height };

	switch (m_State)
	{
	case Fisherman::State::idle:
		width = m_pIdleTexture->GetWidth() / 4;
		height = m_pIdleTexture->GetHeight();
		srcRect = Rectf{ m_CurrFrame * width, 0.f, width, height };
		m_pIdleTexture->Draw(dstRect, srcRect);
		break;
	case Fisherman::State::hook:
		width = m_pHookTexture->GetWidth() / 6;
		height = m_pHookTexture->GetHeight();
		srcRect = Rectf{ m_CurrFrame * width, 0.f, width, height };
		m_pHookTexture->Draw(dstRect, srcRect);
		break;
	case Fisherman::State::fishing:
		width = m_pFishTexture->GetWidth() / 4;
		height = m_pFishTexture->GetHeight();
		srcRect = Rectf{ m_CurrFrame * width, 0.f, width, height };
		m_pFishTexture->Draw(dstRect, srcRect);
		m_pSkillCheck->Draw();
		break;
	default:
		break;
	}
}

void Fisherman::Update(float elapsedSec)
{
	const float m_FrameDuration{ 0.3f };

	m_AnimTime += elapsedSec;

	if (m_AnimTime >= m_FrameDuration)
	{
		m_AnimTime -= m_FrameDuration;

		if (m_State == State::hook)
		{
			if (m_CurrFrame < m_Cols - 1)
			{
				m_CurrFrame++;
			}
			else {
				m_State = State::idle;
			}
		}
		else
		{
			m_CurrFrame = (m_CurrFrame + 1) % m_Cols;
		}
	}
	if (m_State == State::fishing)
	{
		m_pSkillCheck->Update(elapsedSec);
	}
}

void Fisherman::SetState(const State& state)
{
	m_State = state;
}

Fisherman::State Fisherman::GetState() const
{
	return m_State;
}

void Fisherman::ShowSkillCheck(const Vector2f& pos)
{
	delete m_pSkillCheck;
	m_pSkillCheck = new SkillCheck(pos, 20.f, 300.f);
	m_pSkillCheck->ToggleVisibility();
}

void Fisherman::Catch()
{
	m_pSkillCheck->Stop();
}

void Fisherman::InitTextures()
{
	m_pIdleTexture = new Texture("Fisherman/Fisherman_idle.png");
	m_pHookTexture = new Texture("Fisherman/Fisherman_hook.png");
	m_pFishTexture = new Texture("Fisherman/Fisherman_fish.png");
}
