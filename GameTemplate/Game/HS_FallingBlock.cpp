#include "stdafx.h"
#include "Config.h"
#include "HS_FallingBlock.h"
#include "MovingFloor.h"
#include "GameOver.h"
#include "Player.h"

namespace
{
	Vector3 HIGHSPEED_FBLOCK_SCALE = Vector3(1.5f, 1.5f, 5.0f);
	const float HIGHT_SPEED = 1500.0f;
	const float LIMITED = 2000.0f;
}

bool HS_FallingBlock::Start()
{
	string modelPath = m_config-> GetFullPath_3DModel("ashiba_block");// ファイルパスを読み込む。
	m_modelRender.Init(modelPath.c_str());// モデルをセットする。

	m_modelRender.SetScale(HIGHSPEED_FBLOCK_SCALE);
	m_modelRender.Update();

	m_player = FindGO<Player>("player");
	m_movingFloor = FindGO<MovingFloor>("movingfloor");


	m_modelRender.SetPosition(m_position);
	return true;

}

// 更新作業。
void HS_FallingBlock::Update()
{
	Vector3 distanceX;
	Vector3 distanceY;
	distanceX.x = m_player->m_position.x - m_position.x;
	distanceY.y = m_player->m_position.y - m_position.y;


	if (m_player == nullptr)
	{
		m_player = FindGO<Player>("player");
		return;
	}

	//動作処理
	if (distanceY.Length() <= 300.0f && m_player->m_characterController.IsOnGround())
	{
		Move();
	}

	m_modelRender.SetPosition(m_position);

	m_modelRender.Update();

}

// 移動処理。
void HS_FallingBlock::Move()
{
	// 移動速度の初期化。
	Vector3 moveSpeed = Vector3::Zero;

	// モデルの更新。
	m_modelRender.Update();

	// 落下速度
	if (m_movingFloorState == enMovingFloorState_MovingRight)
	{
		moveSpeed.y = -HIGHT_SPEED;
	}

	// ポジションの更新。
	m_position += moveSpeed * g_gameTime->GetFrameDeltaTime();

	// ステートがRightなら。
	if (m_movingFloorState == enMovingFloorState_MovingRight)
	{
		// LIMITED上限に達したら。
		if (m_firstposition.y - LIMITED >= m_position.y)
		{
			// ステートを切り替える。
			m_movingFloorState = enMovingFloorState_MovingLeft;
		}
	}

	// モデルの座標更新。
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
void HS_FallingBlock::Render(RenderContext& rc)
{
	m_modelRender.Draw(rc);
}