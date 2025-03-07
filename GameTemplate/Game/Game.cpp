#include "stdafx.h"
#include "Game.h"
#include "Player.h"

bool Game::Start()
{
	NewGO<Player>(0, "player");
	return true;
}

void Game::Update()
{

}
