#include "stdafx.h"
#include "Enemy.h"
#include "Player.h"
#include "Config.h"
#include "Game.h"
#include "GameOver.h"

namespace
{
	// キャラコンの定数。
	const float RADIUS = 25.0f;
	const float HEIGHT = 100.0f;

	// EnemyStateの定数。
	const float ENEMYSTATE_ZERO = 270.0f;
	const float ENEMYSTATE_ONE = 90.0f;
	const float ENEMYSTATE_TWO = -180.0f;

	// スケール。
	const Vector3 SCALE(10.0f, 10.0f, 10.0f);
}

// アニメーションメソッド。
const::std::string Enemy:: GetFullPath_EnemyAnimation(EnAnimationClip enemyAnimation, const std::string& animationName, bool flag)
{
	std::string Animation = ENEMY_ANIMATION + animationName + ANIMATION_FILE_EXTENSION;

	// アニメーションのロード。
	m_animationclip[enemyAnimation].Load(Animation.c_str());
	m_animationclip[enemyAnimation].SetLoopFlag(flag);

	return Animation;
}

// 初期化処理。
bool Enemy::Start() 
{

	// アニメーションの設定。
	SetEnemyAnimation();

	// モデルの初期化。
	m_modelrender.Init("Assets/modelData/YoshinagaAssets/Skeleton/Skeleton.tkm",m_animationclip, enAnimationclip_num, enModelUpAxisY, true);

	// 大きさをセット。
	m_modelrender.SetScale(SCALE);

	// キャラコン。
	charactercontroller.Init(RADIUS, HEIGHT, m_position);

	// 座標をセット。
	m_modelrender.SetPosition(m_position);

	// 更新処理。
	m_modelrender.Update();

	// 探索処理。
	m_player = FindGO<Player>("player");
	m_game = FindGO<Game>("game");

	return true;
}

// 更新処理。
void Enemy::Update()
{
	// 動作処理。
	Move();

	// 回転処理。
	Rotation();

	// アニメーション。
	EnemyAnimation();

	// モデルをセット。
	m_modelrender.SetPosition(m_position);

	// 更新処理。
	m_modelrender.Update();

	Vector3 diff = m_player->m_position - m_position;
	if (diff.Length() <= 100.0f && Enemyanimationstate != 1)
	{
		if (m_player->m_characterController.IsOnGround() == false)
		{
			Enemyanimationstate = 1;
			m_player->m_moveSpeed.y = 500.0f;
			charactercontroller.RemoveRigidBoby();

			//プレイヤーが敵を踏んだ時の音を再生。
			g_gameSoundEngine->PlaySE(GameSoundList_SE_Player_StepOnEnemy, 1.0f);
		}
		else
		{
			//プレイヤーに触れた
			m_touchPlayerFlag = true;
		}
	}

}

// 動作処理。
void Enemy::Move() {
	if (Enemystate == 0) {
		movespeed.x = -2.0f;
	}
	else if (Enemystate == 1) {
		movespeed.x = 2.0f;
	}
	if (m_position.x >= firstposition.x + 200.0f)
	{
		Enemystate = 0;
	}
	else if (m_position.x <= firstposition.x - 200.0f)
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

// 回転処理。
void Enemy::Rotation() {
	if (Enemystate == 0) {
		rotation.SetRotationDegY(ENEMYSTATE_ZERO);
	}
	else if (Enemystate == 1) {
		rotation.SetRotationDegY(ENEMYSTATE_ONE);
	}
	rotation.AddRotationDegX(ENEMYSTATE_TWO);
	//絵描きさんに回転を教える。
	m_modelrender.SetRotation(rotation);
}

// Enemyのアニメーション。
void Enemy::EnemyAnimation()
{
	switch (Enemyanimationstate) 
	{
	case 0:
		m_modelrender.PlayAnimation(enAnimationclip_walk,0.1f);
		break;
	
	case 1:
		m_modelrender.PlayAnimation(enAnimationclip_death, 0.1f);
		break;
	}
}

// 描画処理。
void Enemy::Render(RenderContext& rc)
{
	m_modelrender.Draw(rc);
}

// アニメーションの再生。
void Enemy::SetEnemyAnimation()
{
	// 待機モーション。
	GetFullPath_EnemyAnimation(enAnimationclip_idle, "SkeletonIdle", true);

	// 歩きモーション。
	GetFullPath_EnemyAnimation(enAnimationclip_walk, "SkeletonWalk", true);

	// 死亡モーション。
	GetFullPath_EnemyAnimation(enAnimationclip_death, "SkeletonDeath", false);

}