#include "stdafx.h"
#include "BackGround.h"
#include "Player.h"
#include "MovingFloor.h"
#include "Game.h"
#include "GameCamera.h"

namespace
{
	Vector3 BACKGROUND_SCALE = Vector3(0.7f, 1.0f, 0.7f);
}

bool Game::Start()
{
	m_player     =  NewGO<Player>(1, "player");
	m_backGround =  NewGO<BackGround>(0, "background");
	m_gameCamera =  NewGO<GameCamera>(2, "gamecamera");

	m_movingFloor=  NewGO<MovingFloor>(0, "movingfloor");
	m_movingFloor->m_position = {0.0f, 0.0f, 100.0f};
	m_modelRender.SetPosition(m_position);

	m_modelRender.Update();
	return true;
}

void Game::Update()
{

}

void Game::Render(RenderContext& rc)
{
	m_backGroundRender.Draw(rc);
	m_modelRender.Draw(rc);
}
