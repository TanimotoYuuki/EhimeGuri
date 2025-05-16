#include "stdafx.h"
#include "TransparentBlock.h"
#include "Player.h"
namespace
{
	//ブロックの表面
	Vector3 BLOCKSURFACE_COLLISION_HEIGHT = Vector3(0.0f, 51.0f, 0.0f);		//高さ
	Vector3	BLOCKSURFACE_COLLISION_SIZE = Vector3(100.0f, 100.0f, 25.0f);	//大きさ
	//ブロックの底面
	Vector3 BLOCKBOTTOM_COLLISION_HEIGHT = Vector3(0.0f, 0.0f, 0.0f);		//高さ
	Vector3 BLOCKBOTTOM_COLLISION_SIZE = Vector3(100.0f, 0.0f, 25.0f);		//大きさ
}

//開始処理
bool TransparentBlock::Start()
{
	//モデルの初期化
	m_transparentBlockModel.IniTranslucent("Assets/modelData/Stage/Assets/tatakareta_ato_no_block.tkm", 0, 0, enModelUpAxisZ, false, true);
	m_transparentBlockModel.SetPosition(m_position);
	m_transparentBlockModel.Update();

	//モデルを透明に設定
	m_transparentBlockModel.SetAlpha(0.0f);

	//ブロックの表面のコリジョン
	m_blockSurfaceCollision = NewGO<CollisionObject>(0, "collisionobject");
	//ボックス形状のコリジョン作成
	m_blockSurfaceCollision->CreateBox
	(
		m_position + BLOCKSURFACE_COLLISION_HEIGHT,	//位置
		Quaternion::Identity,						//回転
		BLOCKSURFACE_COLLISION_SIZE					//大きさ
	);
	m_blockSurfaceCollision->SetIsEnableAutoDelete(false);

	//ブロックの底面のコリジョン
	m_blockBottomCollision = NewGO<CollisionObject>(0, "collisionobject");
	//ボックス形状のコリジョン作成
	m_blockBottomCollision->CreateBox
	(
		m_position,						//位置
		Quaternion::Identity,			//回転
		BLOCKBOTTOM_COLLISION_SIZE		//大きさ
	);
	m_blockBottomCollision->SetIsEnableAutoDelete(false);

	//インスタンス
	m_player = FindGO<Player>("player");
	return true;
}

//更新処理
void TransparentBlock::Update()
{
	//透明ブロックを叩く用距離(X軸)の計算
	m_blockTouchDistanceX.x = m_player->m_position.x - m_position.x;

	//透明ブロックを叩いていないとき
	if (m_blockTouchFlag != true)
	{
		//X軸で一定の距離まで行っていたら
		if (m_blockTouchDistanceX.Length() < 50.0f)
		{
			//ブロックの表面のコリジョンが衝突していない状態で
			//プレイヤーとブロックの底面のコリジョンが衝突したらプレイヤーが落下するかつモデルを不透明にする
			if (m_blockSurfaceCollision->IsHit(m_player->GetCharacterController()) == false &&
				m_blockBottomCollision->IsHit(m_player->GetCharacterController()) == true
				)
			{
				//ブロックに当たった時のプレイヤーの動き
				m_player->m_moveSpeed.y = m_position.y - 500.0f;

				//求めた落下速度の値がプラスなら反転する
				if (m_player->m_moveSpeed.y > 0.0f)
				{
					m_player->m_moveSpeed.y *= -1.0f;
				}

				//モデルを不透明にする
				m_transparentBlockModel.SetAlpha(1.0f);

				//ブロックを叩いた
				m_blockTouchFlag = true;

				//当たり判定が作られていないか？
				if (m_collisionCreatFlag != true)
				{
					//当たり判定の作成
					m_physicsStaticObject.CreateFromModel(m_transparentBlockModel.GetModel(), m_transparentBlockModel.GetModel().GetWorldMatrix());
					m_collisionCreatFlag = true;
				}
			}
		}
	}
	//透明ブロックを叩いているとき
	else
	{
		//X軸で一定の距離まで行っていたら
		if (m_blockTouchDistanceX.Length() < 50.0f)
		{
			//プレイヤーとブロックの底面のコリジョンが衝突したらプレイヤーが落下する
			if (m_blockBottomCollision->IsHit(m_player->GetCharacterController()) == true)
			{
				//ブロックに当たった時のプレイヤーの動き
				m_player->m_moveSpeed.y = m_position.y - 500.0f;

				//求めた落下速度の値がプラスなら反転する
				if (m_player->m_moveSpeed.y > 0.0f)
				{
					m_player->m_moveSpeed.y *= -1.0f;
				}
			}
		}
	}
}

//描画処理
void TransparentBlock::Render(RenderContext& rc)
{
	//透明ブロック
	m_transparentBlockModel.Draw(rc);
}