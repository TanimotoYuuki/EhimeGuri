#pragma once
class Player;
class Config;
class Tower : public IGameObject
{
public:
	Tower() {};
	~Tower() {};

	bool Start();// 初期化処理。
	void Update();// 更新処理。
	void Move();// 動作処理。
	void Render(RenderContext& rc);// 描画処理。	
	/// <summary>
	/// 座標のセット
	/// </summary>
	void SetPosition(const Vector3 position)
	{
		m_position = position;
	}
	/// <summary>
	/// 座標を取得
	/// </summary>
	const Vector3& GetPosition()const
	{
		return m_position;
	}

	/// <summary>
	/// タワーのコリジョンの衝突判定
	/// </summary>
	void TowerCollisionDetection();

	Vector3 m_position;
	Vector3 m_firstPosition;

private:
	Config* m_config;
	CollisionObject* m_collisionObject;
	Player* m_player = nullptr;
	PhysicsStaticObject m_physicsStaticObject;
	ModelRender m_modelRender;

	bool m_isHitTowerCollision = false;//タワーのコリジョンに衝突したか？
	bool m_isNotHitTowerCollision = false;//タワーのコリジョンに衝突していないか?
	bool m_playerTowerJumpFlag = false;//プレイヤーがタワーでジャンプしたか？

	// 移動方向を決めるステート。
	enum enMovingFloorState
	{
		enMovingFloorState_MovingRight, // 右。
		enMovingFloorState_MovingLeft// 左。
	};

	// ステートの初期化。
	enMovingFloorState m_movingFloorState = enMovingFloorState_MovingRight;
};

