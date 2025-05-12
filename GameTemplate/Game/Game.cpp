#include "stdafx.h"
#include "Block.h"
#include "BackGround.h"
#include "ClearPoint.h"
#include "Enemy.h"
#include "FallingBlock.h"
#include "Game.h"
#include "GameOver.h"
#include "GameCamera.h"
#include "HS_FallingBlock.h"
#include "Needle.h"
#include "MovingFloor.h"
#include "Player.h"
#include "Scaffold.h"
#include "ScaffoldBlock.h"
#include "StageClear.h"
#include "S_MovingFloor.h"
#include "TransparentBlock.h"
#include "Title.h"
#include "Towel.h"
#include "Fade.h"
#include"ItemEnemy.h"
#include"Tobeyaki.h"
#include"sinju.h"
#include"Mikan.h"
#include"Jako.h"
#include"Taruto.h"

namespace
{
	Vector3 TRANSPARENTBLOCK_SCALE = Vector3(10.0f, 10.0f, 10.0f);
	Vector3 BACKGROUND_SCALE = Vector3(10.0f, 10.0f, 10.0f);
	Vector3	NEEDLE_SCALE = Vector3(10.0f, 10.0f, 10.0f);
	const int ENEMY_NUM = 4;
}

Game::~Game()
{
	DeleteGO(m_backGround);
	DeleteGO(m_player);
	DeleteGO(m_gameCamera);
	for (int i = 0; i < ENEMY_NUM; i++) {
		DeleteGO(m_enemyList[i]);
	}
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
	DeleteGO(m_block1);
	DeleteGO(m_block2);
	DeleteGO(m_block3);
	DeleteGO(m_block4);
	DeleteGO(m_scaffold);
	DeleteGO(m_scaffold1);
	DeleteGO(m_towel);
	DeleteGO(m_clearPoint);
	DeleteGO(m_s_MovingFloor);
	DeleteGO(m_s_MovingFloor1);
	DeleteGO(m_s_MovingFloor2);
	DeleteGO(m_s_MovingFloor3);
	DeleteGO(m_HS_FallingBlock);
	DeleteGO(m_itemenemy);
	DeleteGO(m_tobeyaki);
	DeleteGO(m_sinju);
	DeleteGO(m_mikan);
	DeleteGO(m_jako);
	DeleteGO(m_taruto);
}

bool Game::Start()
{
	m_backGround =  NewGO<BackGround>(1, "background");
	m_backGroundRender.Init("Assets/modelData/Stage/Assets/Stage1.tkm", 0, 0, enModelUpAxisZ, false, true);
	m_backGroundRender.SetScale(BACKGROUND_SCALE);
	m_backGroundRender.Update();

	m_physicsStaticObject.CreateFromModel(m_backGroundRender.GetModel(), m_backGroundRender.GetModel().GetWorldMatrix());
	m_physicsStaticObject.GetbtCollisionObject()->setUserIndex(enCollisionAttr_Stage1);

	m_player     =  NewGO<Player>(1, "player");
	m_gameCamera =  NewGO<GameCamera>(2, "gamecamera");
	m_gameCamera->SetTarget(m_player);

	Vector3 enemyPosList[ENEMY_NUM] = {
		{2800.0f,94.0f,0.0f},
		{400.0f,94.0f,0.0f},
		{4800.0f,94.0f,0.0f},
		{12300.0f,200.0f,0.0f}
	};

	for (int i = 0; i < ENEMY_NUM; i++) {
		m_enemyList[i] = NewGO<Enemy>(0, "enemy");
		m_enemyList[i]->m_position = enemyPosList[i];
		m_enemyList[i]->firstposition = enemyPosList[i];
	}

	m_itemenemy = NewGO<ItemEnemy>(1, "itemenemy");
	m_itemenemy->m_position = { 9050.0f,600.0f,0.0f };
	m_itemenemy->firstposition = m_itemenemy->m_position;

	/*m_tobeyaki = NewGO<Tobeyaki>(1, "tobeyaki");
	m_tobeyaki->m_position = { 800.0f,200.0f,0.0f };*/


	m_mappuRender.Init("Assets/modelData/mappu.DDS", 350.0f, 40.0f);
	m_mappuRender.SetPosition(Vector3(400.0f, 400.0f, 0.0f));
	m_gennzaitiRender.Init("Assets/modelData/gennzaiti.DDS", 50.0f, 50.0f);
	m_gennzaitiRender.SetPosition(Vector3(260.0f, 430.0f, 0.0f));

	m_sutaminaMaxrender.Init("Assets/modelData/sutaminamax.DDS", 350.0f, 40.0f);
	m_sutaminaMaxrender.SetPosition(Vector3(-175.0f, 300.0f, 0.0f));
	m_sutaminaMaxrender.SetPivot(Vector2(0.0f, 0.5f));
	m_sutamina0render.Init("Assets/modelData/sutamina0.DDS", 350.0f, 40.0f);
	m_sutamina0render.SetPosition(Vector3(0.0f, 300.0f, 0.0f));

	m_taorukuroRender.Init("Assets/modelData/taorukuro.DDS", 100.0f, 100.0f);
	m_taorukuroRender.SetPosition(Vector3(-750.0f, 400.0f, 0.0f));
	m_taorutoriRender.Init("Assets/modelData/taorutori.DDS", 100.0f, 100.0f);
	m_taorutoriRender.SetPosition(Vector3(-750.0f, 400.0f, 0.0f));

	//ステージ背景の初期化
	m_stageBackGround.Init("Assets/Sprite/background/1stage.dds", 12800, 900, true);
	m_stageBackGround.Update();

	for (int i = 0; i < enEhimePlace_Num; i++)
	{
		//愛媛県の場所のスプライトの情報を取得してから初期化する
		GetEhimePlaceSpriteData(i);
		m_ehimePlace[i].Init(m_ehimePlaceFilePath, 1024, 128);
		m_ehimePlace[i].SetPosition(m_ehimePlacePosition);
		m_ehimePlace[i].SetScale(Vector3(0.35f, 0.35f, 0.35f));
		m_ehimePlace[i].Update();

		//愛媛県の名所のスプライトの情報を取得してから初期化する
		GetEhimeFamousPlaceSpriteData(i);
		m_ehimeFamousPlace[i].Init(m_ehimeFamousPlaceFilePath, 1024, 128);
		m_ehimeFamousPlace[i].SetPosition(m_ehimeFamousPlacePosition);
		m_ehimeFamousPlace[i].SetScale(Vector3(0.35f, 0.35f, 0.35f));
		m_ehimeFamousPlace[i].Update();
	}

	TransparentBlock_NewGO();
	FallingBlock_NewGO();
	ScaffoldBlock_NewGO();
	Needle_NewGO();
	MovingFloor_NewGO();
	Block_NewGO();
	//Signboard_NewGO();
	Scaffold_NewGO();
	Item_NewGO();
	ClearPoint_NewGO();
	HS_fallingBlock_NewGO();
	S_MovingFloor_NewGO();
	Fade_NewGO();

	//現在位置の設定
	m_stageBackGround.SetCurrentPosition(m_player->m_position);
	//ゴール位置の設定
	m_stageBackGround.SetGoalPosition(m_clearPoint->position);
	m_modelRender.Update();
//	PhysicsWorld::GetInstance()->EnableDrawDebugWireFrame();
	return true;
}

// 更新作業。
void Game::Update()
{
	//ステージクリアとゲームオーバーの時は処理しない
	if (m_player->m_stageClearFlag == true ||
		m_player->m_gameOverFlag == true
		)
	{
		return;
	}

	if (m_timer <= 0.0f) {
		if (m_gameOverFlag != true)
		{
			NewGO<GameOver>(0, "gameover");
			DeleteGO(m_fade);
			m_gameOverFlag = true;
		}
		return;
	}

	//現在の愛媛県の場所の設定
	SetNowEhimePlace(m_player->m_position);

	//現在位置の更新
	m_stageBackGround.SetCurrentPosition(m_player->m_position);

	//ステージ背景の更新
	m_stageBackGround.Update();

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

	m_taorukuroRender.Update();
	m_taorutoriRender.Update();

}

// 透明ブロックのNewGO。
void Game::TransparentBlock_NewGO()
{
	m_transparentBlock3 = NewGO<TransparentBlock>(1, "transparentblock");
	m_transparentBlock3->m_position = { 4700.0f, 325.0f, 0.0f };
	m_transparentBlock3->m_firstposition = m_transparentBlock3->m_position;

	m_transparentBlock4 = NewGO<TransparentBlock>(1, "transparentblock");
	m_transparentBlock4->m_position = { 4800.0f, 325.0f, 0.0f };
	m_transparentBlock4->m_firstposition = m_transparentBlock4->m_position;

	m_transparentBlock5 = NewGO<TransparentBlock>(1, "transparentblock");
	m_transparentBlock5->m_position = { 4900.0f, 325.0f, 0.0f };
	m_transparentBlock5->m_firstposition = m_transparentBlock5->m_position;

	m_transparentBlock6 = NewGO<TransparentBlock>(1, "transparentblock");
	m_transparentBlock6->m_position = { 5000.0f, 325.0f, 0.0f };
	m_transparentBlock6->m_firstposition = m_transparentBlock6->m_position;

	m_transparentBlock7 = NewGO<TransparentBlock>(1, "transparentblock");
	m_transparentBlock7->m_position = { 5100.0f, 325.0f, 0.0f };
	m_transparentBlock7->m_firstposition = m_transparentBlock7->m_position;

	m_transparentBlock8 = NewGO<TransparentBlock>(1, "transparentblock");
	m_transparentBlock8->m_position = { 5200.0f, 325.0f, 0.0f };
	m_transparentBlock8->m_firstposition = m_transparentBlock8->m_position;

	m_transparentBlock9 = NewGO<TransparentBlock>(1, "transparentblock");
	m_transparentBlock9->m_position = { 5300.0f, 325.0f, 0.0f };
	m_transparentBlock9->m_firstposition = m_transparentBlock9->m_position;

	/*m_transparentBlock10 = NewGO<TransparentBlock>(1, "transparentblock");
	m_transparentBlock10->m_position = { 10300.0f, 200.0f, 0.0f };
	m_transparentBlock10->m_firstposition = m_transparentBlock10->m_position;*/

	m_modelRender.SetPosition(m_position);
}

// 落ちるブロックのNewGO。
void Game::FallingBlock_NewGO()
{
	m_fallingBlock = NewGO<FallingBlock>(0, "fallingblock");
	m_fallingBlock->m_position = { 7400.0f, 420.0f, 20.0f };
	m_fallingBlock->m_firstposition = m_fallingBlock->m_position;

	m_fallingBlock1 = NewGO<FallingBlock>(0, "fallingblock");
	m_fallingBlock1->m_position = { 8000.0f, 470.0f, 20.0f };
	m_fallingBlock1->m_firstposition = m_fallingBlock1->m_position;

	m_fallingBlock2 = NewGO<FallingBlock>(0, "fallingblock");
	m_fallingBlock2->m_position = { 8600.0f, 515.0f, 20.0f };
	m_fallingBlock2->m_firstposition = m_fallingBlock2->m_position;

	m_modelRender.SetPosition(m_position);
}

// 足場ブロックのNewGO。
void Game::ScaffoldBlock_NewGO()
{
	m_scaffoldBlock = NewGO<ScaffoldBlock>(0, "scaffoldblock");
	m_scaffoldBlock->m_position = { 6650.0f, 125.0f, 0.0f };
	m_scaffoldBlock->m_firstposition = m_scaffoldBlock->m_position;
	m_modelRender.SetPosition(m_position);
}

// 針のNewGO。
void Game::Needle_NewGO()
{
	m_needle1 = NewGO<Needle>(0, "needle");
	m_needle1->m_needlePosition = { 15800.0f, 400.0f, 0.0f };
	m_needle1->firstposition = m_needle1->m_needlePosition;

	m_modelRender.SetPosition(m_position);
}

// 動く床のNewGO。
void Game::MovingFloor_NewGO()
{
	
	m_movingFloor1 = NewGO<MovingFloor>(0, "movingfloor");
	m_movingFloor1->SetPosition(Vector3{ 11000.0f, 180.0f, 200.0f });

	m_movingFloor2 = NewGO<MovingFloor>(0, "movingfloor");
	m_movingFloor2->SetPosition(Vector3{ 12000.0f, 200.0f, 200.0f });

	m_modelRender.SetPosition(m_position);
}

// ブロックのNewGO。
void Game::Block_NewGO()
{
	/*m_block = NewGO<Block>(0, "block");
	m_block->m_position = { 11000.0f, 900.0f, 0.0f };
	m_block->m_firstposition = m_block->m_position;*/


	m_block = NewGO<Block>(0, "block");
	m_block->m_position = { 500.0f, 325.0f, 0.0f };
	m_block->m_firstposition = m_block->m_position;

	m_block1 = NewGO<Block>(0, "block");
	m_block1->m_position = { 12300.0f, 400.0f, 0.0f };
	m_block1->m_firstposition = m_block->m_position;

	m_block2 = NewGO<Block>(0, "block");
	m_block2->m_position = { 14000.0f, 600.0f, 0.0f };
	m_block2->m_firstposition = m_block->m_position;

	m_block3 = NewGO<Block>(0, "block");
	m_block3->m_position = { 15000.0f, 600.0f, 0.0f };
	m_block3->m_firstposition = m_block->m_position;

	m_block4 = NewGO<Block>(0, "block");
	m_block4->m_position = { 2800.0f, 325.0f, 0.0f };
	m_block4->m_firstposition = m_block->m_position;
	m_modelRender.SetPosition(m_position);

}

// 足場ブロック。
void Game::Scaffold_NewGO()
{
	m_scaffold1 = NewGO<Scaffold>(0, "scaffold");
	m_scaffold1->m_position = { 12950.0f, 200.0f, 200.0f };
	m_scaffold1->m_firstposition = m_scaffold1->m_position;
	m_modelRender.SetPosition(m_position);
}

// アイテムのNewGO。
void Game::Item_NewGO()
{
  /* m_towel = NewGO<Towel>(0,"towel");
   m_towel->m_position = { 10500.0f, 250.0f, 0.0f };     //第二ステージ用
   m_modelRender.SetPosition(m_position);*/

   m_sinju = NewGO<sinju>(0, "sinju");
   m_sinju->m_position = { 14470.0f,600.0f,0.0f };
   m_modelRender.SetPosition(m_position);

   /*m_tobeyaki = NewGO<Tobeyaki>(0, "tobeyaki");
   m_tobeyaki->m_position = { 700.0f,200.0f,0.0f };　　　//第二ステージ用
   m_modelRender.SetPosition(m_position);*/

   m_jako = NewGO<Jako>(0, "jako");
   m_jako->m_position = { 6000.0f,500.0f,0.0f };
   m_modelRender.SetPosition(m_position);

   /*m_taruto = NewGO<Taruto>(0 , "taruto");
   m_taruto->m_position = { 500.0f,200.0f,0.0f };     //第二ステージ用
   m_modelRender.SetPosition(m_position);*/

}

// クリアポイントのNewGO。
void Game::ClearPoint_NewGO()
{
	m_clearPoint = NewGO<ClearPoint>(0, "clearpoint");
	m_clearPoint->position = { 17500.0f, 700.0f, 0.0f };
	m_modelRender.SetPosition(m_position);
}

// 落下速度の遅い床。
void Game::S_MovingFloor_NewGO()
{
	m_s_MovingFloor = NewGO<S_MovingFloor>(0, "s_movingfloor");
	m_s_MovingFloor->m_position = { 13575.0f, 300.0f, 10.0f };
	m_s_MovingFloor->m_firstPosition = m_s_MovingFloor->m_position;

	m_s_MovingFloor1 = NewGO<S_MovingFloor>(0, "s_movingfloor");
	m_s_MovingFloor1->m_position = { 14175.0f, 300.0f, 10.0f };

	m_s_MovingFloor2 = NewGO<S_MovingFloor>(0, "s_movingfloor");
	m_s_MovingFloor2->m_position = { 14775.0f, 300.0f, 10.0f };

	m_s_MovingFloor3 = NewGO<S_MovingFloor>(0, "s_movingfloor");
	m_s_MovingFloor3->m_position = { 15375.0f, 300.0f, 10.0f };

	m_modelRender.SetPosition(m_position);
}

// 落下速度の速い床。
void Game::HS_fallingBlock_NewGO()
{
	m_HS_FallingBlock = NewGO<HS_FallingBlock>(0, "hs_fallingblock");
	m_HS_FallingBlock->m_position = { 17500.0f,1000.0f, 200.0f };
	m_HS_FallingBlock->m_firstposition = m_HS_FallingBlock->m_position;
	m_modelRender.SetPosition(m_position);
}

// フェード。
void Game::Fade_NewGO()
{
	NewGO<Fade>(0, "fade");
	m_fade = FindGO<Fade>("fade");
	//フェードをフェードインに切り替える
	m_fade->FadeTransition(enFadeState_FadeIn);
}

// 描画処理。
void Game::Render(RenderContext& rc)
{
	m_stageBackGround.Draw(rc);
	m_modelRender.Draw(rc);

	//ステージクリアとゲームオーバーではないときは描画する
	if (m_player->m_stageClearFlag != true && 
		m_player->m_gameOverFlag != true
		)
	{
		//愛媛県の場所
		m_ehimePlace[m_nowEhimePlace].Draw(rc);
		//愛媛県の名所
		m_ehimeFamousPlace[m_nowEhimePlace].Draw(rc);
		if (m_player->m_playernowsutamina < 300) {
			m_sutamina0render.Draw(rc);
			m_sutaminaMaxrender.Draw(rc);
		}
		m_fontRender.Draw(rc);
		m_timerRender.Draw(rc);
		m_mappuRender.Draw(rc);
		m_gennzaitiRender.Draw(rc);
	}
}

//現在の愛媛県の場所の設定
void Game::SetNowEhimePlace(const Vector3& pos)
{
	//ステージごとの特定の位置まで行ったら現在の場所を切り替える
	if (pos.x >= 15060.0f)
	{
		//鬼北町
		m_nowEhimePlace = enEhimePlace_Onihoku;
	}
	else if (pos.x >= 10945.0f)
	{
		//宇和島市
		m_nowEhimePlace = enEhimePlace_Uwajima;
	}
	else if (pos.x >= 6940.0f)
	{
		//八幡浜市
		m_nowEhimePlace = enEhimePlace_Yawatahama;
	}
	else if (pos.x >= 2730.0f)
	{
		//大洲市
		m_nowEhimePlace = enEhimePlace_Ooze;
	}
	else
	{
		//伊予市
		m_nowEhimePlace = enEhimePlace_Iyo;
	}
}
