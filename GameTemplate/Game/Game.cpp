#include "stdafx.h"
#include "BackGround.h"
#include "Player.h"
//#include "MovingFloor.h"
#include "Game.h"
#include "GameCamera.h"

//namespace
//{
//	Vector3 BACKGROUND_SCALE = Vector3(0.7f, 1.0f, 0.7f);
//}

bool Game::Start()
{

	NewGO<Player>(0, "player");
	NewGO<BackGround>(0, "background");
	NewGO<GameCamera>(0, "gamecamera");

//↓コメントアウトを解除する場合Playerを1にする
// 	その際、カメラを2, UIのCPPは2
//	NewGO<MovingFloor>(0, "movingfloor");
	return true;
}

void Game::Update()
{

}

void Game::Render(RenderContext& rc)
{
//	m_backGroundRender.Draw(rc);
}
