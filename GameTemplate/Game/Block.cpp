#include "stdafx.h"
#include "Block.h"
#include"Player.h"
namespace
{
//	Vector3 SCALE = Vector3(5.0f, 5.0f, 5.0f);
	Vector3 COLLISION_HEIGHT = Vector3(0.0f, 50.0f, 0.0f);
	Vector3	COLLISION_SIZE = Vector3(365.0f, 5.0f, 225.0f);

}

Block::Block()
{

}

Block::~Block()
{

}

bool Block::Start()
{
	m_modelRender.Init("Assets/modelData/Stage/Assets/叩かれたあとのブロック.tkm", 0, 0, enModelUpAxisZ, false, true);
//	m_modelRender.SetScale(SCALE);
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
	m_blockTouchDistance = m_player->m_position - m_position;
	if (m_blockTouchDistanceX.Length() < 50.0f)
	{
		//一定の距離まで行っていたら
		if (m_blockTouchDistance.Length() < 80.0f)
		{
			//ブロックに当たった時のプレイヤーの動き
			m_player->m_moveSpeed.y = m_position.y - 650.0f;
		}
	}
	
}

void Block::Render(RenderContext& rc)
{
	m_modelRender.Draw(rc);
}