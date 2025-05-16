#include "stdafx.h"
#include "sinju.h"
#include "Config.h"
#include"Player.h"
namespace
{
	Vector3 SCALE = Vector3{ 0.5f,0.5f,0.5f };
}

bool sinju::Start() {

	string modelPath = m_config-> GetFullPath_Item("sinju");// ファイルパスを読み込む。
	m_modelRender.Init(modelPath.c_str(), 0, 0, enModelUpAxisZ, false, true);// モデルをセットする。

	m_player = FindGO<Player>("player");
	m_modelRender.Update();
	m_rotation.SetRotationDegX(-30.0f);
	return true;
}
void sinju::Update() {
	Rotation();
	m_modelRender.SetPosition(m_position);
	m_modelRender.SetScale(SCALE);
	m_modelRender.Update();
	Vector3 deff = m_player->m_position - m_position;
	if (deff.Length() <= 125.0f) {
		//m_player->taoruCount += 1;
		DeleteGO(this);
	}
}
void sinju::Rotation() {
	m_rotation.AddRotationDegY(2.0f);
	m_modelRender.SetRotation(m_rotation);
}
void sinju::Render(RenderContext& rc) {
	m_modelRender.Draw(rc);
}