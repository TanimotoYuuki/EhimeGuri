#include "stdafx.h"
#include "FallingBlock.h"
#include "GameOver.h"
#include "Player.h"

namespace
{
	Vector3 FALLINGBLOCK_SCALE = Vector3(3.0f, 3.0f, 5.0f);

	float SPEED = 340.0f;
	float LIMITED = 300.0f;
	Vector3 COLLISION_HEIGHT = Vector3(0.0f, 50.0f, 0.0f);
	Vector3	COLLISION_SIZE = Vector3(365.0f, 5.0f, 225.0f);
}

FallingBlock::FallingBlock()
{
	
}

FallingBlock::~FallingBlock()
{

}

bool FallingBlock::Start()
{
	m_modelRender.Init("Assets/modelData/Stage/Assets/足場ブロック.tkm", 0, 0, enModelUpAxisZ, false, true);
	
	
	m_modelRender.SetScale(FALLINGBLOCK_SCALE);
	m_modelRender.Update();
	m_player = FindGO<Player>("player");
	m_movingFloor = FindGO<MovingFloor>("movingfloor");
	m_physicsStaticObject.CreateFromModel(m_modelRender.GetModel(), m_modelRender.GetModel().GetWorldMatrix());

	m_collisionObject = NewGO<CollisionObject>(0, "collisionobject");


	//コリジョンを動く床に設置
	m_collisionObject->CreateBox
	(
		m_position + COLLISION_HEIGHT,
		Quaternion::Identity,
		COLLISION_SIZE
	);

	m_modelRender.SetPosition(m_position);

	m_collisionObject->SetIsEnableAutoDelete(false);
	m_firstposition = m_position;
	return true;
}

void FallingBlock::Move()
{
		Vector3 moveSpeed = Vector3::Zero;
		m_modelRender.Update();

		if (m_movingFloorState == enMovingFloorState_MovingRight)
		{
			moveSpeed.y = -SPEED;
		}
		
		m_position += moveSpeed * g_gameTime->GetFrameDeltaTime();


		m_modelRender.SetPosition(m_position);

		//コリジョンオブジェクトとプレイヤーのキャラクターコントローラーが。
		//衝突したら。(キャラクターが動く床の上に乗ったら)。
		if (m_collisionObject->IsHit(m_player->GetCharacterController()) == true)
		{
			//動く床の移動速度をキャラクターの移動速度に加算。
			m_player->AddMoveSpeed(moveSpeed);
		}
}



void FallingBlock::Update()
{
	if (m_player == nullptr)
	{
		m_player = FindGO<Player>("player");
		return;
	}

	Vector3 distanceX;
	Vector3 distanceY;

	
	distanceX.x = m_player->m_position.x - m_position.x;
	distanceY.y = m_player->m_position.y - m_position.y;


	//通常版の床
	if (distanceX.Length() < 350.0f && distanceY.Length() < 350.0f && m_player->m_characterController.IsOnGround())
	{
		Move();
	}
	
	m_modelRender.Update();
	m_physicsStaticObject.SetPosition(m_position);
	m_collisionObject->SetPosition(m_position + COLLISION_HEIGHT);
}


void FallingBlock::Render(RenderContext& rc)
{
	m_modelRender.Draw(rc);
}