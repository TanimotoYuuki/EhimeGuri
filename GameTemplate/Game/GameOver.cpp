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
	//プレイヤーの操作
	Action();

	//スプライトの動作
	SpriteMove();
	//if (g_pad[0]->IsPress(enButtonA))
	//{
	//	NewGO<Title>(0);
	//	DeleteGO(this);
	//}
}

void GameOver::Render(RenderContext& rc)
{
	//ゲームオーバーUI
	m_gameOverUI.Draw(rc);

	//選択UI(コンティニュー)
	m_selectUI[enSelect_Continue].Draw(rc);

	//選択UI(タイトルへ戻る)
	m_selectUI[enSelect_ReturnTitle].Draw(rc);

	//AボタンUI
	m_aButtonUI.Draw(rc);

	//決定UI
	m_decisionUI.Draw(rc);
}

//スプライトの初期化
void GameOver::InitSprite()
{
	//ゲームオーバーUI
	m_gameOverUI.Init("Assets/gameover/text/gameover.dds", 1024, 128);
	m_gameOverUI.SetPosition(m_gameOverPosition);
	m_gameOverUI.Update();

	//選択UI(コンティニュー)
	m_selectUI[enSelect_Continue].Init("Assets/gameover/text/continue.dds", 1024, 128);
	m_selectUI[enSelect_Continue].SetPosition(Vector3(-200.0f, -200.0f, 0.0f));
	m_selectUI[enSelect_Continue].SetScale(Vector3(0.5f, 0.5f, 0.5f));
	m_selectUI[enSelect_Continue].SetMulColor(Vector4(1.0f, 1.0f, 1.0f, 1.0f));
	m_selectUI[enSelect_Continue].Update();
	m_selectUIColor[enSelect_Continue] = m_selectUI[enSelect_Continue].GetMulColor();

	//選択UI(タイトルへ戻る)
	m_selectUI[enSelect_ReturnTitle].Init("Assets/gameover/text/returntitle.dds", 1024, 128);
	m_selectUI[enSelect_ReturnTitle].SetPosition(Vector3(200.0f, -200.0f, 0.0f));
	m_selectUI[enSelect_ReturnTitle].SetScale(Vector3(0.5f, 0.5f, 0.5f));
	m_selectUI[enSelect_ReturnTitle].SetMulColor(Vector4(1.0f, 1.0f, 1.0f, 1.0f));
	m_selectUI[enSelect_ReturnTitle].Update();
	m_selectUIColor[enSelect_ReturnTitle] = m_selectUI[enSelect_ReturnTitle].GetMulColor();

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
}

//プレイヤーの操作
void GameOver::Action()
{
	//Aボタンを押していないとき？
	if (m_pressButtonFlag != true)
	{
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

		if (g_pad[0]->IsTrigger(enButtonA))
		{
			m_pressButtonFlag = true;
		}
	}
	//遷移フラグが立ったら
	else if (m_transitionFlag == true)
	{
		switch (m_select)
		{
		case enSelect_Continue:			//コンティニュー
			m_fade->FadeTransition(enFadeState_FadeOut);
			if (g_gameTime->StopWatch(2.0f))
			{
				DeleteGO(this);
				DeleteGO(m_game);
				NewGO<Game>(0, "game");
			}
			break;
		case enSelect_ReturnTitle:		//タイトルへ戻る
			m_fade->FadeTransition(enFadeState_FadeOut);
			if (g_gameTime->StopWatch(1.5f))
			{
				NewGO<Title>(0, "title");
				DeleteGO(this);
				DeleteGO(m_game);
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
	//遷移フラグが立っていないとき
	if (m_transitionFlag != true)
	{
		//Aボタンが押されたら
		if (m_pressButtonFlag == true)
		{
			//ボタンを押したときの動作をしたか？
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