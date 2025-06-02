#pragma once
/// <summary>
/// ゲームカメラ。
/// </summary>
class Player;
class GameCamera :public IGameObject
{
public:
	GameCamera();
	~GameCamera();
	bool Start();// 初期化処理。
	void Update();// 更新処理。

	void SetTarget(Player* player) { m_player = player; }

	Player* m_player = nullptr;	//プレイヤー用のインスタンス。
	Vector3 m_cameraTarget;		//カメラの注視点。
	Vector3 m_leftScreenEdge;	//左画面端。
	Vector3 m_toCameraPos;		//注視点から視点に向かうベクトル。
};

