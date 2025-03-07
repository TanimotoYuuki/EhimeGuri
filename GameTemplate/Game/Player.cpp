#include "stdafx.h"
#include "Player.h"
#include"Game.h"
Player::Player() {
	animationClip[enAnimationClip_idle].Load("Assets/animData/playeridle.tka");
	animationClip[enAnimationClip_idle].SetLoopFlag(true);
	animationClip[enAnimationClip_walk].Load("Assets/animData/playerwalk.tka");
	animationClip[enAnimationClip_walk].SetLoopFlag(true);
	animationClip[enAnimationClip_run].Load("Assets/animData/playerrun.tka");
	animationClip[enAnimationClip_run].SetLoopFlag(true);
	modelRender.Init("Assets/modelData/player/player.tkm", animationClip,
		enAnimationClip_num, enModelUpAxisZ);
	modelRender.SetScale(Vector3(0.5f, 0.5f, 0.5f));
	characterController.Init(25.0f, 75.0f, position);
}
Player::~Player() {

}

void Player::Update() {
	Move();
	Rotation();
	ManageState();
	PlayAnimation();
	modelRender.Update();
}
void Player::Move() {
	moveSpeed.x = 0.0f;
	moveSpeed.z = 0.0f;
	//スティックの入力量を取得
	Vector3 stickL;
	stickL.x = g_pad[0]->GetLStickXF();
	stickL.y = g_pad[0]->GetLStickYF();
	//カメラの前方向と右方向にベクトルを持ってくる
	Vector3 forward = g_camera3D->GetForward();
	Vector3 right = g_camera3D->GetRight();
	//y方向には移動しない
	forward.y = 0.0f;
	right.y = 0.0f;
	//左スティックの入力量と120.0fを乗算
	right *= stickL.x * 480.0f;
	forward *= stickL.y * 480.0f;
	//移動速度に上記で計算したベクトルを加算する
	moveSpeed += right + forward;

	//キャラクターコントローラーを使って座標を移動させる
	position = characterController.Execute(moveSpeed, 1.0f / 60.0f);
	//絵描きさんに座標を教える
	modelRender.SetPosition(position);
}
void Player::Rotation() {
	//xかzの移動速度があったら(スティックの入力があったら)
	if (fabsf(moveSpeed.x) >= 0.001f || fabsf(moveSpeed.z) >= 0.001f) {
		//キャラクターの方向を変える
		rotation.SetRotationYFromDirectionXZ(moveSpeed);
		//絵描きさんに回転を教える
		modelRender.SetRotation(rotation);
	}
}
void Player::ManageState() {
	//xかzの移動速度があったら(スティックの入力があったら)
	
		if (fabsf(moveSpeed.x) >= 0.001f|| fabsf(moveSpeed.z) >= 0.001f){
			if (g_pad[0]->IsPress(enButtonB)) {
				m_playerState = enPlayer_run;
			}
			else {
				m_playerState = enPlayer_walk;
				return;
			}
		}
	//xとzの移動速度がなかったら(スティックの入力がなかったら)
	else {
		//ステートを０にする(待機)
		m_playerState = enPlayer_idle;
	}
}
void Player::PlayAnimation() {
	switch (m_playerState) {
	case enPlayer_idle:
		modelRender.PlayAnimation(enAnimationClip_idle);
		break;
	case enPlayer_walk:
		modelRender.PlayAnimation(enAnimationClip_walk);
		break;
	case enPlayer_run:
		modelRender.PlayAnimation(enAnimationClip_run);
		break;
	}
}
void Player::Render(RenderContext& rc) {
	modelRender.Draw(rc);
}