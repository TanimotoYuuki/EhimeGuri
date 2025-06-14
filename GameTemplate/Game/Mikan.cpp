#include "stdafx.h"
#include "Config.h"
#include "Mikan.h"
#include"Player.h"
#include"Game.h"
namespace
{
	const Vector3 SCALE{ 0.5f,0.5f,0.5f };
}
bool Mikan::Start() {

	string modelPath = m_config->GetFullPath_Item("mikan");// ファイルパスを読み込む。
	m_modelRender.Init(modelPath.c_str(), 0, 0, enModelUpAxisZ, false, true);// モデルをセットする。
	
	m_player = FindGO<Player>("player");
	m_game = FindGO<Game>("game");
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
			m_player->mikanCount += 1;

			// アイテムを取得したの音の再生。
			g_gameSoundEngine->PlaySE(GameSoundList_SE_Object_ItemGet, 3.0f);

			m_game->m_itemGetNum++;
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
