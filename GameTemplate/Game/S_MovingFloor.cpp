#include "stdafx.h"
#include "S_MovingFloor.h"
#include "MovingFloor.h"
#include "Player.h"
#include "math.h"

namespace
{
	Vector3 SCALE = Vector3(3.0f, 3.0f, 3.0f);// オブジェクトの大きさ。
	const float S_SPEED = 200.0f;// 落下速度。
	const float LIMITED = 100.0f;// 落下範囲。
	Vector3 COLLISION_HEIGHT = Vector3(0.0f, 50.0f, 0.0f);// コリジョンの高さ。
	Vector3	COLLISION_SIZE = Vector3(365.0f, 5.0f, 225.0f);// コリジョンの大きさ。
}

bool S_MovingFloor::Start()
{
	//動かしたいオブジェクトのファイルパス
	m_modelRender.Init("Assets/modelData/Stage/Assets/ashiba_block.tkm", 0, 0, enModelUpAxisZ, false, true);
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

// 更新作業。
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

// 移動処理。
void S_MovingFloor::Move()
{	
	// ステートがRightなら。
	if (m_movingFloorState == enMovingFloorState_MovingRight)
	{
		// 下降。
		moveSpeed.y = -S_SPEED;
	}

	// ステートがLeftなら。
	else if (m_movingFloorState == enMovingFloorState_MovingLeft)
	{
		// 上昇。
		moveSpeed.y = +S_SPEED;
	}
	
	// 座標の更新。
	m_position += moveSpeed * g_gameTime->GetFrameDeltaTime();

	// ステートがRightなら。
	if (m_movingFloorState == enMovingFloorState_MovingRight)
	{
		// y座標がLIMITEDに達したら。
		if (m_firstPosition.y - LIMITED >= m_position.y)
		{
			// ステートをLeftに。
			m_movingFloorState = enMovingFloorState_MovingLeft;
		}
	}

	// ステートがLeftなら。
	else if (m_movingFloorState == enMovingFloorState_MovingLeft)
	{
		// y座標がLIMITEDに達したら。
		if (m_firstPosition.y + LIMITED <= m_position.y)
		{
			// ステートをRightに。
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

// 描画処理。
void S_MovingFloor::Render(RenderContext& rc)
{
	m_modelRender.Draw(rc);
}