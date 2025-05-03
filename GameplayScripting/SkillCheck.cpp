#include "pch.h"
#include "SkillCheck.h"
#include "Texture.h"
#include <utils.h>
#include <iostream>

SkillCheck::SkillCheck(const Vector2f& pos, float width, float speed) : m_Width(width), m_Position(pos), m_IsHidden(true), m_Speed{ speed },
m_ShowFeedback{ false }, m_IsMoving{ false }, m_BorderRect{ pos.x - 200.f, pos.y, 400.f, 75.f }, m_PlayerRect{ pos.x - 100.f, pos.y, 5.f, 75.f },
m_pFeedback{ nullptr }, m_FeedbackTimer{ 1.f }
{
}

SkillCheck::~SkillCheck()
{
	delete m_pFeedback;
	m_pFeedback = nullptr;
}

void SkillCheck::Draw() const
{
	if (m_IsHidden == false)
	{
		utils::SetColor(Color4f(0.f, 0.f, 0.f, 0.75f));
		utils::FillRect(m_BorderRect);
		utils::SetColor(Color4f(1.f, 1.f, 0.f, 0.75f));
		utils::FillRect(m_Position.x, m_Position.y, m_Width, m_BorderRect.height);
		utils::SetColor(Color4f(1.f, 1.f, 1.f, 1.f));
		utils::FillRect(m_PlayerRect);
		if (m_ShowFeedback == true)
		{
			m_pFeedback->Draw(Vector2f{ m_Position.x - m_pFeedback->GetWidth() / 2, m_Position.y * 1.5f});
		}
	}
}

void SkillCheck::Update(float elapsedSec)
{
	if (m_IsHidden == false)
	{
		m_PlayerRect.left += m_Speed * elapsedSec;
		if (m_PlayerRect.left + m_Width >= m_BorderRect.left + m_BorderRect.width || m_PlayerRect.left <= m_BorderRect.left)
		{
			m_Speed = -m_Speed;
		}
		if (m_ShowFeedback == true)
		{
			m_FeedbackTimer -= elapsedSec;
			if (m_FeedbackTimer <= 0.f)
			{
				m_ShowFeedback = false;
				ToggleVisibility();
			}
		}
	}
}

void SkillCheck::Stop()
{
	if (m_IsHidden == false)
	{
		m_Speed = 0.f;
		CheckSucces();
	}
}

void SkillCheck::ToggleVisibility()
{
	m_IsHidden = !m_IsHidden;
}

void SkillCheck::CheckSucces()
{
	m_ShowFeedback = true;
	std::string font{ "Font.ttf" };
	std::string text{ "" };

	if (m_PlayerRect.left <= m_Position.x + m_Width && m_PlayerRect.left >= m_Position.x)
	{
		text = "Nice! You got it!";
		m_pFeedback = new Texture{ text, font, 50, Color4f{0.f, 1.f, 0.f, 1.f} };
	}
	else {
		text = "Snap! It got away...";
		m_pFeedback = new Texture{ text, font, 50, Color4f{1.f, 0.f, 0.f, 1.f} };
	}
}
