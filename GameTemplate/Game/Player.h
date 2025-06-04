#pragma once
class Game;
class GameOver;
class S_MovibgFloor;
class Enemy;
class Towel;
class ItemEnemy;
class Player:public IGameObject
{
public:
	Player();
	~Player();
	void Update();								
	void Render(RenderContext& rc);				
	void Move();								
	void Rotation();							
	void ManageState();							
	void PlayAnimation();						
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

	/// <summary>
	/// ItemEnemyクラスの検索。
	/// </summary>
	void ItemEnemyFindGO();

	/// <summary>
	/// リスポーン地点の設定。
	/// </summary>
	/// <param name="pos">位置</param>
	void SetRespawnPositon(const Vector3& pos)
	{
		m_respawnPosition = pos;
	}

	/// <summary>
	/// プレイヤーをリスポーンする。
	/// </summary>
	void PlayerRespawn()
	{
		m_position = m_respawnPosition;
		m_rotation = m_respawnRotation;
		m_modelRender.SetPosition(m_position);
		m_modelRender.SetRotation(m_rotation);
		m_characterController.SetPosition(m_position);
		m_respawnFlag = true;
	}

	/// <summary>
	/// プレイヤーがリスポーンしたか？
	/// </summary>
	/// <returns>trueならリスポーンしている</returns>
	bool IsPlayerRespawn()
	{
		return m_respawnFlag;
	}

	Vector3 m_platformVelocity = Vector3::Zero;

	

	bool IsOnGround() const
	{
		return m_isOnGround;
	}

	enum EnAnimationClip {
		enAnimationClip_idle,
		enAnimationClip_walk,
		enAnimationClip_run,
		enAnimationClip_jump,
		enAnimationClip_stageclear,
		enAnimationClip_gameover,
		enAnimationClip_num
	};

	enum PlayerState {
		enPlayer_idle,
		enPlayer_walk,
		enPlayer_run,
		enPlayer_jump,
		enPlayer_stageclear,
		enPlayer_gameover,
		enPlayer_num
	};
	ModelRender	m_modelRender;
	Vector3	m_position;			
	AnimationClip m_animationClip[enAnimationClip_num];
	Vector3	m_moveSpeed = Vector3::Zero;
	Quaternion m_rotation;
	Vector3	m_initPosition;//初期位置
	Vector3 m_respawnPosition;//リスポーン用位置

	Quaternion m_respawnRotation;//リスポーン用回転
	CharacterController m_characterController;


	int	NeedleCount = 0;
	int	clearCount = 0;
	int	m_playerState = enPlayer_idle;
	int	m_needleCount = 0;
	int	taoruCount = 0;
	int jakoCount = 0;
	int sinjuCount = 0;
	int mikanCount = 0;
	int tobeyakiCount = 0;
	int tarutoCount = 0;
	Game* m_game = nullptr;
	Enemy* m_enemy = nullptr;
	GameOver* m_gameover = nullptr;
	Towel* m_towel = nullptr;
	ItemEnemy* m_itemEnemy;//アイテムエネミー用インスタンス
	int m_playermaxsutamina = 300;
	int	m_playernowsutamina = 300;
	bool m_sutaminaZeroFlag = false;
	bool m_jumpFlag = true;
	bool m_isOnGround = true;
	bool m_stageClearFlag = false;
	bool m_gameOverFlag = false;
	int checcount = 0;
	bool m_respawnFlag = false;//リスポーンしたか？
	bool m_itemEnemyFindGoCompleteFlag = false;//ItemEnemyクラスの検索が完了したか？
};

