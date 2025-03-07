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
	//�X�e�B�b�N�̓��͗ʂ��擾
	Vector3 stickL;
	stickL.x = g_pad[0]->GetLStickXF();
	stickL.y = g_pad[0]->GetLStickYF();
	//�J�����̑O�����ƉE�����Ƀx�N�g���������Ă���
	Vector3 forward = g_camera3D->GetForward();
	Vector3 right = g_camera3D->GetRight();
	//y�����ɂ͈ړ����Ȃ�
	forward.y = 0.0f;
	right.y = 0.0f;
	//���X�e�B�b�N�̓��͗ʂ�120.0f����Z
	right *= stickL.x * 480.0f;
	forward *= stickL.y * 480.0f;
	//�ړ����x�ɏ�L�Ōv�Z�����x�N�g�������Z����
	moveSpeed += right + forward;

	//�L�����N�^�[�R���g���[���[���g���č��W���ړ�������
	position = characterController.Execute(moveSpeed, 1.0f / 60.0f);
	//�G�`������ɍ��W��������
	modelRender.SetPosition(position);
}
void Player::Rotation() {
	//x��z�̈ړ����x����������(�X�e�B�b�N�̓��͂���������)
	if (fabsf(moveSpeed.x) >= 0.001f || fabsf(moveSpeed.z) >= 0.001f) {
		//�L�����N�^�[�̕�����ς���
		rotation.SetRotationYFromDirectionXZ(moveSpeed);
		//�G�`������ɉ�]��������
		modelRender.SetRotation(rotation);
	}
}
void Player::ManageState() {
	//x��z�̈ړ����x����������(�X�e�B�b�N�̓��͂���������)
	
		if (fabsf(moveSpeed.x) >= 0.001f|| fabsf(moveSpeed.z) >= 0.001f){
			if (g_pad[0]->IsPress(enButtonB)) {
				m_playerState = enPlayer_run;
			}
			else {
				m_playerState = enPlayer_walk;
				return;
			}
		}
	//x��z�̈ړ����x���Ȃ�������(�X�e�B�b�N�̓��͂��Ȃ�������)
	else {
		//�X�e�[�g���O�ɂ���(�ҋ@)
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