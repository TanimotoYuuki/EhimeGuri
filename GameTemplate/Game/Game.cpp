#include "stdafx.h"
#include "BackGround.h"
#include "Game.h"
#include "Player.h"

bool Game::Start()
{
	NewGO<Player>(0, "player");
	NewGO<BackGround>(0, "background");
	return true;
}

void Game::Update()
{

}
