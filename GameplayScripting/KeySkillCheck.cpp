#include "KeySkillCheck.h"
#include "utils.h"

Texture* KeySkillCheck::m_pUpArrowText = nullptr;
Texture* KeySkillCheck::m_pDownArrowText = nullptr;
Texture* KeySkillCheck::m_pLeftArrowText = nullptr;
Texture* KeySkillCheck::m_pRightArrowText = nullptr;
Texture* KeySkillCheck::m_pUpArrowTextSuccess = nullptr;
Texture* KeySkillCheck::m_pDownArrowTextSuccess = nullptr;
Texture* KeySkillCheck::m_pLeftArrowTextSuccess = nullptr;
Texture* KeySkillCheck::m_pRightArrowTextSuccess = nullptr;

KeySkillCheck::KeySkillCheck(const Vector2f& pos)
	: m_IsHidden{ false },
	m_Position{ pos },
	m_CurrKeyIndex{ 0 },
	m_ShowFeedback{ false },
	m_FeedbackTimer{ 1.f },
	m_pFeedback{ }
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
}

void KeySkillCheck::Draw() const
{
	if (m_IsHidden == false)
	{
		Rectf rect{ m_Position.x, m_Position.y, 400.f, 75.f };
		utils::SetColor(Color4f(0.f, 0.f, 0.f, 0.75f));
		utils::FillRect(rect);

		for (size_t i = 0; i < m_KeyTextures.size(); i++)
		{
			m_KeyTextures[i]->Draw(Vector2f{ 50.f + m_Position.x + 125.f * i, m_Position.y });
		}
		if (m_ShowFeedback == true)
		{
			m_pFeedback->Draw(Vector2f{ m_Position.x, m_Position.y - m_pFeedback->GetHeight() + 175.f });
		}
	}
}

void KeySkillCheck::Update(float elapsedSec)
{
	if (m_IsHidden == false)
	{
		const Uint8* state = SDL_GetKeyboardState(NULL);

		if (m_CurrKeyIndex < m_Keys.size())
		{
			SDL_KeyCode expectedKey = m_Keys[m_CurrKeyIndex];

			if (state[SDL_GetScancodeFromKey(expectedKey)])
			{
				switch (expectedKey)
				{
				case SDLK_UP:
					m_KeyTextures[m_CurrKeyIndex] = m_pUpArrowTextSuccess;
					break;
				case SDLK_DOWN:
					m_KeyTextures[m_CurrKeyIndex] = m_pDownArrowTextSuccess;
					break;
				case SDLK_LEFT:
					m_KeyTextures[m_CurrKeyIndex] = m_pLeftArrowTextSuccess;
					break;
				case SDLK_RIGHT: m_KeyTextures[m_CurrKeyIndex] = m_pRightArrowTextSuccess;
					break;
				}
				++m_CurrKeyIndex;
			}
		}
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
	const std::string font{ "Font.ttf" };
	std::string text{ "" };

	if (m_CurrKeyIndex >= m_Keys.size() - 1 == true)
	{
		m_ShowFeedback = true;
		delete m_pFeedback;
		text = "Nice! You got it!";
		m_pFeedback = new Texture{ text, font, 50, Color4f{0.f, 1.f, 0.f, 1.f} };
		return true;
	}
	else {
		return false;
	}
}

std::vector<SDL_KeyCode> KeySkillCheck::GetRandKeys()
{
	const int randKeyAmount{ 3 };
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
	const int txtSize{ 50 };
	const std::string font{ "Font.ttf" };
	m_pUpArrowText = new Texture("^", font, txtSize, yellow);
	m_pDownArrowText = new Texture("V", font, txtSize, yellow);
	m_pLeftArrowText = new Texture("<", font, txtSize, yellow);
	m_pRightArrowText = new Texture(">", font, txtSize, yellow);

	const Color4f green{ 0.f, 1.f, 0.f, 0.75f };
	m_pUpArrowTextSuccess = new Texture("^", font, txtSize, green);
	m_pDownArrowTextSuccess = new Texture("V", font, txtSize, green);
	m_pLeftArrowTextSuccess = new Texture("<", font, txtSize, green);
	m_pRightArrowTextSuccess = new Texture(">", font, txtSize, green);
}
