#include "stdafx.h"
#include "Stage1.h"
#include "Config.h"
namespace
{
	const Vector3 BACKGROUND_SCALE(10.0f, 10.0f, 10.0f);
}

bool Stage1::Start()
{
	string modelPath = m_config->GetFullPath_3DModel("Stage1");// ファイルパスを読み込む。
    m_backGroundRender.Init(modelPath.c_str(), 0, 0, enModelUpAxisZ, false, true);// モデルをセットする。

	m_backGroundRender.SetScale(BACKGROUND_SCALE);
	m_backGroundRender.Update();
	//当たり判定を作成
	m_physicsSraricObject.CreateFromModel(m_backGroundRender.GetModel(), m_backGroundRender.GetModel().GetWorldMatrix());

	return true;
}

// 更新処理。
void Stage1::Update()
{
	m_backGroundRender.Update();
}

// 描画処理。
void Stage1::Render(RenderContext& rc)
{
	m_backGroundRender.Draw(rc);
}