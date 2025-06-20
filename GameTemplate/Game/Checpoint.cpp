#include "stdafx.h"
#include "Checpoint.h"
#include "Player.h" 
#include "Config.h"
#include "graphics/effect/EffectEmitter.h"
namespace
{
	const Vector3 SCALE(2.0f, 2.0f, 2.0f);
}
bool Checpoint::Start() {
	string modelPath = m_config->GetFullPath_3DModel("GoalPole");// ファイルパスを読み込む。
	m_modelRender.Init(modelPath.c_str());// モデルをセットする。
	// エフェクトの初期化。
	EffectEngine::GetInstance()->ResistEffect(EffectList_CheckPointGet, u"Assets/effect/checkpointget.efk");
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

	Vector3 diff;
	diff.x = position.x - m_player->m_position.x;
	if (diff.Length() < 20.0f)
	{
		m_player->checcount = 1;

		//エフェクトの処理
		EffectEmitter* effectEmitter = NewGO<EffectEmitter>(0);
		effectEmitter->Init(EffectList_CheckPointGet);

		//エフェクトの位置の設定
		Vector3 checPointLocalPos = { 0.0f,30.0f,0.0f };
		checPointLocalPos += position;
		effectEmitter->SetPosition(checPointLocalPos);

		//エフェクトの大きさの設定
		effectEmitter->SetScale({ 10.0f,10.0f,10.0f });

		//エフェクトの再生
		effectEmitter->Play();

		//中間地点を通過した時の音の再生。
		g_gameSoundEngine->PlaySE(GameSoundList_SE_Object_PassingCheckPoint, 1.0f);
		DeleteGO(this);
	}
}
void Checpoint::Render(RenderContext& rc) {
	m_modelRender.Draw(rc);
}
