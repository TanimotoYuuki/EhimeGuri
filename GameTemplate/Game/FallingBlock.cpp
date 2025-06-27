#include "stdafx.h"
#include "Config.h"
#include "FallingBlock.h"
#include "GameOver.h"
#include "Player.h"

// 名前空間。
namespace
{
	const float SPEED = 340.0f;//モデルの落下速度
	const float LIMITED = 300.0f;//モデルが動ける上限数
	const float DISTANCE = 350.0f;// 処理が発動する距離。
	const Vector3 COLLISION_HEIGHT(0.0f, 50.0f, 0.0f);//コリジョンの高さ
	const Vector3 COLLISION_SIZE (365.0f, 5.0f, 225.0f);//コリジョンの大きさ
	const Vector3 FALLINGBLOCK_SCALE(3.0f, 3.0f, 5.0f);	//モデルの大きさ

}

FallingBlock::~FallingBlock()
{
	DeleteGO(m_collisionObject);
}

// 初期化処理。
bool FallingBlock::Start()
{
	//ファイルパス
	string modelPath = m_config->GetFullPath_3DModel("ashiba_block");// ファイルパスを読み込む。
	m_modelRender.Init(modelPath.c_str(), 0, 0, enModelUpAxisZ, false, true);// モデルをセットする。
	
	// モデルの大きさ。
	m_modelRender.SetScale(FALLINGBLOCK_SCALE);

	// モデルの更新作業。
	m_modelRender.Update();

	// 探索処理。
	m_player = FindGO<Player>("player");
	m_movingFloor = FindGO<MovingFloor>("movingfloor");

	// 当たり判定。
	m_physicsStaticObject.CreateFromModel(m_modelRender.GetModel(), m_modelRender.GetModel().GetWorldMatrix());

	// コリジョン。
	m_collisionObject = NewGO<CollisionObject>(0, "collisionobject");


	//コリジョンを動く床に設置
	m_collisionObject->CreateBox
	(
		m_position + COLLISION_HEIGHT,
		Quaternion::Identity,
		COLLISION_SIZE
	);

	// 座標を設定。
	m_modelRender.SetPosition(m_position);
	m_initPosition = m_position;

	// コリジョンを破棄。
	m_collisionObject->SetIsEnableAutoDelete(false);
	m_firstposition = m_position;
	return true;
}

// 動作処理。
void FallingBlock::Move()
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

// 更新処理。
void FallingBlock::Update()
{

	if (m_player == nullptr)
	{
		m_player = FindGO<Player>("player");
		return;
	}

	distanceX.x = m_player->m_position.x - m_position.x;
	distanceY.y = m_player->m_position.y - m_position.y;


	//コリジョンオブジェクトとプレイヤーのキャラクターコントローラーが。
	//衝突したら。(キャラクターが落下する床の上に乗ったら)。
	if (m_collisionObject->IsHit(m_player->GetCharacterController()) == true)
	{
		if (distanceX.Length() < DISTANCE && distanceY.Length() < DISTANCE && m_player->m_characterController.IsOnGround())
		{
			Move();
		}
	}

	//Playerがリスポーンすると座標をm_initPositionに
	if (m_player->IsPlayerRespawn()) {
		m_position = m_initPosition;
		m_modelRender.SetPosition(m_position);
	}
	
	// モデルの更新処理。
	m_modelRender.Update();

	// 当たり判定。
	m_physicsStaticObject.SetPosition(m_position);

	// コリジョン。
	m_collisionObject->SetPosition(m_position + COLLISION_HEIGHT);

}

// 描画処理。
void FallingBlock::Render(RenderContext& rc)
{
	m_modelRender.Draw(rc);
}