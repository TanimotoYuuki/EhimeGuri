#include "stdafx.h"
#include "Fade.h"


namespace
{
	const float WIDTH = 1600;
	const float HEIGHT = 900;
	static constexpr const char* SPRITE_PATH = "Assets/fade/fade/fade.dds";// スプライトファイルパス
	static constexpr const char* SPRITE_EXTENSION = ".dds"; // 画像用の拡張子。
}



//開始処理
bool Fade::Start()
{
	//各スプライトの初期設定
	//フェード
	//0 フェードの初期化
	m_fade.Init("Assets/fade/fade.dds", 1600, 900);
	//0.1 リニアワイプの描画モードを円形ワイプにする
	m_fade.SetLinearWipeDrawingMode(LinearWipeDrawingMode_Round);
	//0.2 リニアワイプの速度を設定
	m_fade.SetWipeScrollSpeed(1000.0f);

	//ローディング
	//1 ローディングの初期化
	m_loading.Init("Assets/fade/loading.dds", 1024,128);
	//1.1 ローディングの座標の設定
	m_loading.SetPosition(Vector3(475.0f, -345.0f, 0.0f));
	//1.2 ローディングの大きさの設定
	m_loading.SetScale(Vector3(0.75f, 0.75f, 0.75f));
	//1.3 ローディングの更新処理
	m_loading.Update();

	//点
	for (int i = 0; i < 3; i++)
	{
		//2 点の初期化
		m_point[i].Init("Assets/fade/point.dds", 1024, 128);
		//2.1 点の座標の設定
		m_point[i].SetPosition(Vector3(665.0f + 25.0f * (i + 1), -345.0f, 0.0f));
		//2.2 点の初期位置の取得
		m_pointInitPosition[i] = m_point[i].GetPosition();
		//2.3 点の現在位置の取得
		m_pointPosition[i] = m_point[i].GetPosition();
		//2.4 点の大きさの設定
		m_point[i].SetScale(Vector3(0.65f, 0.65f, 0.65f));
		//2.5 点の更新処理
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
		//フェードステート
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

	//以下の条件になったら
	if ((m_fade.GetWipeSize() > 700.0f && //ワイプサイズが700より大きい
		m_fadeState == enFadeState_FadeIn) //フェードステートがフェードイン
		)
	{
		//フェードイン終了
		m_isFadeInFinish = true;
	}
	else
	{
		//フェードイン終了しない
		m_isFadeInFinish = false;
	}

	//フェードステートがローディングのとき
	if (m_fadeState == enFadeState_Loading)
	{
		//ローディングの動作
		LoadingMove();
	}
	else
	{
		//ローディングの動作用の初期化。
		InitLoadingMove();
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
		//点落下する
		m_pointFallFlag = true;
	}

	//点落下
	if (m_pointFallFlag == true)
	{
		m_pointPosition[m_pointMove].y -= 2.0f;
		//特定の高さまで戻ったら
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
			//点落下しない
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
	m_fade.Draw(rc);

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