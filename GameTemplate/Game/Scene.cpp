#include "stdafx.h"
#include "Scene.h"
#include "Stage1.h"
#include "Stage2.h"
Scene_Manager* Scene_Manager::instance = nullptr; // シングルトンインスタンスの初期化

bool Scene::Start()
{
	return true;
}

bool TitleScene::Start()
{
	// タイトルシーンの初期化処理を行う。
	 m_title =NewGO<Title>(0, "Title"); // タイトルシーンの初期化処理を行う。
	return true;
}

bool Stage1Scene::Start()
{
	// ステージ1の初期化処理を行う。
    m_stage1 = NewGO<Stage1>(0, "Stage1"); // ステージ1の初期化処理を行う。

	return true;
}

bool Stage2Scene::Start()
{
	// ステージ2の初期化処理を行う。
	m_stage2 = NewGO<Stage2>(0, "Stage2"); // ステージ2の初期化処理を行う。
	return true;
}

bool Scene_Manager::Start()
{

	return true;
}

void Scene::Update()
{
	// シーンマネージャーのUpdateを呼び出す。
	Scene_Manager::GetInstance()->Update();
}

// タイトルシーン::更新処理。
void TitleScene::Update()  
{  
	//Titleメニューのスタートが押されているかでステージ遷移を判定する。
	if (g_pad[0]->IsPress(enButtonA))
	{
		// ステージ1へ遷移する。
		Scene_Manager::GetInstance()->SetRequest(SceneID::S_Stage1);
	}
}

void Stage1Scene::Update()  
{  
	// ステージをクリアしたかの判定を行う  
	//if (g_pad[0]->IsPress(enButtonA)) // ステージクリアの条件を判定する。
	//{
	//	// ステージクリアフラグが立っている場合、ステージ2へ遷移する。
	//	Scene_Manager::GetInstance()->SetRequest(SceneID::S_Stage2);
	//}  
}

// ステージ2シーン::更新処理。
void Stage2Scene::Update()
{
	// ステージをクリアしたかの判定を行う。

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

// シーンの初期化処理。
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