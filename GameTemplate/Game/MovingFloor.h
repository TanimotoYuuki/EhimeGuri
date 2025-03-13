//#pragma once 
//
//class Player;
//class BackGround;
///// <summary>
///// 動く床。
///// </summary>
//class MovingFloor : public IGameObject
//{
//public:
//	MovingFloor();
//	~MovingFloor();
//
//	bool Start();
//	void Update();
//	void Render(RenderContext& rc);
//	/// <summary>
//	/// 座標を設定。
//	/// </summary>
//	void SetPosition(const Vector3& position)
//	{
//		m_position = position;
//	}
//
//	const Vector3& GetPosition()const
//	{
//		return m_position;
//	}
//
//private:
//	/// <summary>
//	/// 移動処理。
//	/// </summary>
//	void Move();
//
//	Vector3										m_position;
//	Vector3										m_firstPosition;
//	ModelRender									m_modelRender;
//	Player									  * m_player = nullptr;
//	PhysicsStaticObject							m_physicsStaticObject;				//静的物理オブジェクト。
////	CollisionObject						      * m_collisionObject = nullptr;		//コリジョンオブジェクト。
//	enum enMovingFloorState
//	{
//		enMovingFloorState_MovingRight,
//		enMovingFloorState_MovingLeft
//	};
//	enMovingFloorState							m_MovingFloorState = enMovingFloorState_MovingRight;
//};
