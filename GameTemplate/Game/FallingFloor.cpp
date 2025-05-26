#include "stdafx.h"
#include "FallingFloor.h"
#include "Player.h"

#include "Config.h"

bool FallingFloor::Start()
{
	string modelPath = m_filePathConfig->GetFullPath_3DModel("Stage2");// ファイルパスを読み込む。
	m_modelRender.Init(modelPath.c_str());// モデルをセットする。

	// 座標を設定する。
	m_modelRender.SetPosition(m_position);

	return true;// 戻り値を設定。
}

// 更新処理。
void FallingFloor::Update()
{
	Floor(); // 落下処理の更新。
	m_modelRender.Update();
}

// 落下処理。
void FallingFloor::Floor()
{
	m_modelRender.Update();// 更新処理。
}

// 描画処理。
void FallingFloor::Render(RenderContext& rc)
{
	m_modelRender.Draw(rc);// 描画処理。
}