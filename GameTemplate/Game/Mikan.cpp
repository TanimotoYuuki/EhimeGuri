#include "stdafx.h"
#include "Mikan.h"
#include"Player.h"
namespace
{
	Vector3 SCALE = Vector3{ 0.5f,0.5f,0.5f };
}
bool Mikan::Start() {
	m_modelRender.Init("Assets/modelData/tokusannhinn/mikan.tkm", 0, 0, enModelUpAxisZ, false, true);
	m_player = FindGO<Player>("player");
	m_modelRender.Update();
	m_rotation.SetRotationDegX(-30.0f);
	return true;
}
void Mikan::Update() {
	Rotation();
	m_modelRender.SetPosition(m_position);
	m_modelRender.SetScale(SCALE);
	m_modelRender.Update();
	Vector3 deff = m_player->m_position - m_position;
	if (m_player->m_characterController.IsOnGround())
	{
		if (deff.Length() <= 70.0f) {
			//m_player->taoruCount += 1;
			DeleteGO(this);
		}
	}
}
void Mikan::Rotation() {
	m_rotation.AddRotationDegY(2.0f);
	m_modelRender.SetRotation(m_rotation);
}
void Mikan::Render(RenderContext& rc) {
	m_modelRender.Draw(rc);
}
