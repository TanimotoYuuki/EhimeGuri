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
	// ステージ1のEnemyの座標。
	const Vector3 STAGE1_ENEMY_POSITION1(2800.0f, 94.0f, 0.0f);
	const Vector3 STAGE1_ENEMY_POSITION2(400.0f, 94.0f, 0.0f);
	const Vector3 STAGE1_ENEMY_POSITION3(4800.0f, 94.0f, 0.0f);
	const Vector3 STAGE1_ENEMY_PODITION4(12900.0f, 225.0f, 0.0f);

	// ステージ2。
	const Vector3 STAGE2_ENEMY_POSITION1(800.0f, 200.0f, 0.0f);
	const Vector3 STAGE2_ENEMY_POSITION2(1400.0f, 200.0f, 0.0f);
	const Vector3 STAGE2_ENEMY_POSITION3(4250.0f, 500.0f, 0.0f);
	const Vector3 STAGE2_ENEMY_POSITION4(4600.0f, 300.0f, 0.0f);
	const Vector3 STAGE2_ENEMY_POSITION5(7100.0f, 200.0f, 0.0f);
	const Vector3 STAGE2_ENEMY_POSITION6(8000.0f, 500.0f, 0.0f);

	// チェックポイント。
	const Vector3 STAGE1_CHECKPOINT_POSITION(10300.0f, 100.0f, 0.0f);
	const Vector3 STAGE2_CHECKPOINT_POSITION(9350.0f, 360.0f, 0.0f);

	const Vector3 BACKGROUND_FIRSTPOSITION(0.0f, 0.0f, 0.0f);
	const Vector3 ITEM_ENEMY_POSITION(9050.0f, 600.0f, 0.0f);
	const Vector3 ITEM_DROP_ENEMY(7700.0f, 400.0f, 0.0f);

	/// マップ。
	const float MAP_WIDTH = 350.0f;
	const float MAP_HEIGHT = 40.0f;
	const Vector3 MAP_POSITION(400.0f, 400.0f, 0.0f);

	// 現在地。
	const float LOCATION_WIDTH = 50.0f;
	const float LOCATION_HEIGHT = 50.0f;
	const Vector3 LOCATION_POSITION(260.0f, 430.0f, 0.0f);

	// スタミナ -最大値-
	const float MAX_WIDHT = 350.0f;
	const float MAX_HEIGHT = 40.0f;
	const Vector3 MAX_POSITION(-175.0f, 300.0f, 0.0f);
	const Vector2 SUTAMINA_PIVOT(0.0f, 0.5f);

	// スタミナ -最小値-
	const float MIN_WIDHT = 350.0f;
	const float MIN_HEIGHT = 40.0f;
	const Vector3 MIN_POSITION(0.0f, 300.0f, 0.0f);

	// アイテム。
	const float ITEM_WIDHT = 100.0f;
	const float ITEM_HEIGHT = 100.0f;
	const Vector3 JAKO_POSITION(-750.0f, 400.0f, 0.0f);
	const Vector3 MIKAN_POSITION(-650.0f, 400.0f, 0.0f);
	const Vector3 PEARL_POSITION(-550.0f, 400.0f, 0.0f);
	const Vector3 TOBE_WARE_POSITION(-750.0f, 400.0f, 0.0f);
	const Vector3 TARTO_POSITION(-650.0f, 400.0f, 0.0f);
	const Vector3 TOWEL_SCALE(1.3f, 1.3f, 1.3f);
	const Vector3 TOWEL_POSITION(-550.0f, 400.0f, 0.0f);
	const Vector3 TOWELPOSITION(10100.0f, 550.0f, 0.0f);
	const Vector3 TOBE_WARE_OBJECT_POSITION(3850.0f, 450.0f, 0.0f);
	
	const float TIMER = 180.0f;

	const Vector3 RATEOFREDUCTION(1.0f, 1.0, 1.0f);

	const int STAGE1_ENEMY_NUM = 4;
	const int STAGE2_ENEMY_NUM = 6;
	const int ITEM_NUM = 6;
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
		m_stage1EnemyList[i] = NewGO<Enemy>(0, "enemy");
		m_stage1EnemyList[i]->m_position = enemyPosList[i];
		m_stage1EnemyList[i]->firstposition = enemyPosList[i];
	}

	


	/// <summary>
	/// マップを読み込む関数。
	/// </summary>
	SetMap();
			
	/// <summary>
	/// スタミナを読み込む関数。
	/// </summary>
	SetStamina();


	/// <summary>
	/// アイテムを設定。
	/// </summary>
	SetItem();
	
	/// <summary>
	/// アイテムを取得。
	/// </summary>
	ObtainItem();

	/// <summary>
	/// NewGO関数。
	/// </summary>
	Object_NewGO();

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

	//アイテムテキスト関連のスプライトの初期化
	for (int i = 0; i < enItem_Num; i++)
	{
		//アイテムテキスト
		//0 アイテムテキスト関連のスプライトの情報を取得
		GetItemTextSpriteData(i);
		//0.1 アイテムテキストのスプライトの初期化
		m_itemText[i].Init(m_itemTextFilePath, 1024, 128);
		//0.2 アイテムテキストのスプライトの位置を設定
		m_itemText[i].SetPosition(m_itemTextPosition);
		//0.3 アイテムテキストのスプライトの大きさを設定
		m_itemText[i].SetScale(Vector3(0.25f,0.25f,0.25f));
		//0.4 アイテムテキストのスプライトの乗算カラーの設定
		m_itemText[i].SetMulColor(Vector4(1.0f, 1.0f, 1.0f, m_itemTextAlpha));
		//0.5 アイテムテキストのスプライトの更新
		m_itemText[i].Update();

		//アイテム取得テキスト
		//1 アイテム取得テキストのスプライトの初期化
		m_itemGetText[i].Init(m_itemGetTextFilePath, 1024, 128);
		//1.1 アイテム取得テキストのスプライトの位置の設定
		m_itemGetText[i].SetPosition(m_itemGetTextPosition);
		//1.2 アイテム取得テキストのスプライトの大きさの設定
		m_itemGetText[i].SetScale(Vector3(0.25f, 0.25f, 0.25f));
		//1.3 アイテム取得テキストのスプライトの乗算カラーの設定
		m_itemGetText[i].SetMulColor(Vector4(1.0f, 1.0f, 1.0f, m_itemTextAlpha));
		//1.4 アイテム取得テキストのスプライトの更新
		m_itemGetText[i].Update();
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

	//アイテムの総数の設定
	m_totalItemNum = ITEM_NUM;

//	PhysicsWorld::GetInstance()->EnableDrawDebugWireFrame();
	return true;
}

// 更新作業。
void Game::Update()
{
////// 第2ステージ用 /////////////////////////////////////////////
    //現在ステージ2をプレイしているとき
	if (GetStageState() == enStageState_Stage2)
	{
		// チェックポイント。
		// チェックポイント用のインスタンスがnullptrだったらNewGOする。	  
		if (m_checpoint == nullptr)
		{
			Stage2CheckPoint_NewGO();
		}

		//アイテムエネミー用のインスタンスがnullptrだったらNewGOする。
		if (m_itemenemy == nullptr)
		{
			Item_Enemy_NewGO();
		}

		//ステージ2用のエネミーをNewGOするかどうか判定するフラグがtrueになっていたらNewGOする。
		if (m_stage2EnemyNewGOFlag == true)
		{
			Vector3 enemyPosList[STAGE2_ENEMY_NUM] = {
				{STAGE2_ENEMY_POSITION1},
				{STAGE2_ENEMY_POSITION2},
				{STAGE2_ENEMY_POSITION3},
				{STAGE2_ENEMY_POSITION4},
				{STAGE2_ENEMY_POSITION5},
				{STAGE2_ENEMY_POSITION6}
			};

			for (int i = 0; i < STAGE2_ENEMY_NUM; i++) {
				m_stage2EnemyList[i] = NewGO<Enemy>(0, "enemy");
				m_stage2EnemyList[i]->m_position = enemyPosList[i];
				m_stage2EnemyList[i]->firstposition = enemyPosList[i];
			}
			m_stage2EnemyNewGOFlag = false;
		}

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

		// 砥部焼。
		if(m_tobeyaki == nullptr)
		{
			TobeWare_NewGO();
		}

		// タオル。
		if (m_towel == nullptr)
		{
			Towel_NewGO();
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
	Vector3 heri = {RATEOFREDUCTION};
	heri.x *= nokori;
	m_sutaminaMaxrender.SetScale(heri);

	// 更新処理をまとめる処理。
	Updates();

	//現在ステージ1をプレイしているとき
	if (GetStageState() == enStageState_Stage1)
	{
		m_gennzaitiRender.SetPosition(Vector3(260.0f + m_player->m_position.x / 60, 430.0f, 0.0f));
	}
	//現在ステージ1をプレイしているとき
	else if (GetStageState() == enStageState_Stage2)
	{
		m_gennzaitiRender.SetPosition(Vector3(260.0f + m_player->m_position.x / 55, 430.0f, 0.0f));
	}

	//アイテムテキスト関連のスプライトの動作
	ItemTextSpriteMove(m_itemTextDrawingUI);

	m_itemText[m_itemTextDrawingUI].Update();
	m_itemGetText[m_itemTextDrawingUI].Update();

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

// オブジェクトのNewGOをまとめておく場所。
void Game::Object_NewGO()
{
	// 透明ブロック。
	TransparentBlock_NewGO();

	// 落ちるブロック。
	FallingBlock_NewGO();

	// 動く床。
	MovingFloor_NewGO();

	// ブロック。
	Block_NewGO();

	// 足場ブロック。
	Scaffold_NewGO();

	// アイテム。
	Item_NewGO();

	// ステージ1のゴールポール。
	Stage1Goal_NewGO();

	// 落下速度の遅い床。
	S_MovingFloor_NewGO();

	// ステージ1のチェックポイント。
	Stage1CheckPoint_NewGO();

	// アイテムをドロップする敵。
	ItemEnemy_NewGO();

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

// アイテムをドロップする敵のNewGO。
void Game::Item_Enemy_NewGO()
{
	m_itemenemy = NewGO<ItemEnemy>(1, "itemenemy");
	m_itemenemy->m_position = { ITEM_DROP_ENEMY };
	m_itemenemy->firstposition = m_itemenemy->m_position;
	m_player->m_itemEnemy = nullptr;
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
	m_Stage2Goal->position = { 15950.0f, 125.0f, 0.0f };
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

// チェックポイントのNewGO。
void Game::Stage1CheckPoint_NewGO()
{
	m_checpoint = NewGO<Checpoint>(1, "checpoint");
	m_checpoint->position = { STAGE1_CHECKPOINT_POSITION };
	m_modelRender.SetPosition(m_position);
}

// ステージ2用。
void Game::Stage2CheckPoint_NewGO()
{
	m_checpoint = NewGO<Checpoint>(1, "checpoint");
	m_checpoint->position = {STAGE2_CHECKPOINT_POSITION};
	m_modelRender.SetPosition(m_position);

}

// アイテムをドロップする敵のNewGO。
void Game::ItemEnemy_NewGO()
{
	m_itemenemy = NewGO<ItemEnemy>(1, "itemenemy");
	m_itemenemy->m_position = { ITEM_ENEMY_POSITION };
	m_itemenemy->firstposition = m_itemenemy->m_position;
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

		//UI描画用の変数でアイテムを取得しているときにアイテムテキスト関連UIを描画する
		if (m_itemTextDrawingUI != enItem_NoGetItem)
		{
			//アイテムテキスト
			m_itemText[m_itemTextDrawingUI].Draw(rc);
			//アイテム取得テキスト
			m_itemGetText[m_itemTextDrawingUI].Draw(rc);
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
		m_stageBackGroundTransitionPosition[enEhimePlace_Matuyama] = Vector3(15950.0f, 125.0f, 0.0f);
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
		//プレイヤーがリスポーンしているとき　かつ
		//ステージ背景を遷移するかどうかを判定するフラグが立っていないとき
		else if (m_player->IsPlayerRespawn() && m_stageBackGroundTransitionFlag != true)
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

	//遷移用のステージ背景が透明・不透明または
	//プレイヤーがリスポーンしているとき
	if (m_stageBackGroundTransitionAlpha < 0.0f || m_stageBackGroundTransitionAlpha > 1.0f || m_player->IsPlayerRespawn())
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

//アイテムテキスト関連のスプライトの動作
void Game::ItemTextSpriteMove(int item)
{
	//アイテムを取得したら
	if (item != enItem_NoGetItem)
	{
		//アイテムテキスト関連のスプライトを動作するフラグが立っていないとき
		if (m_itemTextMoveFlag != true)
		{
			//3.0秒経過したら
			if (g_gameTime->StopWatch(3.0f))
			{
				//アイテムテキスト関連のスプライトを動作する
				m_itemTextMoveFlag = true;
			}
		}
		//アイテムテキスト関連のスプライトを動作フラグするフラグが立っているとき
		else
		{
			//アイテムテキスト関連のスプライトを透明にしていく
			m_itemTextAlpha -= g_gameTime->GetFrameDeltaTime();

			//アイテムテキスト関連のスプライトの透明度が0.0fになったら
			if (m_itemTextAlpha < 0.0f)
			{
				//動作を終了する
				m_itemTextDrawingUI = enItem_NoGetItem;
				m_itemTextAlpha = 1.0f;
				m_itemTextMoveFlag = false;
				return;
			}

			//アイテムテキスト関連のスプライトの乗算カラーの設定
			m_itemText[m_itemTextDrawingUI].SetMulColor(Vector4(1.0f, 1.0f, 1.0f, m_itemTextAlpha));
			m_itemGetText[m_itemTextDrawingUI].SetMulColor(Vector4(1.0f, 1.0f, 1.0f, m_itemTextAlpha));
		}
	}
}

void Game::MainObjectDelete()
{
	//プレイヤー
	DeleteGO(m_player);

	//ゲームカメラ
	DeleteGO(m_gameCamera);

	//ゲームタイマー
	DeleteGO(m_gameTimer);
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

	//チェックポイント
	DeleteGO(m_checpoint);

	//クリアポイント
	DeleteGO(m_Stage1Goal);

	//落下速度の遅い床
	DeleteGO(m_s_MovingFloor);
	DeleteGO(m_s_MovingFloor1);
	DeleteGO(m_s_MovingFloor2);
	DeleteGO(m_s_MovingFloor3);

	//アイテムエネミー
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
}

//ステージ2オブジェクトの削除。
void Game::Stage2ObjectDelete()
{
	//敵
	const auto& enemys = FindGOs<Enemy>("enemy");
	for (auto enemy : enemys)
	{
		DeleteGO(enemy);
	}

	// 回転床。
	DeleteGO(m_RotationFloor);

	// ゴールポール。
	DeleteGO(m_Stage2Goal);

	// タワー。
	DeleteGO(m_tower);

	//アイテムエネミー
	DeleteGO(m_itemenemy);

	//チェックポイント
	DeleteGO(m_checpoint);

	//アイテム
	DeleteGO(m_tobeyaki);
	DeleteGO(m_towel);
	m_taruto = FindGO<Taruto>("taruto");
	DeleteGO(m_taruto);
}

// マップをセットする。
void Game::SetMap()
{
	// マップ。
	InitMap();

	// 現在地。
	InitMap_CurrentLocation();
}

// マップ。
void Game::InitMap()
{
	string Map = m_config->GetFullPaht_DDS("mappu", MAP_WIDTH, MAP_HEIGHT);
	m_mappuRender.Init(Map.c_str(), MAP_WIDTH, MAP_HEIGHT);
	m_mappuRender.SetPosition(MAP_POSITION);
}

// マップの現在地。
void Game::InitMap_CurrentLocation()
{
	string Location = m_config->GetFullPaht_DDS("gennzaiti", LOCATION_WIDTH, LOCATION_HEIGHT);
	m_gennzaitiRender.Init(Location.c_str(), LOCATION_WIDTH, LOCATION_HEIGHT);
	m_gennzaitiRender.SetPosition(LOCATION_POSITION);

}

// スタミナをセットする。
void Game::SetStamina()
{
	// スタミナの最大値。
	Stamina_Max();

	// スタミナの最小値。
	Stamina_Min();
}

// スタミナの最大値。
void Game::Stamina_Max()
{
	string Sutamina_MAX = m_config->GetFullPaht_DDS("sutaminamax", MAX_WIDHT, MIN_HEIGHT);
	m_sutaminaMaxrender.Init(Sutamina_MAX.c_str(), MAX_WIDHT, MIN_HEIGHT);
	m_sutaminaMaxrender.SetPosition(MAX_POSITION);
	m_sutaminaMaxrender.SetPivot(SUTAMINA_PIVOT);
}

// スタミナの最小値。
void Game::Stamina_Min()
{
	string Sutamina_Min = m_config->GetFullPaht_DDS("sutamina0", MIN_WIDHT, MIN_HEIGHT);
	m_sutamina0render.Init(Sutamina_Min.c_str(), MIN_WIDHT, MIN_HEIGHT);
	m_sutamina0render.SetPosition(MIN_POSITION);

}

// アイテムをセットする。
void Game::SetItem()
{
	// じゃこ天。
	SetJako();

	// みかん。
	SetMikan();

	// 真珠。
	SetPearl();

	// 砥部焼。
	SetTobeWare();

	// タルト。
	SetTart();

	// タオル。
	SetTowel();
}

// アイテムを取得する。
void Game::ObtainItem()
{
	// じゃこ天。
	ObtainJako();

	// みかん。
	ObtainMikan();

	// 真珠。
	ObtainPearl();

	// 砥部焼。
	ObtainTobeWare();

	// タルト。
	ObtainTart();

	// タオル。
	ObtainTowel();
}

// じゃこ天をセット。
void Game::SetJako()
{
	string Jako = m_config->GetFullPaht_DDS("jako", ITEM_WIDHT, ITEM_HEIGHT);
	m_jakorender.Init(Jako.c_str(), ITEM_WIDHT, ITEM_HEIGHT);
	m_jakorender.SetPosition(JAKO_POSITION);
}

// じゃこ天を取得
void Game::ObtainJako()
{
	string Jako = m_config->GetFullPaht_DDS("jakoget", ITEM_WIDHT, ITEM_HEIGHT);
	m_jakogetrender.Init(Jako.c_str(), ITEM_WIDHT, ITEM_HEIGHT);
	m_jakogetrender.SetPosition(JAKO_POSITION);
}

// みかんをセット。
void Game::SetMikan()
{
	string Mikan = m_config->GetFullPaht_DDS("mikan", ITEM_WIDHT, ITEM_HEIGHT);
	m_mikanRender.Init(Mikan.c_str(), ITEM_WIDHT, ITEM_HEIGHT);
	m_mikanRender.SetPosition(MIKAN_POSITION);
}

// みかんを取得。
void Game::ObtainMikan()
{
	string Mikan = m_config->GetFullPaht_DDS("mikanget", ITEM_WIDHT, ITEM_HEIGHT);
	m_mikangetRender.Init(Mikan.c_str(), ITEM_WIDHT, ITEM_HEIGHT);
	m_mikangetRender.SetPosition(MIKAN_POSITION);

}

// 真珠をセット。
void Game::SetPearl()
{
	string Pearl = m_config->GetFullPaht_DDS("sinju", ITEM_WIDHT, ITEM_HEIGHT);
	m_sinjuRender.Init(Pearl.c_str(), ITEM_WIDHT, ITEM_HEIGHT);
	m_sinjuRender.SetPosition(PEARL_POSITION);
}

// 真珠を取得。
void Game::ObtainPearl()
{
	string Pearl = m_config->GetFullPaht_DDS("sinjuget", ITEM_WIDHT, ITEM_HEIGHT);
	m_sinjugetRender.Init(Pearl.c_str(), ITEM_WIDHT, ITEM_HEIGHT);
	m_sinjugetRender.SetPosition(PEARL_POSITION);

}

// 砥部焼をセット。
void Game::SetTobeWare()
{
	string Tobe_Ware = m_config->GetFullPaht_DDS("tobeyaki", ITEM_WIDHT, ITEM_HEIGHT);
	m_tobeyakiRender.Init(Tobe_Ware.c_str(), ITEM_WIDHT, ITEM_HEIGHT);
	m_tobeyakiRender.SetPosition(TOBE_WARE_POSITION);
}

// 砥部焼を取得。
void Game::ObtainTobeWare()
{
	string Tobe_Ware = m_config->GetFullPaht_DDS("tobeyakiget", ITEM_WIDHT, ITEM_HEIGHT);
	m_tobeyakigetRneder.Init(Tobe_Ware.c_str(), ITEM_WIDHT, ITEM_HEIGHT);
	m_tobeyakigetRneder.SetPosition(TOBE_WARE_POSITION);

}

// タルトをセット。
void Game::SetTart()
{
	string Tart = m_config->GetFullPaht_DDS("taruto", ITEM_WIDHT, ITEM_HEIGHT);
	m_tarutoRender.Init(Tart.c_str(),ITEM_WIDHT, ITEM_HEIGHT);
	m_tarutoRender.SetPosition(TARTO_POSITION);
}

// タルトを取得。
void Game::ObtainTart()
{
	string Tart = m_config->GetFullPaht_DDS("tarutoget", ITEM_WIDHT, ITEM_HEIGHT);
	m_tarutogetRender.Init(Tart.c_str(), ITEM_WIDHT, ITEM_HEIGHT);
	m_tarutogetRender.SetPosition(TARTO_POSITION);
}

// タオルをセット。
void Game::SetTowel()
{
	// タオル・
	string Towel = m_config->GetFullPaht_DDS("taorukuro", ITEM_WIDHT, ITEM_HEIGHT);
	m_taorukuroRender.Init(Towel.c_str(), ITEM_WIDHT, ITEM_HEIGHT);
	m_taorukuroRender.SetPosition(TOWEL_POSITION);
	m_taorukuroRender.SetScale(TOWEL_SCALE);
}

// タオルを取得。
void Game::ObtainTowel()
{
	string towel = m_config->GetFullPaht_DDS("taorutori", ITEM_WIDHT, ITEM_HEIGHT);
	m_taorutoriRender.Init(towel.c_str(), ITEM_WIDHT, ITEM_HEIGHT);
	m_taorutoriRender.SetPosition(TOWEL_POSITION);
	m_taorutoriRender.SetScale(TOWEL_SCALE);
}

//	砥部焼。
void Game::TobeWare_NewGO()
{
	m_tobeyaki = NewGO<Tobeyaki>(0, "tobeyaki");
	m_tobeyaki->m_position = {TOBE_WARE_OBJECT_POSITION};      //第二ステージ用
	m_modelRender.SetPosition(m_position);
}

// タオル。
void Game::Towel_NewGO()
{
	m_towel = NewGO<Towel>(0, "towel");
	m_towel->m_position = {TOWELPOSITION };     //第二ステージ用
	m_modelRender.SetPosition(m_position);
}

// 更新処理をまとめる処理。
void Game::Updates()
{
	m_sutaminaMaxrender.Update();// スタミナの最大値。
	m_sutamina0render.Update();// スタミナの最小値。

	m_mappuRender.Update();// マップ。
	m_gennzaitiRender.Update();// 現在地。

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


}
