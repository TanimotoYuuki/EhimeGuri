#include "stdafx.h"
#include "FallingFloor.h"
#include "Player.h"

#include "Config.h"

// 名前空間。
namespace
{
	const Vector3 SCALE{ 10.0f, 10.0f, 10.0f };// モデルの大きさ。
	const Vector3 COLLISION_HEIGHT(0.0f, 250.0f, 0.0f);// コリジョンの高さ。
	const Vector3 COLLISION_SIZE(500.0f, 3.0f, 225.0f);// コリジョンの大きさ。
	const float SPEED = 340.0f;//モデルの落下速度

}

// 初期化処理。
bool FallingFloor::Start()
{
	m_modelRender.Init("Assets/modelData/FallingFloor/FallingFloor.tkm");
//	m_modelRender.Init("Assets/modelData/FallingFloor.tkm");



	m_modelRender.SetScale(SCALE);
	m_modelRender.Update();
	m_player = FindGO<Player>("player");

	// コリジョンをnew
	m_collisionObject = NewGO<CollisionObject>(0, "collisionobject");


	//コリジョンを設置。
	m_collisionObject->CreateBox
	(
		m_position + COLLISION_HEIGHT,
		Quaternion::Identity,
		COLLISION_SIZE
	);
	m_modelRender.SetPosition(m_position);

	m_collisionObject->SetIsEnableAutoDelete(false);

	// 座標を設定する。
	m_modelRender.SetPosition(m_position);

	return true;// 戻り値を設定。
}

// 更新処理。
void FallingFloor::Update()
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


	//コリジョンオブジェクトとプレイヤーのキャラクターコントローラーが。
	//衝突したら。(キャラクターが落下する床の上に乗ったら)。
	if (m_collisionObject->IsHit(m_player->GetCharacterController()) == true)
	{
		if (distanceX.Length() < 350.0f && distanceY.Length() < 350.0f && m_player->m_characterController.IsOnGround())
		{
			Floor();
		}
	}

	//Playerがリスポーンすると座標をm_initPositionに
	if (m_player->IsPlayerRespawn())
	{
		m_position = m_initPosition;
		m_modelRender.SetPosition(m_position);
	}

	m_physicsStaticObject->SetPosition(m_position);
	m_collisionObject->SetPosition(m_position + COLLISION_HEIGHT);

	m_modelRender.Update();// 更新処理。
}

// 落下処理。
void FallingFloor::Floor()
{
	Vector3 moveSpeed = Vector3::Zero;
	m_modelRender.Update();

	//ステートがRightになったら下降
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

// 描画処理。
void FallingFloor::Render(RenderContext& rc)
{
	m_modelRender.Draw(rc);// 描画処理。
}