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
	m_CurrKeyIndex{ 0 }
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
			m_KeyTextures[i]->Draw(Vector2f{ m_Position.x + 80.f * i, m_Position.y });
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
	}
}


void KeySkillCheck::ToggleVisibility()
{
	m_IsHidden = !m_IsHidden;
}

bool KeySkillCheck::CheckSuccess()
{
	return m_CurrKeyIndex >= m_Keys.size();
}

std::vector<SDL_KeyCode> KeySkillCheck::GetRandKeys()
{
	const int randKeyAmount{ 5 };
	std::vector<SDL_KeyCode> keys{};

	for (size_t i = 0; i < randKeyAmount; i++)
	{
		int randKeyNr = rand() % 4;
		switch (randKeyNr)
		{
		case 0:
			keys.push_back(SDLK_UP);
			m_KeyTextures.push_back(m_pUpArrowText);
			break;
		case 1:
			keys.push_back(SDLK_DOWN);
			m_KeyTextures.push_back(m_pDownArrowText);
			break;
		case 2:
			keys.push_back(SDLK_LEFT);
			m_KeyTextures.push_back(m_pLeftArrowText);
			break;
		case 3:
			keys.push_back(SDLK_RIGHT);
			m_KeyTextures.push_back(m_pRightArrowText);
			break;
		default:
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
	m_pDownArrowText = new Texture("v", font, txtSize, yellow);
	m_pLeftArrowText = new Texture("<", font, txtSize, yellow);
	m_pRightArrowText = new Texture(">", font, txtSize, yellow);

	const Color4f green{ 0.f, 1.f, 0.f, 0.75f };
	m_pUpArrowTextSuccess = new Texture("^", font, txtSize, green);
	m_pDownArrowTextSuccess = new Texture("v", font, txtSize, green);
	m_pLeftArrowTextSuccess = new Texture("<", font, txtSize, green);
	m_pRightArrowTextSuccess = new Texture(">", font, txtSize, green);
}
