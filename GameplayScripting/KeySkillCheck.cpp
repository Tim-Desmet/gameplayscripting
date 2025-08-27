#include "KeySkillCheck.h"
#include "utils.h"
#include "SoundEffect.h"
#include <iostream>

Texture* KeySkillCheck::m_pUpArrowText = nullptr;
Texture* KeySkillCheck::m_pDownArrowText = nullptr;
Texture* KeySkillCheck::m_pLeftArrowText = nullptr;
Texture* KeySkillCheck::m_pRightArrowText = nullptr;
Texture* KeySkillCheck::m_pUpArrowTextSuccess = nullptr;
Texture* KeySkillCheck::m_pDownArrowTextSuccess = nullptr;
Texture* KeySkillCheck::m_pLeftArrowTextSuccess = nullptr;
Texture* KeySkillCheck::m_pRightArrowTextSuccess = nullptr;

KeySkillCheck::KeySkillCheck(const Vector2f& pos, int rarity)
	: m_IsHidden{ false },
	m_Position{ pos },
	m_CurrKeyIndex{ 0 },
	m_ShowFeedback{ false },
	m_FeedbackTimer{ 1.f },
	m_pFeedback{ },
	m_Difficuly{ rarity },
	m_FullyFailed{ false }
{
	LoadTextures();
	m_Keys = GetRandKeys();
}

KeySkillCheck::~KeySkillCheck()
{
	delete m_pUpArrowText;
	m_pUpArrowText = nullptr;
	delete m_pDownArrowText;
	m_pDownArrowText = nullptr;
	delete m_pLeftArrowText;
	m_pLeftArrowText = nullptr;
	delete m_pRightArrowText;
	m_pRightArrowText = nullptr;
	delete m_pUpArrowTextSuccess;
	m_pUpArrowTextSuccess = nullptr;
	delete m_pDownArrowTextSuccess;
	m_pDownArrowTextSuccess = nullptr;
	delete m_pLeftArrowTextSuccess;
	m_pLeftArrowTextSuccess = nullptr;
	delete m_pRightArrowTextSuccess;
	m_pRightArrowTextSuccess = nullptr;
	delete m_pFeedback;
	m_pFeedback = nullptr;
	delete m_pInfoText;
	m_pInfoText = nullptr;
	delete m_pInputSound;
	m_pInputSound = nullptr;
	delete m_pFail;
	m_pFail = nullptr;
}

void KeySkillCheck::Draw() const
{
	const float arrowWidth = m_pDownArrowText->GetWidth();
	const float spacing = 30.f;
	const int count = m_KeyTextures.size();

	const float totalWidth = count * arrowWidth + (count - 1) * spacing;
	const float startX = m_Position.x + 200.f - totalWidth / 2.f;

	if (m_IsHidden == false)
	{
		Rectf rect{ m_Position.x, m_Position.y, 400.f, 75.f };
		utils::SetColor(Color4f(0.f, 0.f, 0.f, 0.75f));
		utils::FillRect(rect);

		for (size_t i = 0; i < m_KeyTextures.size(); i++)
		{
			m_KeyTextures[i]->Draw(Vector2f{ startX + i * (arrowWidth + spacing), m_Position.y});
		}
		if (m_ShowFeedback == true)
		{
			m_pFeedback->Draw(Vector2f{ m_Position.x + 20.f, m_Position.y - m_pFeedback->GetHeight() + 250.f });
		}
		else {
			m_pInfoText->Draw(Vector2f{ m_Position.x + m_pInfoText->GetWidth() / 2, m_Position.y - m_pInfoText->GetHeight() });
		}
	}
}

void KeySkillCheck::Update(float elapsedSec)
{
	if (m_IsHidden == false)
	{
		if (m_ShowFeedback == true)
		{
			m_FeedbackTimer -= elapsedSec;
			if (m_FeedbackTimer <= 0.f)
			{
				m_ShowFeedback = false;
				ToggleVisibility();
			}
		}
	}
}

void KeySkillCheck::ToggleVisibility()
{
	m_IsHidden = !m_IsHidden;
}

bool KeySkillCheck::CheckSuccess()
{

	const Uint8* state = SDL_GetKeyboardState(NULL);
	const std::string font{ "Font.ttf" };
	std::string text{ "" };

	if (m_CurrKeyIndex < m_Keys.size())
	{
		SDL_KeyCode expectedKey = m_Keys[m_CurrKeyIndex];

		if (state[SDL_GetScancodeFromKey(expectedKey)])
		{
			m_FullyFailed = false;
			switch (expectedKey)
			{
			case SDLK_UP:
				m_KeyTextures[m_CurrKeyIndex] = m_pUpArrowTextSuccess;
				m_pInputSound->Play(false);
				break;
			case SDLK_DOWN:
				m_KeyTextures[m_CurrKeyIndex] = m_pDownArrowTextSuccess;
				m_pInputSound->Play(false);
				break;
			case SDLK_LEFT:
				m_KeyTextures[m_CurrKeyIndex] = m_pLeftArrowTextSuccess;
				m_pInputSound->Play(false);
				break;
			case SDLK_RIGHT: m_KeyTextures[m_CurrKeyIndex] = m_pRightArrowTextSuccess;
				m_pInputSound->Play(false);
				break;
			}
			++m_CurrKeyIndex;
		}
		else {
			m_ShowFeedback = true;
			delete m_pFeedback;
			text = "Snap! It got away...";
			m_pFeedback = new Texture{ text, font, 50, Color4f{1.f, 0.f, 0.f, 1.f} };
			m_pFail->Play(false);
			m_FullyFailed = true;
			return false;
		}
	}

	if (m_CurrKeyIndex >= m_Keys.size())
	{
		m_FullyFailed = false;
		m_ShowFeedback = true;
		delete m_pFeedback;
		text = "Nice! You got it!";
		m_pFeedback = new Texture{ text, font, 50, Color4f{0.f, 1.f, 0.f, 1.f} };
		return true;
	}
	else {
		m_FullyFailed = false;
		return false;
	}
	
}

bool KeySkillCheck::IsFullyFailed()
{
	return m_FullyFailed;
}

std::vector<SDL_KeyCode> KeySkillCheck::GetRandKeys()
{
	const int randKeyAmount{ m_Difficuly / 2 + 1 };
	std::vector<SDL_KeyCode> keys{};
	keys.reserve(randKeyAmount);

	for (size_t i = 0; i < randKeyAmount; i++)
	{
		int randKeyNr;
		SDL_KeyCode newKey{};

		do
		{
			randKeyNr = rand() % 4;
			switch (randKeyNr)
			{
			case 0:
				newKey = SDLK_UP;
				break;
			case 1:
				newKey = SDLK_DOWN;
				break;
			case 2:
				newKey = SDLK_LEFT;
				break;
			case 3:
				newKey = SDLK_RIGHT;
				break;
			}
		} while (!keys.empty() && newKey == keys.back());

		keys.push_back(newKey);

		switch (newKey)
		{
		case SDLK_UP:
			m_KeyTextures.push_back(m_pUpArrowText);
			break;
		case SDLK_DOWN:
			m_KeyTextures.push_back(m_pDownArrowText);
			break;
		case SDLK_LEFT:
			m_KeyTextures.push_back(m_pLeftArrowText);
			break;
		case SDLK_RIGHT:
			m_KeyTextures.push_back(m_pRightArrowText);
			break;
		}
	}
	return keys;
}

void KeySkillCheck::LoadTextures()
{
	const Color4f yellow{ 1.f, 1.f, 0.f, 0.75f };
	const int txtSize{ 60 };
	const std::string arrowFont{ "FiraCode.ttf" };
	const std::string font{ "Font.ttf" };
	m_pUpArrowText = new Texture(u8"↑", arrowFont, txtSize, yellow);
	m_pDownArrowText = new Texture(u8"↓", arrowFont, txtSize, yellow);
	m_pLeftArrowText = new Texture(u8"←", arrowFont, txtSize, yellow);
	m_pRightArrowText = new Texture(u8"→", arrowFont, txtSize, yellow);

	const Color4f green{ 0.f, 1.f, 0.f, 0.75f };
	m_pUpArrowTextSuccess = new Texture(u8"↑", arrowFont, txtSize, green);
	m_pDownArrowTextSuccess = new Texture(u8"↓", arrowFont, txtSize, green);
	m_pLeftArrowTextSuccess = new Texture(u8"←", arrowFont, txtSize, green);
	m_pRightArrowTextSuccess = new Texture(u8"→", arrowFont, txtSize, green);

	std::cout << u8"↓";

	m_pInfoText = new Texture("Use the arrow keys!", font, txtSize / 3, yellow);
	m_pInputSound = new SoundEffect("Sound/input.wav");
	m_pInputSound->SetVolume(25);
	m_pFail = new SoundEffect("Sound/fail.mp3");
	m_pFail->SetVolume(25);
}
