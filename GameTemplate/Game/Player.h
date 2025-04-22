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
	void Update();								//更新処理
	void Render(RenderContext& rc);				//描画処理
	void Move();								//移動処理
	void Rotation();							//回転処理
	void ManageState();							//ステート管理
	void PlayAnimation();						//アニメーションの再生
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

	//アニメーションクリップ
	enum EnAnimationClip {
		enAnimationClip_idle,
		enAnimationClip_walk,
		enAnimationClip_run,
		enAnimationClip_jump,
		enAnimationClip_num
	};

	//プレイヤーステート
	enum PlayerState {
		enPlayer_idle,
		enPlayer_walk,
		enPlayer_run,
		enPlayer_jump,
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
	bool				m_isOnGround = true;			//!<地面の上にいる？
	bool G = true;
private:

};

