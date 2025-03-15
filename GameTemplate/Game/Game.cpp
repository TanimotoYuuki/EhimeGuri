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

	SutaminaMaxrender.Init("Assets/modelData/sutaminamax.DDS", 350.0f, 40.0f);
	SutaminaMaxrender.SetPosition(Vector3(-175.0f, 300.0f, 0.0f));
	SutaminaMaxrender.SetPivot(Vector2(0.0f, 0.5f));
	Sutamina0render.Init("Assets/modelData/sutamina0.DDS", 350.0f, 40.0f);
	Sutamina0render.SetPosition(Vector3(0.0f, 300.0f, 0.0f));




	m_modelRender.Update();
	return true;
}

void Game::Update()
{
	////数値確認用。
	//wchar_t wcsbuf[256];
	//swprintf_s(wcsbuf, 256, L"残り時間%d秒", (int)(m_player->m_playernowsutamina));
	////表示するテキストを設定。
	//m_fontRender.SetText(wcsbuf);
	////フォントの位置を設定。
	//m_fontRender.SetPosition(Vector3(-160.0f, 500.0f, 0.0f));
	////フォントの大きさを設定。
	//m_fontRender.SetScale(1.2f);
	////フォントの色を設定。
	//m_fontRender.SetColor(g_vec4Yellow);
	


	int MaxSuta = m_player->m_playermaxsutamina;
	int nowSuta = m_player->m_playernowsutamina;
	float nokori = (float)nowSuta / (float)MaxSuta;
	Vector3 heri = { 1.0f,1.0,1.0f };
	heri.x *= nokori;
	SutaminaMaxrender.SetScale(heri);

	SutaminaMaxrender.Update();
	Sutamina0render.Update();
}

void Game::Render(RenderContext& rc)
{
	m_backGroundRender.Draw(rc);
	m_modelRender.Draw(rc);
	
	Sutamina0render.Draw(rc);
	SutaminaMaxrender.Draw(rc);

	m_fontRender.Draw(rc);
}
