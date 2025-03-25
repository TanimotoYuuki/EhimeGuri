#include "stdafx.h"
#include "Player.h"
#include "Game.h"
#include "GameOver.h"

namespace {
	const float SUTAMINA_MAX = 300.0f;
}
Player::Player() {
	m_animationClip[enAnimationClip_idle].Load("Assets/animData/playeridle.tka");
	m_animationClip[enAnimationClip_idle].SetLoopFlag(true);
	m_animationClip[enAnimationClip_walk].Load("Assets/animData/playerwalk.tka");
	m_animationClip[enAnimationClip_walk].SetLoopFlag(true);
	m_animationClip[enAnimationClip_run].Load("Assets/animData/playerrun.tka");
	m_animationClip[enAnimationClip_run].SetLoopFlag(true);
	m_animationClip[enAnimationClip_jump].Load("Assets/animData/playerjump.tka");
	m_animationClip[enAnimationClip_jump].SetLoopFlag(false);
	m_modelRender.Init("Assets/modelData/player/player.tkm", m_animationClip,
		enAnimationClip_num, enModelUpAxisZ, true);

	m_modelRender.SetScale(Vector3(0.5f, 0.5f, 0.5f));
	m_position = { 133.0f,94.0f,0.0f };
	m_initPosition = { 133.0f,94.0f,0.0f };
	m_characterController.Init(25.0f, 75.0f, m_position);
	m_rotation.SetRotationDegY(90.0f);
	m_initRotation.SetRotationDegY(90.0f);

	m_modelRender.SetPosition(m_position);
	m_modelRender.SetRotation(m_rotation);
	m_modelRender.Update();
}
Player::~Player() {

}

void Player::Update() {
	if (m_playernowsutamina == 0) {
		m_sutaminaZeroFlag=true;
	}
	if (m_sutaminaZeroFlag == true) {
		Derei();//一定時間たってから。
	}
	//移動処理
	Move();
	//回転処理
	Rotation();
	//ステート処理
	ManageState();
	//アニメーション
	PlayAnimation();
	//描画処理
	m_modelRender.Update();
	
}
void Player::Move() {
	m_moveSpeed.x = 0.0f;
	m_moveSpeed.z = 0.0f;
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
	forward *= stickL.y * 0.0f;
	//移動速度に上記で計算したベクトルを加算する
	m_moveSpeed += right + forward;
	//ダッシュ
	if (g_pad[0]->IsPress(enButtonB) && m_playernowsutamina > 0 && m_sutaminaZeroFlag == false&& m_characterController.IsOnGround()) {
		m_moveSpeed.x *= 2.0f;
		m_moveSpeed.z *= 0.0f;
	}

	float glavity = 9.0f;
	//地面についていたら
	if (m_characterController.IsOnGround()) {
		//重力をなくす
		m_moveSpeed.y = 0.0f;
		//Aボタンが押されたら
		if (g_pad[0]->IsTrigger(enButtonA)) {
			//ジャンプさせる
			m_moveSpeed.y = 400.0f;
		}
	}
	
	m_moveSpeed.y -= glavity;
	
	/*if (m_position.y <= 0.0f) {
		m_position.y = 0.0f;
	}*/

	if (m_position.y <= -500.0f) {
		m_position = m_initPosition;
		m_rotation = m_initRotation;
		m_modelRender.SetPosition(m_position);
		m_modelRender.SetRotation(m_rotation);
		m_characterController.SetPosition( m_position);
	}



	//キャラクターコントローラーを使って座標を移動させる
	m_position = m_characterController.Execute(m_moveSpeed, 1.0f / 60.0f);

	//絵描きさんに座標を教える
	m_modelRender.SetPosition(m_position);
}
void Player::Rotation() {
	//xかzの移動速度があったら(スティックの入力があったら)
	if (fabsf(m_moveSpeed.x) >= 0.001f || fabsf(m_moveSpeed.z) >= 0.001f) {
		//キャラクターの方向を変える
		m_rotation.SetRotationYFromDirectionXZ(m_moveSpeed);
		//絵描きさんに回転を教える
		m_modelRender.SetRotation(m_rotation);
	}
}
void Player::ManageState() {
	//地面についてなかったら
	if (m_characterController.IsOnGround() == false) {
		m_playerState = enPlayer_jump;
		//ここでManageState関数の処理を終わらせる
		PlayerhealSutamina();
		return;
	}
	//xかzの移動速度があったら(スティックの入力があったら)
	if (fabsf(m_moveSpeed.x) >= 0.001f|| fabsf(m_moveSpeed.z) >= 0.001f){
		if (g_pad[0]->IsPress(enButtonB)&&m_playernowsutamina>0&&m_sutaminaZeroFlag==false) {
			m_playerState = enPlayer_run;
			PlayerStamina();
		}
		else {
			m_playerState = enPlayer_walk;
			PlayerhealSutamina();
		}
	}
	//xとzの移動速度がなかったら(スティックの入力がなかったら)
	else {
		m_playerState = enPlayer_idle;
		PlayerhealSutamina();
	}
}
void Player::PlayAnimation() {
	switch (m_playerState) {
	case enPlayer_idle:
		m_modelRender.PlayAnimation(enAnimationClip_idle);
		break;
	case enPlayer_walk:
		m_modelRender.PlayAnimation(enAnimationClip_walk);
		m_moveSpeed.z *= 0.0f;
		break;
	case enPlayer_jump:
		m_modelRender.PlayAnimation(enAnimationClip_jump);
		break;
	case enPlayer_run:
		m_modelRender.PlayAnimation(enAnimationClip_run);
		
		break;
	}
}
void Player::PlayerStamina()
{
	m_playernowsutamina -=1 /*g_gameTime->GetFrameDeltaTime()*/;
	if (m_playernowsutamina < 0) {
		m_playernowsutamina = 0;
	}
}
void Player::PlayerhealSutamina() {
	m_playernowsutamina += 1;
	if (m_playernowsutamina > SUTAMINA_MAX) {
		m_playernowsutamina = SUTAMINA_MAX;
	}
}
void Player::Derei() {
	if (m_playermaxsutamina / 2.0f<m_playernowsutamina) {
		m_sutaminaZeroFlag = false;
	}
}
void Player::Render(RenderContext& rc) {
	m_modelRender.Draw(rc);
}