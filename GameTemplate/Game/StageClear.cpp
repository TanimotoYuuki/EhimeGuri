#include "stdafx.h"
#include "StageClear.h"
#include "Player.h"
#include "Fade.h"
#include "GameCamera.h"
#include "GameTimer.h"
#include "Game.h"
#include "Title.h"
#include "Scene.h"
namespace
{
	//ステージクリア演出をする位置。
	const Vector3 STAGE_CLEAR_POSITION = Vector3(0.0f, 0.0f, 0.0f);
	//ステージ2の開始位置
	const Vector3 STAGE2_START_POSITION = Vector3(0.0f, 160.0f, 0.0f);
}

//開始処理。
bool StageClear::Start()
{
	//ステージクリアUI。
	//0 ステージクリアUIの初期化。
	m_stageClearUI.Init("Assets/Sprite/stageclear.dds", 1024, 128);
	//0.1 ステージクリアUIの座標の設定。
	m_stageClearUI.SetPosition(m_position);
	//0.2 ステージクリアUIの更新。
	m_stageClearUI.Update();

	//ステージクリアスプライト用のイージングを設定。
	SetStageClearSpriteEasing();

	//インスタンス。
	//0 プレイヤー。
	m_player = FindGO<Player>("player");
	m_player->m_stageClearFlag = true;

	//1 フェード。
	NewGO<Fade>(0, "fade");
	m_fade = FindGO<Fade>("fade");
	m_fade->FadeTransition(enFadeState_None);

	//2 ゲームカメラ
	m_gameCamera = FindGO<GameCamera>("gamecamera");

	//3 ゲームタイマー
	m_gameTimer = FindGO<GameTimer>("gametimer");

	//4 ゲーム
	m_game = FindGO<Game>("game");

	//ステージクリアBGMの再生。
	g_gameSoundEngine->PlaySE(GameSoundList_SE_System_StageClear, 1.0f);
	return true;
}

//更新処理。
void StageClear::Update()
{
	//ステージクリアスプライト用のイージングの更新処理。
	UpdateStageClearSpriteEasing();

	//ローディング開始フラグが立っているとき
	if (m_loadingStartFlag)
	{
		//ローディング処理
		LoadingProcess();
	}
}

void StageClear::LoadingProcess()
{
	// ローディング画面表示中。
	if (m_fade->GetFadeState() == enFadeState_Loading)
	{
		// 3.0f経過したら。
		if (g_gameTime->StopWatch(3.0f))
		{
			// プレイヤーをステージ2の開始位置に移動。
			if (m_player != nullptr)
			{
				// ステージ2でのプレイヤーの初期設定
				// 位置
				m_player->m_characterController.SetPosition(STAGE2_START_POSITION);
				m_player->m_modelRender.SetPosition(STAGE2_START_POSITION);
				m_player->m_initPosition = STAGE2_START_POSITION;
				// 角度
				m_player->m_rotation.SetRotationDegY(90.0f);
				m_player->m_modelRender.SetRotation(m_player->m_rotation);
				// 更新
				m_player->m_modelRender.Update();

				// プレイヤークラスのチェックカウントを0にする
				m_player->checcount = 0;

				// プレイヤークラスのステージクリアフラグをfalseにする
				m_player->m_stageClearFlag = false;

				// プレイヤークラスのフェード用のインスタンスをnullptrにする
				m_player->m_fade = nullptr;
			}

			// カメラをステージ2の開始位置に移動。
			m_gameCamera->m_stageTransitionFlag = true;

			// 制限時間の設定
			m_gameTimer->SetTimeLimit(180.0f);

			// ステージ1オブジェクトの削除
			m_game->Stage1ObjectDelete();

			// ゲームクラスのチェックポイント用のインスタンスをnullptrにする
			m_game->m_checpoint = nullptr;

			// ゲームクラスのアイテムエネミー用のインスタンスをnullptrにする
			m_game->m_itemenemy = nullptr;

			// ステージ2用のエネミーをNewGOするフラグをtrueにする
			m_game->m_stage2EnemyNewGOFlag = true;

			// 愛媛県での場所の変更
			m_game->m_nowEhimePlace = m_game->enEhimePlace_Kumakougen;
			m_game->m_previousEhimePlace = m_game->enEhimePlace_Kumakougen;
			m_game->m_ehimePlaceDrawingUI = m_game->enEhimePlace_Kumakougen;
			m_game->m_ehimeFamousPlaceDrawingUI = m_game->enEhimePlace_Kumakougen;

			// ステージ2に移行
			m_game->SetStageState(m_game->enStageState_Stage2);

			// SceneManagerを経由してステージ2への遷移を要求。
			Scene_Manager::GetInstance()->SetRequest(SceneID::S_Stage2);
			// オブジェクトを削除。
			DeleteGO(this);
		}
	}
}
//描画処理。
void StageClear::Render(RenderContext& rc)
{
	//ステージクリアUI。
	m_stageClearUI.Draw(rc);
}

//ステージクリアスプライト用のイージングを設定。
void StageClear::SetStageClearSpriteEasing()
{
	m_beforeEasingPosition = m_position;
	m_afterEasingPosition = Vector3(1250.0f, 275.0f, 0.0f);
	m_easingTime = 0.0f;
}

//ステージクリアスプライト用のイージングの更新処理。
void StageClear::UpdateStageClearSpriteEasing()
{
	//特定の位置に行ったらステージクリア演出をする。
	if (m_position.x > STAGE_CLEAR_POSITION.x && m_stageClearDirectionFinishFlag != true)
	{
		//1.0秒経過したらステージクリア演出を終了する。
		if (g_gameTime->StopWatch(1.0f))
		{
			//ステージクリア演出を終了する。
			m_stageClearDirectionFinishFlag = true;
		}
		return;
	}

	m_easingTime += 0.5f * g_gameTime->GetFrameDeltaTime();

	//割合が1.0f以上になったら割合を固定する。
	if (m_easingTime > 1.0f)
	{
		m_easingTime = 1.0f;

		//フェードをローディングに切り替える
		m_fade->FadeTransition(enFadeState_FadeOut);

		//ローディング開始フラグを立てる
		m_loadingStartFlag = true;
	}

	//ステージクリアUIの更新。
	m_position.Lerp(m_easingTime, m_beforeEasingPosition, m_afterEasingPosition);
	m_stageClearUI.SetPosition(m_position);
	m_stageClearUI.Update();
}