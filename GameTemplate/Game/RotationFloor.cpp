#include "stdafx.h"
#include "RotationFloor.h"
#include "Config.h"
#include "Player.h"

namespace
{
	const Vector3 SCALE{ 5.0f, 5.0f, 5.0f };// モデルの大きさ。
	const Vector3 COLLISION_HEIGHT(0.0f, 140.0f, 0.0f);// コリジョンの高さ。
	const Vector3 COLLISION_SIZE(190.0f, 280.0f, 290.0f);// コリジョンの大きさ。

}

RotationFloor::~RotationFloor()
{
	DeleteGO(m_collisionObject);
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
	m_collisionObject->SetRotation(m_Rot);

	//距離を求める
	m_distance = m_position - m_player->m_position;

	//プレイヤーがジャンプしているとき
	if (!m_player->m_characterController.IsOnGround())
	{
		//回転床のコリジョンに衝突したら
		if (m_collisionObject->IsHit(m_player->m_characterController)) {
			//X方向にプレイヤーを移動する
			Vector3 playerPos = m_player->GetPosition();
			if (playerPos.x < m_position.x) {
				playerPos.x -= 22.0f;
			}
			else {
				playerPos.x += 22.0f;
			}
			m_player->m_characterController.SetPosition(playerPos);
			m_player->m_modelRender.SetPosition(playerPos);
			m_player->m_modelRender.Update();
		}
	}

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