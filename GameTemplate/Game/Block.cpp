#include "stdafx.h"
#include "Block.h"
#include"Player.h"
namespace
{
	Vector3 COLLISION_HEIGHT = Vector3(0.0f, 50.0f, 0.0f);
	Vector3	COLLISION_SIZE = Vector3(100.0f, 100.0f, 25.0f);
}

Block::Block()
{

}

Block::~Block()
{

}

bool Block::Start()
{
	m_modelRender.Init("Assets/modelData/Stage/Assets/tatakareta_ato_no_block.tkm", 0, 0, enModelUpAxisZ, false, true);
	m_modelRender.Update();
	//当たり判定
	m_physicsStaticObject.CreateFromModel(m_modelRender.GetModel(), m_modelRender.GetModel().GetWorldMatrix());

	m_collisionObject = NewGO<CollisionObject>(0, "collisionobject");
	m_player = FindGO<Player>("player");

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

void Block::Update()
{

	m_modelRender.Update();
	m_physicsStaticObject.SetPosition(m_position);
	m_collisionObject->SetPosition(m_position + COLLISION_HEIGHT);
	m_blockTouchDistanceX.x = m_player->m_position.x - m_position.x;
	if (m_blockTouchDistanceX.Length() < 50.0f)
	{
		//プレイヤーとブロックのコリジョンが衝突したらプレイヤーが落下する
		if (m_collisionObject->IsHit(m_player->GetCharacterController()) == true)
		{
			//ブロックに当たった時のプレイヤーの動き
			m_player->m_moveSpeed.y = m_position.y - 500.0f;
		}
	}
	
}

void Block::Render(RenderContext& rc)
{
	m_modelRender.Draw(rc);
}