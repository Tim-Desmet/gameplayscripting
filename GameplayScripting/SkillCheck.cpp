#include "pch.h"
#include "SkillCheck.h"

SkillCheck::SkillCheck(const Vector2f& pos)
{
}

SkillCheck::~SkillCheck()
{
}

void SkillCheck::Draw() const
{
}

void SkillCheck::Update(float elapsedSec)
{
}

void SkillCheck::Stop()
{
	if (m_IsHidden == false)
	{
		m_Speed = 0.f;
	}
}

void SkillCheck::ToggleVisibility()
{
	m_IsHidden = !m_IsHidden;
}

bool SkillCheck::CheckSucces()
{
	return false;
}
