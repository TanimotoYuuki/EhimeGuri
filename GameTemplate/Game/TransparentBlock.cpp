#include "stdafx.h"
#include "Config.h"
#include "TransparentBlock.h"
#include "Player.h"
namespace
{
	//ブロックの表面。
	const Vector3 BLOCKSURFACE_COLLISION_HEIGHT(0.0f, 51.0f, 0.0f);// 高さ。
	const Vector3 BLOCKSURFACE_COLLISION_SIZE(100.0f, 100.0f, 25.0f);// 大きさ。

	//ブロックの底面。
	const Vector3 BLOCKBOTTOM_COLLISION_HEIGHT(0.0f, 0.0f, 0.0f);// 高さ。
	const Vector3 BLOCKBOTTOM_COLLISION_SIZE(100.0f, 0.0f, 25.0f);// 大きさ。

	//ブロックを叩ける距離。
	float BLOCK_TOUCH_DISTANCE = 50.0f;// 距離。

	//透明ブロックをーが叩いたときの動き。
	Vector3 BLOCK_TOUCH_MOVE = Vector3(0.0f, 500.0f, 0.0f);// 動き。
}

//開始処理。
bool TransparentBlock::Start()
{
	//透明ブロック。
	//0 透明ブロックの初期化。
	string modelPath = m_config-> GetFullPath_3DModel("TRANSPARENTBLOCLK");// ファイルパスを読み込む。
	m_transparentBlockModel.IniTranslucent(modelPath.c_str(), 0, 0, enModelUpAxisZ, false, true);// モデルをセットする。
	//0.1 透明ブロックの座標の設定。
	m_transparentBlockModel.SetPosition(m_position);
	//0.2 透明ブロックの更新。
	m_transparentBlockModel.Update();
	//0.3 モデルを透明に設定。
	m_transparentBlockModel.SetAlpha(0.0f);

	//ブロックの表面のコリジョン。
	m_blockSurfaceCollision = NewGO<CollisionObject>(0, "collisionobject");
	//ボックス形状のコリジョン作成。
	m_blockSurfaceCollision->CreateBox
	(
		m_position + BLOCKSURFACE_COLLISION_HEIGHT,	//位置。
		Quaternion::Identity,						//回転。
		BLOCKSURFACE_COLLISION_SIZE					//大きさ。
	);
	m_blockSurfaceCollision->SetIsEnableAutoDelete(false);

	//ブロックの底面のコリジョン。
	m_blockBottomCollision = NewGO<CollisionObject>(0, "collisionobject");
	//ボックス形状のコリジョン作成。
	m_blockBottomCollision->CreateBox
	(
		m_position,						//位置。
		Quaternion::Identity,			//回転。
		BLOCKBOTTOM_COLLISION_SIZE		//大きさ。
	);
	m_blockBottomCollision->SetIsEnableAutoDelete(false);

	//インスタンス。
	//0 プレイヤー。
	m_player = FindGO<Player>("player");
	return true;
}

//更新処理
void TransparentBlock::Update()
{
	//透明ブロックを叩く用距離(X軸)の計算。
	m_blockTouchDistanceX.x = m_player->m_position.x - m_position.x;

	//透明ブロックを叩いていないとき。
	if (m_blockTouchFlag != true)
	{
		//X軸で一定の距離まで行っていたら。
		if (m_blockTouchDistanceX.Length() < BLOCK_TOUCH_DISTANCE)
		{
			//ブロックの表面のコリジョン衝突判定
			BlockSurfaceCollisionHitDetection();

			//ブロックの表面のコリジョンが衝突していない状態で
			//プレイヤーとブロックの底面のコリジョンが衝突したらプレイヤーが落下するかつモデルを不透明にする。
			if (m_blockSurfaceCollisionHitFlag == false &&
				m_blockBottomCollision->IsHit(m_player->GetCharacterController()) == true
				)
			{
				//ブロックに当たった時のプレイヤーの動き。
				m_player->m_moveSpeed.y = m_position.y - BLOCK_TOUCH_MOVE.y;

				//求めた落下速度の値がプラスなら反転する。
				if (m_player->m_moveSpeed.y > 0.0f)
				{
					m_player->m_moveSpeed.y *= -1.0f;
				}

				//モデルを不透明にする。
				m_transparentBlockModel.SetAlpha(1.0f);

				//ブロックを叩いた。
				m_blockTouchFlag = true;

				//当たり判定が作られていないか？
				if (m_collisionCreatFlag != true)
				{
					//当たり判定の作成。
					m_physicsStaticObject.CreateFromModel(m_transparentBlockModel.GetModel(), m_transparentBlockModel.GetModel().GetWorldMatrix());
					m_collisionCreatFlag = true;
				}

				//ブロックを叩いた時の音の再生。
				g_gameSoundEngine->PlaySE(GameSoundList_SE_Object_BlockTouch, 2.0f);
			}
		}
	}

	//透明ブロックを叩いているとき。
	else
	{
		//X軸で一定の距離まで行っていたら。
		if (m_blockTouchDistanceX.Length() < BLOCK_TOUCH_DISTANCE)
		{
			//プレイヤーとブロックの底面のコリジョンが衝突したらプレイヤーが落下する。
			if (m_blockBottomCollision->IsHit(m_player->GetCharacterController()) == true)
			{
				//ブロックに当たった時のプレイヤーの動き。
				m_player->m_moveSpeed.y = m_position.y - BLOCK_TOUCH_MOVE.y;

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
}

//描画処理。
void TransparentBlock::Render(RenderContext& rc)
{
	//透明ブロック。
	m_transparentBlockModel.Draw(rc);
}

//ブロックの表面のコリジョン衝突判定
void TransparentBlock::BlockSurfaceCollisionHitDetection()
{
	//プレイヤーがジャンプしているとき
	if (!m_player->m_characterController.IsOnGround())
	{
		//ブロックの表面のコリジョンに衝突していないとき
		if (m_blockSurfaceCollisionHitFlag != true)
		{
			//プレイヤーがジャンプしているときにブロックの表面のコリジョンが衝突したら
			if (m_blockSurfaceCollision->IsHit(m_player->GetCharacterController()) == true)
			{
				//ブロックの表面のコリジョンに衝突した
				m_blockSurfaceCollisionHitFlag = true;
			}
		}
	}
	else
	{
		//ブロックの表面のコリジョンに衝突していない
		m_blockSurfaceCollisionHitFlag = false;
	}
}