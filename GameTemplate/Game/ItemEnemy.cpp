#include "stdafx.h"
#include "ItemEnemy.h"
#include "Player.h"
#include "Game.h"
#include "GameOver.h"
#include"Mikan.h"
#include"Taruto.h"
#include "graphics/effect/EffectEmitter.h"
bool ItemEnemy::Start() {
	animationclip[enAnimationclip_idle].Load("Assets/modelData/YoshinagaAssets/SkeletonAnim/SkeletonIdle.tka");
	animationclip[enAnimationclip_idle].SetLoopFlag(true);
	animationclip[enAnimationclip_walk].Load("Assets/modelData/YoshinagaAssets/SkeletonAnim/SkeletonWalk.tka");
	animationclip[enAnimationclip_walk].SetLoopFlag(true);
	animationclip[enAnimationclip_death].Load("Assets/modelData/YoshinagaAssets/SkeletonAnim/SkeletonDeath.tka");
	animationclip[enAnimationclip_death].SetLoopFlag(false);
	m_modelrender.Init("Assets/modelData/YoshinagaAssets/Skeleton/Skeleton.tkm",
		animationclip, enAnimationclip_num, enModelUpAxisY, true);
	m_modelrender.SetScale(Vector3(10.0f, 10.0f, 10.0f));
	charactercontroller.Init(30.0f, 70.0f, m_position);
	m_modelrender.SetPosition(m_position);
	m_modelrender.Update();
	// エフェクトの初期化。
	EffectEngine::GetInstance()->ResistEffect(EffectList_EnemyHit, u"Assets/effect/enemyhiteffect.efk");
	m_player = FindGO<Player>("player");
	m_game = FindGO<Game>("game");
	return true;
}
void ItemEnemy::Move() {
	if (Enemystate == 0) {
		movespeed.x = -2.0f;
	}
	else if (Enemystate == 1) {
		movespeed.x = 2.0f;
	}
	if (m_position.x >= firstposition.x + 100.0f)
	{
		Enemystate = 0;
	}
	else if (m_position.x <= firstposition.x - 100.0f)
	{
		Enemystate = 1;
	}
	if (Enemyanimationstate == 1) {
		movespeed.x = 0;
		if (!m_modelrender.IsPlayingAnimation())
		{
			DeleteGO(this);
		}
	}
	m_position = charactercontroller.Execute(movespeed, 1.0f);
	float glavity = 3.0f;
	if (charactercontroller.IsOnGround()) {
		//重力をなくす
		movespeed.y = 0.0f;
	}
	movespeed.y -= glavity;
}

void ItemEnemy::Rotation() {
	if (Enemystate == 0) {
		rotation.SetRotationDegY(270.0f);
		//Enemystate = 1;
	}
	else if (Enemystate == 1) {
		rotation.SetRotationDegY(90.0f);
		//Enemystate = 0;
	}
	//rotation.SetRotationDegX(270.0f);
	rotation.AddRotationDegX(-180.0f);
	//絵描きさんに回転を教える。
	m_modelrender.SetRotation(rotation);
}
void ItemEnemy::EnemyAnimation() {
	switch (Enemyanimationstate) {
	case 0:
		m_modelrender.PlayAnimation(enAnimationclip_walk, 0.1f);
		break;

	case 1:
		m_modelrender.PlayAnimation(enAnimationclip_death, 0.1f);
		break;
	}
}




void ItemEnemy::Update() {
	Move();
	Rotation();
	EnemyAnimation();

	m_modelrender.SetPosition(m_position);
	m_modelrender.Update();
	Vector3 diff = m_player->m_position - m_position;
	if (diff.Length() <= 100.0f && Enemyanimationstate != 1) {
		if (m_player->m_characterController.IsOnGround() == false) {
			Enemyanimationstate = 1;
			m_player->m_moveSpeed.y = 500.0f;
			charactercontroller.RemoveRigidBoby();
			//現在ステージ1をプレイしているとき
			if (m_game->GetStageState() == m_game->enStageState_Stage1)
			{
				NewGO<Mikan>(0, "mikan");
				m_mikan = FindGO<Mikan>("mikan");
				m_mikan->m_position = m_position;
				m_mikan->m_position.y = m_position.y + 45.0f;
			}
			//現在ステージ2をプレイしているとき
			else if (m_game->GetStageState() == m_game->enStageState_Stage2)
			{
				NewGO<Taruto>(0, "taruto");
				m_taruto = FindGO<Taruto>("taruto");
				m_taruto->m_position = m_position;
				m_taruto->m_position.y = m_position.y + 45.0f;
			}

			//エフェクトの処理
			EffectEmitter* effectEmitter = NewGO<EffectEmitter>(0);
			effectEmitter->Init(EffectList_EnemyHit);

			//エフェクトの位置の設定
			Vector3 enemyLocalPos = { 0.0f,120.0f,0.0f };
			enemyLocalPos += m_position;
			effectEmitter->SetPosition(enemyLocalPos);

			//エフェクトの大きさの設定
			effectEmitter->SetScale({ 30.0f,30.0f,30.0f });

			//エフェクトの再生
			effectEmitter->Play();

			//プレイヤーが敵を踏んだ時の音を再生。
			g_gameSoundEngine->PlaySE(GameSoundList_SE_Player_StepOnEnemy, 1.0f);
		}
		else {
			//プレイヤーに触れた。
			m_touchPlayerFlag = true;
		}
	}

}
void ItemEnemy::Render(RenderContext& rc) {
	m_modelrender.Draw(rc);
}