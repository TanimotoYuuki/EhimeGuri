#include "stdafx.h"
#include "TransparentBlock.h"
#include "Player.h"

//開始処理
bool TransparentBlock::Start()
{
	//モデルの初期化
	m_transparentBlockModel.IniTranslucent("Assets/modelData/Stage/Assets/tatakareta_ato_no_block.tkm", 0, 0, enModelUpAxisZ, false, true);
	m_transparentBlockModel.SetPosition(m_position);
	m_transparentBlockModel.Update();

	//モデルを透明に設定
	m_transparentBlockModel.SetAlpha(0.0f);

	//インスタンス
	m_player = FindGO<Player>("player");
	return true;
}

//更新処理
void TransparentBlock::Update()
{
	//距離を求める
	//透明ブロックを叩いていないか
	if (m_blockTouchFlag != true)
	{
		//X軸はY軸で一定の距離まで行くまたはジャンプしていなかったら距離を求めない
		if (m_position.y > m_player->m_position.y + 75.0f || m_player->m_playerState != m_player->enPlayer_jump)
		{
			//透明ブロックを叩く用距離(X軸)の計算
			m_blockTouchDistanceX.x = m_player->m_position.x - m_position.x;
		}
		//透明ブロックを叩く用距離(Y軸)の計算
		m_blockTouchDistanceY.y = m_player->m_position.y - m_position.y;
	}
	else
	{
		//透明ブロックを叩く用距離(X軸)の計算
		m_blockTouchDistanceX.x = m_player->m_position.x - m_position.x;
		//透明ブロックを叩く用距離(Y軸)の計算
		m_blockTouchDistance = m_player->m_position - m_position;
	}

	//透明ブロックを叩いていないとき
	if (m_blockTouchFlag != true)
	{
		//X軸で一定の距離まで行っていたら
		if (m_blockTouchDistanceX.Length() < 50.0f)
		{
			//Y軸で一定の距離まで行っていたら
			if (m_blockTouchDistanceY.Length() < 70.0f)
			{
				//ブロックに当たった時のプレイヤーの動き
				m_player->m_moveSpeed.y = m_position.y - 650.0f;

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
		//一定の距離まで行っていたら
		if (m_blockTouchDistanceX.Length() < 50.0f)
		{
			//一定の距離まで行っていたら
			if (m_blockTouchDistance.Length() < 70.0f)
			{
				//ブロックに当たった時のプレイヤーの動き
				m_player->m_moveSpeed.y = m_position.y - 650.0f;
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