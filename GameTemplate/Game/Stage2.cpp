#include "stdafx.h"
#include "Stage2.h"
#include "Config.h"
#include "FallingFloor.h"
#include "MovingNeedle.h"
#include "RotationFloor.h"
#include "Tower.h"
#include "Player.h"
#include "level3DRender.h"
#include "StairsInTheForest.h"
#include <string>
using namespace std;

namespace
{
	const Vector3 SCALE{ 6.5f, 6.5f, 6.5f };// モデルの大きさ。
	const Vector3 COLLISION_HEIGHT(0.0f, 250.0f, 0.0f);// コリジョンの高さ。
	const Vector3 COLLISION_SIZE(500.0f, 3.0f, 225.0f);// コリジョンの大きさ。
}


bool Stage2::Start()
{
	//Configの初期化
	m_filePathConfig = NewGO<Config>(0, "config");

	//モデルの初期化
	m_modelRender.Init("Assets/level3D/Stage2.tkm", 0, 0, enModelUpAxisZ, false, true);
	m_modelRender.SetScale(SCALE);// スケールのセット。

	//レベルオブジェクトのロード
	//LevelRender();


	m_modelRender.Update();// モデルの更新。
	m_physicsStaticObject.CreateFromModel(m_modelRender.GetModel(),m_modelRender.GetModel().GetWorldMatrix());

	m_player = FindGO<Player>("player");
	return true;
}

// 更新処理。
void Stage2::Update()
{
	m_modelRender.Update();// モデルの更新。

	//ステージクリアとゲームオーバーの時は処理しない
	if (m_player->m_stageClearFlag == true ||
		m_player->m_gameOverFlag == true
		)
	{
		return;
	}

	//ステージ2BGMの再生。
	g_gameSoundEngine->PlayBGM(GameSoundList_BGM_Stage2, 1.0f);
}

// 描画処理。
void Stage2::Render(RenderContext& rc)
{
	m_level3DRender.Draw(rc);// レベルの描画。
	m_modelRender.Draw(rc);// モデルの描画。
}