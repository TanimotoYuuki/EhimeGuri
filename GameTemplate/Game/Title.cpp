#include "stdafx.h"
#include "system/system.h"
#include "Title.h"
#include "Fade.h"

Title::Title()
{
	//スカイキューブの初期化
	InitSky();

	//アニメーションの初期化
	InitAnimation();

	//モデルの初期化
	InitModel();

	//スプライトの初期化
	InitSprite();

	//カメラの初期化
	InitCamera();

	m_fade = FindGO<Fade>("fade");
}

Title::~Title()
{
	DeleteGO(m_skyCube);
}

//更新処理
void Title::Update()
{
	//スタート用のフェードが終わったら
	if (m_startFadeFinishFlag != true)
	{
		if (g_gameTime->StopWatch(1.0f) == true)
		{
			m_startFadeFinishFlag = true;
		}
	}
	//スタート用のフェードが終わったら
	else if (m_startFadeFinishFlag == true)
	{
		//タイトル背景が表示したら
		if (m_titleBackGroundFadeFinishFlag == true)
		{
			//プレイヤー側の操作
			Action();
		}

		//スプライトの動作
		SpriteMove();
	}

	//ゲームスタートフラグが立っているとき
	if (m_gameStartFlag == true)
	{
		//プレイヤーモデルの動作
		PlayerModelMove();
	}

	//カメラの更新
	UpdateCamera();

	//アニメーション管理
	AnimationManage();

	//アニメーション再生
	PlayAnimation();

	//更新処理
	m_playerModel.Update();
	m_backGroundModel[enBackGroundModel_Base].Update();
	m_backGroundModel[enBackGroundModel_Grass].Update();
}

//描画
void Title::Render(RenderContext& rc)
{
	//ステージモデル
	m_backGroundModel[enBackGroundModel_Base].Draw(rc);
	m_backGroundModel[enBackGroundModel_Grass].Draw(rc);

	//プレイヤーモデル
	m_playerModel.Draw(rc);

	//ゲーム開始フラグが立っていないか？
	if (m_gameStartFlag != true)
	{
		//タイトル背景
		m_titleBackGround.Draw(rc);
	}

	//スタート用フェードが終わったか？
	if (m_startFadeFinishFlag == true)
	{
		//タイトル画面遷移
		switch (m_titleTransition)
		{
		case enTitleTransition_Title: //タイトル
			//Aボタンを押すUI
			m_pressAButtonUI.Draw(rc);
			break;
		case enTitleTransition_ModeSelect: //モード選択
			//ゲーム開始フラグが立っていないか？
			if (m_gameStartFlag != true)
			{
				//モード選択UI
				m_modeUI[enModeSelect_Start].Draw(rc);
				m_modeUI[enModeSelect_HowToPlay].Draw(rc);
				m_modeUI[enModeSelect_Shutdown].Draw(rc);
				
				//ゲームパッドUI
				m_gamePadUI[enGamePad_AButton].Draw(rc);
				m_gamePadUI[enGamePad_BButton].Draw(rc);

				//決定UI
				m_decisionUI.Draw(rc);

				//戻るUI
				m_returnUI.Draw(rc);
			}
			break;
		case enTitleTransition_HowToPlay: //遊び方
			//遊び方UI
			m_howToPlayUI.Draw(rc);

			//ゲームパッドUI
			m_gamePadUI[enGamePad_AButton].Draw(rc);

			//戻るUI
			m_returnUI.Draw(rc);
			break;
		default:
			break;
		}
	}
}

//プレイヤー側の操作
void Title::Action()
{
	//ゲーム開始フラグが立っていないか？
	if (m_gameStartFlag != true)
	{
		//タイトル画面遷移
		switch (m_titleTransition)
		{
		case enTitleTransition_Title: //タイトル
			if (g_pad[0]->IsTrigger(enButtonA))
			{
				m_pressButtonFlag = true;
			}

			//画面遷移フラグが立っていたら
			if (m_titleTransitionFlag == true)
			{
				//モード選択へ遷移
				m_titleTransition = enTitleTransition_ModeSelect;
				m_titleTransitionFlag = false;
			}
			break;
		case enTitleTransition_ModeSelect: //モード選択
			if (g_pad[0]->IsTrigger(enButtonUp))
			{
				//現在の選択がスタートだったら
				if (m_modeSelect==enModeSelect_Start)
				{
					//ゲーム終了に移動
					m_modeSelect = enModeSelect_Shutdown;
					return;
				}
				//上に上がる
				m_modeSelect -= 1;
			}
			else if (g_pad[0]->IsTrigger(enButtonDown))
			{
				//現在の選択がゲーム終了だったら
				if (m_modeSelect==enModeSelect_Shutdown)
				{
					//スタートに移動
					m_modeSelect = enModeSelect_Start;
					return;
				}
				//下に下がる
				m_modeSelect += 1;
			}

			if (g_pad[0]->IsTrigger(enButtonA))
			{
				m_pressButtonFlag = true;
			}
			else if (g_pad[0]->IsTrigger(enButtonB))
			{
				//タイトルへ遷移
				m_titleTransition = enTitleTransition_Title;
			}

			//画面遷移フラグが立っていたら
			if (m_titleTransitionFlag == true)
			{
				//現在の選択がスタートだったら
				if (m_modeSelect == enModeSelect_Start)
				{
					//ゲーム開始
					m_gameStartFlag = true;
				}
				//現在の選択が遊び方だったら
				else if (m_modeSelect == enModeSelect_HowToPlay)
				{
					//遊び方へ遷移
					m_titleTransition = enTitleTransition_HowToPlay;
				}
				//現在の選択がゲーム終了だったら
				else if (m_modeSelect == enModeSelect_Shutdown)
				{
					//ゲーム終了
					g_gameLoop.m_isLoop = false;
				}
				m_titleTransitionFlag = false;
			}
			break;
		case enTitleTransition_HowToPlay: //遊び方
			if (g_pad[0]->IsTrigger(enButtonA))
			{
				//モード選択へ遷移
				m_titleTransition = enTitleTransition_ModeSelect;
			}
			break;
		default:
			break;
		}
	}
	else
	{
		//画面端に行ったら
		if (m_playerModelPosition.x > FRAME_BUFFER_W / 2)
		{
			m_fade->FadeTransition(enFadeState_FadeOut);
			if (g_gameTime->StopWatch(2.5f))
			{
				//ゲーム開始
				NewGO<Game>(0, "game");
				m_fade->FadeTransition(enFadeState_FadeIn);
				DeleteGO(this);
			}
		}
	}
}

//スプライトの動作
void Title::SpriteMove()
{
	//タイトル画面遷移
	switch (m_titleTransition)
	{
	case enTitleTransition_Title: //タイトル
		//タイトル背景が表示していないとき
		if (m_titleBackGroundFadeFinishFlag != true)
		{
			m_alpha += g_gameTime->GetFrameDeltaTime();
			m_titleBackGround.SetMulColor(Vector4(1.0f, 1.0f, 1.0f, m_alpha));
			m_titleBackGround.Update();
			if (m_alpha > 1.0f)
			{
				m_alpha = 0.0f;
				m_titleBackGroundFadeFinishFlag = true;
			}
			return;
		}

		//Aボタンが押されたら
		if (m_pressButtonFlag == true)
		{
			//ボタンを押したときの動作をしたか？
			if (m_pressButtonActionFlag != true)
			{
				m_pressAButtonUI.SetMulColor(Vector4(0.0f, 0.0f, 0.0f, 1.0f));
				m_pressAButtonUI.Update();
				if (g_gameTime->StopWatch(0.1f) == true)
				{
					m_pressButtonActionFlag = true;
				}
				return;
			}
			else
			{
				//画面遷移していないとき
				if (m_titleTransitionFlag != true)
				{
					m_pressAButtonUI.SetMulColor(Vector4(1.0f, 1.0f, 1.0f, 1.0f));
					m_pressAButtonUI.Update();
					if (g_gameTime->StopWatch(0.1f) == true)
					{
						m_titleTransitionFlag = true;
						m_alpha = 0.0f;
						m_pressButtonFlag = false;
						m_pressButtonActionFlag = false;
					}
					return;
				}
			}
		}

		//Aボタンを押すUIを透明にしたり元に戻したりする
		m_alpha += g_gameTime->GetFrameDeltaTime();
		m_pressAButtonUI.SetMulColor(Vector4(1.0f, 1.0f, 1.0f, fabsf(sinf(m_alpha))));
		m_pressAButtonUI.Update();
		break;
	case enTitleTransition_ModeSelect: //モード選択

		//Aボタンが押されたら
		if (m_pressButtonFlag == true)
		{
			//ボタンを押したときの動作をしたか？
			if (m_pressButtonActionFlag != true)
			{
				//モード選択
				switch (m_modeSelect)
				{
				case enModeSelect_Start: //スタート
					m_modeUI[enModeSelect_Start].SetMulColor(Vector4(0.0f, 0.0f, 0.0f, 1.0f));
					m_modeUI[enModeSelect_Start].Update();
					break;
				case enModeSelect_HowToPlay: //遊び方
					m_modeUI[enModeSelect_HowToPlay].SetMulColor(Vector4(0.0f, 0.0f, 0.0f, 1.0f));
					m_modeUI[enModeSelect_HowToPlay].Update();
					break;
				case enModeSelect_Shutdown: //ゲーム終了
					m_modeUI[enModeSelect_Shutdown].SetMulColor(Vector4(0.0f, 0.0f, 0.0f, 1.0f));
					m_modeUI[enModeSelect_Shutdown].Update();
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
				//画面遷移していないとき
				if (m_titleTransitionFlag != true)
				{
					//モード選択
					switch (m_modeSelect)
					{
					case enModeSelect_Start: //スタート
						m_modeUI[enModeSelect_Start].SetMulColor(Vector4(1.0f, 1.0f, 1.0f, 1.0f));
						m_modeUI[enModeSelect_Start].Update();
						break;
					case enModeSelect_HowToPlay: //遊び方
						m_modeUI[enModeSelect_HowToPlay].SetMulColor(Vector4(1.0f, 1.0f, 1.0f, 1.0f));
						m_modeUI[enModeSelect_HowToPlay].Update();
						break;
					case enModeSelect_Shutdown: //ゲーム終了
						m_modeUI[enModeSelect_Shutdown].SetMulColor(Vector4(1.0f, 1.0f, 1.0f, 1.0f));
						m_modeUI[enModeSelect_Shutdown].Update();
						break;
					default:
						break;
					}
					if (g_gameTime->StopWatch(0.1f) == true)
					{
						m_titleTransitionFlag = true;
						m_pressButtonFlag = false;
						m_pressButtonActionFlag = false;
					}
					return;
				}
			}
		}

		//現在の選択がスタートだったら
		if (m_modeSelect == enModeSelect_Start)
		{
			//モード選択UI
			m_modeUI[enModeSelect_Start].SetMulColor(m_modeUIColor[enModeSelect_Start]);
			m_modeUI[enModeSelect_HowToPlay].SetMulColor(Vector4(0.0f, 0.0f, 0.0f, 1.0f));
			m_modeUI[enModeSelect_Shutdown].SetMulColor(Vector4(0.0f, 0.0f, 0.0f, 1.0f));
		}
		//現在の選択が遊び方だったら
		else if (m_modeSelect == enModeSelect_HowToPlay)
		{
			//モード選択UI
			m_modeUI[enModeSelect_Start].SetMulColor(Vector4(0.0f, 0.0f, 0.0f, 1.0f));
			m_modeUI[enModeSelect_HowToPlay].SetMulColor(m_modeUIColor[enModeSelect_HowToPlay]);
			m_modeUI[enModeSelect_Shutdown].SetMulColor(Vector4(0.0f, 0.0f, 0.0f, 1.0f));
		}
		//現在の選択がゲーム終了だったら
		else if (m_modeSelect == enModeSelect_Shutdown)
		{
			//モード選択UI
			m_modeUI[enModeSelect_Start].SetMulColor(Vector4(0.0f, 0.0f, 0.0f, 1.0f));
			m_modeUI[enModeSelect_HowToPlay].SetMulColor(Vector4(0.0f, 0.0f, 0.0f, 1.0f));
			m_modeUI[enModeSelect_Shutdown].SetMulColor(m_modeUIColor[enModeSelect_HowToPlay]);
		}

		//ゲームパッド(Aボタン)
		m_gamePadUI[enGamePad_AButton].SetPosition(Vector3(325.0f, -345.0f, 0.0f));
		m_gamePadUI[enGamePad_AButton].Update();

		//戻るUI
		m_returnUI.SetPosition(Vector3(600.0f, -350.0f, 0.0f));
		m_returnUI.Update();
		break;
	case enTitleTransition_HowToPlay: //遊び方
		//ゲームパッド(Aボタン)
		m_gamePadUI[enGamePad_AButton].SetPosition(Vector3(575.0f, -345.0f, 0.0f));
		m_gamePadUI[enGamePad_AButton].Update();

		//戻るUI
		m_returnUI.SetPosition(Vector3(650.0f, -350.0f, 0.0f));
		m_returnUI.Update();
	default:
		break;
	}
}

//スカイキューブの初期化
void Title::InitSky()
{
	DeleteGO(m_skyCube);
	m_skyCube = NewGO<SkyCube>(0, "skycube");

	m_skyCube->SetLuminance(1.0f);
	m_skyCube->SetType((EnSkyCubeType)m_skyCubeType);
	m_skyCube->SetPosition(Vector3(0.0f, -1000.0f, 0.0f));
	m_skyCube->SetScale(Vector3(750.0f, 750.0f, 750.0f));
	m_skyCube->Update();
}

//アニメーションの初期化
void Title::InitAnimation()
{
	//0.歩くアニメーション
	m_animationClip[enAnimationClip_walk].Load("Assets/animData/playerwalk.tka");
	m_animationClip[enAnimationClip_walk].SetLoopFlag(true);
	//1.走るアニメーション
	m_animationClip[enAnimationClip_run].Load("Assets/animData/playerrun.tka");
	m_animationClip[enAnimationClip_run].SetLoopFlag(true);
}

//モデルの初期化
void Title::InitModel()
{
	//0 ステージの初期化
	m_backGroundModel[enBackGroundModel_Base].Init("Assets/title/background_base.tkm");

	m_backGroundModel[enBackGroundModel_Grass].Init("Assets/title/background_grass.tkm", 0,
		0, enModelUpAxisZ, false, true);

	//0.1 大きさを設定
	m_backGroundModel[enBackGroundModel_Base].SetScale(Vector3(10.0f, 10.0f, 10.0f));
	m_backGroundModel[enBackGroundModel_Base].Update();

	m_backGroundModel[enBackGroundModel_Grass].SetScale(Vector3(10.0f, 10.0f, 10.0f));
	m_backGroundModel[enBackGroundModel_Grass].Update();

	//0.2 スクロール速度を設定
	m_backGroundModel[enBackGroundModel_Base].SetScrollSpeed(-1.0f);

	m_backGroundModel[enBackGroundModel_Grass].SetScrollSpeed(1.0f);

	//1 プレイヤーモデルの初期化
	m_playerModel.Init("Assets/modelData/player/player.tkm", m_animationClip,
		enAnimationClip_num, enModelUpAxisZ, true);

	//1.1 位置を設定
	m_playerModel.SetPosition(m_playerModelPosition);

	//1.2 回転を設定
	m_playerModelRotation.SetRotationDegY(90.0f);
	m_playerModel.SetRotation(m_playerModelRotation);

	//1.3 大きさを設定
	m_playerModel.SetScale(m_playerModelScale);
	m_playerModel.Update();
}

//スプライトの初期化
void Title::InitSprite()
{
	//タイトル背景
	m_titleBackGround.Init("Assets/title/title.dds", 1024, 1024);
	m_titleBackGround.SetPosition(Vector3(0.0f, 300.0f, 0.0f));
	m_titleBackGround.SetScale(Vector3(0.65f, 0.65f, 0.65f));
	m_titleBackGround.SetMulColor(Vector4(1.0f, 1.0f, 1.0f, m_alpha));
	m_titleBackGround.Update();

	//Aボタンを押すUI
	m_pressAButtonUI.Init("Assets/title/text/pressabutton.dds", 1024, 128);
	m_pressAButtonUI.SetPosition(Vector3(0.0f, -150.0f, 0.0f));
	m_pressAButtonUI.SetScale(Vector3(0.75f, 0.75f, 0.75f));
	m_pressAButtonUI.SetMulColor(Vector4(1.0f, 1.0f, 1.0f, m_alpha));
	m_pressAButtonUI.Update();

	//モード選択UI(スタート)
	m_modeUI[enModeSelect_Start].Init("Assets/title/text/start.dds", 1024, 128);
	m_modeUI[enModeSelect_Start].SetPosition(Vector3(0.0f, 0.0f, 0.0f));
	m_modeUI[enModeSelect_Start].SetScale(Vector3(0.5f,0.5f,0.5f));
	m_modeUI[enModeSelect_Start].SetMulColor(Vector4(1.0f, 1.0f, 1.0f, 1.0f));
	m_modeUI[enModeSelect_Start].Update();
	m_modeUIColor[enModeSelect_Start] = m_modeUI[enModeSelect_Start].GetMulColor();

	//モード選択UI(遊び方)
	m_modeUI[enModeSelect_HowToPlay].Init("Assets/title/text/howtoplay.dds", 1024, 128);
	m_modeUI[enModeSelect_HowToPlay].SetPosition(Vector3(0.0f, -75.0f, 0.0f));
	m_modeUI[enModeSelect_HowToPlay].SetScale(Vector3(0.5f,0.5f,0.5f));
	m_modeUI[enModeSelect_HowToPlay].SetMulColor(Vector4(1.0f, 1.0f, 1.0f, 1.0f));
	m_modeUI[enModeSelect_HowToPlay].Update();
	m_modeUIColor[enModeSelect_HowToPlay] = m_modeUI[enModeSelect_HowToPlay].GetMulColor();

	//モード選択UI(ゲーム終了)
	m_modeUI[enModeSelect_Shutdown].Init("Assets/title/text/shutdown.dds", 1024, 128);
	m_modeUI[enModeSelect_Shutdown].SetPosition(Vector3(0.0f, -150.0f, 0.0f));
	m_modeUI[enModeSelect_Shutdown].SetScale(Vector3(0.5f, 0.5f, 0.5f));
	m_modeUI[enModeSelect_Shutdown].SetMulColor(Vector4(1.0f, 1.0f, 1.0f, 1.0f));
	m_modeUI[enModeSelect_Shutdown].Update();
	m_modeUIColor[enModeSelect_Shutdown] = m_modeUI[enModeSelect_Shutdown].GetMulColor();

	//遊び方UI
	m_howToPlayUI.Init("Assets/title/screen/howtoplay.dds", 1500, 800);

	//ゲームパッド(Aボタン)
	m_gamePadUI[enGamePad_AButton].Init("Assets/title/gamepad/abutton.dds", 512, 512);
	m_gamePadUI[enGamePad_AButton].SetPosition(Vector3(325.0f, -345.0f, 0.0f));
	m_gamePadUI[enGamePad_AButton].SetScale(Vector3(0.1f, 0.1f, 0.1f));
	m_gamePadUI[enGamePad_AButton].Update();

	//ゲームパッド(Bボタン)
	m_gamePadUI[enGamePad_BButton].Init("Assets/title/gamepad/bbutton.dds", 512, 512);
	m_gamePadUI[enGamePad_BButton].SetPosition(Vector3(525.0f, -345.0f, 0.0f));
	m_gamePadUI[enGamePad_BButton].SetScale(Vector3(0.1f, 0.1f, 0.1f));
	m_gamePadUI[enGamePad_BButton].Update();

	//ゲームパッド(Xボタン)
	m_gamePadUI[enGamePad_XButton].Init("Assets/title/gamepad/xbutton.dds", 512, 512);

	//ゲームパッド(Yボタン)
	m_gamePadUI[enGamePad_YButton].Init("Assets/title/gamepad/ybutton.dds", 512, 512);

	//ゲームパッド(Lスティック)
	m_gamePadUI[enGamePad_LStick].Init("Assets/title/gamepad/lstick.dds", 512, 512);

	//ゲームパッド(Rスティック)
	m_gamePadUI[enGamePad_RStick].Init("Assets/title/gamepad/rstick.dds", 512, 512);

	//ゲームパッド(十字キー)
	m_gamePadUI[enGamePad_DPad].Init("Assets/title/gamepad/dpad.dds", 512, 512);

	//決定UI
	m_decisionUI.Init("Assets/title/text/decision.dds", 1024, 128);
	m_decisionUI.SetPosition(Vector3(400.0f, -350.0f, 0.0f));
	m_decisionUI.SetScale(Vector3(0.3f, 0.3f, 0.3f));
	m_decisionUI.Update();

	//選択UI
	m_selectUI.Init("Assets/title/text/select.dds", 1024, 128);

	//戻るUI
	m_returnUI.Init("Assets/title/text/return.dds", 1024, 128);
	m_returnUI.SetPosition(Vector3(600.0f, -350.0f, 0.0f));
	m_returnUI.SetScale(Vector3(0.3f, 0.3f, 0.3f));
	m_returnUI.Update();
}

//カメラの初期化
void Title::InitCamera()
{
	g_camera3D->SetNear(1.0f);
	g_camera3D->SetFar(15000.0f);
}

//プレイヤーモデルの動作
void Title::PlayerModelMove()
{
	m_playerModelPosition.x += 7.5f;
	m_playerModel.SetPosition(m_playerModelPosition);
}

//カメラの更新
void Title::UpdateCamera()
{
	if (m_gameStartFlag != true)
	{
		//カメラの位置
		Vector3 CameraPosition = m_playerModelPosition + Vector3(0.0f, 100.0f, -500.0f);
		//カメラの注視点
		Vector3 CameraTarget = m_playerModelPosition;
		CameraTarget.y += 100.0f;

		//カメラの位置を設定
		g_camera3D->SetPosition(CameraPosition);
		//カメラの注視点を設定
		g_camera3D->SetTarget(CameraTarget);
	}
}

//アニメーション管理
void Title::AnimationManage()
{
	//プレイヤーモデル
	PlayerModelAnimationManage();
}

//アニメーション再生
void Title::PlayAnimation()
{
	//プレイヤーモデル
	PlayerModelPlayAnimation();
}

//プレイヤーモデルのアニメーション管理
void Title::PlayerModelAnimationManage()
{
	if (m_gameStartFlag == true)
	{
		m_playerModelAnimationState = enPlayerModelAnimationState_run;
	}
	else
	{
		m_playerModelAnimationState = enPlayerModelAnimationState_walk;
	}
}

//プレイヤーモデルのアニメーション再生
void Title::PlayerModelPlayAnimation()
{
	switch (m_playerModelAnimationState)
	{
	case enPlayerModelAnimationState_walk:	//歩くアニメーション
		m_playerModel.PlayAnimation(enAnimationClip_walk);
		break;
	case enPlayerModelAnimationState_run:	//走るアニメーション
		m_playerModel.PlayAnimation(enAnimationClip_run);
		break;
	default:
		break;
	}
}