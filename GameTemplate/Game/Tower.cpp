#include "stdafx.h"
#include "Tower.h"
#include "Config.h"
#include "Player.h"

namespace
{
	const float LIMITED = 300.0f;// 制限範囲。
	const float SPEED = 500.0f; // 移動速度。

	const Vector3 SCALE(1.5f, 3.0f, 3.0f);
	const Vector3 COLLISION_HEIGHT(0.0f, 600.0f, 0.0f);// コリジョンの高さ。
	const Vector3 COLLISION_SIZE(60.0f, 5.0f, 60.0f);// コリジョンの大きさ。

}

bool Tower::Start()
{

	m_modelRender.Init("Assets/modelData/Tower/Tower.tkm", 0, 0, enModelUpAxisZ, false, true);

	m_modelRender.SetScale(SCALE);
	m_modelRender.Update();
	//当たり判定
	m_physicsStaticObject.CreateFromModel(m_modelRender.GetModel(), m_modelRender.GetModel().GetWorldMatrix());

	m_collisionObject = NewGO<CollisionObject>(0, "collisionobject");

	//コリジョンを動く床に設置
	m_collisionObject->CreateBox
	(
		m_position + COLLISION_HEIGHT,
		Quaternion::Identity,
		COLLISION_SIZE
	);

	// コリジョンの破棄。
	m_collisionObject->SetIsEnableAutoDelete(false);
	m_firstPosition = m_position;


	m_modelRender.Update();
	m_player = FindGO<Player>("Player");
	return true;
}

// 更新処理。
void Tower::Update()
{
	if (m_player == nullptr)
	{
		m_player = FindGO<Player>("player");
		return;
	}

	Move();
	m_modelRender.Update();

	m_physicsStaticObject.SetPosition(m_position);
	m_collisionObject->SetPosition(m_position + COLLISION_HEIGHT);
}

// 動作処理。
void Tower::Move()
{
	// 移動速度の初期化。
	Vector3 moveSpeed = Vector3::Zero;

	// ステートがRightになったら。
	if (m_movingFloorState == enMovingFloorState_MovingRight)
	{
		// 下降。
		moveSpeed.y = -SPEED;
	}

	// ステートがLeftになったら。
	else if (m_movingFloorState == enMovingFloorState_MovingLeft)
	{
		// 上昇。
		moveSpeed.y = SPEED;
	}

	// 座標の更新。
	m_position += moveSpeed * g_gameTime->GetFrameDeltaTime();

	// ステートがRightの場合。
	if (m_movingFloorState == enMovingFloorState_MovingRight)
	{
		// LIMITEDがx座標に到達したら。
		if (m_firstPosition.y - LIMITED >= m_position.y)
		{
			// ステートを切り替える。
			m_movingFloorState = enMovingFloorState_MovingLeft;
		}
	}

	// ステートがLeftの場合。
	else if (m_movingFloorState == enMovingFloorState_MovingLeft)
	{
		// LIMITEDがx座標に到達したら。
		if (m_firstPosition.y + LIMITED <= m_position.y)
		{
			// ステートを切り替える。
			m_movingFloorState = enMovingFloorState_MovingRight;
		}
	}
	m_modelRender.Update();
	m_modelRender.SetPosition(m_position);

	//プレイヤーがジャンプしているとき
	if (!m_player->m_characterController.IsOnGround())
	{
		//プレイヤーがタワーでジャンプしたら処理しない。
		if (m_playerTowerJumpFlag)
		{
			return;
		}

		//タワーのコリジョンの衝突判定
		TowerCollisionDetection();

		//タワーのコリジョンに衝突していたら
		if (!m_isNotHitTowerCollision)
		{
			//慣性を考慮したジャンプをする。
			m_player->m_moveSpeed.y += moveSpeed.y;
			m_playerTowerJumpFlag = true;
		}
	}
	//プレイヤーがジャンプしていないとき
	else
	{
		//地面に着地したらフラグをリセット
		m_isHitTowerCollision = false;
		m_isNotHitTowerCollision = false;
		m_playerTowerJumpFlag = false;
	}
}

void Tower::Render(RenderContext& rc)
{
	m_modelRender.Draw(rc);
}

void Tower::TowerCollisionDetection()
{
	//タワーのコリジョンに衝突したら
	if (m_collisionObject->IsHit(m_player->m_characterController))
	{
		m_isHitTowerCollision = true;
	}
	//タワー以外のコリジョンに衝突したら
	else
	{
		m_isNotHitTowerCollision = true;
	}
}