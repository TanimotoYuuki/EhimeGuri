#include "stdafx.h"
#include "Player.h"
#include "Game.h"
#include "Config.h"
#include "GameOver.h"
#include "Enemy.h"
#include"Towel.h"
using namespace std;

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
	m_animationClip[enAnimationClip_stageclear].Load("Assets/animData/stageclear.tka");
	m_animationClip[enAnimationClip_stageclear].SetLoopFlag(true);
	m_animationClip[enAnimationClip_gameover].Load("Assets/animData/gameover.tka");
	m_animationClip[enAnimationClip_gameover].SetLoopFlag(false);

	//string modelPath = Config::GetFullPath_3DModel("player");// ファイルパスを読み込む。
	//m_modelRender.Init(modelPath.c_str());// モデルをセットする。

	m_modelRender.Init("Assets/modelData/player/player.tkm", m_animationClip,
		enAnimationClip_num, enModelUpAxisZ, true);

	m_modelRender.SetScale(Vector3(0.5f, 0.5f, 0.5f));

	m_position = { 0.0f,94.0f,0.0f };

	m_characterController.Init(25.0f, 100.0f, m_position);
	m_rotation.SetRotationDegY(90.0f);
	m_initRotation.SetRotationDegY(90.0f);

	m_modelRender.SetPosition(m_position);
	m_modelRender.SetRotation(m_rotation);
	m_modelRender.Update();
}
Player::~Player() {

}

void Player::Update() {

	if (checcount == 0) {
		m_initPosition = { 0.0f,94.0f,0.0f };
	}
	else if (checcount == 1) {
		m_initPosition = { 10300.0f,120.0f,0.0f };
	}

	if (m_playernowsutamina == 0) {
		m_sutaminaZeroFlag=true;
	}
	if (m_sutaminaZeroFlag == true) {
		Derei();
	}
	
	Move();
	
	Rotation();
	
	ManageState();
	
	PlayAnimation();

	m_modelRender.Update();
	
}
void Player::Move() {
	m_moveSpeed.x = 0.0f;
	m_moveSpeed.z = 0.0f;
	
	Vector3 stickL;
	if (m_stageClearFlag != true && m_gameOverFlag != true)
	{
		stickL.x = g_pad[0]->GetLStickXF();
		stickL.y = g_pad[0]->GetLStickYF();
	}
	
	Vector3 forward = g_camera3D->GetForward();
	Vector3 right = g_camera3D->GetRight();
	
	forward.y = 0.0f;
	right.y = 0.0f;

	right *= stickL.x * 480.0f;
	forward *= stickL.y * 0.0f;
	
	m_moveSpeed += right + forward;
	
	if (m_stageClearFlag != true && m_gameOverFlag != true)
	{
		if (g_pad[0]->IsPress(enButtonB) && m_playernowsutamina > 0 && m_sutaminaZeroFlag == false && m_characterController.IsOnGround()) {
			m_moveSpeed.x *= 2.0f;
			m_moveSpeed.z *= 0.0f;
		}
	}

 	float glavity = 15.0f;

	
	if (m_characterController.IsOnGround())
	{
		
		m_moveSpeed.y = 0.0f;	

		
		if (m_stageClearFlag != true && m_gameOverFlag != true)
		{
			if (g_pad[0]->IsTrigger(enButtonA)) {
				
				m_moveSpeed.y = 525.0f;
			}
		}
	}
	
	m_moveSpeed.y -= glavity;

	if (m_stageClearFlag != true && m_gameOverFlag != true)
	{
		if (m_position.y <= -500.0f) {
			m_position = m_initPosition;
			m_rotation = m_initRotation;
			m_modelRender.SetPosition(m_position);
			m_modelRender.SetRotation(m_rotation);
			m_characterController.SetPosition(m_position);
		}
	}

	m_position = m_characterController.Execute(m_moveSpeed, 1.0f / 60.0f);
	

	m_position.z = 0.0f;
	m_characterController.SetPosition(m_position);

	m_modelRender.SetPosition(m_position);


}

void Player::Rotation() {
	if (fabsf(m_moveSpeed.x) >= 0.001f || fabsf(m_moveSpeed.z) >= 0.001f) {
		m_rotation.SetRotationYFromDirectionXZ(m_moveSpeed);
		m_modelRender.SetRotation(m_rotation);
	}
}
void Player::ManageState() {
	if (m_stageClearFlag == true)
	{
		m_playerState = enPlayer_stageclear;
		m_rotation.SetRotationDegY(180.0f);
		m_modelRender.SetRotation(m_rotation);
		return;
	}
	else if (m_gameOverFlag == true)
	{
		m_playerState = enPlayer_gameover;
		return;
	}

	if (m_characterController.IsOnGround() == false) {
		m_playerState = enPlayer_jump;
		PlayerhealSutamina();
		return;
	}
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
	else {
		m_playerState = enPlayer_idle;
		PlayerhealSutamina();
	}
}
void Player::PlayAnimation() {
	switch (m_playerState) {
	case enPlayer_idle:
		m_modelRender.PlayAnimation(enAnimationClip_idle,0.1f);
		break;
	case enPlayer_walk:
		m_modelRender.PlayAnimation(enAnimationClip_walk,0.1f);
		m_moveSpeed.z *= 0.0f;
		break;
	case enPlayer_jump:
		m_modelRender.PlayAnimation(enAnimationClip_jump,0.1f);
		break;
	case enPlayer_run:
		m_modelRender.PlayAnimation(enAnimationClip_run,0.1f);
		m_moveSpeed.z *= 0.0f;
		break;
	case enPlayer_stageclear:
		m_modelRender.PlayAnimation(enAnimationClip_stageclear, 0.1f);
		break;
	case enPlayer_gameover:
		m_modelRender.PlayAnimation(enAnimationClip_gameover, 0.1f);
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