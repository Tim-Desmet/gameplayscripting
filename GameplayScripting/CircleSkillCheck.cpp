#include "pch.h"
#include "CircleSkillCheck.h"
#include "SkillCheck.h"
#include "Texture.h"
#include <utils.h>

CircleSkillCheck::CircleSkillCheck(const Vector2f& pos, const float arcSize) : m_Position{ pos }, m_Radius{ 100.f }, m_Speed{ 5.f },
m_ArcSize{ arcSize }, m_Angle{ (rand() % 360) * (float)M_PI / 180.f }, m_SpinAngle{ 0.f }, m_IsHidden{ true }, m_FeedbackTimer{ 1.f },
m_ShowFeedback{ false }, m_pFeedback{ }
{
}

CircleSkillCheck::~CircleSkillCheck()
{
	delete m_pFeedback;
	m_pFeedback = nullptr;
}

void CircleSkillCheck::Draw() const
{
	if (m_IsHidden == false)
	{
		Ellipsef circle{ m_Position, m_Radius, m_Radius };
		utils::SetColor(Color4f{ 0.f, 0.f, 0.f, 1.0f });
		utils::DrawEllipse(circle, 10.f);
		utils::SetColor(Color4f{ 0.f, 0.f, 0.f, 0.5f });
		utils::FillEllipse(circle);

		utils::SetColor(Color4f{ 1.f, 1.f, 0.f, 0.75f });
		utils::FillArc(circle.center, circle.radiusX, circle.radiusY, m_Angle, m_Angle + m_ArcSize);
		utils::SetColor(Color4f{ 1.f, 0.f, 0.f, 0.75f });

		float x = m_Position.x + m_Radius * (float)cos(m_SpinAngle);
		float y = m_Position.y + m_Radius * (float)sin(m_SpinAngle);
		utils::SetColor(Color4f{ 1.f, 0.f, 0.f, 0.75f });
		utils::DrawLine(m_Position, Vector2f{ x, y }, 5.f);

		if (m_ShowFeedback == true)
		{
			m_pFeedback->Draw(Vector2f{ m_Position.x - m_pFeedback->GetWidth() / 2, m_Position.y - m_pFeedback->GetHeight() - 10.f });
		}
	}
}

void CircleSkillCheck::Update(float elapsedSec)
{
	if (m_IsHidden == false)
	{
		m_SpinAngle += m_Speed * elapsedSec;
		if (m_SpinAngle >= 2.f * float(M_PI))
		{
			m_SpinAngle -= 2.f * float(M_PI);
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

void CircleSkillCheck::Stop()
{
	if (m_IsHidden == false)
	{
		m_Speed = 0.f;
	}
}

void CircleSkillCheck::ToggleVisibility()
{
	m_IsHidden = !m_IsHidden;
}

bool CircleSkillCheck::CheckSucces()
{
	m_ShowFeedback = true;
	std::string font{ "Font.ttf" };
	std::string text{ "" };

	delete m_pFeedback;
	if (m_SpinAngle >= m_Angle && m_SpinAngle <= m_Angle + m_ArcSize)
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
