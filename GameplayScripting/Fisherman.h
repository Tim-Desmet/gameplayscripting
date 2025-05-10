#pragma once
#include <vector>
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

	void Draw(const Vector2f& fishPos) const;
	void Update(float elapsedSec);
	void SetState(const State& state);
	State GetState() const;
	void Find(const Vector2f& pos);
	void Catch();
	void CastRod();

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
	std::vector<Fish*> m_pFishCollection;
	Fish* m_pCurrFish;
	bool m_ShowFish;

	void InitTextures();
};

