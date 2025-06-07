#include "stdafx.h"
#include "Enemy.h"
#include "Player.h"
#include "Config.h"
#include "Game.h"
#include "GameOver.h"
bool Enemy::Start() {
	animationclip[enAnimationclip_idle].Load("Assets/modelData/YoshinagaAssets/SkeletonAnim/SkeletonIdle.tka");
	animationclip[enAnimationclip_idle].SetLoopFlag(true);
	animationclip[enAnimationclip_walk].Load("Assets/modelData/YoshinagaAssets/SkeletonAnim/SkeletonWalk.tka");
	animationclip[enAnimationclip_walk].SetLoopFlag(true);
	animationclip[enAnimationclip_death].Load("Assets/modelData/YoshinagaAssets/SkeletonAnim/SkeletonDeath.tka");
	animationclip[enAnimationclip_death].SetLoopFlag(false);
	m_modelrender.Init("Assets/modelData/YoshinagaAssets/Skeleton/Skeleton.tkm",animationclip, enAnimationclip_num, enModelUpAxisY, true);
	m_modelrender.SetScale(Vector3(10.0f, 10.0f, 10.0f));
	charactercontroller.Init(30.0f, 70.0f, m_position);
	m_modelrender.SetPosition(m_position);
	m_modelrender.Update();
	m_player = FindGO<Player>("player");
	m_game = FindGO<Game>("game");
	return true;
}
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

void Enemy::Rotation() {
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
void Enemy::EnemyAnimation() {
	switch (Enemyanimationstate) {
	case 0:
		m_modelrender.PlayAnimation(enAnimationclip_walk,0.1f);
		break;
	
	case 1:
		m_modelrender.PlayAnimation(enAnimationclip_death, 0.1f);
		break;
	}
}




void Enemy::Update() {
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

			//プレイヤーが敵を踏んだ時の音を再生。
			g_gameSoundEngine->PlaySE(GameSoundList_SE_Player_StepOnEnemy, 1.0f);
		}
		else {
			//プレイヤーに触れた
			m_touchPlayerFlag = true;
		}
	}

}
void Enemy::Render(RenderContext& rc) {
	m_modelrender.Draw(rc);
}