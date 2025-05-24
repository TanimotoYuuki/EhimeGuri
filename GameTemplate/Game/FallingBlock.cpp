#include "stdafx.h"
#include "Config.h"
#include "FallingBlock.h"
#include "GameOver.h"
#include "Player.h"

namespace
{
	const Vector3 FALLINGBLOCK_SCALE(3.0f, 3.0f, 5.0f);	//モデルの大きさ
	const float SPEED = 340.0f;//モデルの落下速度
	const float LIMITED = 300.0f;//モデルが動ける上限数
	const Vector3 COLLISION_HEIGHT(0.0f, 50.0f, 0.0f);//コリジョンの高さ
	const Vector3 COLLISION_SIZE (365.0f, 5.0f, 225.0f);//コリジョンの大きさ
}

FallingBlock::FallingBlock()
{
	
}

FallingBlock::~FallingBlock()
{

}

bool FallingBlock::Start()
{
	//ファイルパス
	string modelPath = m_config->GetFullPath_3DModel("ashiba_block");// ファイルパスを読み込む。
	m_modelRender.Init(modelPath.c_str(), 0, 0, enModelUpAxisZ, false, true);// モデルをセットする。
	
	
	m_modelRender.SetScale(FALLINGBLOCK_SCALE);
	m_modelRender.Update();
	m_player = FindGO<Player>("player");
	m_movingFloor = FindGO<MovingFloor>("movingfloor");
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
	m_initPosition = m_position;

	m_collisionObject->SetIsEnableAutoDelete(false);
	m_firstposition = m_position;
	return true;
}

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



void FallingBlock::Update()
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
			Move();
		}
	}

	//Playerがリスポーンすると座標をm_initPositionに
	if (m_player->IsPlayerRespawn()) {
		m_position = m_initPosition;
		m_modelRender.SetPosition(m_position);
	}
	
	m_modelRender.Update();
	m_physicsStaticObject.SetPosition(m_position);
	m_collisionObject->SetPosition(m_position + COLLISION_HEIGHT);
}


void FallingBlock::Render(RenderContext& rc)
{
	m_modelRender.Draw(rc);
}