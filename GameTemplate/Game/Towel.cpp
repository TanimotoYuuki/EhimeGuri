#include "stdafx.h"
#include "Towel.h"
#include"Player.h"
namespace
{
	Vector3 SCALE = Vector3{ 2.0f,2.0f,3.0f }; // 大きさ。
}

bool Towel::Start()
{
	m_modelRender.Init("Assets/modelData/Stage/Assets/Towel.tkm", 0, 0, enModelUpAxisZ, false, true);
	m_player = FindGO<Player>("player");
	m_modelRender.Update();
	return true;
}

// 更新作業。
void Towel::Update()
{
	Rotation();
	m_modelRender.SetScale(SCALE);
	m_modelRender.SetPosition(m_position);
	m_modelRender.Update();
	Vector3 deff = m_player->m_position - m_position;
	if (deff.Length() <= 100.0f) {
		m_player->taoruCount = 1;
		DeleteGO(this);
	}
}

// 回転処理。
void Towel::Rotation()
{
	m_Rot.AddRotationDegY(2.0f);
	m_modelRender.SetRotation(m_Rot);
}

// 描画処理。
void Towel::Render(RenderContext& rc)
{
	m_modelRender.Draw(rc);
}