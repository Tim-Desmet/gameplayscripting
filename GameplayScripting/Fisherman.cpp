#include "pch.h"
#include "Fisherman.h"
#include "Texture.h"
#include "RectSkillCheck.h"
#include "CircleSkillCheck.h"
#include "KeySkillCheck.h"
#include "Fish.h"
#include "Boss.h"
#include <vector>
#include <iostream>

Fisherman::Fisherman(const Vector2f& pos)
	: m_Pos{ pos }, m_State{ State::idle }, m_CurrFrame{ 0 }, m_Cols{ 4 }, m_AnimTime{ 0.f },
	m_pSkillCheck{}, m_pCurrFish{}, m_ShowFish{ false }, m_pCircleSkillCheck{}, m_pKeySkillCheck{}
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
	delete m_pKeySkillCheck;
	m_pKeySkillCheck = nullptr;
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

	if (m_pKeySkillCheck != nullptr)
	{
		m_pKeySkillCheck->Draw();
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

	if (m_pKeySkillCheck != nullptr)
	{
		m_pKeySkillCheck->Update(elapsedSec);
	}

	if (m_ShowFish == true && m_pCurrFish != nullptr)
	{
		m_pCurrFish->Update(elapsedSec);
	}
}

void Fisherman::Find(const Vector2f& pos)
{
	const int skillCheckAmount{ 3 };

	m_State = State::fishing;
	if (m_ShowFish == false)
	{
		int randSkillNr = rand() % skillCheckAmount;
		delete m_pSkillCheck;
		m_pSkillCheck = nullptr;
		delete m_pCircleSkillCheck;
		m_pCircleSkillCheck = nullptr;
		delete m_pKeySkillCheck;
		m_pKeySkillCheck = nullptr;
		m_pCurrFish = new Fish();
		std::cout << m_pCurrFish->GetRarity() << std::endl;
		if (randSkillNr == 0)
		{
			m_pSkillCheck = new RectSkillCheck(Vector2f{ pos.x / 2, pos.y / 4 }, 100.f / m_pCurrFish->GetRarity());
		}
		else if (randSkillNr == 1)
		{
			m_pCircleSkillCheck = new CircleSkillCheck{ Vector2f{pos.x / 2, pos.y / 3} , (float)M_PI / (2 * m_pCurrFish->GetRarity()) };
		}
		else if (randSkillNr == 2) {
			m_pKeySkillCheck = new KeySkillCheck{ Vector2f{pos.x / 2 - 200.f, pos.y / 4}, m_pCurrFish->GetRarity() };
		}
		m_ShowFish = true;
	}
}

int Fisherman::Catch(Boss& boss, int inputType)
{
	if (m_State == State::fishing)
	{
		const int score{ m_pCurrFish->GetRarity() };
		switch (inputType)
		{
		case 0:
			if (m_pSkillCheck != nullptr)
			{
				m_ShowFish = false;
				delete m_pCurrFish;
				m_pCurrFish = nullptr;
				m_State = State::hook;
				m_pSkillCheck->Stop();
				m_pSkillCheck->CheckSucces();
				if (m_pSkillCheck->CheckSucces() == true)
				{
					return score + boss.TakeDamage(score);
				}
				return 0;
			}
			else if (m_pCircleSkillCheck != nullptr)
			{
				m_ShowFish = false;
				delete m_pCurrFish;
				m_pCurrFish = nullptr;
				m_State = State::hook;
				m_pCircleSkillCheck->Stop();
				m_pCircleSkillCheck->CheckSucces();
				if (m_pCircleSkillCheck->CheckSucces() == true)
				{
					return score + boss.TakeDamage(score);
				}
				return 0;
			}
			break;
		case 1:
			if (m_pKeySkillCheck != nullptr)
			{
				if (m_pKeySkillCheck->CheckSuccess())
				{
					m_ShowFish = false;
					delete m_pCurrFish;
					m_pCurrFish = nullptr;
					m_State = State::hook;
					return score + boss.TakeDamage(score);
				}
				return -1;
			}
			break;
		case 2:
			break;
		default:
			break;

		}
		return 0;
	}
	return 0;
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
