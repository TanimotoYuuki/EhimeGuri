#include "stdafx.h"
#include "FallingRocks.h"
#include "Config.h"
using namespace std;


bool FallingRocks::Start()
{
	string modelPath = m_config->GetFullPath_3DModel("FallingRocks");// ファイルパスを読み込む。
	m_modelRender.Init(modelPath.c_str());// モデルをセットする。

	// 重力の初期化
	gravity = Vector3(0.0f, -9.8f, 0.0f);

	// 各落石の初期設定
	for (int i = 0; i < MAX_ROCKS; i++)
	{
		m_spawnTimers[i] = 0.0f;
		m_isActive[i] = false;
		// 生成遅延時間を設定（1秒、2秒、3秒）
		m_spawnDelays[i] = (i + 1) * 1.0f;
		// 初期位置を設定（少しずつずらして配置）
		m_rockPositions[i] = m_position + Vector3(i * 100.0f, 0.0f, 0.0f);
	}

	m_modelRender.Update(); // モデルを更新する。
	return true;
}

// 更新処理。
void FallingRocks::Update()
{
	// 落石処理。
	Move();

	// モデルの位置を更新
	m_modelRender.SetPosition(position);
	m_modelRender.Update();
}

// 動作処理。
void FallingRocks::Move()
{
	// 移動処理はUpdate()に統合
		// 時間を取得する(1フレームあたりの固定値)。
	float deltaTime = 1.0f / 60.0f;

	// 各落石の更新
	for (int i = 0; i < MAX_ROCKS; i++)
	{
		if (!m_isActive[i])
		{
			// 生成タイマーの更新
			m_spawnTimers[i] += deltaTime;

			// 生成遅延時間を超えたら落石をアクティブにする
			if (m_spawnTimers[i] >= m_spawnDelays[i])
			{
				m_isActive[i] = true;
				position = m_rockPositions[i];
				velocity = Vector3::Zero;
			}
		}
		else
		{
			// アクティブな落石の更新
			// 重力による速度の更新
			velocity += gravity * deltaTime;

			// 座標の更新
			position += velocity * deltaTime;

			// 地面に到達したら停止
			if (position.y <= 0.0f)
			{
				position.y = 0.0f;
				velocity = Vector3::Zero;
			}
		}
	}

}

// 描画処理。
void FallingRocks::Render(RenderContext& rc)
{
	// アクティブな落石のみ描画
	for (int i = 0; i < MAX_ROCKS; i++)
	{
		if (m_isActive[i])
		{
			m_modelRender.Draw(rc);
		}
	}
}