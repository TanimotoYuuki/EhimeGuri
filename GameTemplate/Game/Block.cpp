#include "stdafx.h"
#include "Block.h"
#include"Player.h"
#include "Config.h"

namespace
{
  const	Vector3 COLLISION_HEIGHT(0.0f, 50.0f, 0.0f);
  const	Vector3 COLLISION_SIZE(100.0f, 100.0f, 25.0f);
}


// 初期化処理。
bool Block::Start()
{
	string modelPath = m_config->GetFullPath_3DModel("TRANSPARENTBLOCLK");// ファイルパスを読み込む。
	m_modelRender.Init(modelPath.c_str(), 0, 0, enModelUpAxisZ, false, true);// モデルをセットする。

	m_modelRender.Update();
	//当たり判定。
	m_physicsStaticObject.CreateFromModel(m_modelRender.GetModel(), m_modelRender.GetModel().GetWorldMatrix());

	m_collisionObject = NewGO<CollisionObject>(0, "collisionobject");
	m_player = FindGO<Player>("player");

	//コリジョンを動く床に設置。
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

// 更新処理。
void Block::Update()
{

	m_modelRender.Update();
	m_physicsStaticObject.SetPosition(m_position);
	m_collisionObject->SetPosition(m_position + COLLISION_HEIGHT);
	m_blockTouchDistanceX.x = m_player->m_position.x - m_position.x;
	if (m_blockTouchDistanceX.Length() < 50.0f)
	{
		//プレイヤーとブロックのコリジョンが衝突したらプレイヤーが落下する。
		if (m_collisionObject->IsHit(m_player->GetCharacterController()) == true)
		{
			//ブロックに当たった時のプレイヤーの動き。
			m_player->m_moveSpeed.y = m_position.y - 500.0f;

			//求めた落下速度の値がプラスなら反転する。
			if (m_player->m_moveSpeed.y > 0.0f)
			{
				m_player->m_moveSpeed.y *= -1.0f;
			}

			//ブロックを叩いた時の音の再生。
			g_gameSoundEngine->PlaySE(GameSoundList_SE_Object_BlockTouch, 2.0f);
		}
	}
	
}

// 描画処理。
void Block::Render(RenderContext& rc)
{
	m_modelRender.Draw(rc);
}