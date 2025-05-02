#include "pch.h"
#include "SkillCheck.h"
#include <utils.h>

SkillCheck::SkillCheck(const Vector2f& pos, float width, float speed) : m_Width(width), m_Position(pos), m_IsHidden(true), m_Speed{ speed },
m_IsMoving{ false }, m_BorderRect{ pos.x - 200.f, pos.y, 400.f, 75.f }, m_PlayerRect{ pos.x - 100.f, pos.y, 5.f, 75.f }
{
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
	}
}

void SkillCheck::Stop()
{
	m_Speed = 0.f;
	m_IsHidden = true;
}

void SkillCheck::ToggleVisibility()
{
	m_IsHidden = !m_IsHidden;
}
