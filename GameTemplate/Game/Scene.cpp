#include "stdafx.h"
#include "Fade.h"
#include "Scene.h"
#include "Stage1.h"
#include "Stage2.h"
#include "Config.h"
#include "StageClear.h"
#include "Player.h"
#include "GameClear.h"
#include "GameOver.h"
#define SMGetIns Scene_Manager::GetInstance // シングルトンインスタンスを取得するマクロ定義

Scene_Manager* Scene_Manager::instance = nullptr; // シングルトンインスタンスの初期化

Stage1Scene::~Stage1Scene()
{
	DeleteGO(m_stage1);

}

Stage2Scene::~Stage2Scene()
{
	DeleteGO(m_stage2);
	Fade* fade = FindGO<Fade>("fade");
	DeleteGO(fade);
}

GameClearScene::~GameClearScene()
{
	DeleteGO(m_gameClear);
}

// シーン::初期化処理。
bool Scene::Start()
{
	return true;
}

// シーン::更新処理。
void Scene::Update()
{
	// シーンマネージャーのUpdateを呼び出す。
	Scene_Manager::GetInstance()->Update();

}

// タイトルシーン::初期化処理。
bool TitleScene::Start()
{
	// タイトルシーンの初期化処理を行う。
	 m_title =NewGO<Title>(0, "Title"); // タイトルシーンの初期化処理を行う。
	return true;
}

// タイトルシーン::更新処理。
void TitleScene::Update()
{
	//Titleクラスのシーン遷移フラグでステージ遷移を判定する。
	if (m_title->m_sceneTransitionFlag == true)
	{
		// ステージ1へ遷移する。
		SMGetIns()->SetRequest(SceneID::S_Stage1);
	}
}

// ステージ1シーン::初期化処理。
bool Stage1Scene::Start()
{
	// ステージ1の初期化処理を行う。
    m_stage1 = NewGO<Stage1>(0, "Stage1"); // ステージ1の初期化処理を行う。

	// 
	m_stageClear = FindGO<StageClear>("StageClear");

	//インスタンス
	//タイトルシーンのタイトルクラスを取得する。
	m_title = FindGO<Title>("Title"); 
	//ゲームをロードする。
	m_title->m_gameLoadFlag = true;
	return true;
}
   
// ステージ1シーン::更新処理。
void Stage1Scene::Update()  
{  
	if (m_stageClear != nullptr)
	{
		if (m_stageClear->GetIsClear() == true) // フラグを確認
		{
			// ステージクリアフラグが立っている場合、ステージ2へ遷移する。  
			SMGetIns()->SetRequest(SceneID::S_Stage2);
		}
	}

	//SceneManagerを経由してタイトル画面への遷移を要求していたら
	if (Scene_Manager::GetInstance()->GetRequest() == SceneID::S_Title)
	{
		//タイトル画面に遷移する
		SMGetIns()->SetRequest(SceneID::S_Title);
	}
}

// ステージ2シーン::初期化処理。
bool Stage2Scene::Start()
{
	SMGetIns()->SetRequest(SceneID::S_Stage2);

	// ステージ2の初期化処理を行う。
	m_stage2 = NewGO<Stage2>(0, "Stage2"); // ステージ2の初期化処理を行う。

	//プレイヤーを取得
	m_player = FindGO<Player>("player");
	if (m_player != nullptr)
	{
		//プレイヤーをステージ2の開始位置に移動
		m_player->SetPosition(Vector3(0.0f, 0.0f, 0.0f));
		//プレイヤーのステージクリアフラグをリセット
		m_player->m_stageClearFlag = false;
	}

	//カメラをステージ2の開始位置に移動
	g_camera3D->SetPosition(Vector3(0.0f, 300.0f, -800.0f));
	//カメラの注視点を設定
	g_camera3D->SetTarget(Vector3(0.0f, 0.0f, 0.0f));

	//フェードをフェードインに切り替える
	Fade* fade = FindGO<Fade>("fade");
	if (fade != nullptr)
	{
		fade->FadeTransition(enFadeState_FadeIn);
	}

	return true;
}

// ステージ2シーン::更新処理。
void Stage2Scene::Update()
{
	//SceneManagerを経由してゲームクリア画面への遷移を要求していたら
	if (Scene_Manager::GetInstance()->GetRequest() == SceneID::S_GameClear)
	{
		// ステージクリアフラグが立っている場合、ステージ2へ遷移する。  
		SMGetIns()->SetRequest(SceneID::S_GameClear);
	}

	//SceneManagerを経由してタイトル画面への遷移を要求していたら
	if (Scene_Manager::GetInstance()->GetRequest() == SceneID::S_Title)
	{
		//タイトル画面に遷移する
		SMGetIns()->SetRequest(SceneID::S_Title);
	}
}

bool GameClearScene::Start()
{
	// ゲームクリアシーンの初期化処理を行う。
	m_gameClear = NewGO<GameClear>(0, "GameClear"); // ゲームクリアシーンの初期化処理を行う。

	auto* game = FindGO<Game>("game");
	m_gameClear->SetGatheringItemNum(game->m_itemGetNum);
	m_gameClear->SetTotalItemNum(game->m_totalItemNum);
	DeleteGO(game);
	return true;
}

void GameClearScene::Update()
{
	//SceneManagerを経由してゲームクリア画面への遷移を要求していたら
	if (Scene_Manager::GetInstance()->GetRequest() == SceneID::S_Title)
	{
		// ステージクリアフラグが立っている場合、ステージ2へ遷移する。  
		SMGetIns()->SetRequest(SceneID::S_Title);
	}
}

// シーンマネージャー::初期化処理。
bool Scene_Manager::Start()
{

	return true;
}

// マネージャー::更新処理。
void Scene_Manager::Update()
{
	// IDが無効でない場合、シーン遷移を行う。
	if (requestSceneID != SceneID::Invalid)
	{
		ChangeScene(); // シーン遷移。
	}

	if (scene) scene->Update(); // シーンの更新処理を呼び出す。
}

// シーンマネージャー::初期化処理。
void Scene_Manager::ChangeScene()
{
	// 既存のシーンの解放。
	if (scene)
	{
		delete scene;
		scene = nullptr;
	}


	if (requestSceneID != SceneID::Invalid)
	{
		delete scene;

		switch (requestSceneID)
		{
		case SceneID::S_Title:
			 scene = new TitleScene(); // シーンの初期化。
			 requestSceneID = SceneID::Invalid; // シーン遷移後にリクエストを無効化。
		     break;
		case SceneID::S_Stage1:
			 scene = new Stage1Scene(); // シーンの初期化。
			 requestSceneID = SceneID::Invalid;
		     break;
		case SceneID::S_Stage2:
			scene = new Stage2Scene(); // シーンの初期化。
			requestSceneID = SceneID::Invalid;
			break;
		case SceneID::S_GameClear:
			scene = new GameClearScene(); // シーンの初期化。
			requestSceneID = SceneID::Invalid;
			break;
		default:
			break;
		}
	}
		
	// シーンが作られたら Start() を呼び出す。
	if (scene)
	{
		scene->Start(); // シーンの初期化処理を呼び出す。
		// リクエストされたシーンIDを無効化。
		requestSceneID = SceneID::Invalid;

	}

}