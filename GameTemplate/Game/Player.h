#pragma once
class Game;
class Player:public IGameObject
{
public:
	Player();
	~Player();
	void Update();//更新処理
	void Render(RenderContext& rc);//描画処理
	void Move();//移動処理
	void Rotation();//回転処理
	void ManageState();//ステート管理
	void PlayAnimation();//アニメーションの再生
	/*const Vector3& GetPosition() const
	{
		return m_position;
	}
	void AddMoveSpeed(const Vector3& addMoveSpeed)
	{
		m_moveSpeed += addMoveSpeed;
	}
	CharacterController& GetCharacterController()
	{
		return characterController;
	}*/
	ModelRender m_modelRender;//モデルレンダー
	Vector3 position;//座標
	enum EnAnimationClip {
		enAnimationClip_idle,
		enAnimationClip_walk,
		enAnimationClip_run,
		enAnimationClip_jump,
		enAnimationClip_num
	};
	AnimationClip animationClip[enAnimationClip_num];//アニメーションクリップ
	CharacterController characterController;//キャラクターコントローラー
	Vector3 moveSpeed;//移動速度
	/*Vector3 m_position;*/
	Quaternion rotation;//クォータニオン
	enum PlayerState {
		enPlayer_idle,
		enPlayer_walk,
		enPlayer_run,
		enPlayer_jump,
		enPlayer_num
	};
	int m_playerState = enPlayer_idle;//プレイヤーのステート
	Game* game;
private:
//	Vector3						m_moveSpeed = Vector3::Zero;*/
};

