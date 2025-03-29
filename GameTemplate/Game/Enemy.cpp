#include "stdafx.h"
#include "Enemy.h"
#include "Player.h"
#include "Game.h"
#include"GameOver.h"
#include"Needle.h"
#include"FallingBlock.h"
#include"ScaffoldBlock.h"
#include"MovingFloor.h"
#include"GameCamera.h"
bool Enemy::Start() {
	animationclip[enAnimationclip_idle].Load("Assets/modelData/YoshinagaAssets/SkeletonAnim/SkeletonIdle.tka");
	animationclip[enAnimationclip_idle].SetLoopFlag(true);
	animationclip[enAnimationclip_walk].Load("Assets/modelData/YoshinagaAssets/SkeletonAnim/SkeletonWalk.tka");
	animationclip[enAnimationclip_walk].SetLoopFlag(true);
	m_modelrender.Init("Assets/modelData/YoshinagaAssets/Skeleton/Skeleton.tkm",
		animationclip, enAnimationclip_num, enModelUpAxisY);
	m_modelrender.SetScale(Vector3(10.0f, 10.0f, 10.0f));
	charactercontroller.Init(30.0f, 70.0f, m_position);
	m_modelrender.SetPosition(m_position);
	m_modelrender.Update();
	m_player = FindGO<Player>("player");
	m_game = FindGO<Game>("game");
	m_needle = FindGO<Needle>("needle");
	m_fallingblock = FindGO<FallingBlock>("fallingblock");
	m_movingfloor = FindGO<MovingFloor>("movingfloor");
	m_gamecamera = FindGO<GameCamera>("gamecamera");
	return true;
}
void Enemy::Move() {
	if (Enemystate == 0) {
		movespeed.x = -2.0f;
	}
	else if (Enemystate == 1) {
		movespeed.x = 2.0f;
	}
	/*if (m_position.x >= firstposition.x + 200.0f)
	{
		Enemystate = 0;
	}
	else if (m_position.x <= firstposition.x - 200.0f)
	{
		Enemystate = 1;
	}*/
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
	switch (Enemystate) {
	case 0:
		m_modelrender.PlayAnimation(enAnimationclip_walk,0.1f);
		break;
	case 1:
		m_modelrender.PlayAnimation(enAnimationclip_walk,0.1f);
		break;
	}
}

struct SweepResultStage1 :public btCollisionWorld::ConvexResultCallback
{
	bool isHit = false;

	virtual btScalar addSingleResult(btCollisionWorld::LocalConvexResult& covexResult, bool normalInWorldSpace)
	{
		//先にオブジェクトに当たっていたら。
		if (covexResult.m_hitCollisionObject->getUserIndex() == enCollisionAttr_Stage1) {
			isHit = true;
			return 0.0f;
		}

		return 0.0f;
	}
};

void Enemy::Raytest()
{
	m_sphereColl.Create(0.5f);
	btTransform start, end;
	start.setIdentity();
	end.setIdentity();
	Vector3 endPos = m_position;
	//endPos.x + 100.0f;
	switch (Enemystate)
	{
	case 0:
		endPos.x =endPos.x- 10.0f;
		break;
	case 1:
		endPos.x =endPos.x+ 10.0f;
		break;
	}

	start.setOrigin(btVector3(m_position.x, m_position.y + 20.0f, m_position.z));//Rayの始点。
	end.setOrigin(btVector3(endPos.x, m_position.y + 20.0f, endPos.z));//Rayの終点。

	SweepResultStage1 callback;

	//衝突判定。
	PhysicsWorld::GetInstance()->ConvexSweepTest((const btConvexShape*)m_sphereColl.GetBody(), start, end, callback);

	if (callback.isHit == true) {
		if (Enemystate == 0) {
			Enemystate = 1;
		}
		else if (Enemystate == 1) {
			Enemystate = 0;
		}
	}

}
void Enemy::Update() {
	Move();
	Rotation();
	EnemyAnimation();
	Raytest();
	m_modelrender.SetPosition(m_position);
	m_modelrender.Update();
	Vector3 diff = m_player->m_position - m_position;
	/*if (diff.Length() <= 60.0f) {
		NewGO<GameOver>(0, "gameover");
		DeleteGO(this);
		DeleteGO(m_game);
		DeleteGO(m_player);
		DeleteGO(m_needle);
		DeleteGO(m_fallingblock);
		DeleteGO(m_movingfloor);
		DeleteGO(m_gamecamera);
	}*/
}
void Enemy::Render(RenderContext& rc) {
	m_modelrender.Draw(rc);
}