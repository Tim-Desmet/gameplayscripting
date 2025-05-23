#pragma once
#include <vector>
class Texture;
class Fish;
class RectSkillCheck;
class CircleSkillCheck;
class Boss;
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
	void Find(const Vector2f& pos);
	void Catch(Boss& boss);
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
	RectSkillCheck* m_pSkillCheck;
	CircleSkillCheck* m_pCircleSkillCheck;
	Fish* m_pCurrFish;
	bool m_ShowFish;

	void InitTextures();
};

