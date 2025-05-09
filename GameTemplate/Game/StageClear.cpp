#include "stdafx.h"
#include "StageClear.h"
#include "Player.h"
#include "Title.h"

//開始処理
bool StageClear::Start()
{
	//ステージクリアUI
	m_stageClearUI.Init("Assets/Sprite/stageclear.dds", 1024, 128);
	m_stageClearUI.SetPosition(m_position);
	m_stageClearUI.Update();

	//ステージクリアスプライト用のイージングを設定
	SetStageClearSpriteEasing();

	m_player = FindGO<Player>("player");
	m_player->m_stageClearFlag = true;
	return true;
}

//更新処理
void StageClear::Update()
{
	//ステージクリアスプライト用のイージングの更新処理
	UpdateStageClearSpriteEasing();
}

//描画処理
void StageClear::Render(RenderContext& rc)
{
	//ステージクリアUI
	m_stageClearUI.Draw(rc);
}

//ステージクリアスプライト用のイージングを設定
void StageClear::SetStageClearSpriteEasing()
{
	m_beforeEasingPosition = m_position;
	m_afterEasingPosition = Vector3(1250.0f, 275.0f, 0.0f);
	m_easingTime = 0.0f;
}

//ステージクリアスプライト用のイージングの更新処理
void StageClear::UpdateStageClearSpriteEasing()
{
	//特定の位置に行ったらステージクリア演出をする
	if (m_position.x > 0.0f && m_stageClearDirectionFinishFlag != true)
	{
		//1.0秒経過したらステージ演出を終了する
		if (g_gameTime->StopWatch(1.0f))
		{
			m_stageClearDirectionFinishFlag = true;
		}
		return;
	}

	m_easingTime += 0.5f * g_gameTime->GetFrameDeltaTime();

	//割合が1.0f以上になったら割合を固定する
	if (m_easingTime > 1.0f)
	{
		m_easingTime = 1.0f;
	}

	//ステージクリアUIの更新
	m_position.Lerp(m_easingTime, m_beforeEasingPosition, m_afterEasingPosition);
	m_stageClearUI.SetPosition(m_position);
	m_stageClearUI.Update();
}