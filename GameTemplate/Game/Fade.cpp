#include "stdafx.h"
#include "Fade.h"

//開始処理
bool Fade::Start()
{
	//各スプライトの初期設定
	//フェード
	m_fade.Init("Assets/fade/fade.dds", 1600, 900);
	m_fade.SetLinearWipeDrawingMode(LinearWipeDrawingMode_Round);
	m_fade.SetWipeScrollSpeed(1000.0f);

	//ローディング
	m_loading.Init("Assets/fade/loading.dds", 1024,128);
	m_loading.SetPosition(Vector3(475.0f, -345.0f, 0.0f));
	m_loading.SetScale(Vector3(0.75f, 0.75f, 0.75f));
	m_loading.Update();

	//点
	for (int i = 0; i < 3; i++)
	{
		m_point[i].Init("Assets/fade/point.dds", 1024, 128);
		m_point[i].SetPosition(Vector3(665.0f + 25.0f * (i + 1), -345.0f, 0.0f));
		m_pointInitPosition[i] = m_point[i].GetPosition();
		m_pointPosition[i] = m_point[i].GetPosition();
		m_point[i].SetScale(Vector3(0.65f, 0.65f, 0.65f));
		m_point[i].Update();
	}
	return true;
}

//更新処理
void Fade::Update()
{
	//フェードの切り替えをしたか?
	if (m_fadeTransitionFlag != true)
	{
		switch (m_fadeState)
		{
		case enFadeState_FadeIn:	//フェードイン
			//ワイプサイズの設定
			m_fade.SetWipeSize(-50.0f);
			m_fadeTransitionFlag = true;
			break;
		case enFadeState_FadeOut:	//フェードアウト
			//ワイプサイズの設定
			m_fade.SetWipeSize(900.0f);
			m_fadeTransitionFlag = true;
			break;
		default:
			break;
		}
	}

	//フェードステートがローディングのとき
	if (m_fadeState == enFadeState_Loading)
	{
		//ローディングの動作
		LoadingMove();
	}

	//フェードの更新
	m_fade.Update();
}

//ローディングの動作
void Fade::LoadingMove()
{
	//特定の高さまで行ったら
	if (m_pointPosition[m_pointMove].y > m_pointInitPosition[m_pointMove].y + 25.0f)
	{
		m_pointFallFlag = true;
	}

	//点落下
	if (m_pointFallFlag == true)
	{
		m_pointPosition[m_pointMove].y -= 2.0f;
		//特定の位置まで行ったら
		if (m_pointPosition[m_pointMove].y < m_pointInitPosition[m_pointMove].y)
		{
			//位置を固定
			m_pointPosition[m_pointMove].y = m_pointInitPosition[m_pointMove].y;

			//点動作の位置が右なら
			if (m_pointMove == enPoint_Right)
			{
				//点動作の位置を左に変更
				m_pointMove = enPoint_Left;
			}
			else
			{
				//点動作の位置の切り替え
				m_pointMove++;
			}
			m_pointFallFlag = false;
		}
	}
	//点上昇
	else
	{
		m_pointPosition[m_pointMove].y += 2.0f;
	}

	//点の更新
	m_point[m_pointMove].SetPosition(m_pointPosition[m_pointMove]);
	m_point[m_pointMove].Update();
}

//描画処理
void Fade::Render(RenderContext& rc)
{
	//フェード
	//フェードステートがenFadeState_None以外は描画する
	if (m_fadeState != enFadeState_None)
	{
		m_fade.Draw(rc);
	}

	//フェードステートがローディングなら描画する
	if (m_fadeState == enFadeState_Loading)
	{
		//ローディング
		m_loading.Draw(rc);

		//点
		for (int i = 0; i < 3; i++)
		{
			m_point[i].Draw(rc);
		}
	}
}