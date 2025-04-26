#include "stdafx.h"
#include "Player.h"
#include "Game.h"
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
	m_animationClip[enAnimationClip_gameover].Load("Assets/animData/gameover.tka");
	m_animationClip[enAnimationClip_gameover].SetLoopFlag(false);
	m_modelRender.Init("Assets/modelData/player/player.tkm", m_animationClip,
		enAnimationClip_num, enModelUpAxisZ, true);

	m_modelRender.SetScale(Vector3(0.5f, 0.5f, 0.5f));

	m_position = { 0.0f,94.0f,0.0f };

	
	//・ｽe・ｽX・ｽg・ｽv・ｽ・ｽ・ｽC・ｽp
//	m_position = { 16250.0f, 800.0f, 0.0f };


	m_initPosition = { 0.0f,94.0f,0.0f };
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


	if (m_playernowsutamina == 0) {
		m_sutaminaZeroFlag=true;
	}
	if (m_sutaminaZeroFlag == true) {
		Derei();//・ｽ・ｽ闔橸ｿｽﾔゑｿｽ・ｽ・ｽ・ｽﾄゑｿｽ・ｽ・ｽB
	}
	//・ｽﾚ難ｿｽ・ｽ・ｽ・ｽ・ｽ
	Move();
	//・ｽ・ｽ]・ｽ・ｽ・ｽ・ｽ
	Rotation();
	//・ｽX・ｽe・ｽ[・ｽg・ｽ・ｽ・ｽ・ｽ
	ManageState();
	//・ｽA・ｽj・ｽ・ｽ・ｽ[・ｽV・ｽ・ｽ・ｽ・ｽ
	PlayAnimation();

	

	//・ｽ`・ｽ謠茨ｿｽ・ｽ
	m_modelRender.Update();
	
}
void Player::Move() {
	m_moveSpeed.x = 0.0f;
	m_moveSpeed.z = 0.0f;
	//・ｽX・ｽe・ｽB・ｽb・ｽN・ｽﾌ難ｿｽ・ｽﾍ量ゑｿｽ謫ｾ
	Vector3 stickL;
	if (m_gameoverFlag != true)
	{
		stickL.x = g_pad[0]->GetLStickXF();
		stickL.y = g_pad[0]->GetLStickYF();
	}
	//・ｽJ・ｽ・ｽ・ｽ・ｽ・ｽﾌ前・ｽ・ｽ・ｽ・ｽ・ｽﾆ右・ｽ・ｽ・ｽ・ｽ・ｽﾉベ・ｽN・ｽg・ｽ・ｽ・ｽ・ｽ・ｽ・ｽ・ｽ・ｽﾄゑｿｽ・ｽ・ｽ
	Vector3 forward = g_camera3D->GetForward();
	Vector3 right = g_camera3D->GetRight();
	//y・ｽ・ｽ・ｽ・ｽ・ｽﾉは移難ｿｽ・ｽ・ｽ・ｽﾈゑｿｽ
	forward.y = 0.0f;
	right.y = 0.0f;
	//・ｽ・ｽ・ｽX・ｽe・ｽB・ｽb・ｽN・ｽﾌ難ｿｽ・ｽﾍ量ゑｿｽ120.0f・ｽ・ｽ・ｽZ
	right *= stickL.x * 480.0f;
	forward *= stickL.y * 0.0f;
	//・ｽﾚ難ｿｽ・ｽ・ｽ・ｽx・ｽﾉ擾ｿｽL・ｽﾅ計・ｽZ・ｽ・ｽ・ｽ・ｽ・ｽx・ｽN・ｽg・ｽ・ｽ・ｽ・ｽ・ｽ・ｽZ・ｽ・ｽ・ｽ・ｽ
	m_moveSpeed += right + forward;
	//・ｽ_・ｽb・ｽV・ｽ・ｽ
	if (m_gameoverFlag != true)
	{
		if (g_pad[0]->IsPress(enButtonB) && m_playernowsutamina > 0 && m_sutaminaZeroFlag == false && m_characterController.IsOnGround()) {
			m_moveSpeed.x *= 2.0f;
			m_moveSpeed.z *= 0.0f;
		}
	}

 	float glavity = 15.0f;

	// ・ｽn・ｽﾊにつゑｿｽ・ｽﾄゑｿｽ・ｽ・ｽ・ｽ・ｽ
	if (m_characterController.IsOnGround())
	{
		//・ｽd・ｽﾍゑｿｽﾈゑｿｽ・ｽ・ｽ
		m_moveSpeed.y = 0.0f;	

		//A・ｽ{・ｽ^・ｽ・ｽ・ｽ・ｽ・ｽ・ｽ・ｽ・ｽ・ｽ黷ｽ・ｽ・ｽ
		if (m_gameoverFlag != true)
		{
			if (g_pad[0]->IsTrigger(enButtonA)) {
				//・ｽW・ｽ・ｽ・ｽ・ｽ・ｽv・ｽ・ｽ・ｽ・ｽ・ｽ・ｽ
				m_moveSpeed.y = 525.0f;
			}
		}
	}
	
	m_moveSpeed.y -= glavity;

	if (m_gameoverFlag != true)
	{
		if (m_position.y <= -500.0f) {
			m_position = m_initPosition;
			m_rotation = m_initRotation;
			m_modelRender.SetPosition(m_position);
			m_modelRender.SetRotation(m_rotation);
			m_characterController.SetPosition(m_position);
		}
	}


	//・ｽL・ｽ・ｽ・ｽ・ｽ・ｽN・ｽ^・ｽ[・ｽR・ｽ・ｽ・ｽg・ｽ・ｽ・ｽ[・ｽ・ｽ・ｽ[・ｽ・ｽg・ｽ・ｽ・ｽﾄ搾ｿｽ・ｽW・ｽ・ｽﾚ難ｿｽ・ｽ・ｽ・ｽ・ｽ・ｽ・ｽ
	m_position = m_characterController.Execute(m_moveSpeed, 1.0f / 60.0f);
	

	m_position.z = 0.0f;

	//・ｽG・ｽ`・ｽ・ｽ・ｽ・ｽ・ｽ・ｽﾉ搾ｿｽ・ｽW・ｽ・ｽ・ｽ・ｽ・ｽ・ｽ・ｽ
	m_modelRender.SetPosition(m_position);


}

void Player::Rotation() {
	//x・ｽ・ｽz・ｽﾌ移難ｿｽ・ｽ・ｽ・ｽx・ｽ・ｽ・ｽ・ｽ・ｽ・ｽ・ｽ・ｽ・ｽ・ｽ(・ｽX・ｽe・ｽB・ｽb・ｽN・ｽﾌ難ｿｽ・ｽﾍゑｿｽ・ｽ・ｽ・ｽ・ｽ・ｽ・ｽ・ｽ・ｽ)
	if (fabsf(m_moveSpeed.x) >= 0.001f || fabsf(m_moveSpeed.z) >= 0.001f) {
		//・ｽL・ｽ・ｽ・ｽ・ｽ・ｽN・ｽ^・ｽ[・ｽﾌ包ｿｽ・ｽ・ｽ・ｽ・ｽﾏゑｿｽ・ｽ・ｽ
		m_rotation.SetRotationYFromDirectionXZ(m_moveSpeed);
		//・ｽG・ｽ`・ｽ・ｽ・ｽ・ｽ・ｽ・ｽﾉ会ｿｽ]・ｽ・ｽ・ｽ・ｽ・ｽ・ｽ・ｽ
		m_modelRender.SetRotation(m_rotation);
	}
}
void Player::ManageState() {
	if (m_gameoverFlag == true)
	{
		m_playerState = enPlayer_gameover;
		return;
	}

	//・ｽn・ｽﾊにつゑｿｽ・ｽﾄなゑｿｽ・ｽ・ｽ・ｽ・ｽ・ｽ・ｽ
	if (m_characterController.IsOnGround() == false) {
		m_playerState = enPlayer_jump;
		//・ｽ・ｽ・ｽ・ｽ・ｽ・ｽManageState・ｽﾖ撰ｿｽ・ｽﾌ擾ｿｽ・ｽ・ｽ・ｽ・ｽI・ｽ・ｽ轤ｹ・ｽ・ｽ
		PlayerhealSutamina();
		return;
	}
	//x・ｽ・ｽz・ｽﾌ移難ｿｽ・ｽ・ｽ・ｽx・ｽ・ｽ・ｽ・ｽ・ｽ・ｽ・ｽ・ｽ・ｽ・ｽ(・ｽX・ｽe・ｽB・ｽb・ｽN・ｽﾌ難ｿｽ・ｽﾍゑｿｽ・ｽ・ｽ・ｽ・ｽ・ｽ・ｽ・ｽ・ｽ)
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
	//x・ｽ・ｽz・ｽﾌ移難ｿｽ・ｽ・ｽ・ｽx・ｽ・ｽ・ｽﾈゑｿｽ・ｽ・ｽ・ｽ・ｽ・ｽ・ｽ(・ｽX・ｽe・ｽB・ｽb・ｽN・ｽﾌ難ｿｽ・ｽﾍゑｿｽ・ｽﾈゑｿｽ・ｽ・ｽ・ｽ・ｽ・ｽ・ｽ)
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