#pragma once

class Texture;
class Fish;
class SkillCheck;
class Fisherman 
{
public:
	enum class State {
		idle,
		hook,
		fishing,
	};

	Fisherman(const Vector2f& pos);
	~Fisherman();
	Fisherman(const Fisherman& other);
	Fisherman& operator=(const Fisherman& other);

	void Draw() const;
	void Update(float elapsedSec);
	void SetState(const State& state);
	State GetState() const;
	void Catch(const Vector2f& pos);

private:
	Vector2f m_Pos;
	State m_State;
	int m_CurrFrame;
	int m_Cols;
	float m_AnimTime;
	const Texture* m_pIdleTexture;
	const Texture* m_pHookTexture;
	const Texture* m_pFishTexture;
	SkillCheck* m_pSkillCheck;

	void InitTextures();
};

