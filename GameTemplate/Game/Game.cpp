#include "stdafx.h"
#include "BackGround.h"
#include "Game.h"
#include "Player.h"
#include"GameCamera.h"

bool Game::Start()
{
	NewGO<Player>(0, "player");
	NewGO<BackGround>(0, "background");
	NewGO<GameCamera>(0, "gamecamera");
	return true;
}

void Game::Update()
{

}
