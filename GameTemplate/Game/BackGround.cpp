#include "stdafx.h"
#include "BackGround.h"
#include "Config.h"
namespace
{
	Vector3 BACKGROUND_SCALE = Vector3(10.0f, 10.0f, 10.0f);
}

bool BackGround::Start()
{
	string modelPath = m_config->GetFullPath_3DModel("Stage1");// ファイルパスを読み込む。
    m_backGroundRender.Init(modelPath.c_str());// モデルをセットする。

	m_backGroundRender.SetScale(BACKGROUND_SCALE);
	m_backGroundRender.Update();
	//当たり判定を作成
	m_physicsSraricObject.CreateFromModel(m_backGroundRender.GetModel(), m_backGroundRender.GetModel().GetWorldMatrix());
//	m_physicsStaticObject.GetbtCollisionObject()->setUserIndex(enCollisionAttr_Stage1);

	return true;
}

// 更新処理。
void BackGround::Update()
{
	m_backGroundRender.Update();
}

// 描画処理。
void BackGround::Render(RenderContext& rc)
{
	m_backGroundRender.Draw(rc);
}