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
	m_pWaterTexture = new Texture{"Objects/ocean.png"};
	m_pFishingHutTexture = new Texture{"Objects/Fishing_hut.png"};

	const Vector2f fisherPosisher{ 135.f, GetViewPort().height / 2 + 10.f };
	m_pFisherman = new Fisherman(fisherPosisher);
	const Vector2f bossStartPos{ GetViewPort().width, GetViewPort().height / 3 + 20.f };
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
}

void Game::Update( float elapsedSec )
{
	m_pFisherman->Update(elapsedSec);
	m_pBoss->Update(elapsedSec);
}

void Game::Draw( ) const
{
	ClearBackground( );
	glPushMatrix();
	glScalef(1.7f, 1.7f, 1.f);
	m_pWaterTexture->Draw();
	glPopMatrix();
	m_pFishingHutTexture->Draw(Vector2f{ -30.f, GetViewPort().height / 2 }, Rectf{ 0.f, 0.f, m_pFishingHutTexture->GetWidth(), 2 * m_pFishingHutTexture->GetHeight() / 3 - 8.f });
	m_pFisherman->Draw(Vector2f(GetViewPort().width / 2, 3 * GetViewPort().height / 4));
	m_pBoss->Draw();
}

void Game::ProcessKeyDownEvent( const SDL_KeyboardEvent & e )
{
	switch (e.keysym.sym)
	{
	case SDLK_e:
		m_pFisherman->Find(Vector2f(GetViewPort().width, GetViewPort().height));
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
