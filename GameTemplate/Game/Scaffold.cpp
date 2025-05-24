#include "stdafx.h"
#include "Scaffold.h"
#include "Config.h"

namespace
{
	const Vector3 SCALE(5.0f, 5.0f, 5.0f);// 大きさ。
    const Vector3 COLLISION_HEIGHT(0.0f, 250.0f, 0.0f);// コリジョンの高さ。
    const Vector3 COLLISION_SIZE(500.0f, 3.0f, 225.0f);// コリジョンの大きさ。
}


bool Scaffold::Start()
{
	string modelPath = m_config-> GetFullPath_3DModel("ashiba_block");// ファイルパスを読み込む。
	m_modelRender.Init(modelPath.c_str(), 0, 0, enModelUpAxisZ, false, true);// モデルをセットする。

	// スケール。
	m_modelRender.SetScale(SCALE);
	
	// モデルの更新。
	m_modelRender.Update();

	//当たり判定とコリジョン。
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
void Scaffold::Update()
{
	m_modelRender.Update();
	m_physicsStaticObject.SetPosition(m_position);
	m_collisionObject->SetPosition(m_position + COLLISION_HEIGHT);

}

// 描画処理。
void Scaffold::Render(RenderContext& rc)
{
	m_modelRender.Draw(rc);
}