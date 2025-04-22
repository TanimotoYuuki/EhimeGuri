#include "stdafx.h"
#include "GameOver.h"
#include "Player.h"
#include "Fade.h"
#include "Title.h"
#include "Game.h"

GameOver::~GameOver()
{
	DeleteGO(m_fade);
}

bool GameOver::Start()
{
	//スプライトの初期化
	InitSprite();

	m_player = FindGO<Player>("player");
	m_player->m_gameoverFlag = true;

	NewGO<Fade>(0, "fade");
	m_fade = FindGO<Fade>("fade");
	m_fade->FadeTransition(enFadeState_None);

	m_game = FindGO<Game>("game");
	return true;
}

void GameOver::Update()
{
	//スプライトの動作
	SpriteMove();

	//ゲームオーバー演出が終わったら
	if (m_gameOverDirectionFlag == true)
	{
		//プレイヤーの操作
		Action();
	}
}

void GameOver::Render(RenderContext& rc)
{
	//ゲームオーバーUI
	m_gameOverUI.Draw(rc);

	//選択UI(コンティニュー)
	m_selectUI[enSelect_Continue].Draw(rc);

	//選択UI(タイトルへ戻る)
	m_selectUI[enSelect_ReturnTitle].Draw(rc);

	//ゲームオーバー演出が終わったら
	if (m_gameOverDirectionFlag == true)
	{
		//AボタンUI
		m_aButtonUI.Draw(rc);

		//決定UI
		m_decisionUI.Draw(rc);
	}
}

//スプライトの初期化
void GameOver::InitSprite()
{
	//ゲームオーバーUI
	m_gameOverUI.Init("Assets/gameover/text/gameover.dds", 1024, 128);
	m_gameOverUI.SetPosition(m_gameOverUIPosition);
	m_gameOverUIRotation.SetRotationDegZ(20.0f);
	m_gameOverUI.SetRotation(m_gameOverUIRotation);
	m_gameOverUI.SetPivot(Vector2(0.5f, 0.0f));
	m_gameOverUI.Update();

	//選択UI(コンティニュー)
	m_selectUI[enSelect_Continue].Init("Assets/gameover/text/continue.dds", 1024, 128);
	m_selectUI[enSelect_Continue].SetPosition(Vector3(-250.0f, -200.0f, 0.0f));
	m_selectUI[enSelect_Continue].SetScale(Vector3(0.5f, 0.5f, 0.5f));
	m_selectUI[enSelect_Continue].SetMulColor(Vector4(1.0f, 1.0f, 1.0f, 1.0f));
	m_selectUIColor[enSelect_Continue] = m_selectUI[enSelect_Continue].GetMulColor();
	m_selectUI[enSelect_Continue].SetMulColor(Vector4(1.0f, 1.0f, 1.0f, 0.0f));
	m_selectUI[enSelect_Continue].Update();

	//選択UI(タイトルへ戻る)
	m_selectUI[enSelect_ReturnTitle].Init("Assets/gameover/text/returntitle.dds", 1024, 128);
	m_selectUI[enSelect_ReturnTitle].SetPosition(Vector3(250.0f, -200.0f, 0.0f));
	m_selectUI[enSelect_ReturnTitle].SetScale(Vector3(0.5f, 0.5f, 0.5f));
	m_selectUI[enSelect_ReturnTitle].SetMulColor(Vector4(1.0f, 1.0f, 1.0f, 1.0f));
	m_selectUIColor[enSelect_ReturnTitle] = m_selectUI[enSelect_ReturnTitle].GetMulColor();
	m_selectUI[enSelect_ReturnTitle].SetMulColor(Vector4(1.0f, 1.0f, 1.0f, 0.0f));
	m_selectUI[enSelect_ReturnTitle].Update();

	//AボタンUI
	m_aButtonUI.Init("Assets/gameover/gamepad/abutton.dds", 512, 512);
	m_aButtonUI.SetPosition(Vector3(Vector3(525.0f, -345.0f, 0.0f)));
	m_aButtonUI.SetScale(Vector3(0.1f, 0.1f, 0.1f));
	m_aButtonUI.Update();

	//決定UI
	m_decisionUI.Init("Assets/gameover/text/decision.dds", 1024, 128);
	m_decisionUI.SetPosition(Vector3(600.0f, -345.0f, 0.0f));
	m_decisionUI.SetScale(Vector3(0.3f, 0.3f, 0.3f));
	m_decisionUI.Update();

	//ゲームオーバースプライト用のイージング(位置)を設定
	SetGameOverSpriteEasingPosition();
}

//プレイヤーの操作
void GameOver::Action()
{
	//Aボタンを押していないとき選択ができる
	if (m_pressButtonFlag != true)
	{
		//十字キーを左に倒したら
		if (g_pad[0]->IsTrigger(enButtonLeft))
		{
			//現在の選択がスタートだったら
			if (m_select == enSelect_Continue)
			{
				//ゲーム終了に移動
				m_select = enSelect_ReturnTitle;
				return;
			}
			//左にいく
			m_select -= 1;
		}
		//十字キーを右に倒したら
		else if (g_pad[0]->IsTrigger(enButtonRight))
		{
			//現在の選択がゲーム終了だったら
			if (m_select == enSelect_ReturnTitle)
			{
				//スタートに移動
				m_select = enSelect_Continue;
				return;
			}
			//右にいく
			m_select += 1;
		}

		//Aボタンを押したらボタンを押したときの演出が流れる
		if (g_pad[0]->IsTrigger(enButtonA))
		{
			m_pressButtonFlag = true;
		}
	}
	//遷移フラグが立ったら選択に応じて反映する
	else if (m_transitionFlag == true)
	{
		switch (m_select)
		{
		case enSelect_Continue:			//コンティニュー
			m_fade->FadeTransition(enFadeState_FadeOut);
			if (g_gameTime->StopWatch(3.0f))
			{
				DeleteGO(this);
				DeleteGO(m_game);
				NewGO<Game>(0, "game");
			}
			break;
		case enSelect_ReturnTitle:		//タイトルへ戻る
			m_fade->FadeTransition(enFadeState_FadeOut);
			if (g_gameTime->StopWatch(2.0f))
			{
				DeleteGO(this);
				DeleteGO(m_game);
				NewGO<Title>(0, "title");
			}
			break;
		default:
			break;
		}
	}
}

//スプライトの動作
void GameOver::SpriteMove()
{
	//ゲームオーバー演出が終わっていないか?
	if (m_gameOverDirectionFlag != true)
	{
		//ゲームオーバー演出ステート
		switch (m_gameOverDirectionState)
		{
		case enGameOverDirection_GameOver:		//ゲームオーバー
			//イージングが終わっていないか?
			if (m_easingFinishFlag != true)
			{
				//ゲームオーバースプライト用のイージング(位置)の更新処理
				UpdateGameOverSpriteEasingPosition();
			}
			else
			{
				//ゲームオーバースプライト用の弾力性の更新処理
				UpdateGameOverSpriteElasticity();
			}
			break;
		case enGameOverDirection_Select:		//選択
			m_selectUIAlphaColor += 0.75f * g_gameTime->GetFrameDeltaTime();

			//選択UIが不透明になったら
			if (m_selectUIAlphaColor > 1.0f)
			{
				m_selectUIAlphaColor = 1.0f;
				m_gameOverDirectionFlag = true;
				return;
			}

			//選択UI
			m_selectUI[enGameOverDirection_GameOver].SetMulColor(Vector4(1.0f, 1.0f, 1.0f, m_selectUIAlphaColor));
			m_selectUI[enGameOverDirection_Select].SetMulColor(Vector4(1.0f, 1.0f, 1.0f, m_selectUIAlphaColor));
			break;
		default:
			break;
		}
		return;
	}
	//遷移フラグが立っていないとき
	else if (m_transitionFlag != true)
	{
		//Aボタンが押されたら
		if (m_pressButtonFlag == true)
		{
			//ボタンを押したときの動作をしていないか?
			if (m_pressButtonActionFlag != true)
			{
				//選択
				switch (m_select)
				{
				case enSelect_Continue:			//コンティニュー
					m_selectUI[enSelect_Continue].SetMulColor(Vector4(0.0f, 0.0f, 0.0f, 1.0f));
					m_selectUI[enSelect_Continue].Update();
					break;
				case enSelect_ReturnTitle:		//タイトルへ戻る
					m_selectUI[enSelect_ReturnTitle].SetMulColor(Vector4(0.0f, 0.0f, 0.0f, 1.0f));
					m_selectUI[enSelect_ReturnTitle].Update();
					break;
				default:
					break;
				}
				if (g_gameTime->StopWatch(0.1f) == true)
				{
					m_pressButtonActionFlag = true;
				}
				return;
			}
			else
			{
				//選択
				switch (m_select)
				{
				case enSelect_Continue:			//コンティニュー
					m_selectUI[enSelect_Continue].SetMulColor(Vector4(1.0f, 1.0f, 1.0f, 1.0f));
					m_selectUI[enSelect_Continue].Update();
					break;
				case enSelect_ReturnTitle:		//タイトルへ戻る
					m_selectUI[enSelect_ReturnTitle].SetMulColor(Vector4(1.0f, 1.0f, 1.0f, 1.0f));
					m_selectUI[enSelect_ReturnTitle].Update();
					break;
				default:
					break;
				}
				if (g_gameTime->StopWatch(0.1f) == true)
				{
					m_transitionFlag = true;
				}
				return;
			}
		}
	}

	//選択
	switch (m_select)
	{
	case enSelect_Continue:			//コンティニュー
		//選択UI
		m_selectUI[enSelect_Continue].SetMulColor(m_selectUIColor[enSelect_Continue]);
		m_selectUI[enSelect_ReturnTitle].SetMulColor(Vector4(0.0f, 0.0f, 0.0f, 1.0f));
		break;
	case enSelect_ReturnTitle:		//タイトルへ戻る
		//選択UI
		m_selectUI[enSelect_Continue].SetMulColor(Vector4(0.0f, 0.0f, 0.0f, 1.0f));
		m_selectUI[enSelect_ReturnTitle].SetMulColor(m_selectUIColor[enSelect_ReturnTitle]);
		break;
	default:
		break;
	}
}

//ゲームオーバースプライト用のイージング(位置)を設定
void GameOver::SetGameOverSpriteEasingPosition()
{
	m_beforeEasingPosition = m_gameOverUIPosition;
	m_afterEasingPosition = Vector3(15.0f, 50.0f, 0.0f);
	m_easingTime = 0.0f;
}

//ゲームオーバースプライト用のイージング(位置)の更新処理
void GameOver::UpdateGameOverSpriteEasingPosition()
{
	m_easingTime += 2.0f * g_gameTime->GetFrameDeltaTime();

	if (m_easingTime > 1.0f)
	{
		m_easingTime = 1.0f;
		m_easingFinishFlag = true;
		m_gameOverUIFarstHeight = m_afterEasingPosition;
		SetCoefficientOfRestitution(90.0f, 50.0f);
	}

	m_gameOverUIPosition.Lerp(m_easingTime, m_beforeEasingPosition, m_afterEasingPosition);
	m_gameOverUI.SetPosition(m_gameOverUIPosition);
	m_gameOverUI.Update();
}

//ゲームオーバースプライト用のイージング(回転)を設定
void GameOver::SetGameOverSpriteEasingRotation(float angle)
{
	m_beforeEasingRotation = m_gameOverUIRotation;

	Quaternion afterGameOverUIRotation;
	afterGameOverUIRotation.SetRotationDegZ(angle);

	m_afterEasingRotation = afterGameOverUIRotation;
	m_easingTime = 0.0f;
}

//ゲームオーバースプライト用のイージング(回転)の更新処理
void GameOver::UpdateGameOverSpriteEasingRotation()
{
	m_easingTime += 1.7f * g_gameTime->GetFrameDeltaTime();

	if (m_easingTime > 1.0f)
	{
		m_easingTime = 1.0f;
	}

	m_gameOverUIRotation.Slerp(m_easingTime, m_beforeEasingRotation, m_afterEasingRotation);
	m_gameOverUI.SetRotation(m_gameOverUIRotation);
	m_gameOverUI.Update();
}

//ゲームオーバースプライト用の弾力性の更新処理
void GameOver::UpdateGameOverSpriteElasticity()
{
	//ゲームオーバーUI用の演出が終わったら次の演出に移る
	if (m_gameOverUIHitCount == 5)
	{
		m_gameOverDirectionState = enGameOverDirection_Select;
		m_gameOverUIRotation.SetRotationDegZ(0.0f);
		m_gameOverUI.SetRotation(m_gameOverUIRotation);
		m_gameOverUI.Update();
	}

	//ゲームオーバーUIが落下していないとき
	if (m_gameOverUIFallFlag != true)
	{
		m_gameOverUIPosition.y += pow(m_coefficientOfRestitution, m_exponentiation) * 250.0f;
		SetGameOverSpriteEasingRotation(m_angle);
		m_gameOverUIFallFlag = true;
	}
	else
	{
		m_gameOverUIPosition.y -= pow(m_coefficientOfRestitution, m_exponentiation) * 9.8f;
		UpdateGameOverSpriteEasingRotation();
		//ゲームオーバーUIが最初の高さに戻ったか?
		if (m_gameOverUIPosition.y <= m_gameOverUIFarstHeight.y)
		{
			if (m_gameOverUIFallFlag == true)
			{
				m_gameOverUIPosition.y = m_gameOverUIFarstHeight.y;
				m_exponentiation += 3;

				//偶数は角度用の変数を反転して加算
				if (m_gameOverUIHitCount % 2 == 0)
				{
					m_angle *= -1.0f;
					m_angle += 5.0f / m_gameOverUIHitCount;
				}
				//奇数は角度用の変数を反転して減算
				else
				{
					m_angle *= -1.0f;
					m_angle -= 5.0f / m_gameOverUIHitCount;
				}

				m_gameOverUIHitCount++;
				m_gameOverUIFallFlag = false;
			}
		}
	}
	m_gameOverUI.SetPosition(m_gameOverUIPosition);
	m_gameOverUI.Update();
}