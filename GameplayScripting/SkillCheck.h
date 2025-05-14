#pragma once
class Texture;
class SkillCheck
{
public:
	SkillCheck(const Vector2f& pos);
	~SkillCheck();
	virtual void Draw() const;
	virtual void Update(float elapsedSec);
	void Stop();
	void ToggleVisibility();
	virtual bool CheckSucces();

private:
	Vector2f m_Position;
	bool m_IsHidden;
	float m_Speed;

	bool m_ShowFeedback;
	Texture* m_pFeedback;
	float m_FeedbackTimer;
};

