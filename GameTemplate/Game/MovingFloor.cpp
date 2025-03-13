#include "stdafx.h"
#include "MovingFloor.h"
#include "Player.h"


//namespace
//{
//	Vector3 SCALE = Vector3(3.0f, 1.0f, 3.0f);
//	float SPEED = 200.0f;
//	float LIMITED = 300.0f;
//	Vector3 COLLISION_HEIGHT = Vector3(0.0f, 50.0f, 0.0f);
//	Vector3	COLLISION_SIZE = Vector3(365.0f, 5.0f, 225.0f);
//}
//
//MovingFloor::MovingFloor()
//{
//
//}
//
//MovingFloor::~MovingFloor()
//{
//
//}
//
//bool MovingFloor::Start()
//{
//
//}
//
//void MovingFloor::Update()
//{
//	if (m_player == nullptr)
//	{
//		m_player = FindGO<Player>("player");
//		return;
//	}
//	Move();
//	m_modelRender.Update();
////	m_physicsStaticObject.
//}
//
//void MovingFloor::Move()
//{
//	Vector3 moveSpeed = Vector3::Zero;
//
//	if (m_movingFloorState == enMovingFloorState_MovingRight)
//	{
//		moveSpeed.x = -SPEED;
//	}
//
//	else if (m_movingFloorState == enMovingFloorState_MovingLeft)
//	{
//		moveSpeed.x = SPEED;
//	}
//	
//	m_position += moveSpeed * g_gameTime->GetFrameDeltaTime();
//
//	if (m_movingFloorState == enMovingFloorState_MovingRight)
//	{
//		if (m_firstPosition.x -LIMITED >= m_position.x)
//		{
//			m_movingFloorState == enMovingFloorState_MovingRight;
//		}
//	}
//
//	else if (m_movingFloorState == enMovingFloorState_MovingLeft)
//	{
//		if (m_firstPosition.x + LIMITED <= m_position.x)
//		{
//			m_movingFloorState = enMovingFloorState_MovingRight;
//		}
//	}
//	/// <summary>
//	/// コリジョンオブジェクトとプレイヤーのキャラクターコントローラーが。
//	/// 衝突したら。(キャラクターが動く床の上に乗ったら)。
//	/// </summary>
//	if (m_collisionObject->IsHit(m_player->GetCharacterController()) == true)
//	{
//		//動く床の移動速度をキャラクターの移動速度に加算。
//		m_player->AddMoveSpeed(moveSpeed);
//	}
//}
//
//void MovingFloor::Render(RenderContext& rc)
//{
//	m_modelRender.Draw(rc);
//}