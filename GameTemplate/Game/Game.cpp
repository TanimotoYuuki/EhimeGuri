#include "stdafx.h"
#include "FallingBlock.h"
#include "Player.h"
#include "MovingFloor.h"
#include "ScaffoldBlock.h"
#include "Needle.h"
#include "Game.h"
#include "GameOver.h"
#include "GameCamera.h"
#include "Enemy.h"
#include "TransparentBlock.h"

namespace
{
	Vector3 BACKGROUND_SCALE = Vector3(10.0f, 10.0f, 10.0f);
	Vector3	NEEDLE_SCALE = Vector3(10.0f, 10.0f, 10.0f);
	const int ENEMY_NUM = 1;
}

bool Game::Start()
{
	m_backGroundRender.Init("Assets/modelData/Stage/Assets/Stage1.tkm", 0, 0, enModelUpAxisZ, false, true);
	m_backGroundRender.SetScale(BACKGROUND_SCALE);
	m_backGroundRender.Update();
	//当たり判定を作成
	m_physicsStaticObject.CreateFromModel(m_backGroundRender.GetModel(), m_backGroundRender.GetModel().GetWorldMatrix());
	//ステージにレイ用の属性を与える。
	m_physicsStaticObject.GetbtCollisionObject()->setUserIndex(enCollisionAttr_Stage1);


	m_player     =  NewGO<Player>(1, "player");
	m_gameCamera =  NewGO<GameCamera>(2, "gamecamera");
	m_gameCamera->SetTarget(m_player);

	Vector3 enemyPosList[ENEMY_NUM] = {
		{3200.0f,94.0f,0.0f}
	};

	for (int i = 0; i < ENEMY_NUM; i++) {
		m_enemyList[i] = NewGO<Enemy>(0, "enemy");
		m_enemyList[i]->m_position = enemyPosList[i];
		m_enemyList[i]->firstposition = enemyPosList[i];
	}

	m_movingFloor=  NewGO<MovingFloor>(0, "movingfloor");
	m_movingFloor->SetPosition(Vector3{7500.0f, 0.0f, 0.0f});
	m_modelRender.SetPosition(m_position);

	
	m_sutaminaMaxrender.Init("Assets/modelData/sutaminamax.DDS", 350.0f, 40.0f);
	m_sutaminaMaxrender.SetPosition(Vector3(-175.0f, 300.0f, 0.0f));
	m_sutaminaMaxrender.SetPivot(Vector2(0.0f, 0.5f));
	m_sutamina0render.Init("Assets/modelData/sutamina0.DDS", 350.0f, 40.0f);
	m_sutamina0render.SetPosition(Vector3(0.0f, 300.0f, 0.0f));
	

	//m_needle = NewGO<Needle>(0, "needle");
	//m_needle->m_needlePosition = {-200.0f,0.0f,0.0f};
	//m_needle->firstposition = m_needle->m_needlePosition;
	m_modelRender.SetPosition(m_position);

	m_scaffoldBlock = NewGO<ScaffoldBlock>(0, "scaffoldblock");
	m_scaffoldBlock->m_position = { 8000.0f, 0.0f, 0.0f };
	m_scaffoldBlock->firstposition = m_scaffoldBlock->m_position;
	m_modelRender.SetPosition(m_position);
	
	m_fallingBlock = NewGO<FallingBlock>(0, "fallingblock");
	m_fallingBlock->f_position = { 1000.0f, 150.0f, 0.0f };
	m_fallingBlock->firstposition = m_fallingBlock->f_position;
	m_modelRender.SetPosition(m_position);
	
	m_transparentBlock = NewGO<TransparentBlock>(1, "transparentblock");

	m_modelRender.Update();
	PhysicsWorld::GetInstance()->EnableDrawDebugWireFrame();
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
	
	//テスト用
	//m_fontRender.SetText(L"カウントの上昇");
	//m_fontRender.SetPosition(Vector3(-160.0f, 500.0f, 0.0f));
	//m_fontRender.SetScale(1.2f);
	//////フォントの色を設定。
	//m_fontRender.SetColor(g_vec4Yellow);

	if (m_player == nullptr) {
		return;
	}

	if (m_player->NeedleCount == 1)
	{	
		NewGO<GameOver>(0);
		DeleteGO(m_gameOver);
		DeleteGO(m_player);
		DeleteGO(m_movingFloor);
		DeleteGO(m_fallingBlock);
		for (int i = 0; i < ENEMY_NUM; i++) {
			DeleteGO(m_enemyList[i]);
		}
		m_player = nullptr;
		m_movingFloor = nullptr;
		m_fallingBlock = nullptr;
		m_gameCamera->SetTarget(nullptr);
	}
	
	int MaxSuta = m_player->m_playermaxsutamina;
	int nowSuta = m_player->m_playernowsutamina;
	float nokori = (float)nowSuta / (float)MaxSuta;
	Vector3 heri = { 1.0f,1.0,1.0f };
	heri.x *= nokori;
	m_sutaminaMaxrender.SetScale(heri);

	wchar_t wcsbuf[256];
	swprintf_s(wcsbuf, 256, L"残り%.1f秒", float(m_timer));
	m_timerRender.SetText(wcsbuf);
	m_timerRender.SetPosition(Vector3(0.0f, 500.0f, 0.0f));
	m_timerRender.SetColor({ 1.0f,0.0f,0.0f,1.0f });
	m_timerRender.SetScale(1.0f);

	m_timer -= g_gameTime->GetFrameDeltaTime();

	if (m_timer <= 0.0f) {
		NewGO<GameOver>(0, "gameover");
		DeleteGO(this);
		DeleteGO(m_player);
		DeleteGO(m_movingFloor);
		DeleteGO(m_fallingBlock);
		DeleteGO(m_needle);
		for (int i = 0; i < ENEMY_NUM; i++) {
			DeleteGO(m_enemyList[i]);
		}
		m_player = nullptr;
		m_movingFloor = nullptr;
		m_fallingBlock = nullptr;
		m_gameCamera->SetTarget(nullptr);
	}
	m_sutaminaMaxrender.Update();
	m_sutamina0render.Update();
}

void Game::Render(RenderContext& rc)
{
	m_backGroundRender.Draw(rc);
	m_modelRender.Draw(rc);
	//スタミナが３００以下のときにゲージを出す
	if (m_player->m_playernowsutamina<300) {
		m_sutamina0render.Draw(rc);
		m_sutaminaMaxrender.Draw(rc);
	}
	m_fontRender.Draw(rc);
	m_timerRender.Draw(rc);
}
