#include "stdafx.h"
#include "TransparentBlock.h"
#include "Player.h"


TransparentBlock::TransparentBlock()
{

}

TransparentBlock::~TransparentBlock()
{

}

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

void TransparentBlock::Update()
{
	//距離を求める
	//透明ブロックを叩いたか？
	if (m_blockTouchFlag != true)
	{
		//X軸はジャンプしていたら距離を求めない
		if (m_position.y > m_player->m_position.y + 75.0f || m_player->m_playerState != m_player->enPlayer_jump)
		{
			m_blockTouchDistanceX.x = m_player->m_position.x - m_position.x;
		}
		m_blockTouchDistanceY.y = m_player->m_position.y - m_position.y;
	}
	else
	{
		m_blockTouchDistanceX.x = m_player->m_position.x - m_position.x;
		m_blockTouchDistance = m_player->m_position - m_position;
	}

	//ブロックを叩いたか？
	if (m_blockTouchFlag != true)
	{
		//一定の距離まで行っていたら
		if (m_blockTouchDistanceX.Length() < 50.0f)
		{
			//一定の距離まで行っていたら
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
					m_physicsStaticObject.CreateFromModel(m_transparentBlockModel.GetModel(), m_transparentBlockModel.GetModel().GetWorldMatrix());
					m_collisionCreatFlag = true;
				}
			}
		}
	}
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

void TransparentBlock::Render(RenderContext& rc)
{
	m_transparentBlockModel.Draw(rc);
}