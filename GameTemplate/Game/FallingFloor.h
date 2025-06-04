#pragma once
class Config;
class Player;
class FallingFloor : public IGameObject
{
public:
	/// <summary>
	/// 落下する床。
	/// 第2ステージ専用モデル 兼 LevelObject。 
	/// </summary>
	FallingFloor() {};
	~FallingFloor() {};


	bool Start();
	void Update();// 更新処理。
	void Floor();// 落下処理。
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



private:
	enum enMovingFloorState
	{
		enMovingFloorState_MovingRight,
		enMovingFloorState_MovingLeft
	};
	enMovingFloorState m_movingFloorState = enMovingFloorState_MovingRight;
	CollisionObject* m_collisionObject = nullptr;// コリジョン。
	Player* m_player = nullptr;// プレイヤー。
	PhysicsStaticObject* m_physicsStaticObject;// 当たり判定。
	Config* m_filePathConfig = nullptr;// コンフィグ。
	ModelRender m_modelRender;// モデル。
	Vector3 m_position;// 座標。
	Vector3 m_initPosition;// 座標を設定。

};

