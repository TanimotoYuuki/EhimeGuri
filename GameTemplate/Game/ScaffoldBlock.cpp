#include "stdafx.h"
#include "ScaffoldBlock.h"

namespace
{
	Vector3 SCALE = Vector3(10.0f, 10.0f, 10.0f);
	Vector3 COLLISION_HEIGHT = Vector3(0.0f, 250.0f, 0.0f);
	Vector3	COLLISION_SIZE = Vector3(500.0f, 3.0f, 225.0f);
}


ScaffoldBlock::ScaffoldBlock()
{

}

ScaffoldBlock::~ScaffoldBlock()
{

}

bool ScaffoldBlock::Start()
{
	m_modelRender.Init("Assets/modelData/Stage/Assets/キノコの足場ブロック.tkm", 0, 0, enModelUpAxisZ, false, true);
	m_modelRender.SetScale(SCALE);
	m_modelRender.Update();
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

void ScaffoldBlock::Update()
{
	m_modelRender.Update();
	m_physicsStaticObject.SetPosition(m_position);
	m_collisionObject->SetPosition(m_position + COLLISION_HEIGHT);
}

void ScaffoldBlock::Render(RenderContext& rc)
{
	m_modelRender.Draw(rc);
}