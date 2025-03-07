#pragma once
class Game;
class Player:public IGameObject
{
public:
	Player();
	~Player();
	void Update();//�X�V����
	void Render(RenderContext& rc);//�`�揈��
	void Move();//�ړ�����
	void Rotation();//��]����
	void ManageState();//�X�e�[�g�Ǘ�
	void PlayAnimation();//�A�j���[�V�����̍Đ�
	ModelRender modelRender;//���f�������_�[
	Vector3 position;//���W
	enum EnAnimationClip {
		enAnimationClip_idle,
		enAnimationClip_walk,
		enAnimationClip_run,
		enAnimationClip_num
	};
	AnimationClip animationClip[enAnimationClip_num];//�A�j���[�V�����N���b�v
	CharacterController characterController;//�L�����N�^�[�R���g���[���[
	Vector3 moveSpeed;//�ړ����x
	Quaternion rotation;//�N�H�[�^�j�I��
	enum PlayerState {
		enPlayer_idle,
		enPlayer_walk,
		enPlayer_run,
		enPlayer_num
	};
	int m_playerState = enPlayer_idle;//�v���C���[�̃X�e�[�g
	Game* game;
};

