#include "pch.h"
#include "Game.h"
#include "Texture.h"
#include "Fisherman.h"
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
	m_pWaterTexture = new Texture{"Objects/Water.png"};
	m_pFishingHutTexture = new Texture{"Objects/Fishing_hut.png"};

	const Vector2f fisherPosisher{ 135.f, GetViewPort().height / 4 + 10.f };
	m_pFisherman = new Fisherman{ fisherPosisher };
}

void Game::Cleanup( )
{
	delete m_pWaterTexture;
	m_pWaterTexture = nullptr;
	delete m_pFishingHutTexture;
	m_pFishingHutTexture = nullptr;
	delete m_pFisherman;
	m_pFisherman = nullptr;
}

void Game::Update( float elapsedSec )
{
	m_pFisherman->Update(elapsedSec);
}

void Game::Draw( ) const
{
	ClearBackground( );
	DrawMap();
	m_pFisherman->Draw();
}

void Game::ProcessKeyDownEvent( const SDL_KeyboardEvent & e )
{
	switch (e.keysym.sym)
	{
	case SDLK_e:
		m_pFisherman->SetState(Fisherman::State::fishing);
		m_pFisherman->ShowSkillCheck(Vector2f(GetViewPort().width / 2, GetViewPort().height / 2));
		break;
	case SDLK_q:
		m_pFisherman->SetState(Fisherman::State::hook);
		break;
	case SDLK_SPACE:
		m_pFisherman->Catch();
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

void Game::DrawMap() const
{
	DrawWater();
	m_pFishingHutTexture->Draw(Vector2f{ -30.f, GetViewPort().height / 4 },
		Rectf{0.f, 0.f, m_pFishingHutTexture->GetWidth(), 2 * m_pFishingHutTexture->GetHeight() / 3 - 8.f});
}

void Game::DrawWater() const
{
	const float height{ m_pWaterTexture->GetHeight() / 3 - 10.f};
	const float width{ m_pWaterTexture->GetWidth() };
	const Rectf texClip{ 0.f, 0.f, width, height };

	for (float yPos = (GetViewPort().height / 3); yPos >= -height; yPos -= height)
	{
		for (float xPos = 0.f; xPos < GetViewPort().width; xPos += width)
		{
			Rectf rect{ xPos, yPos, width, height };
			m_pWaterTexture->Draw(rect, texClip);
		}
	}
}
