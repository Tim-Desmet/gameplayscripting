#include "pch.h"
#include "Game.h"
#include "Texture.h"
#include "Fisherman.h"
#include "Boss.h"
#include <utils.h>

Game::Game( const Window& window ) 
	:BaseGame{ window }
{
	Initialize();
}

Game::~Game( )
{
	Cleanup( );
}

void Game::Initialize( )
{
	SetConsoleOutputCP(CP_UTF8);
	m_Score = 0;
	m_ShowInfo = false;
	m_IsGameOver = false;
	m_IsPaused = false;
	std::string info{ "Controls: E = Cast rod, SPACEBAR = Attempt skillcheck" };
	std::string gameOver{ "Game Over X(" };
	std::string restart{ "Press r to restart" };

	m_pWaterTexture = new Texture{"Objects/ocean.png"};
	m_pFishingHutTexture = new Texture{"Objects/Fishing_hut.png"};
	m_pInfoTexture = new Texture(info, "Font.ttf", 20, Color4f{ 1.f, 1.f, 0.f, 1.f });
	m_pGameOverTexture = new Texture(gameOver, "Font.ttf", 80, Color4f{ 1.f, 0.f, 0.f, 1.f });
	m_pRestartTexture = new Texture(restart, "Font.ttf", 30, Color4f{ 1.f, 0.f, 0.f, 1.f });
	m_pScoreTexture = new Texture(std::to_string(m_Score), "Font.ttf", 30, Color4f{ 0.f, 0.f, 1.f, 1.f });
	m_pAddedScoreTexture = nullptr;

	const Vector2f fisherPosisher{ 135.f, GetViewPort().height / 2 + 10.f };
	m_pFisherman = new Fisherman(fisherPosisher);
	const Vector2f bossStartPos{ GetViewPort().width - 20.f, GetViewPort().height / 3 };
	m_pBoss = new Boss(bossStartPos);
}

void Game::Cleanup( )
{
	delete m_pWaterTexture;
	m_pWaterTexture = nullptr;
	delete m_pFishingHutTexture;
	m_pFishingHutTexture = nullptr;
	delete m_pFisherman;
	m_pFisherman = nullptr;
	delete m_pBoss;
	m_pBoss = nullptr;
	delete m_pInfoTexture;
	m_pInfoTexture = nullptr;
	delete m_pGameOverTexture;
	m_pGameOverTexture = nullptr;
	delete m_pRestartTexture;
	m_pRestartTexture = nullptr;
	delete m_pScoreTexture;
	m_pScoreTexture = nullptr;
	delete m_pAddedScoreTexture;
	m_pAddedScoreTexture = nullptr;
}

void Game::Update( float elapsedSec )
{
	const float fisherPosisherX{ 135.f };
	if (m_IsGameOver == false && m_IsPaused == false)
	{
		m_pFisherman->Update(elapsedSec);
		if (m_pBoss != nullptr)
		{
			m_pBoss->Update(elapsedSec);
			if (m_pBoss->GetXPos() <= fisherPosisherX)
			{
				GameOver();
			}
		}
	}
}

void Game::Draw( ) const
{
	ClearBackground( );
	glPushMatrix();
	glScalef(1.7f, 1.7f, 1.f);
	m_pWaterTexture->Draw();
	glPopMatrix();
	m_pFishingHutTexture->Draw(Vector2f{ -30.f, GetViewPort().height / 2 }, Rectf{ 0.f, 0.f, m_pFishingHutTexture->GetWidth(), 2 * m_pFishingHutTexture->GetHeight() / 3 - 8.f });
	m_pFisherman->Draw(Vector2f(GetViewPort().width / 2, 30.f));
	m_pScoreTexture->Draw(Vector2f{ GetViewPort().width - m_pScoreTexture->GetWidth() - 10.f, GetViewPort().height - m_pScoreTexture->GetHeight() - 10.f});
	if (m_pAddedScoreTexture != nullptr)
	{
		m_pAddedScoreTexture->Draw(Vector2f{ GetViewPort().width - m_pScoreTexture->GetWidth() - 10.f, GetViewPort().height - m_pScoreTexture->GetHeight() - m_pAddedScoreTexture->GetHeight() - 10.f});
	}
	if (m_pBoss != nullptr)
	{
		m_pBoss->Draw();
	}
	if (m_ShowInfo == true)
	{
		m_pInfoTexture->Draw(Vector2f{ GetViewPort().left, GetViewPort().height - m_pInfoTexture->GetHeight() - 5.f });
	}
	if (m_IsGameOver == true)
	{
		m_pGameOverTexture->Draw(Vector2f{ GetViewPort().width / 2 - m_pGameOverTexture->GetWidth() / 2, GetViewPort().height / 2 });
		m_pRestartTexture->Draw(Vector2f{ GetViewPort().width / 2 - m_pRestartTexture->GetWidth() / 2, GetViewPort().height / 2 - 20.f });
		Rectf gameOverBlur{ GetViewPort().left + 5.f, GetViewPort().bottom + 5.f, GetViewPort().width - 10.f, GetViewPort().height - 10.f };
		utils::SetColor(Color4f{ 0.f, 0.f, 0.f, 0.5f });
		utils::FillRect(gameOverBlur);
	}
}

void Game::ProcessKeyDownEvent( const SDL_KeyboardEvent & e )
{
	switch (e.keysym.sym)
	{
	case SDLK_e:
		if (m_IsGameOver == false && m_IsPaused == false)
		{
			m_pFisherman->Find(Vector2f(GetViewPort().width, GetViewPort().height));
		}
		break;
	case SDLK_SPACE:
		if (m_pBoss != nullptr && m_IsGameOver == false && m_IsPaused == false)
		{
			int addedScore = 10 * m_pFisherman->Catch(*m_pBoss, 0);
			m_Score += addedScore;
			delete m_pScoreTexture;
			delete m_pAddedScoreTexture;
			m_pScoreTexture = new Texture(std::to_string(m_Score), "Font.ttf", 30, Color4f{ 0.f, 0.f, 1.f, 1.f });
			m_pAddedScoreTexture = new Texture("+" + std::to_string(addedScore), "Font.ttf", 25, Color4f{0.f, 0.f, 1.f, 0.5f});
		}
		break;
	case SDLK_i:
		m_ShowInfo = !m_ShowInfo;
		break;
	case SDLK_r:
		if (m_IsGameOver == true)
		{
			m_Score = 0;
			m_IsGameOver = false;
			const Vector2f bossStartPos{ GetViewPort().width - 20.f, GetViewPort().height / 3 };
			m_pBoss = new Boss(bossStartPos);
		}
		break;
	case SDLK_p:
		m_IsPaused = !m_IsPaused;
		break;
	case SDLK_UP:
	case SDLK_DOWN:
	case SDLK_RIGHT:
	case SDLK_LEFT:
		if (m_pBoss != nullptr && m_IsGameOver == false && m_IsPaused == false)
		{
			int newScore{ 10 * m_pFisherman->Catch(*m_pBoss, 1) };
			if (newScore >= 0)
			{
				m_Score += newScore;
				delete m_pScoreTexture;
				m_pScoreTexture = new Texture(std::to_string(m_Score), "Font.ttf", 30, Color4f{ 0.f, 0.f, 1.f, 1.f });
			}
		}
		break;
	default:
		break;
	}
}

void Game::ProcessKeyUpEvent( const SDL_KeyboardEvent& e )
{
	//std::cout << "KEYUP event: " << e.keysym.sym << std::endl;
	//switch ( e.keysym.sym )
	//{
	//case SDLK_LEFT:
	//	//std::cout << "Left arrow key released\n";
	//	break;
	//case SDLK_RIGHT:
	//	//std::cout << "`Right arrow key released\n";
	//	break;
	//case SDLK_1:
	//case SDLK_KP_1:
	//	//std::cout << "Key 1 released\n";
	//	break;
	//}
}

void Game::ProcessMouseMotionEvent( const SDL_MouseMotionEvent& e )
{
	//std::cout << "MOUSEMOTION event: " << e.x << ", " << e.y << std::endl;
}

void Game::ProcessMouseDownEvent( const SDL_MouseButtonEvent& e )
{
	//std::cout << "MOUSEBUTTONDOWN event: ";
	//switch ( e.button )
	//{
	//case SDL_BUTTON_LEFT:
	//	std::cout << " left button " << std::endl;
	//	break;
	//case SDL_BUTTON_RIGHT:
	//	std::cout << " right button " << std::endl;
	//	break;
	//case SDL_BUTTON_MIDDLE:
	//	std::cout << " middle button " << std::endl;
	//	break;
	//}
	
}

void Game::ProcessMouseUpEvent( const SDL_MouseButtonEvent& e )
{
	//std::cout << "MOUSEBUTTONUP event: ";
	//switch ( e.button )
	//{
	//case SDL_BUTTON_LEFT:
	//	std::cout << " left button " << std::endl;
	//	break;
	//case SDL_BUTTON_RIGHT:
	//	std::cout << " right button " << std::endl;
	//	break;
	//case SDL_BUTTON_MIDDLE:
	//	std::cout << " middle button " << std::endl;
	//	break;
	//}
}

void Game::ClearBackground( ) const
{
	glClearColor( 0.5f, 0.8f, 0.9f, 1.f );
	glClear( GL_COLOR_BUFFER_BIT );
}

void Game::GameOver()
{
	m_IsGameOver = true;
	delete m_pBoss;
	m_pBoss = nullptr;
}

//void Game::DrawWater() const
//{
//	const float height{ m_pWaterTexture->GetHeight() / 3 - 10.f};
//	const float width{ m_pWaterTexture->GetWidth() };
//	const Rectf texClip{ 0.f, 0.f, width, height };
//
//	for (float yPos = (GetViewPort().height / 3); yPos >= -height; yPos -= height)
//	{
//		for (float xPos = 0.f; xPos < GetViewPort().width; xPos += width)
//		{
//			Rectf rect{ xPos, yPos, width, height };
//			m_pWaterTexture->Draw(rect, texClip);
//		}
//	}
//}
