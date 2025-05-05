#include "stdafx.h"
#include "ScaffoldBlock.h"

namespace
{
	Vector3 SCALE = Vector3(10.0f, 10.0f, 10.0f); // 大きさ。
	Vector3 COLLISION_HEIGHT = Vector3(0.0f, 250.0f, 0.0f);// コリジョンの高さ。
	Vector3	COLLISION_SIZE = Vector3(500.0f, 3.0f, 225.0f);// コリジョンの大きさ。
}

bool ScaffoldBlock::Start()
{
	// ファイルパス。
	m_modelRender.Init("Assets/modelData/Stage/Assets/kinoko_ashiba_block.tkm", 0, 0, enModelUpAxisZ, false, true);

	// 大きさ。
	m_modelRender.SetScale(SCALE);

	// 更新作業。
	m_modelRender.Update();

	// 当たり判定とコリジョン。
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

// 更新作業。
void ScaffoldBlock::Update()
{
	m_modelRender.Update();
	m_physicsStaticObject.SetPosition(m_position);
	m_collisionObject->SetPosition(m_position + COLLISION_HEIGHT);
}

// 描画処理。
void ScaffoldBlock::Render(RenderContext& rc)
{
	m_modelRender.Draw(rc);
}