#include "stdafx.h"
#include "Config.h"
#include "Towel.h"
#include"Player.h"
#include"Game.h"
namespace
{
	const Vector3 SCALE{ 0.07f,0.07f,0.08f }; // 大きさ。
}

bool Towel::Start()
{
	
	string modelPath = m_config-> GetFullPath_3DModel("Towel");// ファイルパスを読み込む。
	m_modelRender.Init(modelPath.c_str(), 0, 0, enModelUpAxisZ, false, true);// モデルをセットする。

	m_player = FindGO<Player>("player");
	m_game = FindGO<Game>("game");
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

		//アイテムテキスト関連UIを描画する
		m_game->m_itemTextDrawingUI = m_game->enItem_Taoru;
		m_game->ItemTextSpriteMoveReset();

		// アイテムを取得したの音の再生。
		g_gameSoundEngine->PlaySE(GameSoundList_SE_Object_ItemGet, 3.0f);

		m_game->m_itemGetNum++;
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