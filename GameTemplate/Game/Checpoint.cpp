#include "stdafx.h"
#include "Checpoint.h"
#include "Player.h" 
#include "Config.h"
namespace
{
	const Vector3 SCALE(2.0f, 2.0f, 2.0f);
}
bool Checpoint::Start() {
	string modelPath = m_config->GetFullPath_3DModel("GoalPole");// ファイルパスを読み込む。
	m_modelRender.Init(modelPath.c_str());// モデルをセットする。
	m_player = FindGO<Player>("player");
	m_modelRender.Update();
	m_config = FindGO<Config>("config");
	return true;
}
void Checpoint::Update() 
{
	m_modelRender.SetScale(SCALE);
	m_modelRender.SetPosition(position);
	m_modelRender.Update();

}
void Checpoint::Render(RenderContext& rc) {
	m_modelRender.Draw(rc);
}
