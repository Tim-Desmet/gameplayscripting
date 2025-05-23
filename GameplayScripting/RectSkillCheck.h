#pragma once
#include <utils.h>
class Texture;
class RectSkillCheck
{
public:
	RectSkillCheck(const Vector2f& pos, const float width);
	~RectSkillCheck();
	void Draw() const;
	void Update(float elapsedSec);
	void Stop();
	void ToggleVisibility();
	bool CheckSucces();

private:
	Vector2f m_Position;
	float m_Width;
	bool m_IsHidden;
	bool m_IsMoving;
	float m_Speed;
	Rectf m_PlayerRect;
	Rectf m_BorderRect;

	bool m_ShowFeedback;
	Texture* m_pFeedback;
	float m_FeedbackTimer;
};

