#include "stdafx.h"
#include "GameOver.h"
#include "Player.h"
#include "Fade.h"
#include "Title.h"
#include "Game.h"
#include "Scene.h"

namespace
{
	// 反発係数。
	const float REBOUNDCOEFFICIENT_BEFORE = 90.0f;
	const float REBOUNDCOEFFICIENT_AFTER = 50.0f;

	// スプライトイージング用。
	const Vector3 AFTERPOSITION(15.0f, 50.0f, 0.0f);

	// 乗算カラー。
	const Vector4 BLACK(0.0f, 0.0f, 0.0f, 1.0f);
	const Vector4 WHITE(1.0f, 1.0f, 1.0f, 1.0f);

	// deltaTIme() に乗算する値。
	const float DELTATIMEMULTIPLIER = 0.5f;

// 決定UI
	// 大きさ。
	const Vector3 DECISION_SCALE(0.3f, 0.3f, 0.3f);
	// 座標。
	const Vector3 DECISION_POSITION(600.0f, -345.0f, 0.0f);
	// 解像度。
	const float DECISION_WIDTH = 1024;
	const float DECISION_HEIGHT = 128;

// 選択UI
	// 大きさ。
	const Vector3 SELECT_SCALE(0.3f, 0.3f, 0.3f);
	// 座標。
	const Vector3 SELECT_POSITION(400.0f, -345.0f, 0.0f);
	// 解像度。
	const float SELECT_WIDTH = 1024;
	const float SELECT_HEIGHT = 128;

// Aボタン。
	// 大きさ。
	const Vector3 ABUTTON_SCALE(0.1f, 0.1f, 0.1f);
	// 座標。
	const Vector3 ABUTTON_POSITION(525.0f, -345.0f, 0.0f);
	// 解像度。
	const float ABUTTON_WIDTH = 512;
	const float ABUTTON_HEIGHT = 512;

// 十字キー。
	// 大きさ。
	const Vector3 DPAD_SCALE(0.1f, 0.1f, 0.1f);
	// 座標。
	const Vector3 DPAD_POSITION(325.0f, -345.0f, 0.0f);
	// 解像度。
	const float DPAD_WIDTH = 512;
	const float DPAD_HEIGHT = 512;

// Lスティック。
	// 大きさ。
	const Vector3 LSTICK_SCALE(0.1f, 0.1f, 0.1f);
	// 座標。
	const Vector3 LSTICK_POSITION(275.0f, -345.0f, 0.0f);
	// 解像度。
	const float LSTICK_WIDTH = 512;
	const float LSTICK_HEIGHT = 512;

// 乗算カラー。
	const Vector4 MULCOLOR(1.0f, 1.0f, 1.0f, 0.0f);

// タイトルへ戻る処理。
	// 大きさ。
	const Vector3 RETURNTITLE_SCALE(0.5f, 0.5f, 0.5f);
	const Vector3 RETURNTITLE_POSITION(250.0f, -200.0f, 0.0f);

	// 解像度。
	const float RETURNTITLE_WIDTH = 1024;
	const float RETURNTITLE_HEIGHT = 128;

// ゲームオーバー時の選択UI
	// 大きさ。
	const Vector3 CHOICEUI_SCALE(0.5f, 0.5f, 0.5f);
	// 座標。
	const Vector3 CHOICEUI_POSITION(-250.0f, -200.0f, 0.0f);
	// 解像度。
	const float CHOICEU_WIDTH = 1024;
	const float CHOICEU_HEIGHT = 128;

// ゲームオーバーUI
	// ピポット。
	const Vector2 GAMEOVER_PIVOT(0.5f, 0.0f);
	// 回転軸。
	const float GAMEOVER_DEGZ(20.0f);
	// 解像度。
	const float GAMEOVER_WIDTH = 1024;
	const float GAMEOVER_HEIGHT = 128;


}


//開始処理。
bool GameOver::Start()
{
	//スプライトの初期化。
	InitSprite();
	
	//インスタンス。
	//0 プレイヤー。
	m_player->m_gameOverFlag = true;

	//1 フェード。
	m_fade = FindGO<Fade>("fade");

	//2 ゲーム。
	m_game = FindGO<Game>("game");

	//ゲームオーバー時の音の再生。
	g_gameSoundEngine->PlaySE(GameSoundList_SE_System_GameOver, 1.0f);
	return true;
}

//更新処理。
void GameOver::Update()
{
	if (m_player == nullptr)
	{
		m_player = FindGO<Player>("player");
	}


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
		//LスティックUI。
		m_lStickUI.Draw(rc);

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
	SetGameOver();

	//ゲームオーバー時の選択UI(コンティニュー)。
	SetChoiceUI();

	//ゲームオーバー時の選択UI(タイトルへ戻る)。
	SetReturnTitle();
	
	//ゲームパッド(Lスティック)UI
	SetLStick();

	//十字キーUI。
	SetDpadUI();

	//AボタンUI。
	SetAbuttonUI();

	//選択UI。
	SetDecisionUI();

	//決定UI。
	SetDecisionUI();

	//ゲームオーバースプライト用のイージング(位置)を設定。
	SetGameOverSpriteEasingPosition();
}

//プレイヤーの操作。
void GameOver::Action()
{
	//Aボタンを押していないとき選択ができる。
	if (m_pressButtonFlag != true)
	{
		//十字キーを左に倒す または
		//左スティックを左に倒したとき
		if (g_pad[0]->IsTrigger(enButtonLeft) || g_pad[0]->IsTriggerLStickLeft())
		{
			//選択音の再生。
			g_gameSoundEngine->PlaySE(GameSoundList_SE_SelectScreen_Select, 1.0f);
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
		//十字キーを右に倒す または
		//左スティックを右に倒したとき
		else if (g_pad[0]->IsTrigger(enButtonRight) || g_pad[0]->IsTriggerLStickRight())
		{
			//選択音の再生。
			g_gameSoundEngine->PlaySE(GameSoundList_SE_SelectScreen_Select, 1.0f);
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

			//決定音(画面遷移用)の再生。
			g_gameSoundEngine->PlaySE(GameSoundList_SE_SelectScreen_Decision_ScreenTransition, 1.0f);
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

				//現在ステージ1をプレイしているとき
				if (m_game->GetStageState() == m_game->enStageState_Stage1)
				{
					//ステージ1オブジェクトの削除
					m_game->Stage1ObjectDelete();
				}
				//現在ステージ2をプレイしているとき
				else if (m_game->GetStageState() == m_game->enStageState_Stage2)
				{
					//ステージ2オブジェクトの削除
					m_game->Stage2ObjectDelete();
				}

				//メインオブジェクトの削除
				m_game->MainObjectDelete();

				DeleteGO(m_game);
				NewGO<Game>(0, "game");
			}
			break;
		case enSelect_ReturnTitle:		//タイトルへ戻る。
			//2.0秒経過したらタイトルへ戻る。
			if (g_gameTime->StopWatch(2.0f))
			{
				DeleteGO(this);
				
				//現在ステージ1をプレイしているとき
				if (m_game->GetStageState() == m_game->enStageState_Stage1)
				{
					//ステージ1オブジェクトの削除
					m_game->Stage1ObjectDelete();
				}
				//現在ステージ2をプレイしているとき
				else if (m_game->GetStageState() == m_game->enStageState_Stage2)
				{
					//ステージ2オブジェクトの削除
					m_game->Stage2ObjectDelete();
				}

				//メインオブジェクトの削除
				m_game->MainObjectDelete();

				DeleteGO(m_game);
				//SceneManagerを経由してタイトル画面への遷移を要求する
				Scene_Manager::GetInstance()->SetRequest(SceneID::S_Title);
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
				//ゲームオーバー演出を終了する。
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
					m_gameOverSelectUI[enSelect_Continue].SetMulColor(BLACK);
					m_gameOverSelectUI[enSelect_Continue].Update();
					break;
				case enSelect_ReturnTitle:		//タイトルへ戻る。
					//ゲームオーバー時の選択UIのタイトルへ戻るのカラーを黒にする。
					m_gameOverSelectUI[enSelect_ReturnTitle].SetMulColor(BLACK);
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
					m_gameOverSelectUI[enSelect_Continue].SetMulColor(WHITE);
					m_gameOverSelectUI[enSelect_Continue].Update();
					break;
				case enSelect_ReturnTitle:		//タイトルへ戻る。
					//ゲームオーバー時の選択UIのコンティニューのカラーを白にする。
					m_gameOverSelectUI[enSelect_ReturnTitle].SetMulColor(WHITE);
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

	//Aボタンを押していないとき
	if (m_pressButtonFlag != true)
	{
		m_gameOverSelectUIScaleChange = m_gameOverSelectUI[m_gameOverSelect].GetScale();

		//ゲームオーバー時の選択UIの大きさを小さくしないとき
		if (m_gameOverSelectUIScaleDownFlag != true)
		{
			//ゲームオーバー時の選択UIを大きくする。
			m_gameOverSelectUIScaleChange.x += g_gameTime->GetFrameDeltaTime() * DELTATIMEMULTIPLIER;
			m_gameOverSelectUIScaleChange.y += g_gameTime->GetFrameDeltaTime() * DELTATIMEMULTIPLIER;
			m_gameOverSelectUIScaleChange.z += g_gameTime->GetFrameDeltaTime() * DELTATIMEMULTIPLIER;

			if (m_gameOverSelectUIScaleChange.x > 0.7f)
			{
				m_gameOverSelectUIScaleDownFlag = true;
			}
		}
		//ゲームオーバー時の選択UIの大きさを小さくするとき
		else
		{
			//ゲームオーバー時の選択UIを小さくする。
			m_gameOverSelectUIScaleChange.x -= g_gameTime->GetFrameDeltaTime() * DELTATIMEMULTIPLIER;
			m_gameOverSelectUIScaleChange.y -= g_gameTime->GetFrameDeltaTime() * DELTATIMEMULTIPLIER;
			m_gameOverSelectUIScaleChange.z -= g_gameTime->GetFrameDeltaTime() * DELTATIMEMULTIPLIER;

			if (m_gameOverSelectUIScaleChange.x < DELTATIMEMULTIPLIER)
			{
				m_gameOverSelectUIScaleDownFlag = false;
			}
		}
	}

	//ゲームオーバー時の選択。
	switch (m_gameOverSelect)
	{
	case enSelect_Continue:			//コンティニュー。
		//ゲームオーバー時の選択UI。
		//大きさ。
		m_gameOverSelectUI[enSelect_Continue].SetScale(m_gameOverSelectUIScaleChange);
		m_gameOverSelectUI[enSelect_ReturnTitle].SetScale(m_gameOverSelectUIScale[enSelect_ReturnTitle]);
		
		//乗算カラー。
		m_gameOverSelectUI[enSelect_Continue].SetMulColor(m_gameOverSelectUIColor[enSelect_Continue]);
		m_gameOverSelectUI[enSelect_ReturnTitle].SetMulColor(BLACK);

		//更新
		m_gameOverSelectUI[enSelect_Continue].Update();
		m_gameOverSelectUI[enSelect_ReturnTitle].Update();
		break;
	case enSelect_ReturnTitle:		//タイトルへ戻る。
		//ゲームオーバー時の選択UI。
		//大きさ。
		m_gameOverSelectUI[enSelect_Continue].SetScale(m_gameOverSelectUIScale[enSelect_Continue]);
		m_gameOverSelectUI[enSelect_ReturnTitle].SetScale(m_gameOverSelectUIScaleChange);

		//乗算カラー。
		m_gameOverSelectUI[enSelect_Continue].SetMulColor(BLACK);
		m_gameOverSelectUI[enSelect_ReturnTitle].SetMulColor(m_gameOverSelectUIColor[enSelect_ReturnTitle]);

		//更新
		m_gameOverSelectUI[enSelect_Continue].Update();
		m_gameOverSelectUI[enSelect_ReturnTitle].Update();
		break;
	default:
		break;
	}
}

//ゲームオーバースプライト用のイージング(位置)を設定。
void GameOver::SetGameOverSpriteEasingPosition()
{
	m_beforeEasingPosition = m_gameOverUIPosition;
	m_afterEasingPosition = AFTERPOSITION;
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
		SetCoefficientOfRestitution(REBOUNDCOEFFICIENT_BEFORE, REBOUNDCOEFFICIENT_AFTER);
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

// 決定UI用。
void GameOver::SetDecisionUI()
{
	//6 決定UIの初期化。
	m_decisionUI.Init("Assets/gameover/text/decision.dds", DECISION_WIDTH, DECISION_HEIGHT);
	//6.1 決定UIの座標の設定。
	m_decisionUI.SetPosition(DECISION_POSITION);
	//6.2 決定UIの大きさの設定。
	m_decisionUI.SetScale(DECISION_SCALE);
	//6.3 決定UIの更新処理。
	m_decisionUI.Update();

}

// 選択UI用。
void GameOver::SetSelectUI()
{
	//6 選択UIの初期化。
	m_selectUI.Init("Assets/title/text/select.dds", SELECT_WIDTH, SELECT_HEIGHT);
	//6.1 選択UIの座標の設定。
	m_selectUI.SetPosition(SELECT_POSITION);
	//6.2 選択UIの大きさの設定。
	m_selectUI.SetScale(SELECT_SCALE);
	//6.3 選択UIの更新処理。
	m_selectUI.Update();

}

// AボタンUI用。
void GameOver::SetAbuttonUI()
{
	//5 AボタンUIの初期化。
	m_aButtonUI.Init("Assets/gameover/gamepad/abutton.dds", ABUTTON_WIDTH, ABUTTON_HEIGHT);
	//5.1 AボタンUIの座標の設定
	m_aButtonUI.SetPosition(ABUTTON_POSITION);
	//5.2 AボタンUIの大きさの設定。
	m_aButtonUI.SetScale(ABUTTON_SCALE);
	//5.3 AボタンUIの更新処理。
	m_aButtonUI.Update();
}

// 十字キー用。
void GameOver::SetDpadUI()
{
	//4 十字キーUIの初期化。
	m_dPadUI.Init("Assets/title/gamepad/dpad.dds", DPAD_WIDTH, DPAD_HEIGHT);
	//4.1 十字キーUIの座標の設定。
	m_dPadUI.SetPosition(DPAD_POSITION);
	//4.2 十字キーUIの大きさの設定。
	m_dPadUI.SetScale(DPAD_SCALE);
	//4.3 十字キーUIの更新処理。
	m_dPadUI.Update();
}

// Lスティック用。
void GameOver::SetLStick()
{
	//3 ゲームパッド(Lスティック)UIの初期化
	m_lStickUI.Init("Assets/title/gamepad/lstick.dds", LSTICK_WIDTH, LSTICK_HEIGHT);
	//3.1 ゲームパッド(Lスティック)UIの大きさの設定
	m_lStickUI.SetPosition(LSTICK_POSITION);
	//3.2 ゲームパッド(Lスティック)UIの大きさの設定
	m_lStickUI.SetScale(LSTICK_SCALE);
	//3.3 ゲームパッド(Lスティック)UIの更新
	m_lStickUI.Update();

}

// タイトルへ戻る処理。
void GameOver::SetReturnTitle()
{
	//2 ゲームオーバー時の選択UI(タイトルへ戻る)の初期化。
	m_gameOverSelectUI[enSelect_ReturnTitle].Init("Assets/gameover/text/returntitle.dds", RETURNTITLE_WIDTH, RETURNTITLE_HEIGHT);
	//2.1 ゲームオーバー時の選択UI(タイトルへ戻る)の座標の設定。
	m_gameOverSelectUI[enSelect_ReturnTitle].SetPosition(RETURNTITLE_POSITION);
	//2.2 ゲームオーバー時の選択UI(タイトルへ戻る)の大きさの設定。
	m_gameOverSelectUI[enSelect_ReturnTitle].SetScale(RETURNTITLE_SCALE);
	//2.3 ゲームオーバー時の選択UI(コンティニュー)の大きさの取得。
	m_gameOverSelectUIScale[enSelect_ReturnTitle] = m_gameOverSelectUI[enSelect_ReturnTitle].GetScale();
	//2.4 ゲームオーバー時の選択UI(タイトルへ戻る)の乗算カラー用変数の乗算カラーの設定。
	m_gameOverSelectUI[enSelect_ReturnTitle].SetMulColor(MULCOLOR);
	//2.5 ゲームオーバー時の選択UI(タイトルへ戻る)の乗算カラーの取得。
	m_gameOverSelectUIColor[enSelect_ReturnTitle] = m_gameOverSelectUI[enSelect_ReturnTitle].GetMulColor();
	//2.6 ゲームオーバー時の選択UI(タイトルへ戻る)の乗算カラーの設定。
	m_gameOverSelectUI[enSelect_ReturnTitle].SetMulColor(MULCOLOR);
	//2.7 ゲームオーバー時の選択UI(タイトルへ戻る)の更新処理。
	m_gameOverSelectUI[enSelect_ReturnTitle].Update();
}

// ゲームオーバー時の選択UI
void GameOver::SetChoiceUI()
{
	//1 ゲームオーバー時の選択UI(コンティニュー)の初期化。
	m_gameOverSelectUI[enSelect_Continue].Init("Assets/gameover/text/continue.dds", CHOICEU_WIDTH, CHOICEU_HEIGHT);
	//1.1 ゲームオーバー時の選択UI(コンティニュー)の座標の設定。
	m_gameOverSelectUI[enSelect_Continue].SetPosition(CHOICEUI_POSITION);
	//1.2 ゲームオーバー時の選択UI(コンティニュー)の大きさの設定。
	m_gameOverSelectUI[enSelect_Continue].SetScale(CHOICEUI_SCALE);
	//1.3 ゲームオーバー時の選択UI(コンティニュー)の大きさの取得。
	m_gameOverSelectUIScale[enSelect_Continue] = m_gameOverSelectUI[enSelect_Continue].GetScale();
	//1.4 ゲームオーバー時の選択UI(コンティニュー)の乗算カラー用変数の乗算カラーの設定。
	m_gameOverSelectUI[enSelect_Continue].SetMulColor(MULCOLOR);
	//1.5 ゲームオーバー時の選択UI(コンティニュー)の乗算カラーの取得。
	m_gameOverSelectUIColor[enSelect_Continue] = m_gameOverSelectUI[enSelect_Continue].GetMulColor();
	//1.6 ゲームオーバー時の選択UI(コンティニュー)の乗算カラーの設定。
	m_gameOverSelectUI[enSelect_Continue].SetMulColor(MULCOLOR);
	//1.7 ゲームオーバー時の選択UI(コンティニュー)の更新処理。
	m_gameOverSelectUI[enSelect_Continue].Update();

}

// ゲームオーバー。
void GameOver::SetGameOver()
{
	//0 ゲームオーバーUIの初期化。
	m_gameOverUI.Init("Assets/gameover/text/gameover.dds", GAMEOVER_WIDTH, GAMEOVER_HEIGHT);
	//0.1 ゲームオーバーUIの座標の設定。
	m_gameOverUI.SetPosition(m_gameOverUIPosition);
	//0.2 ゲームオーバーUIの回転の設定。
	m_gameOverUIRotation.SetRotationDegZ(GAMEOVER_DEGZ);
	m_gameOverUI.SetRotation(m_gameOverUIRotation);
	//0.3 ゲームオーバーUIのピボットの設定。
	m_gameOverUI.SetPivot(GAMEOVER_PIVOT);
	//0.4 ゲームオーバーUIの更新処理。
	m_gameOverUI.Update();

}