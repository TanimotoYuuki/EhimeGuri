#include "stdafx.h"
#include "ItemEnemy.h"
#include "Player.h"
#include "Game.h"
#include "GameOver.h"
#include"Mikan.h"
#include"Taruto.h"

namespace
{
	// ステート0。
	const float STATE_ZERO_DEG(270.0f);
	// ステート1。
	const float STATE_ONE_DEG(90.0f);
	// 加算回転軸。
	const float ADD_ROD(-180.0f);
	// 重力。
	const float GLAVITY(3.0f);
	// 大きさ。
	const Vector3 SCALE(10.0f, 10.0f, 10.0f);

// キャラコン。
	const float CHARACON_RADIUS = 30.0f;
	const float CHARACON_HEIGHT = 70.0f;
}

// アニメーションをセットするメソッド。
const std::string ItemEnemy::GetFullPaht_Animation(Enannimation enAnimationClip, const std::string& animationName, bool flag)
{
	std::string Animation = FileParh + animationName + tka;

	animationclip[enAnimationClip].Load(Animation.c_str());
	animationclip[enAnimationClip].SetLoopFlag(flag);

	return Animation;
}

bool ItemEnemy::Start() 
{
	// アニメーションをセットする。
	//SetAnimation();

	animationclip[enAnimationclip_idle].Load("Assets/modelData/YoshinagaAssets/SkeletonAnim/SkeletonIdle.tka");
	animationclip[enAnimationclip_idle].SetLoopFlag(true);
	animationclip[enAnimationclip_walk].Load("Assets/modelData/YoshinagaAssets/SkeletonAnim/SkeletonWalk.tka");
	animationclip[enAnimationclip_walk].SetLoopFlag(true);
	animationclip[enAnimationclip_death].Load("Assets/modelData/YoshinagaAssets/SkeletonAnim/SkeletonDeath.tka");
	animationclip[enAnimationclip_death].SetLoopFlag(false);

	// モデルをセット。
	m_modelrender.Init("Assets/modelData/YoshinagaAssets/Skeleton/Skeleton.tkm",
		animationclip, enAnimationclip_num, enModelUpAxisY, true);

	// 大きさをセット。
	m_modelrender.SetScale(SCALE);

	// キャラコンのセット。
	charactercontroller.Init(CHARACON_RADIUS, CHARACON_HEIGHT, m_position);

	// 座標をセット。
	m_modelrender.SetPosition(m_position);

	// 更新処理。
	m_modelrender.Update();

	// 探索処理。
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
	if (charactercontroller.IsOnGround()) {
		//重力をなくす
		movespeed.y = 0.0f;
	}
	movespeed.y -= GLAVITY;
}

void ItemEnemy::Rotation() {
	if (Enemystate == 0) {
		rotation.SetRotationDegY(STATE_ZERO_DEG);
	}
	else if (Enemystate == 1) {
		rotation.SetRotationDegY(STATE_ONE_DEG);
	}
	rotation.AddRotationDegX(ADD_ROD);
	//絵描きさんに回転を教える。	
	m_modelrender.SetRotation(rotation);
}

void ItemEnemy::EnemyAnimation() 
{
	switch (Enemyanimationstate)
	{
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

// アニメーションをセットする。
void ItemEnemy::SetAnimation()
{
	// 待機モーション。
	GetFullPaht_Animation(enAnimationclip_idle,"SkeletonIdle", true);

	// 歩きモーション。
	GetFullPaht_Animation(enAnimationclip_idle, "SkeletonWalk", true);

	// 死亡モーション。
	GetFullPaht_Animation(enAnimationclip_idle, "SkeletonDeath", false);

}