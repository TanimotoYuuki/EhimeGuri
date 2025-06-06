#include "stdafx.h"
#include "RotationFloor.h"
#include "Config.h"

namespace
{
	const Vector3 SCALE{ 10.0f, 10.0f, 10.0f };// モデルの大きさ。
	const Vector3 COLLISION_HEIGHT(0.0f, 250.0f, 0.0f);// コリジョンの高さ。
	const Vector3 COLLISION_SIZE(500.0f, 3.0f, 225.0f);// コリジョンの大きさ。

}

bool RotationFloor::Start()
{
	m_modelRender.Init("Assets/modelData/RotationFloor/RotationFloor.tkm");


	m_modelRender.SetScale(SCALE);

	m_modelRender.Update();// モデルの更新。
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


	return true;
}

void RotationFloor::Update()
{
	m_modelRender.Update();
}

void RotationFloor::Rotation()
{
	m_Rot.AddRotationDegY(2.0f);

	//絵描きさんに回転を教える。
	m_modelRender.SetRotation(m_Rot);

}

void RotationFloor::Render(RenderContext& rc)
{
	m_modelRender.Draw(rc);
}