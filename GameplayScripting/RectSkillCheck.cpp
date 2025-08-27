#include "pch.h"
#include "RectSkillCheck.h"
#include "Texture.h"
#include <utils.h>

RectSkillCheck::RectSkillCheck(const Vector2f& pos, const float width)
	: m_Width(width),
	m_IsHidden( false ),
	m_Speed{ 300.f },
	m_ShowFeedback{ false },
	m_IsMoving{ false },
	m_BorderRect{ pos.x - 200.f, pos.y, 400.f, 75.f },
	m_PlayerRect{ pos.x - 200.f, pos.y, 5.f, 75.f },
	m_pFeedback{ },
	m_FeedbackTimer{ 1.f }
{
	m_Position.x = rand() % (int)(m_BorderRect.width - m_BorderRect.left) + m_BorderRect.left;
	m_Position.y = pos.y;
}

RectSkillCheck::~RectSkillCheck()
{
	delete m_pFeedback;
	m_pFeedback = nullptr;
}

void RectSkillCheck::Draw() const
{
	if (m_IsHidden == false)
	{
		utils::SetColor(Color4f(0.f, 0.f, 0.f, 0.75f));
		utils::FillRect(m_BorderRect);
		utils::SetColor(Color4f(1.f, 1.f, 0.f, 0.75f));
		utils::FillRect(m_Position.x, m_Position.y, m_Width, m_BorderRect.height);
		utils::SetColor(Color4f(1.f, 0.f, 0.f, 1.f));
		utils::FillRect(m_PlayerRect);
		if (m_ShowFeedback == true)
		{
			m_pFeedback->Draw(Vector2f{ m_BorderRect.left + 200.f - m_pFeedback->GetWidth() / 2, m_Position.y - m_pFeedback->GetHeight() + 250.f});
		}
	}
}

void RectSkillCheck::Update(float elapsedSec)
{
	if (m_IsHidden == false)
	{
		m_PlayerRect.left += m_Speed * elapsedSec;
		if (m_PlayerRect.left + m_PlayerRect.width >= m_BorderRect.left + m_BorderRect.width || m_PlayerRect.left <= m_BorderRect.left)
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

void RectSkillCheck::Stop()
{
	if (m_IsHidden == false)
	{
		m_Speed = 0.f;
	}
}

void RectSkillCheck::ToggleVisibility()
{
	m_IsHidden = !m_IsHidden;
}

bool RectSkillCheck::CheckSucces()
{
	m_ShowFeedback = true;
	std::string font{ "Font.ttf" };
	std::string text{ "" };

	delete m_pFeedback;
	if (m_PlayerRect.left <= m_Position.x + m_Width && m_PlayerRect.left + m_PlayerRect.width >= m_Position.x)
	{
		text = "Nice! You got it!";
		m_pFeedback = new Texture{ text, font, 50, Color4f{0.f, 1.f, 0.f, 1.f} };
		return true;
	}
	else {
		text = "Snap! It got away...";
		m_pFeedback = new Texture{ text, font, 50, Color4f{1.f, 0.f, 0.f, 1.f} };
		return false;
	}
}
