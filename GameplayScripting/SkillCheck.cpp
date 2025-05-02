#include "pch.h"
#include "SkillCheck.h"
#include <utils.h>
#include <iostream>

SkillCheck::SkillCheck(const Vector2f& pos, float width, float speed) : m_Width(width), m_Position(pos), m_IsHidden(true), m_Speed{ speed },
m_IsMoving{ false }, m_BorderRect{ pos.x - 200.f, pos.y, 400.f, 75.f }, m_PlayerRect{ pos.x - 100.f, pos.y, 5.f, 75.f }
{
}

SkillCheck::~SkillCheck()
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
	if (m_IsHidden == false)
	{
		m_Speed = 0.f;
		CheckSucces();
		ToggleVisibility();
	}
}

void SkillCheck::ToggleVisibility()
{
	m_IsHidden = !m_IsHidden;
}

void SkillCheck::CheckSucces()
{
	if (m_PlayerRect.left <= m_Position.x + m_Width && m_PlayerRect.left >= m_Position.x)
	{
		// Catch
		std::cout << "Nice! You got it!";
	}
	else {
		// No Catch
		std::cout << "Snap! It got away...";
	}
}
