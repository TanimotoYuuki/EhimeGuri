#include "stdafx.h"
#include "Player.h"
#include "MovingFloor.h"
#include "Game.h"
#include "GameCamera.h"

namespace
{
	Vector3 BACKGROUND_SCALE = Vector3(10.0f, 10.0f, 10.0f);
}


bool Game::Start()
{
	
	m_physicsStaticObject.CreateFromModel(m_backGroundRender.GetModel(), m_backGroundRender.GetModel().GetWorldMatrix());


	m_player     =  NewGO<Player>(1, "player");
	m_gameCamera =  NewGO<GameCamera>(2, "gamecamera");
	m_movingFloor=  NewGO<MovingFloor>(0, "movingfloor");
	m_movingFloor->SetPosition(Vector3(0.0f, 10.0f, 0.0f));


	m_modelRender.Update();
	return true;
}

void Game::Update()
{
	m_backGroundRender.Update();
}

void Game::Render(RenderContext& rc)
{
	m_backGroundRender.Draw(rc);
	m_modelRender.Draw(rc);
}
