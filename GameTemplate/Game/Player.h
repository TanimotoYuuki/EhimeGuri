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
	ModelRender modelRender;//モデルレンダー
	Vector3 position;//座標
	enum EnAnimationClip {
		enAnimationClip_idle,
		enAnimationClip_walk,
		enAnimationClip_run,
		enAnimationClip_num
	};
	AnimationClip animationClip[enAnimationClip_num];//アニメーションクリップ
	CharacterController characterController;//キャラクターコントローラー
	Vector3 moveSpeed;//移動速度
	Quaternion rotation;//クォータニオン
	enum PlayerState {
		enPlayer_idle,
		enPlayer_walk,
		enPlayer_run,
		enPlayer_num
	};
	int m_playerState = enPlayer_idle;//プレイヤーのステート
	Game* game;
};

