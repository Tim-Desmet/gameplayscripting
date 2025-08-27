#pragma once
#include "Texture.h"
#include <vector>
class SoundEffect;
class KeySkillCheck
{
public:
	KeySkillCheck(const Vector2f& pos, int rarity);
	~KeySkillCheck();

	void Draw() const;
	void Update(float elapsedSec);
	void ToggleVisibility();
	bool CheckSuccess();
	bool IsFullyFailed();

private:
	Vector2f m_Position;
	bool m_IsHidden;
	int m_CurrKeyIndex;
	int m_Difficuly;
	bool m_FullyFailed;

	static Texture* m_pUpArrowText;
	static Texture* m_pDownArrowText;
	static Texture* m_pLeftArrowText;
	static Texture* m_pRightArrowText;
	static Texture* m_pUpArrowTextSuccess;
	static Texture* m_pDownArrowTextSuccess;
	static Texture* m_pLeftArrowTextSuccess;
	static Texture* m_pRightArrowTextSuccess;

	std::vector<SDL_KeyCode> m_Keys;
	std::vector<Texture*> m_KeyTextures;

	bool m_ShowFeedback;
	Texture* m_pFeedback;
	float m_FeedbackTimer;

	Texture* m_pInfoText;
	SoundEffect* m_pInputSound;
	SoundEffect* m_pFail;

	std::vector<SDL_KeyCode> GetRandKeys();
	void LoadTextures();
};