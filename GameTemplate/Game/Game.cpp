#include"stdafx.h"
#include"Block.h"
#include"Stage1.h"
#include"ClearPoint.h"
#include"Config.h"
#include"Enemy.h"
#include"FallingBlock.h"
#include"Game.h"
#include"GameOver.h"
#include"GameCamera.h"
#include"GameTimer.h"
#include"movingNeedle.h"
#include"MovingFloor.h"
#include"Player.h"
#include"Scaffold.h"
#include"StageClear.h"
#include"S_MovingFloor.h"
#include"TransparentBlock.h"
#include"Title.h"
#include"Towel.h"
#include"Tower.h"
#include"Fade.h"
#include"ItemEnemy.h"
#include"Tobeyaki.h"
#include"sinju.h"
#include"Mikan.h"
#include"Jako.h"
#include"Taruto.h"
#include"Checpoint.h"
#include"RotationFloor.h"

namespace
{
	const Vector3 STAGE1_ENEMY_POSITION1(2800.0f, 94.0f, 0.0f);
	const Vector3 STAGE1_ENEMY_POSITION2(400.0f, 94.0f, 0.0f);
	const Vector3 STAGE1_ENEMY_POSITION3(4800.0f, 94.0f, 0.0f);
	const Vector3 STAGE1_ENEMY_PODITION4(12900.0f, 225.0f, 0.0f);
	const Vector3 STAGE2_ENEMY_POSITION1(800.0f, 200.0f, 0.0f);
	const Vector3 STAGE2_ENEMY_POSITION2(1400.0f, 200.0f, 0.0f);
	const Vector3 STAGE2_ENEMY_POSITION3(4250.0f, 500.0f, 0.0f);
	const Vector3 STAGE2_ENEMY_POSITION4(4600.0f, 300.0f, 0.0f);
	const Vector3 STAGE2_ENEMY_POSITION5(7100.0f, 200.0f, 0.0f);
	const Vector3 STAGE2_ENEMY_POSITION6(8000.0f, 500.0f, 0.0f);
	const Vector3 BACKGROUND_FIRSTPOSITION(0.0f, 0.0f, 0.0f);

	const float TIMER = 180.0f;

	const int STAGE1_ENEMY_NUM = 4;
	const int STAGE2_ENEMY_NUM = 6;
}

Game::~Game()
{
	DeleteGO(m_player);
	DeleteGO(m_gameCamera);
	const auto& enemys = FindGOs<Enemy>("enemy");
	for (auto enemy : enemys)
	{
		DeleteGO(enemy);
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
	DeleteGO(m_Stage1Goal);
	DeleteGO(m_s_MovingFloor);
	DeleteGO(m_s_MovingFloor1);
	DeleteGO(m_s_MovingFloor2);
	DeleteGO(m_s_MovingFloor3);
	DeleteGO(m_itemenemy);
	DeleteGO(m_tobeyaki);
	DeleteGO(m_sinju);
	DeleteGO(m_jako);
	DeleteGO(m_taruto);
	//ドロップアイテムをDeleteGOする場合
	//ドロップアイテムのクラスをここでFindGOしてからDeleteGOしてください。
	m_mikan = FindGO<Mikan>("mikan");
	DeleteGO(m_mikan);
	DeleteGO(m_checpoint);

}

// 初期化処理。
bool Game::Start()
{
	/// <summary>
	/// ゲームタイマーのNewGO関数。
	/// </summary>
	GameTimer_NewGO();

	/// <summary>
	/// フェード関数。
	/// </summary>
	Fade_NewGO();

	m_player     =  NewGO<Player>(1, "player");
	m_gameCamera =  NewGO<GameCamera>(2, "gamecamera");
	m_gameCamera->SetTarget(m_player);

	Vector3 enemyPosList[STAGE1_ENEMY_NUM] = {
		{STAGE1_ENEMY_POSITION1},
		{STAGE1_ENEMY_POSITION2},
		{STAGE1_ENEMY_POSITION3},
		{STAGE1_ENEMY_PODITION4}
	};

	for (int i = 0; i < STAGE1_ENEMY_NUM; i++) {
		m_enemyList[i] = NewGO<Enemy>(0, "enemy");
		m_enemyList[i]->m_position = enemyPosList[i];
		m_enemyList[i]->firstposition = enemyPosList[i];
	}

	m_itemenemy = NewGO<ItemEnemy>(1, "itemenemy");
	m_itemenemy->m_position = { 9050.0f,600.0f,0.0f };
	m_itemenemy->firstposition = m_itemenemy->m_position;

	/*m_tobeyaki = NewGO<Tobeyaki>(1, "tobeyaki");
	m_tobeyaki->m_position = { 800.0f,200.0f,0.0f };*/

	m_checpoint = NewGO<Checpoint>(1, "checpoint");
	m_checpoint->position = { 10300.0f,100.0f,0.0f };
	m_modelRender.SetPosition(m_position);


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

	m_jakorender.Init("Assets/modelData/jako.DDS", 100.0f, 100.0f);
	m_jakorender.SetPosition(Vector3(-750.0f, 400.0f, 0.0f));
	m_jakogetrender.Init("Assets/modelData/jakoget.DDS", 100.0f, 100.0f);
	m_jakogetrender.SetPosition(Vector3(-750.0f, 400.0f, 0.0f));

	m_mikanRender.Init("Assets/modelData/mikan.DDS", 100.0f, 100.0f);
	m_mikanRender.SetPosition(Vector3(-650.0f, 400.0f, 0.0f));
	m_mikangetRender.Init("Assets/modelData/mikanget.DDS", 100.0f, 100.0f);
	m_mikangetRender.SetPosition(Vector3(-650.0f, 400.0f, 0.0f));

	m_sinjuRender.Init("Assets/modelData/sinju.DDS", 100.0f, 100.0f);
	m_sinjuRender.SetPosition(Vector3(-550.0f, 400.0f, 0.0f));
	m_sinjugetRender.Init("Assets/modelData/sinjuget.DDS", 100.0f, 100.0f);
	m_sinjugetRender.SetPosition(Vector3(-550.0f, 400.0f, 0.0f));

	m_tarutoRender.Init("Assets/modelData/taruto.DDS", 100.0f, 100.0f);
	m_tarutoRender.SetPosition(Vector3(-550.0f, 400.0f, 0.0f));
	m_tarutogetRender.Init("Assets/modelData/tarutoget.DDS", 100.0f, 100.0f);
	m_tarutogetRender.SetPosition(Vector3(-550.0f, 400.0f, 0.0f));

	m_tobeyakiRender.Init("Assets/modelData/tobeyaki.DDS", 100.0f, 100.0f);
	m_tobeyakiRender.SetPosition(Vector3(-650.0f, 400.0f, 0.0f));
	m_tobeyakigetRneder.Init("Assets/modelData/tobeyakiget.DDS", 100.0f, 100.0f);
	m_tobeyakigetRneder.SetPosition(Vector3(-650.0f, 400.0f, 0.0f));
	/// <summary>
	/// 3DオブジェクトのNewGO関数。
	/// </summary>
	TransparentBlock_NewGO();
	FallingBlock_NewGO();
	MovingFloor_NewGO();
	Block_NewGO();
	Scaffold_NewGO();
	Item_NewGO();
	Stage1Goal_NewGO();
	S_MovingFloor_NewGO();

	//ステージ背景・愛媛県の場所・愛媛県の名所の初期化。
	for (int i = 0; i < enEhimePlace_Num; i++)
	{
		//ステージ背景。
		//0 ステージ背景の情報を取得。
		GetStageBackGroundData(i);
		//0.1 ステージ背景の初期化。
		m_stageBackGround[i].Init(m_stageBackGroundFilePath, 2200, 900, true);
		//0.2 ステージ背景をぼかす用のテクセルサイズの設定
		m_stageBackGround[i].SetTexelSize(1.5f);
		//0.3 ステージ背景の更新
		m_stageBackGround[i].Update();

		//遷移用のステージ背景
		//1 遷移用のステージ背景の初期化
		m_stageBackGroundTransition[i].Init(m_stageBackGroundFilePath, 2200, 900, true);
		//1.1 遷移用のステージ背景の乗算カラーの設定
		m_stageBackGroundTransition[i].SetMulColor(Vector4(1.0f, 1.0f, 1.0f, m_stageBackGroundTransitionAlpha));
		//1.2 遷移用のステージ背景をぼかす用のテクセルサイズの設定
		m_stageBackGroundTransition[i].SetTexelSize(1.5f);
		//1.3 遷移用のステージ背景の更新
		m_stageBackGroundTransition[i].Update();
		
		//愛媛県の場所のスプライト。
		//0 愛媛県の場所のスプライトの情報を取得。
		GetEhimePlaceSpriteData(i);
		//0.1 愛媛県の場所のスプライトの初期化。
		m_ehimePlace[i].Init(m_ehimePlaceFilePath, 1024, 128);
		//0.2 愛媛県の場所のスプライトの位置を設定。
		m_ehimePlace[i].SetPosition(m_ehimePlacePosition);
		//0.3 愛媛県の場所のスプライトの大きさを設定。
		m_ehimePlace[i].SetScale(Vector3(0.35f, 0.35f, 0.35f));
		//0.4 愛媛県の場所のスプライトの更新。
		m_ehimePlace[i].Update();

		//愛媛県の名所のスプライト。
		//1 愛媛県の名所のスプライトの情報を取得。
		GetEhimeFamousPlaceSpriteData(i);
		//1.1 愛媛県の名所のスプライトの初期化。
		m_ehimeFamousPlace[i].Init(m_ehimeFamousPlaceFilePath, 1024, 128);
		//1.2 愛媛県の名所のスプライトの位置を設定。
		m_ehimeFamousPlace[i].SetPosition(m_ehimeFamousPlacePosition);
		//1.3 愛媛県の名所のスプライトの大きさを設定。
		m_ehimeFamousPlace[i].SetScale(Vector3(0.35f, 0.35f, 0.35f));
		//1.4 愛媛県の名所のスプライトの更新。
		m_ehimeFamousPlace[i].Update();
	}

	//ステージ背景用の現在位置の更新。
	UpdateStageBackGroundCurrentPosition();

	//現在位置の設定。
	m_stageBackGround[m_nowEhimePlace].SetCurrentPosition(m_stageBackGroundCurrentPosition);
	m_stageBackGroundTransition[m_previousEhimePlace].SetCurrentPosition(m_stageBackGroundCurrentPositionMemory[m_previousEhimePlace]);

	//ステージ背景用のゴール位置の更新。
	UpdateStageBackGroundGolePosition();

	//ゴール位置の設定。
	m_stageBackGround[m_nowEhimePlace].SetGoalPosition(m_stageBackGroundGolePosition);
	m_stageBackGroundTransition[m_previousEhimePlace].SetGoalPosition(m_stageBackGroundGolePositionMemory[m_previousEhimePlace]);

	// 更新作業。
	m_modelRender.Update();

//	PhysicsWorld::GetInstance()->EnableDrawDebugWireFrame();
	return true;
}

// 更新作業。
void Game::Update()
{
////// 第2ステージ用 /////////////////////////////////////////////
	// チェックポイント。
	// チェックポイント用のインスタンスがnullptrだったらNewGOする。	  
	if (m_checpoint == nullptr)
	{
		m_checpoint = NewGO<Checpoint>(1, "checpoint");
		m_checpoint->position = { 9350.0f,360.0f,0.0f };
		m_modelRender.SetPosition(m_position);
	}

	//アイテムエネミー用のインスタンスがnullptrだったらNewGOする。
	if (m_itemenemy == nullptr)
	{
		m_itemenemy = NewGO<ItemEnemy>(1, "itemenemy");
		m_itemenemy->m_position = { 7700.0f, 400.0f, 0.0f };
		m_itemenemy->firstposition = m_itemenemy->m_position;
		m_player->m_itemEnemy = nullptr;
	}

	//ステージ2用のエネミーをNewGOするかどうか判定するフラグがtrueになっていたらNewGOする。
	if (m_stage2EnemyNewGOFlag == true)
	{
		Vector3 enemyPosList[STAGE2_ENEMY_NUM] = {
			{STAGE2_ENEMY_POSITION1},
			{STAGE2_ENEMY_POSITION2},
			{STAGE2_ENEMY_POSITION3},
			{STAGE2_ENEMY_POSITION4}
			,{STAGE2_ENEMY_POSITION5}
			,{STAGE2_ENEMY_POSITION6}
		};

		for (int i = 0; i < STAGE2_ENEMY_NUM; i++) {
			m_enemyList[i] = NewGO<Enemy>(0, "enemy");
			m_enemyList[i]->m_position = enemyPosList[i];
			m_enemyList[i]->firstposition = enemyPosList[i];
		}
		m_stage2EnemyNewGOFlag = false;
	}

	//現在ステージ2をプレイしているとき
	if (GetStageState() == enStageState_Stage2)
	{
		// 回転床。
		if (m_RotationFloor == nullptr)
		{
			RotationFloor_NewGO();
		}

		// ゴールポール。
		if (m_Stage2Goal == nullptr)
		{
			State2Goal_NewGO();
		}

		// タワー。
		if (m_tower == nullptr)
		{
			Tower_NewGO();
		}

		if(m_tobeyaki == nullptr)
		{
			m_tobeyaki = NewGO<Tobeyaki>(0, "tobeyaki");
			m_tobeyaki->m_position = { 3850.0f,450.0f,0.0f };      //第二ステージ用
			m_modelRender.SetPosition(m_position);
		}

		if (m_towel == nullptr)
		{
			m_towel = NewGO<Towel>(0, "towel");
			m_towel->m_position = { 10100.0f, 550.0f, 0.0f };     //第二ステージ用
			m_modelRender.SetPosition(m_position);
		}
	}

////////////////////////////////////////////////////////////////////

	//ステージクリアとゲームオーバーの時は処理しない
	if (m_player->m_stageClearFlag == true ||
		m_player->m_gameOverFlag == true
		)
	{
		return;
	}

	//時間切れになったらゲームオーバー演出を流す
	if (m_gameTimer->IsTimeUp()) {
		//ゲームオーバーの演出が流れていないとき
		if (m_gameOverFlag != true)
		{
			NewGO<GameOver>(0, "gameover");
			DeleteGO(m_fade);
			DeleteGO(m_gameTimer);
			//ゲームオーバー演出を流す
			m_gameOverFlag = true;
		}

		//現在ステージ1をプレイしていたら
		if (GetStageState() == enStageState_Stage1)
		{
			//ステージ1BGMを削除
			DeleteGO(g_gameSoundEngine->GetSoundInstance(GameSoundList_BGM_Stage1));
		}
		//現在ステージ2をプレイしていたら
		else if(GetStageState() == enStageState_Stage2)
		{
			//ステージ2BGMを削除
			DeleteGO(g_gameSoundEngine->GetSoundInstance(GameSoundList_BGM_Stage2));
		}
		return;
	}

	//現在の愛媛県の場所の設定
	SetNowEhimePlace(m_player->m_position);

	//プレイヤーが注視点の現在位置より移動していたら
	if (m_player->m_position.x >= m_gameCamera->m_cameraTarget.x)
	{
		//ステージ背景の現在位置の更新
		UpdateStageBackGroundCurrentPosition();

		//ステージ背景の現在位置の更新
		m_stageBackGround[m_nowEhimePlace].SetCurrentPosition(m_stageBackGroundCurrentPosition);

		//ステージ背景のゴール位置の更新
		UpdateStageBackGroundGolePosition();

		//ステージ背景のゴール位置の設定
		m_stageBackGround[m_nowEhimePlace].SetGoalPosition(m_stageBackGroundGolePosition);
	}

	//ステージ背景の更新
	m_stageBackGround[m_nowEhimePlace].Update();

	//ステージ背景を遷移するフラグが立っていないとき処理する
	if (m_stageBackGroundTransitionFlag != true)
	{
		//遷移用のステージ背景の現在位置の更新
		m_stageBackGroundTransition[m_previousEhimePlace].SetCurrentPosition(m_stageBackGroundCurrentPositionMemory[m_previousEhimePlace]);

		//遷移用のステージ背景のゴール位置の設定
		m_stageBackGroundTransition[m_previousEhimePlace].SetGoalPosition(m_stageBackGroundGolePositionMemory[m_previousEhimePlace]);
	}

	//遷移用のステージ背景の更新
	m_stageBackGroundTransition[m_previousEhimePlace].Update();

	int MaxSuta = m_player->m_playermaxsutamina;
	int nowSuta = m_player->m_playernowsutamina;
	float nokori = (float)nowSuta / (float)MaxSuta;
	Vector3 heri = { 1.0f,1.0,1.0f };
	heri.x *= nokori;
	m_sutaminaMaxrender.SetScale(heri);

	m_sutaminaMaxrender.Update();
	m_sutamina0render.Update();

	m_mappuRender.Update();
	m_gennzaitiRender.Update();
	m_gennzaitiRender.SetPosition(Vector3(260.0f + m_player->m_position.x / 60, 430.0f, 0.0f));

	m_taorukuroRender.Update();
	m_taorutoriRender.Update();

	m_jakorender.Update();
	m_jakogetrender.Update();

	m_mikanRender.Update();
	m_mikangetRender.Update();

	m_sinjuRender.Update();
	m_sinjugetRender.Update();

	m_tobeyakiRender.Update();
	m_tobeyakigetRneder.Update();

	m_tarutoRender.Update();
	m_tarutogetRender.Update();
	
	//現在ステージ1をプレイしているとき
	if (GetStageState() == enStageState_Stage1)
	{
		//ステージ1BGMを再生。
		g_gameSoundEngine->PlayBGM(GameSoundList_BGM_Stage1, 1.0f);
	}
}

// ゲームタイマーのNewGO。
void Game::GameTimer_NewGO()
{
	m_gameTimer = NewGO<GameTimer>(0, "gametimer");
	m_gameTimer->SetTimeLimit(TIMER);
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

	m_modelRender.SetPosition(m_position);
}

// 落ちるブロックのNewGO。
void Game::FallingBlock_NewGO()
{
	m_fallingBlock = NewGO<FallingBlock>(0, "fallingblock");
	m_fallingBlock->m_position = { 8600.0f, 515.0f, 20.0f };
	m_fallingBlock->m_firstposition = m_fallingBlock->m_position;

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
   m_sinju = NewGO<sinju>(0, "sinju");
   m_sinju->m_position = { 14470.0f,600.0f,0.0f };
   m_modelRender.SetPosition(m_position);

   m_jako = NewGO<Jako>(0, "jako");
   m_jako->m_position = { 6000.0f,500.0f,0.0f };
   m_modelRender.SetPosition(m_position);
}

// ゴールポール。(Stage1)
void Game::Stage1Goal_NewGO()
{
	m_Stage1Goal = NewGO<ClearPoint>(0, "clearpoint");
	m_Stage1Goal->position = { 17500.0f, 700.0f, 0.0f };
	m_modelRender.SetPosition(m_position);
}

// ゴールポール。(Stage2)
void Game::State2Goal_NewGO()
{
	m_Stage2Goal = NewGO<ClearPoint>(0, "clearpoint");
	m_Stage2Goal->position = { 16000.0f, 100.0f, 0.0f };
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

// 回転床のNewGO
void Game::RotationFloor_NewGO()
{
	m_RotationFloor = NewGO<RotationFloor>(0, "RotationFloor");
	m_RotationFloor->m_position = { 3500.0f, 100.0f, 0.0f };
	m_modelRender.SetPosition(m_position);
}

// タワーのNewGO
void Game::Tower_NewGO()
{
	m_tower = NewGO<Tower>(0, "tower");
	m_tower->m_position = { 15000.0f, 0.0f, 0.0f };
	m_modelRender.SetPosition(m_position);
}

// フェード。
void Game::Fade_NewGO()
{
	NewGO<Fade>(0, "fade");
	m_fade = FindGO<Fade>("fade");
	//フェードをフェードインに切り替える。
	m_fade->FadeTransition(enFadeState_FadeIn);
}

// 描画処理。
void Game::Render(RenderContext& rc)
{
	//ステージ背景。
	m_stageBackGround[m_nowEhimePlace].Draw(rc);

	//ステージ背景を遷移するとき描画する
	if (m_stageBackGroundTransitionFlag == true)
	{
		//遷移用のステージ背景
		m_stageBackGroundTransition[m_previousEhimePlace].Draw(rc);
	}

	m_modelRender.Draw(rc);

	//ステージクリアとゲームオーバーではないときは描画する。
	if (m_player->m_stageClearFlag != true && 
		m_player->m_gameOverFlag != true
		)
	{
		//愛媛県の場所
		m_ehimePlace[m_ehimeFamousPlaceDrawingUI].Draw(rc);
		//愛媛県の名所
		m_ehimeFamousPlace[m_ehimeFamousPlaceDrawingUI].Draw(rc);
		if (m_player->m_playernowsutamina < 300) {
			m_sutamina0render.Draw(rc);
			m_sutaminaMaxrender.Draw(rc);
		}
		m_fontRender.Draw(rc);
		m_mappuRender.Draw(rc);
		m_gennzaitiRender.Draw(rc);

		//現在ステージ1をプレイしているとき
		if (GetStageState() == enStageState_Stage1)
		{
			if (m_player->jakoCount == 0) {
				m_jakorender.Draw(rc);
			}
			else if (m_player->jakoCount == 1) {
				m_jakogetrender.Draw(rc);
			}
			if (m_player->mikanCount == 0) {
				m_mikanRender.Draw(rc);
			}
			else if (m_player->mikanCount == 1) {
				m_mikangetRender.Draw(rc);
			}
			if (m_player->sinjuCount == 0) {
				m_sinjuRender.Draw(rc);
			}
			else if (m_player->sinjuCount == 1) {
				m_sinjugetRender.Draw(rc);
			}
		}
		//現在ステージ2をプレイしているとき
		else if (GetStageState() == enStageState_Stage2)
		{
			if (m_player->tarutoCount == 0) {
				m_tarutoRender.Draw(rc);
			}
			else if (m_player->tarutoCount == 1) {
				m_tarutogetRender.Draw(rc);
			}
			if (m_player->tobeyakiCount == 0) {
				m_tobeyakiRender.Draw(rc);
			}
			else if (m_player->tobeyakiCount == 1) {
				m_tobeyakigetRneder.Draw(rc);
			}
			if (m_player->taoruCount == 0) {
				m_taorukuroRender.Draw(rc);
			}
			else if (m_player->taoruCount == 1) {
				m_taorutoriRender.Draw(rc);
			}
		}
	}
}

//愛媛県の場所のスプライトの情報を取得。
void Game::GetStageBackGroundData(int place)
{
	//愛媛県の場所。
	switch (place)
	{
	//伊予市。
	case enEhimePlace_Iyo:				
		m_stageBackGroundFilePath = "Assets/Sprite/background/1stage/iyo.dds";
		m_stageBackGroundTransitionPosition[enEhimePlace_Iyo] = Vector3(4000.0f, 0.0f, 0.0f);
		break;

	//大洲市。
	case enEhimePlace_Oozu:				
		m_stageBackGroundFilePath = "Assets/Sprite/background/1stage/oozu.dds";
		m_stageBackGroundTransitionPosition[enEhimePlace_Oozu] = Vector3(7200.0f, 0.0f, 0.0f);
		break;

	//八幡浜市。
	case enEhimePlace_Yawatahama:		
		m_stageBackGroundFilePath = "Assets/Sprite/background/1stage/yawatahama.dds";
		m_stageBackGroundTransitionPosition[enEhimePlace_Yawatahama] = Vector3(10400.0f, 0.0f, 0.0f);
		break;

	//宇和島市。
	case enEhimePlace_Uwajima:			
		m_stageBackGroundFilePath = "Assets/Sprite/background/1stage/uwajima.dds";
		m_stageBackGroundTransitionPosition[enEhimePlace_Uwajima] = Vector3(13600.0f, 0.0f, 0.0f);
		break;

	//鬼北町。
	case enEhimePlace_Onihoku:			
		m_stageBackGroundFilePath = "Assets/Sprite/background/1stage/kihokutyou.dds";
		m_stageBackGroundTransitionPosition[enEhimePlace_Onihoku] = Vector3(m_Stage1Goal->position.x, 0.0f, 0.0f);
		break;

	//久万高原町。
	case enEhimePlace_Kumakougen:		
		m_stageBackGroundFilePath = "Assets/Sprite/background/2stage/kumakougentyou.dds";
		m_stageBackGroundTransitionPosition[enEhimePlace_Kumakougen] = Vector3(4000.0f, 0.0f, 0.0f);
		break;

	//四国中央市。
	case enEhimePlace_Sikokutyuou:		
		m_stageBackGroundFilePath = "Assets/Sprite/background/2stage/sikokutyuou.dds";
		m_stageBackGroundTransitionPosition[enEhimePlace_Sikokutyuou] = Vector3(7200.0f, 0.0f, 0.0f);
		break;

	//新居浜市。
	case enEhimePlace_Niihama:			
		m_stageBackGroundFilePath = "Assets/Sprite/background/2stage/niihama.dds";
		m_stageBackGroundTransitionPosition[enEhimePlace_Niihama] = Vector3(10400.0f, 0.0f, 0.0f);
		break;

	//今治市。
	case enEhimePlace_Imabari:			
		m_stageBackGroundFilePath = "Assets/Sprite/background/2stage/imabari.dds";
		m_stageBackGroundTransitionPosition[enEhimePlace_Imabari] = Vector3(13600.0f, 0.0f, 0.0f);
		break;

	//松山市。
	case enEhimePlace_Matuyama:			
		m_stageBackGroundFilePath = "Assets/Sprite/background/2stage/matuyama.dds";
		m_stageBackGroundTransitionPosition[enEhimePlace_Matuyama] = Vector3(m_Stage1Goal->position.x, 0.0f, 0.0f);
		break;
	default:
		break;
	}
}

//ステージ背景用の初期位置の更新。
void Game::UpdateStageBackGroundCurrentPosition()
{
	//愛媛県での現在位置が伊予市と久万高原町以外の時。
	if (m_nowEhimePlace != enEhimePlace_Iyo && m_nowEhimePlace != enEhimePlace_Kumakougen)
	{
		//ステージ背景用の初期位置。
		m_stageBackGroundInitPosition = m_stageBackGroundTransitionPosition[m_nowEhimePlace - 1];
	}
	//愛媛県での現在位置が伊予市と久万高原町の時。
	else
	{
		//ステージ背景用の初期位置。
		m_stageBackGroundInitPosition = BACKGROUND_FIRSTPOSITION;
	}

	//ステージ背景用の現在位置の更新。
	m_stageBackGroundCurrentPosition = m_player->m_position - m_stageBackGroundInitPosition;

	//各ステージ背景用の現在位置の値を保存する配列にステージ背景用の現在位置の変数を格納する
	m_stageBackGroundCurrentPositionMemory[m_nowEhimePlace] = m_stageBackGroundCurrentPosition;
}

//ステージ背景のゴール位置の更新
void Game::UpdateStageBackGroundGolePosition()
{
	//ステージ背景用のゴール位置の更新
	m_stageBackGroundGolePosition = m_stageBackGroundTransitionPosition[m_nowEhimePlace];

	//各ステージ背景用のゴール位置の値を保存する配列にステージ背景用のゴール位置の変数を格納する
	m_stageBackGroundGolePositionMemory[m_nowEhimePlace] = m_stageBackGroundGolePosition;
}

//現在の愛媛県の場所の設定。
void Game::SetNowEhimePlace(const Vector3& pos)
{
	switch (GetStageState())
	{
	case enStageState_Stage1: //ステージ1
		//ステージごとの特定の位置まで行ったら現在の場所を切り替える。
		if (pos.x >= m_stageBackGroundTransitionPosition[enEhimePlace_Uwajima].x)
		{
			//鬼北町。
			NowEhimePlaceTransition(enEhimePlace_Onihoku);
		}
		else if (pos.x >= m_stageBackGroundTransitionPosition[enEhimePlace_Yawatahama].x)
		{
			//宇和島市。
			NowEhimePlaceTransition(enEhimePlace_Uwajima);
		}
		else if (pos.x >= m_stageBackGroundTransitionPosition[enEhimePlace_Oozu].x)
		{
			//八幡浜市。
			NowEhimePlaceTransition(enEhimePlace_Yawatahama);
		}
		else if (pos.x >= m_stageBackGroundTransitionPosition[enEhimePlace_Iyo].x)
		{
			//大洲市。
			NowEhimePlaceTransition(enEhimePlace_Oozu);
		}
		else
		{
			//伊予市。
			NowEhimePlaceTransition(enEhimePlace_Iyo);
		}
		break;
	case enStageState_Stage2: //ステージ2
		//ステージごとの特定の位置まで行ったら現在の場所を切り替える。
		if (pos.x >= m_stageBackGroundTransitionPosition[enEhimePlace_Imabari].x)
		{
			//松山市。
			NowEhimePlaceTransition(enEhimePlace_Matuyama);
		}
		else if (pos.x >= m_stageBackGroundTransitionPosition[enEhimePlace_Niihama].x)
		{
			//今治市。
			NowEhimePlaceTransition(enEhimePlace_Imabari);
		}
		else if (pos.x >= m_stageBackGroundTransitionPosition[enEhimePlace_Sikokutyuou].x)
		{
			//新居浜市。
			NowEhimePlaceTransition(enEhimePlace_Niihama);
		}
		else if (pos.x >= m_stageBackGroundTransitionPosition[enEhimePlace_Kumakougen].x)
		{
			//四国中央市。
			NowEhimePlaceTransition(enEhimePlace_Sikokutyuou);
		}
		else
		{
			//久万高原町。
			NowEhimePlaceTransition(enEhimePlace_Kumakougen);
		}
		break;
	default:
		break;
	}
}

// 愛媛県での現在位置を切り替える。
void Game::NowEhimePlaceTransition(EnEhimePlace enEhimePlace)
{
	//愛媛県での前の位置が引数と異なっていたら処理する
	if (m_previousEhimePlace != enEhimePlace)
	{
		//現在位置の切り替え。
		m_nowEhimePlace = enEhimePlace;

		//プレイヤーがリスポーンしていないとき
		if (!m_player->IsPlayerRespawn())
		{
			//ステージ背景を遷移する
			m_stageBackGroundTransitionFlag = true;
		}
		//プレイヤーがリスポーンしているとき
		else
		{
			//前の位置の切り替え
			m_previousEhimePlace = m_nowEhimePlace;
		}
	}

	//ステージ背景を遷移するフラグが立っているとき
	if (m_stageBackGroundTransitionFlag == true)
	{
		//ステージ背景の遷移
		StageBackGoundTransition(enEhimePlace);
	}

	//愛媛県の場所を描画するUIの更新
	m_ehimePlaceDrawingUI = enEhimePlace;

	//愛媛県の名所を描画するUIの更新
	m_ehimeFamousPlaceDrawingUI = enEhimePlace;
}

//ステージ背景の遷移
void Game::StageBackGoundTransition(EnEhimePlace enEhimePlace)
{
	//愛媛県での前の位置が引数と異なっていたら
	if (m_previousEhimePlace != enEhimePlace)
	{
		//遷移用のステージ背景を透明にする
		m_stageBackGroundTransitionAlpha -= g_gameTime->GetFrameDeltaTime() * 2.0f;
	}
	//愛媛県での前の位置が引数と同じなら
	else
	{
		//遷移用のステージ背景を不透明にする
		m_stageBackGroundTransitionAlpha += g_gameTime->GetFrameDeltaTime() * 2.0f;
	}

	//遷移用のステージ背景が透明または不透明になったら
	if (m_stageBackGroundTransitionAlpha < 0.0f || m_stageBackGroundTransitionAlpha > 1.0f)
	{
		//遷移用のステージ背景の透明度を元の値に戻す
		m_stageBackGroundTransitionAlpha = 1.0f;

		//遷移用のステージ背景(前の背景)の乗算カラーの設定
		m_stageBackGroundTransition[m_previousEhimePlace].SetMulColor(Vector4(1.0f, 1.0f, 1.0f, m_stageBackGroundTransitionAlpha));

		//愛媛県での前の位置が引数と同じなら
		if (m_previousEhimePlace == enEhimePlace)
		{
			//現在位置の切り替え
			m_nowEhimePlace = enEhimePlace;
		}

		//前の位置の切り替え
		m_previousEhimePlace = m_nowEhimePlace;

		//ステージ背景の遷移を終了
		m_stageBackGroundTransitionFlag = false;
	}

	//遷移用のステージ背景の乗算カラーの設定
	m_stageBackGroundTransition[m_previousEhimePlace].SetMulColor(Vector4(1.0f, 1.0f, 1.0f, m_stageBackGroundTransitionAlpha));
}

//ステージ1オブジェクトの削除。
void Game::Stage1ObjectDelete()
{
	//敵
	const auto& enemys = FindGOs<Enemy>("enemy");
	for (auto enemy : enemys)
	{
		DeleteGO(enemy);
	}

	//アイテムをドロップする敵
	DeleteGO(m_itemenemy);

	//透明ブロック
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

	//落ちるブロック
	DeleteGO(m_fallingBlock);
	DeleteGO(m_movingFloor1);
	DeleteGO(m_movingFloor2);

	//ブロック
	DeleteGO(m_block);
	DeleteGO(m_block1);
	DeleteGO(m_block2);
	DeleteGO(m_block3);
	DeleteGO(m_block4);

	//足場ブロック
	DeleteGO(m_scaffold);
	DeleteGO(m_scaffold1);
	DeleteGO(m_towel);
	DeleteGO(m_Stage1Goal);

	//チェックポイント
	DeleteGO(m_checpoint);

	//クリアポイント
	DeleteGO(m_Stage1Goal);
	DeleteGO(m_s_MovingFloor);
	DeleteGO(m_s_MovingFloor1);
	DeleteGO(m_s_MovingFloor2);
	DeleteGO(m_s_MovingFloor3);
	DeleteGO(m_itemenemy);


	//アイテム
	DeleteGO(m_towel);

	DeleteGO(m_tobeyaki);
	DeleteGO(m_sinju);
	DeleteGO(m_jako);
	DeleteGO(m_taruto);
	//ドロップアイテムをDeleteGOする場合
	//ドロップアイテムのクラスをここでFindGOしてからDeleteGOしてください。
	m_mikan = FindGO<Mikan>("mikan");
	DeleteGO(m_mikan);
	DeleteGO(m_checpoint);
}

//ステージ2オブジェクトの削除。
void Game::Stage2ObjectDelete()
{
	DeleteGO(m_RotationFloor);
	DeleteGO(m_Stage2Goal);
	DeleteGO(m_tower);

}