#include "stdafx.h"
#include "StageClear.h"
#include "ClearPoint.h"
#include "Config.h"
#include "Player.h" 
#include "Scene.h"
namespace
{
   //モデルの大きさ。
   const Vector3 SCALE(5.0f, 5.0f, 5.0f);
}

ClearPoint::ClearPoint()
{


	string modelPath = m_config->GetFullPath_3DModel("GoalPole");// ファイルパスを読み込む。
	m_modelRender.Init(modelPath.c_str());// モデルをセットする。

	m_player = FindGO<Player>("player");

	m_stageClear = FindGO<StageClear>("stageClear");
}

// 更新作業。
void ClearPoint::Update()
{

	m_modelRender.SetScale(SCALE);
	m_modelRender.SetPosition(position);
	m_modelRender.Update();
	
	//Playerがこのモデルと衝突するとGameClearを知らせる。
	Vector3 diff = position - m_player->m_position;

	if (diff.Length() < 20.0f)
	{
		StageClear_NewGO();
	}
	//// ゲームクリアのフラグを立てる。
	//m_stageClear->SetIsClear(true);

}

// 描画処理。
void ClearPoint::Render(RenderContext& rc)
{
	m_modelRender.Draw(rc);
}

// NewGO。
void ClearPoint::StageClear_NewGO()
{

	//Playerがこのモデルと衝突するとGameClearを知らせる。
	Vector3 diff = position - m_player->m_position;

	if (diff.Length() < 20.0f)
	{
		NewGO<StageClear>(0, "stageClear");
		DeleteGO(this);
	}

}