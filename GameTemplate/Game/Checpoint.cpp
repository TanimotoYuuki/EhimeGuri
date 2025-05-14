#include "stdafx.h"
#include "Checpoint.h"
#include"Player.h"
#include"Config.h"
namespace
{
	Vector3 SCALE = Vector3(2.0f, 2.0f, 2.0f);
}
bool Checpoint::Start() {
	string modelPath = m_filePathConfig->GetFullPath("GoalPole");// ファイルパスを読み込む。
	m_modelRender.Init(modelPath.c_str());// モデルをセットする。
	m_player = FindGO<Player>("player");
	m_modelRender.Update();
	return true;
}
void Checpoint::Update() {
	m_modelRender.SetScale(SCALE);
	m_modelRender.SetPosition(position);
	m_modelRender.Update();

	Vector3 diff;
	diff.x = position.x - m_player->m_position.x;
	if (diff.Length() < 20.0f)
	{
		m_player->checcount = 1;
		DeleteGO(this);
	}
}
void Checpoint::Render(RenderContext& rc) {
	m_modelRender.Draw(rc);
}
