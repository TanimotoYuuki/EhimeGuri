#include "stdafx.h"
#include "system/system.h"
#include "Title.h"

Title::Title()
{
	//m_titleBackGround.Init("Assets/Sprite/Title.DDS", 1920, 1080);

	//アニメーションの初期化
	InitAnimation();

	//モデルの初期化
	InitModel();

	//スプライトの初期化
	InitSprite();

	//カメラの初期化
	InitCamera();
}

Title::~Title()
{

}

void Title::Update()
{
	//スタート用のフェードが終わったら
	if (g_gameTime->StopWatch(0.8f) == true)
	{
		m_startFadeFinishFlag = true;
	}
	else if (m_startFadeFinishFlag == true)
	{
		//プレイヤー側の操作
		Action();

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

	m_playerModel.Update();
	m_fade.Update();
	//if (g_pad[0]->IsTrigger(enButtonA))
	//{
	//	NewGO<Game>(0, "game");
	//	DeleteGO(this);
	//}
}

void Title::Render(RenderContext& rc)
{
	//m_titleBackGround.Draw(rc);

	//プレイヤーモデル
	m_playerModel.Draw(rc);

	//フェード
	m_fade.Draw(rc);

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
			if (m_gameStartFlag != true)
			{
				//モード選択UI
				m_modeUI[enModeSelect_Start].Draw(rc);
				m_modeUI[enModeSelect_HowToPlay].Draw(rc);
				m_modeUI[enModeSelect_Shutdown].Draw(rc);
				
				//ゲームパッドUI
				m_gamepadUI[enGamePad_AButton].Draw(rc);
				m_gamepadUI[enGamePad_BButton].Draw(rc);

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
			m_gamepadUI[enGamePad_AButton].Draw(rc);

			//戻るUI
			m_returnUI.Draw(rc);
			break;
		default:
			break;
		}
	}
}

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
				//モード選択へ遷移
				m_titleTransition = enTitleTransition_ModeSelect;
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
			}
			else if (g_pad[0]->IsTrigger(enButtonB))
			{
				//タイトルへ遷移
				m_titleTransition = enTitleTransition_Title;
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
		//if (g_pad[0]->IsTrigger(enButtonA))
		//{
		//	m_gameStartFlag = true;
		//}
	}
	else
	{
		//画面端に行ったら
		if (m_playerModelPosition.x > FRAME_BUFFER_W / 2)
		{
			//ゲーム開始
			NewGO<Game>(0, "game");
			DeleteGO(this);
		}
	}
}

void Title::SpriteMove()
{
	//タイトル画面遷移
	switch (m_titleTransition)
	{
	case enTitleTransition_Title: //タイトル
		//Aボタンを押すUIを透明にしたり元に戻したりする
		m_alpha += g_gameTime->GetFrameDeltaTime();
		m_pressAButtonUI.SetMulColor(Vector4(1.0f, 1.0f, 1.0f, fabsf(sinf(m_alpha))));
		m_pressAButtonUI.Update();
		break;
	case enTitleTransition_ModeSelect: //モード選択
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
		m_gamepadUI[enGamePad_AButton].SetPosition(Vector3(325.0f, -345.0f, 0.0f));
		m_gamepadUI[enGamePad_AButton].Update();

		//戻るUI
		m_returnUI.SetPosition(Vector3(600.0f, -350.0f, 0.0f));
		m_returnUI.Update();
		break;
	case enTitleTransition_HowToPlay: //遊び方
		//ゲームパッド(Aボタン)
		m_gamepadUI[enGamePad_AButton].SetPosition(Vector3(575.0f, -345.0f, 0.0f));
		m_gamepadUI[enGamePad_AButton].Update();

		//戻るUI
		m_returnUI.SetPosition(Vector3(650.0f, -350.0f, 0.0f));
		m_returnUI.Update();
	default:
		break;
	}
}

void Title::InitAnimation()
{
	//0.歩くアニメーション
	m_animationClip[enAnimationClip_walk].Load("Assets/animData/playerwalk.tka");
	m_animationClip[enAnimationClip_walk].SetLoopFlag(true);
	//1.走るアニメーション
	m_animationClip[enAnimationClip_run].Load("Assets/animData/playerrun.tka");
	m_animationClip[enAnimationClip_run].SetLoopFlag(true);
}

void Title::InitModel()
{
	//0. プレイヤーモデルの初期化
	m_playerModel.Init("Assets/modelData/player/player.tkm", m_animationClip,
		enAnimationClip_num, enModelUpAxisZ, true);

	//0.1 位置を設定
	m_playerModel.SetPosition(m_playerModelPosition);

	//0.2 回転を設定
	m_playerModelRotation.SetRotationDegY(90.0f);
	m_playerModel.SetRotation(m_playerModelRotation);

	//0.3 大きさを設定
	m_playerModel.SetScale(m_playerModelScale);
	Quaternion playerModelRotation;
	playerModelRotation.SetRotationDegY(90.0f);
	m_playerModel.SetRotation(playerModelRotation);
	m_playerModel.Update();
}

void Title::InitSprite()
{
	//フェード
	m_fade.Init("Assets/title/screen/startfade.dds", 1600, 900);
	m_fade.SetLinearWipeDrawingMode(LinearWipeDrawingMode_Round);
	m_fade.SetWipeScrollSpeed(20.0f);

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
	m_gamepadUI[enGamePad_AButton].Init("Assets/title/gamepad/abutton.dds", 512, 512);
	m_gamepadUI[enGamePad_AButton].SetPosition(Vector3(325.0f, -345.0f, 0.0f));
	m_gamepadUI[enGamePad_AButton].SetScale(Vector3(0.1f, 0.1f, 0.1f));
	m_gamepadUI[enGamePad_AButton].Update();

	//ゲームパッド(Bボタン)
	m_gamepadUI[enGamePad_BButton].Init("Assets/title/gamepad/bbutton.dds", 512, 512);
	m_gamepadUI[enGamePad_BButton].SetPosition(Vector3(525.0f, -345.0f, 0.0f));
	m_gamepadUI[enGamePad_BButton].SetScale(Vector3(0.1f, 0.1f, 0.1f));
	m_gamepadUI[enGamePad_BButton].Update();

	//ゲームパッド(Xボタン)
	m_gamepadUI[enGamePad_XButton].Init("Assets/title/gamepad/xbutton.dds", 512, 512);

	//ゲームパッド(Yボタン)
	m_gamepadUI[enGamePad_YButton].Init("Assets/title/gamepad/ybutton.dds", 512, 512);

	//ゲームパッド(Lスティック)
	m_gamepadUI[enGamePad_LStick].Init("Assets/title/gamepad/lstick.dds", 512, 512);

	//ゲームパッド(Rスティック)
	m_gamepadUI[enGamePad_RStick].Init("Assets/title/gamepad/rstick.dds", 512, 512);

	//ゲームパッド(十字キー)
	m_gamepadUI[enGamePad_DPad].Init("Assets/title/gamepad/dpad.dds", 512, 512);

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

void Title::InitCamera()
{
	g_camera3D->SetNear(1.0f);
	g_camera3D->SetFar(10000.0f);
}

void Title::PlayerModelMove()
{
	m_playerModelPosition.x += 7.5f;
	m_playerModel.SetPosition(m_playerModelPosition);
}

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

void Title::AnimationManage()
{
	//プレイヤーモデル
	PlayerModelAnimationManage();
}

void Title::PlayAnimation()
{
	//プレイヤーモデル
	PlayerModelPlayAnimation();
}

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