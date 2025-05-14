#include "pch.h"
#include "Fisherman.h"
#include "Texture.h"
#include "RectSkillCheck.h"
#include "CircleSkillCheck.h"
#include "Fish.h"
#include <vector>
#include <iostream>

Fisherman::Fisherman(const Vector2f& pos)
	: m_Pos{ pos }, m_State{ State::idle }, m_CurrFrame{ 0 }, m_Cols{ 4 }, m_AnimTime{ 0.f },
	m_pSkillCheck{}, m_pCurrFish{}, m_ShowFish{ false }, m_pCircleSkillCheck{}
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
	delete m_pCircleSkillCheck;
	m_pCircleSkillCheck = nullptr;
	delete m_pCurrFish;
	m_pCurrFish = nullptr;

}

void Fisherman::Draw(const Vector2f& fishPos) const
{
	Rectf srcRect{};
	float width{ 0.f };
	float height{ 0.f };
	Rectf dstRect{ m_Pos.x, m_Pos.y, width, height };
	int row{ 0 };

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
		break;
	default:
		break;
	}

	if (m_pCircleSkillCheck != nullptr)
	{
		m_pCircleSkillCheck->Draw();
	}

	if (m_pSkillCheck != nullptr)
	{
		m_pSkillCheck->Draw();
	}

	if (m_ShowFish == true)
	{
		m_pCurrFish->Draw(fishPos);
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
			m_ShowFish = false;
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

	if (m_pCircleSkillCheck != nullptr)
	{
		m_pCircleSkillCheck->Update(elapsedSec);
	}

	if (m_pSkillCheck != nullptr)
	{
		m_pSkillCheck->Update(elapsedSec);
	}

	if (m_ShowFish == true && m_pCurrFish != nullptr)
	{
		m_pCurrFish->Update(elapsedSec);
	}
}

void Fisherman::Find(const Vector2f& pos)
{
	const int skillCheckAmount{ 2 };

	m_State = State::fishing;
	if (m_ShowFish == false)
	{
		int randSkillNr = rand() % skillCheckAmount;
		delete m_pSkillCheck;
		m_pSkillCheck = nullptr;
		delete m_pCircleSkillCheck;
		m_pCircleSkillCheck = nullptr;

		if (randSkillNr == 0)
		{
			m_pSkillCheck = new RectSkillCheck(Vector2f{ pos.x / 2, 4 * pos.y / 5 }, 20.f);
			m_pSkillCheck->ToggleVisibility();
		}
		else if (randSkillNr == 1)
		{
			m_pCircleSkillCheck = new CircleSkillCheck{ Vector2f{pos.x / 2, pos.y / 2} , M_PI / 6 };
			m_pCircleSkillCheck->ToggleVisibility();
		}
		m_pCurrFish = new Fish();
		m_ShowFish = true;
	}
}

void Fisherman::Catch()
{
	if (m_State == State::fishing)
	{
		if (m_pSkillCheck != nullptr)
		{
			m_pSkillCheck->Stop();
			m_pSkillCheck->CheckSucces();
		}
		else if (m_pCircleSkillCheck != nullptr)
		{
			m_pCircleSkillCheck->Stop();
			m_pCircleSkillCheck->CheckSucces();
		}

		m_ShowFish = false;
		delete m_pCurrFish;
		m_pCurrFish = nullptr;
		m_State = State::hook;
	}
}

void Fisherman::CastRod()
{

}

void Fisherman::InitTextures()
{
	m_pIdleTexture = new Texture("Fisherman/Fisherman_idle.png");
	m_pHookTexture = new Texture("Fisherman/Fisherman_hook.png");
	m_pFishTexture = new Texture("Fisherman/Fisherman_fish.png");
}
