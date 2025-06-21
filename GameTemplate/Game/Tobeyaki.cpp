#include "stdafx.h"
#include "Config.h"
#include "Tobeyaki.h"
#include"Player.h"
#include"Game.h"
#include "graphics/effect/EffectEmitter.h"
namespace
{
	const Vector3 SCALE{ 0.5f,0.5f,0.5f }; 
	const float DEG_X = -30.0f;
	const float DEG_Y = 2.0f;
}
bool Tobeyaki::Start() {

	string modelPath = m_config-> GetFullPath_Item("tobeyaki");// ファイルパスを読み込む。
	m_modelRender.Init(modelPath.c_str(), 0, 0, enModelUpAxisZ, false, true);// モデルをセットする。

	// エフェクトの初期化。
	EffectEngine::GetInstance()->ResistEffect(EffectList_ItemGet, u"Assets/effect/itemget.efk");

	m_player = FindGO<Player>("player");
	m_game = FindGO<Game>("game");
	m_modelRender.Update();
	m_rotation.SetRotationDegX(DEG_X);
	return true;
}
void Tobeyaki::Update() {
	Rotation();
	m_modelRender.SetPosition(m_position);
	m_modelRender.SetScale(SCALE);
	m_modelRender.Update();
	Vector3 deff = m_player->m_position - m_position;
	if (deff.Length() <= 130.0f) {
		m_player->tobeyakiCount += 1;

		//エフェクトの処理
		EffectEmitter* effectEmitter = NewGO<EffectEmitter>(0);
		effectEmitter->Init(EffectList_ItemGet);

		//エフェクトの位置の設定
		Vector3 itemLocalPos = { 0.0f,30.0f,0.0f };
		itemLocalPos += m_position;
		effectEmitter->SetPosition(itemLocalPos);

		//エフェクトの回転の設定
		Quaternion itemLocalRotX;
		Quaternion itemLocalRotY;
		Quaternion itemLocalRot;
		itemLocalRotX.SetRotationDegX(135.0f);
		itemLocalRotY.SetRotationDegY(60.0f);
		itemLocalRot = itemLocalRotX * itemLocalRotY;
		effectEmitter->SetRotation(itemLocalRot);

		//エフェクトの大きさの設定
		effectEmitter->SetScale({ 10.0f,10.0f,10.0f });

		//エフェクトの再生
		effectEmitter->Play();

		// アイテムを取得したの音の再生。
		g_gameSoundEngine->PlaySE(GameSoundList_SE_Object_ItemGet, 3.0f);

		m_game->m_itemGetNum++;
		DeleteGO(this);
	}
}
void Tobeyaki::Rotation() 
{
	m_rotation.AddRotationDegY(DEG_Y);
	
	m_modelRender.SetRotation(m_rotation);
}

void Tobeyaki::Render(RenderContext& rc) {
	m_modelRender.Draw(rc);
}
