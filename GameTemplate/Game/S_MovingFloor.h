#pragma once 
using namespace std;

class Player;
class BackGround;
class Config;
class S_MovingFloor : public IGameObject
{
public:
	/// <summary>
    /// 動く床。
    /// </summary>

	S_MovingFloor() {};
	~S_MovingFloor() {};

	bool Start() override;
	void Update()override;// 更新作業。
	void Render(RenderContext& rc)override;// 描画処理。

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
	int count = 0;
	Vector3 m_firstPosition;
	Vector3	m_position;
	Vector3	moveSpeed = Vector3::Zero;

private:
	Config* m_config = nullptr;
	Player* m_player = nullptr;
	CollisionObject* m_collisionObject = nullptr;		
	ModelRender m_modelRender;
	PhysicsStaticObject m_physicsStaticObject;

	// 移動方向を決めるステート。
	enum enMovingFloorState
	{
		enMovingFloorState_MovingRight,// 左。
		enMovingFloorState_MovingLeft// 右。
	};

	// ステートの初期化。
	enMovingFloorState m_movingFloorState = enMovingFloorState_MovingRight;
};
