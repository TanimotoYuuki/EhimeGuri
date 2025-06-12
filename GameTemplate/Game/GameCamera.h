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
	void SetToCameraPos(const Vector3& toCameraPos)
	{
		m_toCameraPos = toCameraPos;
		m_toCameraPosmultiplier = double(m_toCameraPos.z) / double(- 500.0f);
	}

	Player* m_player = nullptr;				//プレイヤー用のインスタンス。
	Vector3 m_cameraTarget;					//カメラの注視点。
	Vector3 m_leftScreenEdge;				//左画面端。
	Vector3 m_toCameraPos;					//注視点から視点に向かうベクトル。
	double m_toCameraPosmultiplier = 1.0f;	//カメラの倍率。
	bool m_stageTransitionFlag = false;		//ステージ遷移フラグ
};

