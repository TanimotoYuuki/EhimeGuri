#include "stdafx.h"
#include "HS_FallingBlock.h"
#include "MovingFloor.h"
#include "GameOver.h"
#include "Player.h"

namespace
{
	Vector3 HIGHSPEED_FBLOCK_SCALE = Vector3(1.5f, 1.5f, 5.0f);
	float HIGHT_SPEED = 1500.0f;
	float LIMITED = 2000.0f;
}

HS_FallingBlock::HS_FallingBlock()
{
	
}

HS_FallingBlock::~HS_FallingBlock()
{
}

bool HS_FallingBlock::Start()
{
	m_modelRender.Init("Assets/modelData/Stage/Assets/足場ブロック.tkm", 0, 0, enModelUpAxisZ, false, true);
	m_modelRender.SetScale(HIGHSPEED_FBLOCK_SCALE);
	m_modelRender.Update();

	m_player = FindGO<Player>("player");
	m_movingFloor = FindGO<MovingFloor>("movingfloor");


	m_modelRender.SetPosition(m_position);
	return true;

}

void HS_FallingBlock::Move()
{
	Vector3 moveSpeed = Vector3::Zero;

	m_modelRender.Update();

	//落下速度
	if (m_movingFloorState == enMovingFloorState_MovingRight)
	{
		moveSpeed.y = -HIGHT_SPEED;
	}

	m_position += moveSpeed * g_gameTime->GetFrameDeltaTime();

	if (m_movingFloorState == enMovingFloorState_MovingRight)
	{
		if (m_firstposition.y - LIMITED >= m_position.y)
		{
			m_movingFloorState = enMovingFloorState_MovingLeft;
		}
	}

	m_modelRender.SetPosition(m_position);

	//コリジョンオブジェクトとプレイヤーのキャラクターコントローラーが。
	//衝突したら。(キャラクターが動く床の上に乗ったら)。
	if (m_collisionObject->IsHit(m_player->GetCharacterController()) == true)
	{
		//動く床の移動速度をキャラクターの移動速度に加算。
		m_player->AddMoveSpeed(moveSpeed);
	}
}

void HS_FallingBlock::Update()
{
	Vector3 distanceX;
	Vector3 distanceY;
	distanceX.x = m_player->m_position.x - m_position.x;
	distanceY.y = m_player->m_position.y - m_position.y;


	if (m_player == nullptr)
	{
		m_player = FindGO<Player>("player");
		return;
	}

	//動作処理
	if (distanceY.Length() <= 300.0f && m_player->m_characterController.IsOnGround())
	{
		Move();
	}

	m_modelRender.SetPosition(m_position);
	Vector3 diffX;
	diffX.x = m_position.x - m_player->m_position.x;
	Vector3 diffY;
	diffY.y = m_position.y - m_player->m_position.y;

	//if (diffX.Length() < 70.0f && diffY.Length() < 10.0f)
	//{
	//	NewGO<GameOver>(0, "gameover");
	//	DeleteGO(this);
	//}

	m_modelRender.Update();
//	m_physicsStaticObject.SetPosition(m_position);
//	m_collisionObject->SetPosition(m_position + COLLISION_HEIGHT);

}

void HS_FallingBlock::Render(RenderContext& rc)
{
	m_modelRender.Draw(rc);
}