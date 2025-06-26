#include "stdafx.h"
#include "RotationFloor.h"
#include "Config.h"
#include "Player.h"

namespace
{
	const Vector3 SCALE{ 5.0f, 5.0f, 5.0f };// モデルの大きさ。
	const Vector3 COLLISION_HEIGHT(0.0f, 250.0f, 0.0f);// コリジョンの高さ。
	const Vector3 COLLISION_SIZE(500.0f, 3.0f, 225.0f);// コリジョンの大きさ。

}

bool RotationFloor::Start()
{
	m_modelRender.Init("Assets/modelData/RotationFloor/RotationFloor.tkm", 0, 0, enModelUpAxisZ, false, true);


	m_modelRender.SetScale(SCALE);

	m_modelRender.Update();// モデルの更新。

	// コリジョン。
	m_collisionObject = NewGO<CollisionObject>(0, "collisionobject");


	m_physicsStaticObject.CreateFromModel// 静的物理オブジェクトの作成。
	(
		m_modelRender.GetModel(),
		m_modelRender.GetModel().GetWorldMatrix()
	);

	m_collisionObject->CreateBox// コリジョンの作成。
	(
		m_position + COLLISION_HEIGHT,
		Quaternion::Identity,
		COLLISION_SIZE
	);
	m_collisionObject->SetIsEnableAutoDelete(false);// コリジョンの破棄。
	// 座標を設定。
	m_modelRender.SetPosition(m_position);

		// 探索処理。
	m_player = FindGO<Player>("player");

	return true;
}

void RotationFloor::Update()
{
	// 探索処理。
	if (m_player == nullptr)
	{
		m_player = FindGO<Player>("player");
		return;
	}

	// 回転処理。
	Rotation();

	// 当たり判定。
	m_physicsStaticObject.Release();
	m_physicsStaticObject.CreateFromModel
	(
		m_modelRender.GetModel(),
		m_modelRender.GetModel().GetWorldMatrix()
	);

	// コリジョン。
	m_collisionObject->SetPosition(m_position + COLLISION_HEIGHT);


	//m_modelRender.SetPosition(m_position);
	m_modelRender.SetRotation(m_Rot);
	m_modelRender.Update();
}

void RotationFloor::Rotation()
{

	m_Rot.AddRotationDegY(2);

	//絵描きさんに回転を教える。
	m_modelRender.SetRotation(m_Rot);


}

void RotationFloor::Render(RenderContext& rc)
{
	m_modelRender.Draw(rc);
}