#include "stdafx.h"
#include "StageClear.h"
#include "ClearPoint.h"
#include "Config.h"
#include "Player.h" 
#include "Scene.h"
#include "Fade.h"

namespace
{
   //モデルの大きさ。
   const Vector3 SCALE(5.0f, 5.0f, 5.0f);
}

// 開始処理
bool ClearPoint::Start()
{


	string modelPath = m_config->GetFullPath_3DModel("GoalPole");// ファイルパスを読み込む。
	m_modelRender.Init(modelPath.c_str());// モデルをセットする。

	m_player = FindGO<Player>("player");
	m_fade = FindGO<Fade>("fade");
	return true;
}

// 更新作業。
void ClearPoint::Update()
{

	m_modelRender.SetScale(SCALE);
	m_modelRender.SetPosition(position);
	m_modelRender.Update();
	
	//Playerがこのモデルと衝突するとGameClearを知らせる。
	Vector3 diff = position - m_player->m_position;

	// ゴールポールとプレイヤーの距離を測る
	if (diff.Length() < 20.0f)
	{
		// ステージクリアをnew
		StageClear_NewGO();
	}
}

// 描画処理。
void ClearPoint::Render(RenderContext& rc)
{
	m_modelRender.Draw(rc);
}

// NewGO。
void ClearPoint::StageClear_NewGO()
{
	// ステージクリアの処理を追加する場合はここに記述。
    // ゲームクリアのフラグを立てる。
	NewGO<StageClear>(0, "stageClear");
	m_stageClear = FindGO<StageClear>("stageClear");
	m_stageClear->SetIsClear(true);

	// ステージクリアの状態を確認する。
	if (m_stageClear->GetIsClear() == true)
	{
		DeleteGO(m_fade);
		DeleteGO(this);
	}

}