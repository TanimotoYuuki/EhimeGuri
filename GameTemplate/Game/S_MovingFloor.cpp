#include "stdafx.h"
#include "S_MovingFloor.h"
#include "MovingFloor.h"
#include "Player.h"
#include "math.h"

namespace
{
	Vector3 SCALE = Vector3(3.0f, 3.0f, 3.0f);
	float S_SPEED = 200.0f;
//	float S_SPEED = 0.0f;

	float LIMITED = 100.0f;
	Vector3 COLLISION_HEIGHT = Vector3(0.0f, 50.0f, 0.0f);
	Vector3	COLLISION_SIZE = Vector3(365.0f, 5.0f, 225.0f);
}

S_MovingFloor::S_MovingFloor()
{

}

S_MovingFloor::~S_MovingFloor()
{

}

bool S_MovingFloor::Start()
{
	//動かしたいオブジェクトのファイルパス
	m_modelRender.Init("Assets/modelData/Stage/Assets/足場ブロック.tkm", 0, 0, enModelUpAxisZ, false, true);
	m_modelRender.SetScale(SCALE);
	m_modelRender.Update();
	//当たり判定
	m_physicsStaticObject.CreateFromModel(m_modelRender.GetModel(), m_modelRender.GetModel().GetWorldMatrix());

	m_collisionObject = NewGO<CollisionObject>(0, "collisionobject");


	//コリジョンを動く床に設置
	m_collisionObject->CreateBox
	(
		m_position + COLLISION_HEIGHT,
		Quaternion::Identity,
		COLLISION_SIZE
	);

	m_collisionObject->SetIsEnableAutoDelete(false);
	m_firstPosition = m_position;

	m_player = FindGO<Player>("player");
	return true;

}



void S_MovingFloor::Move()
{	

	if (m_movingFloorState == enMovingFloorState_MovingRight)
	{
		moveSpeed.y = -S_SPEED;
	}

	else if (m_movingFloorState == enMovingFloorState_MovingLeft)
	{
		moveSpeed.y = +S_SPEED;
	}
	
	m_position += moveSpeed * g_gameTime->GetFrameDeltaTime();

	if (m_movingFloorState == enMovingFloorState_MovingRight)
	{
		if (m_firstPosition.y - LIMITED >= m_position.y)
		{
			m_movingFloorState = enMovingFloorState_MovingLeft;

		}
	}

	else if (m_movingFloorState == enMovingFloorState_MovingLeft)
	{
		if (m_firstPosition.y + LIMITED <= m_position.y)
		{
			m_movingFloorState = enMovingFloorState_MovingRight;
		}
	}


	//コリジョンオブジェクトとプレイヤーのキャラクターコントローラーが。
	//衝突したら。(キャラクターが動く床の上に)。
	if (m_collisionObject->IsHit(m_player->GetCharacterController()) == true && m_player->m_characterController.IsOnGround())
	{
		m_player->SetPosition
		(
			Vector3(m_player->m_position.x, 
							  m_position.y + 
							  COLLISION_HEIGHT.y, 
							  m_player->m_position.z
				    )
		);
		//動く床の移動速度をキャラクターの移動速度に加算。
		m_player->AddMoveSpeed(moveSpeed);

	}

	m_modelRender.Update();

}

//////////////////////
//////↓試作中////////
/////////////////////

//void S_MovingFloor::Trap()
//{
//	Vector3 moveSpeed = Vector3::Zero;
//
//	if (m_movingFloorState == enMovingFloorState_MovingRight)
//	{
//		moveSpeed.y = -S_SPEED;
//	}
//
//
//	else if (m_movingFloorState == enMovingFloorState_MovingLeft)
//	{
//		moveSpeed.y = S_SPEED;
//	}
//
//	m_position += moveSpeed * g_gameTime->GetFrameDeltaTime();
//
//	if (m_movingFloorState == enMovingFloorState_MovingRight)
//	{
//		if (m_firstPosition.y - LIMITED >= m_position.y)
//		{
//			m_movingFloorState = enMovingFloorState_MovingLeft;
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
//
//
//	m_modelRender.SetPosition(m_position);
//
//	//コリジョンオブジェクトとプレイヤーのキャラクターコントローラーが。
//	//衝突したら。(キャラクターが動く床の上に乗ったら)。
//	if (m_collisionObject->IsHit(m_player->GetCharacterController()) == true)
//	{
//		//動く床の移動速度をキャラクターの移動速度に加算。
//		m_player->AddMoveSpeed(moveSpeed);
//	}
//}

//////////////////////
/////↑試作中////////
/////////////////////

void S_MovingFloor::Update()
{

	Vector3 distanceX;
	Vector3 distanceY;

	distanceX.x = m_player->m_position.x - m_position.x;
	distanceY.y = m_player->m_position.y - m_position.y;

	//コリジョンオブジェクトとプレイヤーのキャラクターコントローラーが。
	//衝突したら。(キャラクターが動く床の上に乗ったら)。
	if (m_collisionObject->IsHit(m_player->GetCharacterController()) == true)
	{
		if (distanceX.Length() < 350.0f && distanceY.Length() < 350.0f && m_player->m_characterController.IsOnGround())
		{
			Move();
		}
	}
	
	m_modelRender.Update();

	m_modelRender.SetPosition(m_position);
	m_physicsStaticObject.SetPosition(m_position);
	m_collisionObject->SetPosition(m_position + COLLISION_HEIGHT);
}

void S_MovingFloor::Render(RenderContext& rc)
{
	m_modelRender.Draw(rc);
}