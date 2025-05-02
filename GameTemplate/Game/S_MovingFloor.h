#pragma once 

class Player;
class BackGround;
/// <summary>
/// 動く床。
/// </summary>
class S_MovingFloor : public IGameObject
{
public:
	S_MovingFloor();
	~S_MovingFloor();

	bool Start() override;
	void Update()override;

	/////↓//////
	///試作中///
//	void Trap();
	/////↑/////

	void Render(RenderContext& rc)override;

	/// <summary>
	/// 座標を設定。
	/// </summary>
	void SetPosition(const Vector3& position)
	{
		m_position = position;
	}

	void SetGroundPlatformVelocity(const Vector3& moveSPEED)
	{
		moveSpeed = moveSPEED;
	}

	Vector3 m_platformVelocity = Vector3::Zero;
	void GroundPlatformVelocity(const Vector3& vel)
	{
		m_platformVelocity = vel;
	}

	const Vector3& GetPosition()const
	{
		return m_position;
	}

	/// <summary>
	/// 移動処理。
	/// </summary>
	void Move();
	int count = 0;
	Vector3										m_firstPosition;
	Vector3										m_position;
	Vector3									    moveSpeed = Vector3::Zero;

private:

	Player									  * m_player = nullptr;
	CollisionObject							  * m_collisionObject = nullptr;		//コリジョンオブジェクト。
	//CharacterController							m_charactecController;

	ModelRender									m_modelRender;
	
	PhysicsStaticObject							m_physicsStaticObject;

	enum enMovingFloorState
	{
		enMovingFloorState_MovingRight,
		enMovingFloorState_MovingLeft
	};
	enMovingFloorState							m_movingFloorState = enMovingFloorState_MovingRight;
};
