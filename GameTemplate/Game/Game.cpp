#include "stdafx.h"
#include "Block.h"
#include "BackGround.h"
#include "ClearPoint.h"
#include "Enemy.h"
#include "FallingBlock.h"
#include "Player.h"
#include "MovingFloor.h"
#include "Scaffold.h"
#include "ScaffoldBlock.h"
#include "Signboard.h"
#include "StageClear.h"
#include "Needle.h"
#include "Game.h"
#include "GameOver.h"
#include "GameCamera.h"
#include "TransparentBlock.h"
#include "Title.h"
#include "Towel.h"

namespace
{
	Vector3 TRANSPARENTBLOCK_SCALE = Vector3(10.0f, 10.0f, 10.0f);
	Vector3 BACKGROUND_SCALE = Vector3(10.0f, 10.0f, 10.0f);
	Vector3	NEEDLE_SCALE = Vector3(10.0f, 10.0f, 10.0f);
	const int ENEMY_NUM = 4;
}

//背景
////背景の関数
//void Game::InitSky()
//{
//	DeleteGO(m_SkyCube);
//	SkyCube* m_SkyCube = NewGO<SkyCube>(0, "skycube");
//	m_SkyCube->SetType(enSkyCubeType_NightToon);
//	m_SkyCube->SetLuminance(1.0f);
//	m_SkyCube->SetScale(100000.0f);
//
//
//	// 環境光の計算のためのIBLテクスチャをセットする。
//	g_renderingEngine->SetAmbientByIBLTexture(m_SkyCube->GetTextureFilePath(), 1.0f);
//	// 環境日光の影響が分かりやすいように、ディレクションライトはオフに。
//	g_renderingEngine->SetDirectionLight(0, g_vec3Zero, g_vec3Zero);
//}


bool Game::Start()
{
	m_backGround =  NewGO<BackGround>(1, "background");
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
		{3200.0f,94.0f,0.0f},
		{600.0f,94.0f,0.0f},
		{4800.0f,94.0f,0.0f},
		{5400.0f,94.0f,0.0f}
	};

	for (int i = 0; i < ENEMY_NUM; i++) {
		m_enemyList[i] = NewGO<Enemy>(0, "enemy");
		m_enemyList[i]->m_position = enemyPosList[i];
		m_enemyList[i]->firstposition = enemyPosList[i];
	}

	m_mappuRender.Init("Assets/modelData/mappu.DDS", 350.0f, 40.0f);
	m_mappuRender.SetPosition(Vector3(400.0f, 400.0f, 0.0f));
	m_gennzaitiRender.Init("Assets/modelData/gennzaiti.DDS", 50.0f, 50.0f);
	m_gennzaitiRender.SetPosition(Vector3(260.0f, 430.0f, 0.0f));

	m_sutaminaMaxrender.Init("Assets/modelData/sutaminamax.DDS", 350.0f, 40.0f);
	m_sutaminaMaxrender.SetPosition(Vector3(-175.0f, 300.0f, 0.0f));
	m_sutaminaMaxrender.SetPivot(Vector2(0.0f, 0.5f));
	m_sutamina0render.Init("Assets/modelData/sutamina0.DDS", 350.0f, 40.0f);
	m_sutamina0render.SetPosition(Vector3(0.0f, 300.0f, 0.0f));
	

	TransparentBlock_NewGO();
	FallingBlock_NewGO();
	ScaffoldBlock_NewGO();
	Needle_NewGO();
	MovingFloor_NewGO();
//	Block_NewGO();
	Signboard_NewGO();
	Scaffold_NewGO();
	Item_NewGO();
	ClearPoint_NewGO();


	m_modelRender.Update();
//	PhysicsWorld::GetInstance()->EnableDrawDebugWireFrame();
	return true;
}


//透明ブロックのNewGO用関数
void Game::TransparentBlock_NewGO()
{
	m_transparentBlock = NewGO<TransparentBlock>(1, "transparentblock");
	m_transparentBlock->m_position = { 4700.0f, 300.0f, 0.0f };
	m_transparentBlock->m_firstposition = m_transparentBlock->m_position;

	m_transparentBlock1 = NewGO<TransparentBlock>(1, "transparentblock");
	m_transparentBlock1->m_position = { 4800.0f, 300.0f, 0.0f };
	m_transparentBlock1->m_firstposition = m_transparentBlock1->m_position;

	m_transparentBlock2 = NewGO<TransparentBlock>(1, "transparentblock");
	m_transparentBlock2->m_position = { 4900.0f, 300.0f, 0.0f };
	m_transparentBlock2->m_firstposition = m_transparentBlock2->m_position;

	m_transparentBlock3 = NewGO<TransparentBlock>(1, "transparentblock");
	m_transparentBlock3->m_position = { 5000.0f, 300.0f, 0.0f };
	m_transparentBlock3->m_firstposition = m_transparentBlock3->m_position;

	m_transparentBlock4 = NewGO<TransparentBlock>(1, "transparentblock");
	m_transparentBlock4->m_position = { 5100.0f, 300.0f, 0.0f };
	m_transparentBlock4->m_firstposition = m_transparentBlock4->m_position;

	m_transparentBlock5 = NewGO<TransparentBlock>(1, "transparentblock");
	m_transparentBlock5->m_position = { 5200.0f, 300.0f, 0.0f };
	m_transparentBlock5->m_firstposition = m_transparentBlock5->m_position;

	m_transparentBlock6 = NewGO<TransparentBlock>(1, "transparentblock");
	m_transparentBlock6->m_position = { 5300.0f, 300.0f, 0.0f };
	m_transparentBlock6->m_firstposition = m_transparentBlock6->m_position;

	m_transparentBlock7 = NewGO<TransparentBlock>(1, "transparentblock");
	m_transparentBlock7->m_position = { 5400.0f, 300.0f, 0.0f };
	m_transparentBlock7->m_firstposition = m_transparentBlock7->m_position;

	m_transparentBlock8 = NewGO<TransparentBlock>(1, "transparentblock");
	m_transparentBlock8->m_position = { 5500.0f, 300.0f, 0.0f };
	m_transparentBlock8->m_firstposition = m_transparentBlock8->m_position;

	m_transparentBlock9 = NewGO<TransparentBlock>(1, "transparentblock");
	m_transparentBlock9->m_position = { 5600.0f, 300.0f, 0.0f };
	m_transparentBlock9->m_firstposition = m_transparentBlock9->m_position;

	m_transparentBlock10 = NewGO<TransparentBlock>(1, "transparentblock");
	m_transparentBlock10->m_position = { 12600.0f, 230.0f, 0.0f };
	m_transparentBlock10->m_firstposition = m_transparentBlock10->m_position;

	m_transparentBlock11 = NewGO<TransparentBlock>(1, "transparentblock");
	m_transparentBlock11->m_position = { 14200.0f, 260.0f, 0.0f };
	m_transparentBlock11->m_firstposition = m_transparentBlock11->m_position;

	m_modelRender.SetPosition(m_position);
}

//落ちる床のNewGO用関数
void Game::FallingBlock_NewGO()
{
	m_fallingBlock = NewGO<FallingBlock>(0, "fallingblock");
	m_fallingBlock->m_position = { 9000.0f, 360.0f, 0.0f };
	m_fallingBlock->m_firstposition = m_fallingBlock->m_position;

	m_fallingBlock1 = NewGO<FallingBlock>(0, "fallingblock");
	m_fallingBlock1->m_position = { 9700.0f, 400.0f, 0.0f };
	m_fallingBlock1->m_firstposition = m_fallingBlock1->m_position;

	m_fallingBlock2 = NewGO<FallingBlock>(0, "fallingblock");
	m_fallingBlock2->m_position = { 10400.0f, 400.0f, 0.0f };
	m_fallingBlock2->m_firstposition = m_fallingBlock2->m_position;
	m_modelRender.SetPosition(m_position);
}

//T型足場ブロックのNewGO関数
void Game::ScaffoldBlock_NewGO()
{
	m_scaffoldBlock = NewGO<ScaffoldBlock>(0, "scaffoldblock");
	m_scaffoldBlock->m_position = { 8000.0f, 150.0f, 0.0f };
	m_scaffoldBlock->m_firstposition = m_scaffoldBlock->m_position;
	m_modelRender.SetPosition(m_position);
}

//針のNewGO用関数
void Game::Needle_NewGO()
{
	m_needle = NewGO<Needle>(0, "needle");
	m_needle->m_needlePosition = { -500.0f,0.0f,0.0f };
	m_needle->firstposition = m_needle->m_needlePosition;

	m_needle1 = NewGO<Needle>(0, "needle");
	m_needle1->m_needlePosition = { 17000.0f, 400.0f, 0.0f };
	m_needle1->firstposition = m_needle1->m_needlePosition;

	m_needle2 = NewGO<Needle>(0, "needle");
	m_needle2->m_needlePosition = { 16100.0f, 400.0f, 0.0f };
	m_needle2->firstposition = m_needle2->m_needlePosition;

	m_modelRender.SetPosition(m_position);
}

//動く床のNewGO用関数
void Game::MovingFloor_NewGO()
{
	/*m_movingFloor = NewGO<MovingFloor>(0, "movingfloor");
	m_movingFloor->SetPosition(Vector3{ 8500.0f, 0.0f, 0.0f });*/

	m_movingFloor1 = NewGO<MovingFloor>(0, "movingfloor");
	m_movingFloor1->SetPosition(Vector3{ 14200.0f, 300.0f, 200.0f });

	m_movingFloor2 = NewGO<MovingFloor>(0, "movingfloor");
	m_movingFloor2->SetPosition(Vector3{ 15200.0f, 300.0f, 200.0f });

	m_modelRender.SetPosition(m_position);
}

//ブロックのNewGO用関数
void Game::Block_NewGO()
{
	m_block = NewGO<Block>(0, "block");
	m_block->m_position = { 11000.0f, 800.0f, 0.0f };
	m_block->m_firstposition = m_block->m_position;

	m_modelRender.SetPosition(m_position);

}

//看板のNewGO用関数
void Game::Signboard_NewGO()
{
	m_signboard = NewGO<Signboard>(0, "signboard");
	m_signboard->m_position = { 100.0f, 80.0f, 100.0f };
	m_signboard->m_firstposition = m_signboard->m_position;
	m_modelRender.SetPosition(m_position);
}

//足場ブロックのNewGO用関数
void Game::Scaffold_NewGO()
{
    m_scaffold = NewGO<Scaffold>(0, "scaffold");
	m_scaffold->m_position = { -500.0f, 0.0f, 200.0f };
	m_scaffold->m_firstposition = m_scaffold->m_position;

	//x … 13300
	
	m_scaffold1 = NewGO<Scaffold>(0, "scaffold");
	m_scaffold1->m_position = { 13200.0f, 260.0f, 200.0f };
	m_scaffold1->m_firstposition = m_scaffold1->m_position;
	m_modelRender.SetPosition(m_position);

}

//アイテムのNewGO用関数
void Game::Item_NewGO()
{
	m_towel = NewGO<Towel>(0,"towel");
	m_towel->m_position = { 12600.0f, 300.0f, 0.0f };
	m_modelRender.SetPosition(m_position);
}

//クリアポイントのNewGO用関数
void Game::ClearPoint_NewGO()
{
	m_clearPoint = NewGO<ClearPoint>(0, "clearpoint");
	m_clearPoint->position = { 17500.0f, 700.0f, 0.0f };
	m_modelRender.SetPosition(m_position);

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

	

	if (m_timer <= 0.0f) {
		NewGO<GameOver>(0, "gameover");
		DeleteGO(this);
		DeleteGO(m_player);
		DeleteGO(m_backGround);;
		DeleteGO(m_transparentBlock);
		DeleteGO(m_transparentBlock1);
		DeleteGO(m_transparentBlock2);
		DeleteGO(m_transparentBlock3);
		DeleteGO(m_transparentBlock4);
		DeleteGO(m_transparentBlock5);
		DeleteGO(m_transparentBlock6);
		DeleteGO(m_transparentBlock7);
		DeleteGO(m_transparentBlock8);
		DeleteGO(m_transparentBlock9);
		DeleteGO(m_transparentBlock10);
		DeleteGO(m_transparentBlock11);
		DeleteGO(m_fallingBlock);
		DeleteGO(m_fallingBlock1);
		DeleteGO(m_fallingBlock2);
		DeleteGO(m_scaffoldBlock);
		DeleteGO(m_needle);
		DeleteGO(m_needle1);
		DeleteGO(m_movingFloor1);
		DeleteGO(m_movingFloor2);
		DeleteGO(m_block);
		DeleteGO(m_signboard);
		DeleteGO(m_scaffold);
		DeleteGO(m_scaffold1);
		DeleteGO(m_towel);
		for (int i = 0; i < ENEMY_NUM; i++) {
			DeleteGO(m_enemyList[i]);
		}
		m_player = nullptr;
		m_movingFloor = nullptr;
		m_fallingBlock = nullptr;
		m_gameCamera->SetTarget(nullptr);
	}

	if (m_player->NeedleCount == 1)
	{	
		NewGO<GameOver>(0, "gameover");
		DeleteGO(this);
		DeleteGO(m_player);
		DeleteGO(m_transparentBlock);
		DeleteGO(m_transparentBlock1);
		DeleteGO(m_transparentBlock2);
		DeleteGO(m_transparentBlock3);
		DeleteGO(m_transparentBlock4);
		DeleteGO(m_transparentBlock5);
		DeleteGO(m_transparentBlock6);
		DeleteGO(m_transparentBlock7);
		DeleteGO(m_transparentBlock8);
		DeleteGO(m_transparentBlock9);
		DeleteGO(m_transparentBlock10);
		DeleteGO(m_transparentBlock11);
		DeleteGO(m_fallingBlock);
		DeleteGO(m_fallingBlock1);
		DeleteGO(m_fallingBlock2);
		DeleteGO(m_scaffoldBlock);
		DeleteGO(m_needle);
		DeleteGO(m_needle1);
		DeleteGO(m_movingFloor1);
		DeleteGO(m_movingFloor2);
		DeleteGO(m_block);
		DeleteGO(m_signboard);
		DeleteGO(m_scaffold);
		DeleteGO(m_scaffold1);
		DeleteGO(m_towel);
		for (int i = 0; i < ENEMY_NUM; i++) {
			DeleteGO(m_enemyList[i]);
		}
		m_player = nullptr;
		m_movingFloor = nullptr;
		m_fallingBlock = nullptr;
		m_gameCamera->SetTarget(nullptr);
	}

	if (m_player->clearCount == 1)
	{
		NewGO<StageClear>(0);
		DeleteGO(this);
	}

	/*if (g_pad[0]->IsTrigger(enButtonX))
	{
		NewGO<Game>(0, "game");
		DeleteGO(this);
	}*/


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

	m_sutaminaMaxrender.Update();
	m_sutamina0render.Update();

	m_mappuRender.Update();
	m_gennzaitiRender.Update();
	m_gennzaitiRender.SetPosition(Vector3(260.0f + m_player->m_position.x / 60, 430.0f, 0.0f));
}

void Game::Render(RenderContext& rc)
{
	
	//m_backGroundRender.Draw(rc);
	m_modelRender.Draw(rc);
	//スタミナが３００以下のときにゲージを出す
	if (m_player->m_playernowsutamina<300) {
		m_sutamina0render.Draw(rc);
		m_sutaminaMaxrender.Draw(rc);
	}
	m_fontRender.Draw(rc);
	m_timerRender.Draw(rc);
	m_mappuRender.Draw(rc);
	m_gennzaitiRender.Draw(rc);
}
