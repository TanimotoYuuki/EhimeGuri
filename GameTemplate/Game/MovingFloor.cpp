#include "stdafx.h"
#include "Config.h"
#include "MovingFloor.h"
#include "Player.h"


namespace
{
	const Vector3 SCALE(3.0f, 1.0f, 3.0f);//オブジェクトの大きさ。
	const float SPEED = 500.0f;// 速度。
	const float LIMITED = 300.0f;// 制限範囲。
	const Vector3 COLLISION_HEIGHT(0.0f, 50.0f, 0.0f);// コリジョンの高さ。
	const Vector3 COLLISION_SIZE(365.0f, 5.0f, 225.0f);// コリジョンの大きさ。
}

MovingFloor::~MovingFloor()
{
	DeleteGO(m_collisionObject);
}

bool MovingFloor::Start()
{
	string modelPath = m_config->GetFullPath_3DModel("ashiba_block");// ファイルパスを読み込む。
	m_modelRender.Init(modelPath.c_str(), 0, 0, enModelUpAxisZ, false, true);// モデルをセットする。

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

	m_player = FindGO<Player>("player");
	return true;

}

// 更新作業。
void MovingFloor::Update()
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
void MovingFloor::Move()
{
	// 移動速度の初期化。
	Vector3 moveSpeed = Vector3::Zero;

	// ステートがRightになったら。
	if (m_movingFloorState == enMovingFloorState_MovingRight)
	{
		// 下降。
		moveSpeed.x = -SPEED;
	}

	// ステートがLeftになったら。
	else if (m_movingFloorState == enMovingFloorState_MovingLeft)
	{
		// 上昇。
		moveSpeed.x = SPEED;
	}

	// 座標の更新。
	m_position += moveSpeed * g_gameTime->GetFrameDeltaTime();

	// ステートがRightの場合。
	if (m_movingFloorState == enMovingFloorState_MovingRight)
	{
		// LIMITEDがx座標に到達したら。
		if (m_firstPosition.x - LIMITED >= m_position.x)
		{
			// ステートを切り替える。
			m_movingFloorState = enMovingFloorState_MovingLeft;
		}
	}

	// ステートがLeftの場合。
	else if (m_movingFloorState == enMovingFloorState_MovingLeft)
	{
		// LIMITEDがx座標に到達したら。
		if (m_firstPosition.x + LIMITED <= m_position.x)
		{
			// ステートを切り替える。
			m_movingFloorState = enMovingFloorState_MovingRight;
		}
	}

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
void MovingFloor::Render(RenderContext& rc)
{
	m_modelRender.Draw(rc);
}