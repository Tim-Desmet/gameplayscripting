#pragma once
#include "BaseGame.h"

class Texture;
class Fisherman;
class Boss;
class Game : public BaseGame
{
public:
	explicit Game( const Window& window );
	Game(const Game& other) = delete;
	Game& operator=(const Game& other) = delete;
	Game( Game&& other) = delete;
	Game& operator=(Game&& other) = delete;
	// http://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#Rh-override
	~Game();

	void Update( float elapsedSec ) override;
	void Draw( ) const override;

	// Event handling
	void ProcessKeyDownEvent( const SDL_KeyboardEvent& e ) override;
	void ProcessKeyUpEvent( const SDL_KeyboardEvent& e ) override;
	void ProcessMouseMotionEvent( const SDL_MouseMotionEvent& e ) override;
	void ProcessMouseDownEvent( const SDL_MouseButtonEvent& e ) override;
	void ProcessMouseUpEvent( const SDL_MouseButtonEvent& e ) override;

private:

	// FUNCTIONS
	void Initialize();
	void Cleanup( );
	void ClearBackground( ) const;

	void GameOver();

	bool m_ShowInfo;
	bool m_IsGameOver;
	bool m_IsPaused;
	int m_Score;
	Texture* m_pWaterTexture;
	Texture* m_pFishingHutTexture;
	Texture* m_pInfoTexture;
	Texture* m_pGameOverTexture;
	Texture* m_pRestartTexture;
	Texture* m_pScoreTexture;
	Fisherman* m_pFisherman;
	Boss* m_pBoss;
};