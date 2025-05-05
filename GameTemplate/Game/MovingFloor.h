#pragma once 

class Player;
class BackGround;
class MovingFloor : public IGameObject
{
public:
	/// <summary>
    /// 動く床。
    /// </summary>

	MovingFloor() {};
	~MovingFloor() {};

	bool Start() override;
	void Update()override; // 更新作業。
	void Render(RenderContext& rc)override; // 描画処理。

	/// <summary>
	/// 座標を設定。
	/// </summary>
	void SetPosition(const Vector3& position)
	{
		m_position = position;
	}

	/// <summary>
    /// 座標を取得。
    /// </summary>
	const Vector3& GetPosition()const
	{
		return m_position;
	}

	/// <summary>
    /// 移動処理。
    /// </summary>
	void Move();
private:
	Player* m_player = nullptr;
	CollisionObject* m_collisionObject = nullptr;		
	Vector3 m_firstPosition;
	ModelRender m_modelRender;
	Vector3 m_position;
	PhysicsStaticObject m_physicsStaticObject;				
	
	// 移動方向を決めるステート。
	enum enMovingFloorState
	{
		enMovingFloorState_MovingRight, // 右。
		enMovingFloorState_MovingLeft// 左。
	};

	// ステートの初期化。
	enMovingFloorState m_movingFloorState = enMovingFloorState_MovingRight;
};
