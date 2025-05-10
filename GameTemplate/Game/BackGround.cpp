#include "stdafx.h"
#include "BackGround.h"

namespace
{
	Vector3 BACKGROUND_SCALE = Vector3(10.0f, 10.0f, 10.0f);
}

bool BackGround::Start()
{
	m_backGroundRender.Init("Assets/modelData/Stage/Assets/Stage1.tkm", 0, 0, enModelUpAxisZ, false, true);
	m_backGroundRender.SetScale(BACKGROUND_SCALE);
	m_backGroundRender.Update();
	//当たり判定を作成
	m_physicsSraricObject.CreateFromModel(m_backGroundRender.GetModel(), m_backGroundRender.GetModel().GetWorldMatrix());
	return true;
}

// 描画処理。
void BackGround::Render(RenderContext& rc)
{
	m_backGroundRender.Draw(rc);
}