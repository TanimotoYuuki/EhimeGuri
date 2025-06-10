#include "stdafx.h"
#include "GameTimer.h"
#include "Fade.h"

GameTimer::~GameTimer() 
{

}

bool GameTimer::Start()
{
	//各スプライトの初期化
	//タイマーUI
	//0 タイマーUIの初期化
	m_timerUI.Init("Assets/Sprite/gametime/timer.dds", 1024, 1024);
	//0.1 タイマーUIの位置の設定
	m_timerUI.SetPosition(Vector3(-50.0f, 400.0f, 0.0f));
	//0.2 タイマーUIの大きさの設定
	m_timerUI.SetScale(Vector3(0.1f, 0.1f, 0.1f));
	//0.3 タイマーUIの乗算カラーの設定
	m_timerUI.SetMulColor(Vector4(1.0f, 1.0f, 1.0f, 1.0f));
	//0.4 タイマーUIの更新
	m_timerUI.Update();

	//数字UI
	for (int i = 0; i < enNumber_Num; i++)
	{
		//1 数字UIの初期化
		std::string filePath = "Assets/Sprite/gametime/number/" + std::to_string(i) + ".dds";
		m_hundredPlaceNumberUI[i].Init(filePath.c_str(), 1024, 128);
		m_tenPlaceNumberUI[i].Init(filePath.c_str(), 1024, 128);
		m_onePlaceNumberUI[i].Init(filePath.c_str(), 1024, 128);

		//1.1 数字UIの位置の設定
		m_hundredPlaceNumberUI[i].SetPosition(Vector3(25.0f, 400.0f, 0.0f));
		m_tenPlaceNumberUI[i].SetPosition(Vector3(75.0f, 400.0f, 0.0f));
		m_onePlaceNumberUI[i].SetPosition(Vector3(125.0f, 400.0f, 0.0f));

		//1.2 数字UIの大きさの設定
		m_hundredPlaceNumberUI[i].SetScale(Vector3(0.5f, 0.5f, 0.5f));
		m_tenPlaceNumberUI[i].SetScale(Vector3(0.5f, 0.5f, 0.5f));
		m_onePlaceNumberUI[i].SetScale(Vector3(0.5f, 0.5f, 0.5f));

		//1.3 数字UIの乗算カラーの設定
		m_hundredPlaceNumberUI[i].SetMulColor(Vector4(1.0f, 1.0f, 1.0f, 1.0f));
		m_tenPlaceNumberUI[i].SetMulColor(Vector4(1.0f, 1.0f, 1.0f, 1.0f));
		m_onePlaceNumberUI[i].SetMulColor(Vector4(1.0f, 1.0f, 1.0f, 1.0f));

		//1.4 数字UIの更新
		m_hundredPlaceNumberUI[i].Update();
		m_tenPlaceNumberUI[i].Update();
		m_onePlaceNumberUI[i].Update();
	}

	//インスタンス
	//フェード
	m_fade = FindGO<Fade>("fade");
	return true;
}

void GameTimer::Update()
{
	//タイマーの更新処理
	UpdateTimer();

	//スプライトの動作
	SpriteMove();
}

void GameTimer::Render(RenderContext& rc)
{
	//タイマーUI
	m_timerUI.Draw(rc);

	//数字UI(百の位)
	m_hundredPlaceNumberUI[m_hundredPlace].Draw(rc);

	//数字UI(十の位)
	m_tenPlaceNumberUI[m_tenPlace].Draw(rc);

	//数字UI(一の位)
	m_onePlaceNumberUI[m_onePlace].Draw(rc);
}

//タイマーの更新処理
void GameTimer::UpdateTimer()
{
	//フェード用インスタンスがnullptrではないとき
	if (m_fade != nullptr)
	{
		//フェードインが終わったら
		if (m_fade->IsFadeInFinish())
		{
			//時間を動かす
			m_time -= g_gameTime->GetFrameDeltaTime();
		}
	}

	//タイマーが0.0秒以下になったら処理しない。
	if (m_time < 0.0f)
	{
		m_timeUpFlag = true;
		return;
	}

	//タイマーが1000秒未満のとき
	if (m_time < 1000.0f)
	{
		//UIを表示するための計算。
		//百の位。
		m_hundredPlace = m_time / 100;

		//十の位。
		m_tenPlace = (int(m_time) % 100) / 10;

		//一の位。
		m_onePlace = int(m_time) % 10;
	}
	//タイマーが1000秒～のとき
	else
	{
		m_hundredPlace = enNumber_Nine;
		m_tenPlace = enNumber_Nine;
		m_onePlace = enNumber_Nine;
	}
}

//スプライトの動作
void GameTimer::SpriteMove()
{
	//タイマーが50秒未満のとき
	if (m_time < 50.0f)
	{
		//色変化の速度
		m_colorChange += g_gameTime->GetFrameDeltaTime() * 10.0f;

		//cos波で0～1を往復
		float t = (cosf(m_colorChange) * 0.5f) + 0.5f; // t: 0.0～1.0

		//タイマーUI
		m_timerUI.SetMulColor(Vector4(1.0f, t, t, 1.0f));
		m_timerUI.Update();

		//数字UI(百の位)
		m_hundredPlaceNumberUI[m_hundredPlace].SetMulColor(Vector4(1.0f, t, t, 1.0f));
		m_hundredPlaceNumberUI[m_hundredPlace].Update();

		//数字UI(十の位)
		m_tenPlaceNumberUI[m_tenPlace].SetMulColor(Vector4(1.0f, t, t, 1.0f));
		m_tenPlaceNumberUI[m_tenPlace].Update();

		//数字UI(一の位)
		m_onePlaceNumberUI[m_onePlace].SetMulColor(Vector4(1.0f, t, t, 1.0f));
		m_onePlaceNumberUI[m_onePlace].Update();
	}
}