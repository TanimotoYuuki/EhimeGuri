#include "stdafx.h"
#include "GameOver.h"
#include "Player.h"
#include "Fade.h"
#include "Title.h"
#include "Game.h"

//デストラクタ。
GameOver::~GameOver()
{
	DeleteGO(m_fade);
}

//開始処理。
bool GameOver::Start()
{
	//スプライトの初期化。
	InitSprite();
	
	//インスタンス。
	//0 プレイヤー。
	m_player = FindGO<Player>("player");
	m_player->m_gameOverFlag = true;

	//1 フェード。
	NewGO<Fade>(0, "fade");
	m_fade = FindGO<Fade>("fade");
	//フェードを描画しないようにする。
	m_fade->FadeTransition(enFadeState_None);

	//2 ゲーム。
	m_game = FindGO<Game>("game");
	return true;
}

//更新処理。
void GameOver::Update()
{
	//スプライトの動作。
	SpriteMove();

	//ゲームオーバー演出が終わったら。
	if (m_gameOverDirectionFlag == true)
	{
		//プレイヤーの操作。
		Action();
	}
}

//描画処理。
void GameOver::Render(RenderContext& rc)
{
	//ゲームオーバーUI。
	m_gameOverUI.Draw(rc);

	//ゲームオーバー時の選択UI(コンティニュー)。
	m_gameOverSelectUI[enSelect_Continue].Draw(rc);

	//ゲームオーバー時の選択UI(タイトルへ戻る)。
	m_gameOverSelectUI[enSelect_ReturnTitle].Draw(rc);

	//ゲームオーバー演出が終わったら描画する。
	if (m_gameOverDirectionFlag == true)
	{
		//十字キーUI。
		m_dPadUI.Draw(rc);

		//AボタンUI。
		m_aButtonUI.Draw(rc);

		//選択UI。
		m_selectUI.Draw(rc);

		//決定UI。
		m_decisionUI.Draw(rc);
	}
}

//スプライトの初期化。
void GameOver::InitSprite()
{
	//各スプライトの初期設定。
	//ゲームオーバーUI。
	//0 ゲームオーバーUIの初期化。
	m_gameOverUI.Init("Assets/gameover/text/gameover.dds", 1024, 128);
	//0.1 ゲームオーバーUIの座標の設定。
	m_gameOverUI.SetPosition(m_gameOverUIPosition);
	//0.2 ゲームオーバーUIの回転の設定。
	m_gameOverUIRotation.SetRotationDegZ(20.0f);
	m_gameOverUI.SetRotation(m_gameOverUIRotation);
	//0.3 ゲームオーバーUIのピボットの設定。
	m_gameOverUI.SetPivot(Vector2(0.5f, 0.0f));
	//0.4 ゲームオーバーUIの更新処理。
	m_gameOverUI.Update();

	//ゲームオーバー時の選択UI(コンティニュー)。
	//1 ゲームオーバー時の選択UI(コンティニュー)の初期化。
	m_gameOverSelectUI[enSelect_Continue].Init("Assets/gameover/text/continue.dds", 1024, 128);
	//1.1 ゲームオーバー時の選択UI(コンティニュー)の座標の設定。
	m_gameOverSelectUI[enSelect_Continue].SetPosition(Vector3(-250.0f, -200.0f, 0.0f));
	//1.2 ゲームオーバー時の選択UI(コンティニュー)の大きさの設定。
	m_gameOverSelectUI[enSelect_Continue].SetScale(Vector3(0.5f, 0.5f, 0.5f));
	//1.3 ゲームオーバー時の選択UI(コンティニュー)の乗算カラー用変数の乗算カラーの設定。
	m_gameOverSelectUI[enSelect_Continue].SetMulColor(Vector4(1.0f, 1.0f, 1.0f, 1.0f));
	//1.4 ゲームオーバー時の選択UI(コンティニュー)の乗算カラーの取得。
	m_gameOverSelectUIColor[enSelect_Continue] = m_gameOverSelectUI[enSelect_Continue].GetMulColor();
	//1.5 ゲームオーバー時の選択UI(コンティニュー)の乗算カラーの設定。
	m_gameOverSelectUI[enSelect_Continue].SetMulColor(Vector4(1.0f, 1.0f, 1.0f, 0.0f));
	//1.6 ゲームオーバー時の選択UI(コンティニュー)の更新処理。
	m_gameOverSelectUI[enSelect_Continue].Update();

	//ゲームオーバー時の選択UI(タイトルへ戻る)。
	//2 ゲームオーバー時の選択UI(タイトルへ戻る)の初期化。
	m_gameOverSelectUI[enSelect_ReturnTitle].Init("Assets/gameover/text/returntitle.dds", 1024, 128);
	//2.1 ゲームオーバー時の選択UI(タイトルへ戻る)の座標の設定。
	m_gameOverSelectUI[enSelect_ReturnTitle].SetPosition(Vector3(250.0f, -200.0f, 0.0f));
	//2.2 ゲームオーバー時の選択UI(タイトルへ戻る)の大きさの設定。
	m_gameOverSelectUI[enSelect_ReturnTitle].SetScale(Vector3(0.5f, 0.5f, 0.5f));
	//2.3 ゲームオーバー時の選択UI(タイトルへ戻る)の乗算カラー用変数の乗算カラーの設定。
	m_gameOverSelectUI[enSelect_ReturnTitle].SetMulColor(Vector4(1.0f, 1.0f, 1.0f, 1.0f));
	//2.4 ゲームオーバー時の選択UI(タイトルへ戻る)の乗算カラーの取得。
	m_gameOverSelectUIColor[enSelect_ReturnTitle] = m_gameOverSelectUI[enSelect_ReturnTitle].GetMulColor();
	//2.5 ゲームオーバー時の選択UI(タイトルへ戻る)の乗算カラーの設定。
	m_gameOverSelectUI[enSelect_ReturnTitle].SetMulColor(Vector4(1.0f, 1.0f, 1.0f, 0.0f));
	//2.6 ゲームオーバー時の選択UI(タイトルへ戻る)の更新処理。
	m_gameOverSelectUI[enSelect_ReturnTitle].Update();

	//十字キーUI。
	//3 十字キーUIの初期化。
	m_dPadUI.Init("Assets/title/gamepad/dpad.dds", 512, 512);
	//3.1 十字キーUIの座標の設定。
	m_dPadUI.SetPosition(Vector3(325.0f, -345.0f, 0.0f));
	//3.2 十字キーUIの大きさの設定。
	m_dPadUI.SetScale(Vector3(0.1f, 0.1f, 0.1f));
	//3.3 十字キーUIの更新処理。
	m_dPadUI.Update();

	//AボタンUI。
	//4 AボタンUIの初期化。
	m_aButtonUI.Init("Assets/gameover/gamepad/abutton.dds", 512, 512);
	//4.1 AボタンUIの座標の設定
	m_aButtonUI.SetPosition(Vector3(Vector3(525.0f, -345.0f, 0.0f)));
	//4.2 AボタンUIの大きさの設定。
	m_aButtonUI.SetScale(Vector3(0.1f, 0.1f, 0.1f));
	//4.3 AボタンUIの更新処理。
	m_aButtonUI.Update();

	//選択UI。
	//5 選択UIの初期化。
	m_selectUI.Init("Assets/title/text/select.dds", 1024, 128);
	//5.1 選択UIの座標の設定。
	m_selectUI.SetPosition(Vector3(400.0f, -345.0f, 0.0f));
	//5.2 選択UIの大きさの設定。
	m_selectUI.SetScale(Vector3(0.3f, 0.3f, 0.3f));
	//5.3 選択UIの更新処理。
	m_selectUI.Update();

	//決定UI。
	//6 決定UIの初期化。
	m_decisionUI.Init("Assets/gameover/text/decision.dds", 1024, 128);
	//6.1 決定UIの座標の設定。
	m_decisionUI.SetPosition(Vector3(600.0f, -345.0f, 0.0f));
	//6.2 決定UIの大きさの設定。
	m_decisionUI.SetScale(Vector3(0.3f, 0.3f, 0.3f));
	//6.3 決定UIの更新処理。
	m_decisionUI.Update();

	//ゲームオーバースプライト用のイージング(位置)を設定。
	SetGameOverSpriteEasingPosition();
}

//プレイヤーの操作。
void GameOver::Action()
{
	//Aボタンを押していないとき選択ができる。
	if (m_pressButtonFlag != true)
	{
		//十字キーを左に倒したら。
		if (g_pad[0]->IsTrigger(enButtonLeft))
		{
			//現在の選択がスタートだったら。
			if (m_gameOverSelect == enSelect_Continue)
			{
				//タイトルへ戻る。
				m_gameOverSelect = enSelect_ReturnTitle;
				return;
			}
			//選択が左にいく。
			m_gameOverSelect -= 1;
		}
		//十字キーを右に倒したら。
		else if (g_pad[0]->IsTrigger(enButtonRight))
		{
			//現在の選択がゲーム終了だったら。
			if (m_gameOverSelect == enSelect_ReturnTitle)
			{
				//ゲームをコンティニューする。
				m_gameOverSelect = enSelect_Continue;
				return;
			}
			//選択が右にいく。
			m_gameOverSelect += 1;
		}

		//Aボタンを押したらボタンを押したときの演出が流れる。
		if (g_pad[0]->IsTrigger(enButtonA))
		{
			//ボタンが押された。
			m_pressButtonFlag = true;
		}
	}
	//遷移フラグが立ったら選択に応じて反映する。
	else if (m_transitionFlag == true)
	{
		//ゲームオーバー時の選択。
		switch (m_gameOverSelect)
		{
		case enSelect_Continue:			//コンティニュー。
			//フェードをフェードアウトに切り替える。
			m_fade->FadeTransition(enFadeState_FadeOut);
			//3.0秒経過したらコンティニューする。
			if (g_gameTime->StopWatch(3.0f))
			{
				DeleteGO(this);
				DeleteGO(m_game);
				NewGO<Game>(0, "game");
			}
			break;
		case enSelect_ReturnTitle:		//タイトルへ戻る。
			//2.0秒経過したらタイトルへ戻る。
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

//スプライトの動作。
void GameOver::SpriteMove()
{
	//ゲームオーバー演出が終わっていないか?
	if (m_gameOverDirectionFlag != true)
	{
		//ゲームオーバー演出ステート。
		switch (m_gameOverDirectionState)
		{
		case enGameOverDirection_GameOver:		//ゲームオーバー。
			//イージングが終わっていないか?
			if (m_easingFinishFlag != true)
			{
				//ゲームオーバースプライト用のイージング(位置)の更新処理。
				UpdateGameOverSpriteEasingPosition();
			}
			else
			{
				//ゲームオーバースプライト用の弾力性の更新処理。
				UpdateGameOverSpriteElasticity();
			}
			break;
		case enGameOverDirection_Select:		//選択。
			m_gameOverSelectUIAlphaColor += 0.75f * g_gameTime->GetFrameDeltaTime();

			//ゲームオーバー時の選択UIが不透明になったらゲームオーバー演出を終了する。
			if (m_gameOverSelectUIAlphaColor > 1.0f)
			{
				m_gameOverSelectUIAlphaColor = 1.0f;
				//ゲームオーバー演出を終了。
				m_gameOverDirectionFlag = true;
				return;
			}

			//ゲームオーバー時の選択UIの乗算カラーの更新。
			m_gameOverSelectUI[enGameOverDirection_GameOver].SetMulColor(Vector4(1.0f, 1.0f, 1.0f, m_gameOverSelectUIAlphaColor));
			m_gameOverSelectUI[enGameOverDirection_Select].SetMulColor(Vector4(1.0f, 1.0f, 1.0f, m_gameOverSelectUIAlphaColor));
			break;
		default:
			break;
		}
		return;
	}
	//遷移フラグが立っていないとき。
	else if (m_transitionFlag != true)
	{
		//Aボタンが押されたらボタンを押したときの演出に移る。
		if (m_pressButtonFlag == true)
		{
			//ボタンを押したときの動作をしていないか?
			if (m_pressButtonActionFlag != true)
			{
				//ゲームオーバー時の選択。
				switch (m_gameOverSelect)
				{
				case enSelect_Continue:			//コンティニュー。
					//ゲームオーバー時の選択UIのコンティニューのカラーを黒にする。
					m_gameOverSelectUI[enSelect_Continue].SetMulColor(Vector4(0.0f, 0.0f, 0.0f, 1.0f));
					m_gameOverSelectUI[enSelect_Continue].Update();
					break;
				case enSelect_ReturnTitle:		//タイトルへ戻る。
					//ゲームオーバー時の選択UIのタイトルへ戻るのカラーを黒にする。
					m_gameOverSelectUI[enSelect_ReturnTitle].SetMulColor(Vector4(0.0f, 0.0f, 0.0f, 1.0f));
					m_gameOverSelectUI[enSelect_ReturnTitle].Update();
					break;
				default:
					break;
				}
				//0.1秒経過したら次の演出に移る。
				if (g_gameTime->StopWatch(0.1f) == true)
				{
					//ボタンを押したときの動作をする。
					m_pressButtonActionFlag = true;
				}
				return;
			}
			//Aボタンを押したらボタンを押したときの動作をする。
			else
			{
				//ゲームオーバー時の選択。
				switch (m_gameOverSelect)
				{
				case enSelect_Continue:			//コンティニュー。
					//ゲームオーバー時の選択UIのコンティニューのカラーを白にする。
					m_gameOverSelectUI[enSelect_Continue].SetMulColor(Vector4(1.0f, 1.0f, 1.0f, 1.0f));
					m_gameOverSelectUI[enSelect_Continue].Update();
					break;
				case enSelect_ReturnTitle:		//タイトルへ戻る。
					//ゲームオーバー時の選択UIのコンティニューのカラーを白にする。
					m_gameOverSelectUI[enSelect_ReturnTitle].SetMulColor(Vector4(1.0f, 1.0f, 1.0f, 1.0f));
					m_gameOverSelectUI[enSelect_ReturnTitle].Update();
					break;
				default:
					break;
				}
				//0.1秒経過したらフェードアウトする。
				if (g_gameTime->StopWatch(0.1f) == true)
				{
					m_transitionFlag = true;
					//フェードをフェードアウトに切り替える。
					m_fade->FadeTransition(enFadeState_FadeOut);
				}
				return;
			}
		}
	}

	//ゲームオーバー時の選択。
	switch (m_gameOverSelect)
	{
	case enSelect_Continue:			//コンティニュー。
		//ゲームオーバー時の選択UI。
		m_gameOverSelectUI[enSelect_Continue].SetMulColor(m_gameOverSelectUIColor[enSelect_Continue]);
		m_gameOverSelectUI[enSelect_ReturnTitle].SetMulColor(Vector4(0.0f, 0.0f, 0.0f, 1.0f));
		break;
	case enSelect_ReturnTitle:		//タイトルへ戻る。
		//ゲームオーバー時の選択UI。
		m_gameOverSelectUI[enSelect_Continue].SetMulColor(Vector4(0.0f, 0.0f, 0.0f, 1.0f));
		m_gameOverSelectUI[enSelect_ReturnTitle].SetMulColor(m_gameOverSelectUIColor[enSelect_ReturnTitle]);
		break;
	default:
		break;
	}
}

//ゲームオーバースプライト用のイージング(位置)を設定。
void GameOver::SetGameOverSpriteEasingPosition()
{
	m_beforeEasingPosition = m_gameOverUIPosition;
	m_afterEasingPosition = Vector3(15.0f, 50.0f, 0.0f);
	m_easingTime = 0.0f;
}

//ゲームオーバースプライト用のイージング(位置)の更新処理。
void GameOver::UpdateGameOverSpriteEasingPosition()
{
	m_easingTime += 2.0f * g_gameTime->GetFrameDeltaTime();

	//割合が1.0f以上になったら次の演出に移る。
	if (m_easingTime > 1.0f)
	{
		m_easingTime = 1.0f;
		m_easingFinishFlag = true;
		m_gameOverUIFarstHeight = m_afterEasingPosition;
		SetCoefficientOfRestitution(90.0f, 50.0f);
	}

	//ゲームオーバーUIの更新。
	m_gameOverUIPosition.Lerp(m_easingTime, m_beforeEasingPosition, m_afterEasingPosition);
	m_gameOverUI.SetPosition(m_gameOverUIPosition);
	m_gameOverUI.Update();
}

//ゲームオーバースプライト用のイージング(回転)を設定。
void GameOver::SetGameOverSpriteEasingRotation(float angle)
{
	m_beforeEasingRotation = m_gameOverUIRotation;

	Quaternion afterGameOverUIRotation;
	afterGameOverUIRotation.SetRotationDegZ(angle);

	m_afterEasingRotation = afterGameOverUIRotation;
	m_easingTime = 0.0f;
}

//ゲームオーバースプライト用のイージング(回転)の更新処理。
void GameOver::UpdateGameOverSpriteEasingRotation()
{
	m_easingTime += 1.7f * g_gameTime->GetFrameDeltaTime();

	//割合が1.0fになったら割合を固定する。
	if (m_easingTime > 1.0f)
	{
		m_easingTime = 1.0f;
	}

	//ゲームオーバーUIの更新。
	m_gameOverUIRotation.Slerp(m_easingTime, m_beforeEasingRotation, m_afterEasingRotation);
	m_gameOverUI.SetRotation(m_gameOverUIRotation);
	m_gameOverUI.Update();
}

//ゲームオーバースプライト用の弾力性の更新処理。
void GameOver::UpdateGameOverSpriteElasticity()
{
	//5回ゲームオーバーUIが跳ねたら次の演出に移る。
	if (m_gameOverUIHitCount == 5)
	{
		m_gameOverDirectionState = enGameOverDirection_Select;
		m_gameOverUIRotation.SetRotationDegZ(0.0f);
		m_gameOverUI.SetRotation(m_gameOverUIRotation);
		m_gameOverUI.Update();
	}

	//落下フラグが立っていないときはゲームオーバーUIを上に上昇する。
	if (m_gameOverUIFallFlag != true)
	{
		m_gameOverUIPosition.y += pow(m_coefficientOfRestitution, m_exponentiation) * 250.0f;
		SetGameOverSpriteEasingRotation(m_angle);
		m_gameOverUIFallFlag = true;
	}
	//落下フラグが立っているときはゲームオーバーUIを下に下降する。
	else
	{
		m_gameOverUIPosition.y -= pow(m_coefficientOfRestitution, m_exponentiation) * 9.8f;
		UpdateGameOverSpriteEasingRotation();
		//ゲームオーバーUIが最初の高さに戻ったか?
		if (m_gameOverUIPosition.y <= m_gameOverUIFarstHeight.y)
		{
			//落下フラグが立っているとき。
			if (m_gameOverUIFallFlag == true)
			{
				//ゲームオーバーUIの高さをイージング(位置)が終わった時の高さに設定する。
				m_gameOverUIPosition.y = m_gameOverUIFarstHeight.y;
				//累乗を3ずつ上昇する。
				m_exponentiation += 3;

				//偶数は角度用の変数を反転して加算。
				if (m_gameOverUIHitCount % 2 == 0)
				{
					m_angle *= -1.0f;
					m_angle += 5.0f / m_gameOverUIHitCount;
				}
				//奇数は角度用の変数を反転して減算。
				else
				{
					m_angle *= -1.0f;
					m_angle -= 5.0f / m_gameOverUIHitCount;
				}

				//何回ゲームオーバーUIが跳ねたかカウントする。
				m_gameOverUIHitCount++;
				
				//ゲームオーバーUIを上昇する。
				m_gameOverUIFallFlag = false;
			}
		}
	}

	//ゲームオーバーUIの更新。
	m_gameOverUI.SetPosition(m_gameOverUIPosition);
	m_gameOverUI.Update();
}