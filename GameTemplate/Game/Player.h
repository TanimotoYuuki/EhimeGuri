#pragma once
class Game;
class GameOver;
class S_MovibgFloor;
class Enemy;
class Towel;
class Player:public IGameObject
{
public:
	Player();
	~Player();
	void Update();								//�X�V����
	void Render(RenderContext& rc);				//�`�揈��
	void Move();								//�ړ�����
	void Rotation();							//��]����
	void ManageState();							//�X�e�[�g�Ǘ�
	void PlayAnimation();						//�A�j���[�V�����̍Đ�
	void PlayerStamina();
	void PlayerhealSutamina();
	void Derei();

	const Vector3& GetPosition() const
	{
		return m_position;
	}

	void SetPosition(const Vector3& position)
	{
		m_position = position;
	}
	void AddMoveSpeed(const Vector3& addMoveSpeed)
	{
		m_moveSpeed += addMoveSpeed;
	}

	CharacterController& GetCharacterController() 
	{
		return m_characterController;
	}

	
	Vector3 m_platformVelocity = Vector3::Zero;

	

	bool IsOnGround() const
	{
		return m_isOnGround;
	}

	//�A�j���[�V�����N���b�v
	enum EnAnimationClip {
		enAnimationClip_idle,
		enAnimationClip_walk,
		enAnimationClip_run,
		enAnimationClip_jump,
		enAnimationClip_gameover,
		enAnimationClip_num
	};

	//�v���C���[�X�e�[�g
	enum PlayerState {
		enPlayer_idle,
		enPlayer_walk,
		enPlayer_run,
		enPlayer_jump,
		enPlayer_gameover,
		enPlayer_num
	};
	ModelRender			m_modelRender;			
	Vector3				m_position;			
	AnimationClip		m_animationClip[enAnimationClip_num];
	Vector3				m_moveSpeed = Vector3::Zero;
	Quaternion			m_rotation;
	Vector3             m_initPosition;

	Quaternion          m_initRotation;
	CharacterController m_characterController;


	int					NeedleCount = 0;
	int					clearCount = 0;
	int					m_playerState = enPlayer_idle;
	int					m_needleCount = 0;
	int					taoruCount = 0;
	Game			  * m_game;
	Enemy			  * m_enemy;
	GameOver		  * m_gameover;
	Towel			  * m_towel;
	int					m_playermaxsutamina = 300;
	int					m_playernowsutamina = 300;
	bool				m_sutaminaZeroFlag = false;
	bool				m_jumpFlag = true;
	bool				m_isOnGround = true;			//!<�n�ʂ̏�ɂ���H
	bool G = true;
	bool m_gameoverFlag = false;
};

