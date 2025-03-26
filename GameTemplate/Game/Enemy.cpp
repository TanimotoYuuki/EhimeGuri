#include "stdafx.h"
#include "Enemy.h"
#include "Player.h"
#include "Game.h"
#include"GameOver.h"
bool Enemy::Start() {
	animationclip[enAnimationclip_idle].Load("Assets/modelData/YoshinagaAssets/SkeletonAnim/SkeletonIdle.tka");
	animationclip[enAnimationclip_idle].SetLoopFlag(true);
	animationclip[enAnimationclip_walk].Load("Assets/modelData/YoshinagaAssets/SkeletonAnim/SkeletonWalk.tka");
	animationclip[enAnimationclip_walk].SetLoopFlag(true);
	m_modelrender.Init("Assets/modelData/YoshinagaAssets/Skeleton/Skeleton.tkm",
		animationclip, enAnimationclip_num, enModelUpAxisY);
	m_modelrender.SetScale(Vector3(10.0f, 10.0f, 10.0f));
	charactercontroller.Init(30.0f, 100.0f, m_position);
	m_modelrender.SetPosition(m_position);
	m_modelrender.Update();
	m_player = FindGO<Player>("player");
	m_game = FindGO<Game>("game");
	return true;
}
void Enemy::Move() {
	if (Enemystate == 0) {
		movespeed.x = 2.0f;
	}
	else if (Enemystate == 1) {
		movespeed.x = -2.0f;
	}
	if (m_position.x >= firstposition.x + 200.0f)
	{
		Enemystate = 1;
	}
	else if (m_position.x <= firstposition.x - 200.0f)
	{
		Enemystate = 0;
	}
	m_position = charactercontroller.Execute(movespeed, 1.0f);
}
void Enemy::Rotation() {
	if (Enemystate == 0) {
		rotation.SetRotationDegY(90.0f);
		Enemystate == 1;
	}
	else if (Enemystate == 1) {
		rotation.SetRotationDegY(270.0f);
		Enemystate == 0;
	}
	//rotation.SetRotationDegX(270.0f);
	rotation.AddRotationDegX(-180.0f);
	//ŠG•`‚«‚³‚ñ‚É‰ñ“]‚ð‹³‚¦‚éB
	m_modelrender.SetRotation(rotation);
}
void Enemy::EnemyAnimation() {
	switch (Enemystate) {
	case 0:
		m_modelrender.PlayAnimation(enAnimationclip_walk);
		break;
	case 1:
		m_modelrender.PlayAnimation(enAnimationclip_walk);
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
	if (diff.Length() <= 60.0f) {
		NewGO<GameOver>(0, "gameover");
		DeleteGO(m_game);
	}
}
void Enemy::Render(RenderContext& rc) {
	m_modelrender.Draw(rc);
}