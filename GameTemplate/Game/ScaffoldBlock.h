#pragma once

class Player;
class ScaffoldBlock : public IGameObject
{
public:
	/// <summary>
	/// 足場ブロック
	/// </summary>
	ScaffoldBlock() {};
	~ScaffoldBlock() {};

	bool Start();
	void Update();// 更新作業。
	void Render(RenderContext & rc);// 描画処理。

	/// <summary>
    /// 座標の設定。
    /// </summary>
	void SetPosition(const Vector3 position)
	{
		m_position = position;
	}

	/// <summary>
    /// 座標の取得。
    /// </summary>
	const Vector3& GetPosition()const
	{
		return m_position;
	}

	Player* m_player = nullptr;
	Vector3 m_position;
	Vector3 m_firstposition;
	PhysicsStaticObject	m_physicsStaticObject;
	ModelRender m_modelRender;
	Quaternion m_Rot;

private:

	// 移動方向を決めるステート
	enum enMovingFloorState
	{
		enMovingFloorState_MovingRight,// 左。
		enMovingFloorState_MovingLeft// 右。
	};

	// ステートの初期化。
	enMovingFloorState m_movingFloorState = enMovingFloorState_MovingRight;
	CollisionObject* m_collisionObject = nullptr;

};

