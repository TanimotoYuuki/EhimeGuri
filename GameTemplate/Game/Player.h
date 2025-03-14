#pragma once
class Game;
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

	const Vector3& GetPosition() const
	{
		return m_position;
	}
	void AddMoveSpeed(const Vector3& addMoveSpeed)
	{
		m_moveSpeed += addMoveSpeed;
	}
	CharacterController& GetCharacterController()
	{
		return m_characterController;
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
	CharacterController m_characterController;
	Vector3				m_moveSpeed = Vector3::Zero;
	Quaternion			m_rotation;
	
	int m_playerState = enPlayer_idle;
	Game			  * m_game;
};

