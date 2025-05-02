#pragma once
#include <utils.h>
class SkillCheck
{
public:
	SkillCheck(const Vector2f& pos, float width, float speed);
	void Draw() const;
	void Update(float elapsedSec);
	void Stop();
	void ToggleVisibility();

private:
	Vector2f m_Position;
	float m_Width;
	bool m_IsHidden;
	bool m_IsMoving;
	float m_Speed;
	Rectf m_PlayerRect;
	Rectf m_BorderRect;
};

