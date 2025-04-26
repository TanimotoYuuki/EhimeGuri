#pragma once 

class Player;
class BackGround;
/// <summary>
/// 動く床。
/// </summary>
class MovingFloor : public IGameObject
{
public:
	MovingFloor();
	~MovingFloor();

	bool Start() override;
	void Update()override;
	void Render(RenderContext& rc)override;

	/// <summary>
	/// 座標を設定。
	/// </summary>
	void SetPosition(const Vector3& position)
	{
		m_position = position;
	}

	const Vector3& GetPosition()const
	{
		return m_position;
	}
	void Move();
private:
	/// <summary>
	/// 移動処理。
	/// </summary>
	

	Player									  * m_player = nullptr;
	CollisionObject							  * m_collisionObject = nullptr;		//コリジョンオブジェクト。

	Vector3										m_firstPosition;
	ModelRender									m_modelRender;
	Vector3										m_position;
	PhysicsStaticObject							m_physicsStaticObject;				
	

	enum enMovingFloorState
	{
		enMovingFloorState_MovingRight,
		enMovingFloorState_MovingLeft
	};
	enMovingFloorState							m_movingFloorState = enMovingFloorState_MovingRight;
};
