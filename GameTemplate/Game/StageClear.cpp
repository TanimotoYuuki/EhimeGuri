#include "stdafx.h"
#include "StageClear.h"
#include "Player.h"

bool StageClear::Start()
{
	//ステージクリア
	m_stageClear.Init("Assets/Sprite/stageclear.dds", 1024, 128);
	m_stageClear.SetPosition(m_position);
	m_stageClear.Update();

	//ステージクリアスプライト用のイージングを設定
	SetStageClearSpriteEasing();

	m_player = FindGO<Player>("player");
	return true;
}

void StageClear::Update()
{
	//ステージクリアスプライト用のイージングの更新処理
	UpdateStageClearSpriteEaging();
}

void StageClear::Render(RenderContext& rc)
{
	m_stageClear.Draw(rc);
}

//ステージクリアスプライト用のイージングを設定
void StageClear::SetStageClearSpriteEasing()
{
	m_beforeEasingPosition = m_position;
	m_afterEasingPosition = Vector3(1250.0f, 275.0f, 0.0f);
	m_easingTime = 0.0f;
}

//ステージクリアスプライト用のイージングの更新処理
void StageClear::UpdateStageClearSpriteEaging()
{
	//特定の位置に行ったらステージクリア演出をする
	if (m_position.x > 0.0f && m_gameClearRenditionFinishFlag != true)
	{
		if (g_gameTime->StopWatch(1.0f))
		{
			m_gameClearRenditionFinishFlag = true;
		}
		return;
	}

	m_easingTime += 0.5f * g_gameTime->GetFrameDeltaTime();

	if (m_easingTime > 1.0f)
	{
		m_easingTime = 1.0f;
		DeleteGO(this);
	}

	m_position.Lerp(m_easingTime, m_beforeEasingPosition, m_afterEasingPosition);
	m_stageClear.SetPosition(m_position);
	m_stageClear.Update();
}