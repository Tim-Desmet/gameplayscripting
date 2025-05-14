#pragma once
class Texture;
class CircleSkillCheck
{
public:
	CircleSkillCheck(const Vector2f& pos, const float arcSize);
	~CircleSkillCheck();
	void Draw() const;
	void Update(float elapsedSec);
	void Stop();
	void ToggleVisibility();
	bool CheckSucces();

private:
	Vector2f m_Position;
	float m_Radius;
	float m_Speed;
	float m_ArcSize;
	float m_Angle;
	float m_SpinAngle;
	bool m_IsHidden;

	bool m_ShowFeedback;
	Texture* m_pFeedback;
	float m_FeedbackTimer;
};

