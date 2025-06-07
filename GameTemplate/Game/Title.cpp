#include "stdafx.h"
#include "system/system.h"
#include "Title.h"
#include "Fade.h"
namespace
{
	//右画面端の座標
	float RIGHT_SCREEN_EDGE_POSITION = FRAME_BUFFER_W / 2;
	//上に選択
	int SELECT_UP = 1;
	//下に選択
	int SELECT_DOWN = 1;
}

//デストラクタ。
Title::~Title()
{
	DeleteGO(m_skyCube);
	DeleteGO(m_fade);
}

//開始処理。
bool Title::Start()
{
	//スカイキューブの初期化。
	InitSky();

	//アニメーションの初期化。
	InitAnimation();

	//モデルの初期化。
	InitModel();

	//スプライトの初期化。
	InitSprite();

	//カメラの初期化。
	InitCamera();

	//ライトカメラの注視点の設定。
	g_renderingEngine->SetLightCameraTarget(m_playerModelPosition);

	//インスタンス。
	//0 フェード。
	NewGO<Fade>(0, "fade");
	m_fade = FindGO<Fade>("fade");
	//フェードをフェードインに切り替える。
	m_fade->FadeTransition(enFadeState_FadeIn);

	return true;
}

//更新処理。
void Title::Update()
{
	//フェードインが終わっていなかったら。
	if (m_fadeInFinishFlag != true)
	{
		//1.0秒経過したらフェードインを終了する。
		if (g_gameTime->StopWatch(1.0f) == true)
		{
			m_fadeInFinishFlag = true;
		}
	}
	//フェードインが終わったら。
	else if (m_fadeInFinishFlag == true)
	{
		//プレイヤー側の操作。
		Action();

		//スプライトの動作。
		SpriteMove();
	}

	//ステージモデルの動作。
	BackGroundModelMove();

	//ゲームスタートフラグが立っているとき。
	if (m_gameStartFlag == true)
	{
		//プレイヤーモデルの動作。
		PlayerModelMove();
	}

	//カメラの更新。
	UpdateCamera();

	//アニメーション管理。
	AnimationManage();

	//アニメーション再生。
	PlayAnimation();

	//モデルの更新。
	m_playerModel.Update();
	m_backGroundModel[enBackGroundModel_Base].Update();
	m_backGroundModel[enBackGroundModel_Grass].Update();

	//ライトカメラの更新。
	g_renderingEngine->SetLightCameraTarget(m_playerModelPosition);

	//このクラスが削除していないとき処理する。
	if (!this->IsDead())
	{
		//タイトル画面BGMの再生。
		g_gameSoundEngine->PlayBGM(GameSoundList_BGM_Title, 1.0f);

		//タイトル画面BGMの音量を取得していなかったら
		if (m_getTitleBGMVolumeFlag != true)
		{
			//タイトル画面BGMの音量を取得。
			m_titleBGMVolume = g_gameSoundEngine->GetVolume(GameSoundList_BGM_Title);
			m_getTitleBGMVolumeFlag = true;
		}
	}
}

//描画処理。
void Title::Render(RenderContext& rc)
{
	//ステージモデル。
	m_backGroundModel[enBackGroundModel_Base].Draw(rc);
	m_backGroundModel[enBackGroundModel_Grass].Draw(rc);

	//プレイヤーモデル。
	m_playerModel.Draw(rc);

	//ゲーム開始フラグが立っていないかつ遊び方用の画面に遷移していないか?
	if (m_gameStartFlag != true && m_titleTransition != enTitleTransition_HowToPlay)
	{
		//タイトル背景。
		m_titleBackGround.Draw(rc);
	}

	//フェードインが終わっていたら描画する。
	if (m_fadeInFinishFlag == true)
	{
		//タイトル画面遷移。
		switch (m_titleTransition)
		{
		case enTitleTransition_Title: //タイトル。
			//Aボタンを押すUI。
			m_pressAButtonUI.Draw(rc);
			break;
		case enTitleTransition_ModeSelect: //モード選択。
			//ゲーム開始フラグが立っていないか？
			if (m_gameStartFlag != true)
			{
				//モード選択UI。
				m_modeUI[enModeSelect_Start].Draw(rc);
				m_modeUI[enModeSelect_HowToPlay].Draw(rc);
				m_modeUI[enModeSelect_Shutdown].Draw(rc);
				
				//ゲームパッドUI。
				m_gamePadUI[enGamePad_DPad].Draw(rc);
				m_gamePadUI[enGamePad_AButton].Draw(rc);
				m_gamePadUI[enGamePad_BButton].Draw(rc);

				//選択UI。
				m_selectUI.Draw(rc);

				//決定UI。
				m_decisionUI.Draw(rc);

				//戻るUI。
				m_returnUI.Draw(rc);
			}
			break;
		case enTitleTransition_HowToPlay: //遊び方。
			//遊び方UI。
			m_howToPlayUI.Draw(rc);

			//ゲームパッドUI。
			m_gamePadUI[enGamePad_AButton].Draw(rc);

			//戻るUI。
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
	//タイトル背景が完全に表示していないとき
	if (m_titleBackGroundFadeInFinishFlag != true)
	{
		//Aボタンを押したら演出をスキップできる
		if (g_pad[0]->IsTrigger(enButtonA))
		{
			//タイトル背景を不透明にする
			m_titleBackGround.SetMulColor(Vector4(1.0f, 1.0f, 1.0f, 1.0f));
			m_alpha = 0.0f;
			//タイトル背景のフェードインが終わった
			m_titleBackGroundFadeInFinishFlag = true;
		}
		return;
	}

	//ゲーム開始フラグが立っていないとき
	if (m_gameStartFlag != true)
	{
		//タイトル画面遷移
		switch (m_titleTransition)
		{
		case enTitleTransition_Title: //タイトル
			//Aボタンを押したらボタンを押したときの演出が流れる
			if (m_pressButtonFlag != true)
			{
				if (g_pad[0]->IsTrigger(enButtonA))
				{
					//ボタンが押された
					m_pressButtonFlag = true;
					
					//決定音の再生。
					g_gameSoundEngine->PlaySE(GameSoundList_SE_SelectScreen_Decision, 1.0f);
				}
			}

			//画面遷移フラグが立っていたら
			if (m_titleTransitionFlag == true)
			{
				//モード選択へ遷移
				m_titleTransition = enTitleTransition_ModeSelect;
				//画面遷移が終わった
				m_titleTransitionFlag = false;
				//ボタンが押されていない
				m_pressButtonFlag = false;
			}
			break;
		case enTitleTransition_ModeSelect: //モード選択
			//Aボタンを押していないとき選択ができる
			if (m_pressButtonFlag != true)
			{
				//十字キーを上に倒したら
				if (g_pad[0]->IsTrigger(enButtonUp))
				{
					//選択音の再生。
					g_gameSoundEngine->PlaySE(GameSoundList_SE_SelectScreen_Select, 1.0f);
					//現在の選択がスタートだったら
					if (m_modeSelect == enModeSelect_Start)
					{
						//ゲーム終了に移動
						m_modeSelect = enModeSelect_Shutdown;
						return;
					}
					//選択が上に上がる
					m_modeSelect -= SELECT_UP;
				}
				//十字キーを下に倒したら
				else if (g_pad[0]->IsTrigger(enButtonDown))
				{
					//選択音の再生。
					g_gameSoundEngine->PlaySE(GameSoundList_SE_SelectScreen_Select, 1.0f);
					//現在の選択がゲーム終了だったら
					if (m_modeSelect == enModeSelect_Shutdown)
					{
						//スタートに移動
						m_modeSelect = enModeSelect_Start;
						return;
					}
					//選択が下に下がる
					m_modeSelect += SELECT_DOWN;
				}

				//Aボタンを押したらボタンを押したときの演出が流れる
				if (g_pad[0]->IsTrigger(enButtonA))
				{
					//ボタンが押された
					m_pressButtonFlag = true;

					//モード選択がスタートを選択していたら
					if (m_modeSelect==enModeSelect_Start)
					{
						//決定音(画面遷移用)の再生。
						g_gameSoundEngine->PlaySE(GameSoundList_SE_SelectScreen_Decision_ScreenTransition, 1.0f);
					}
					//モード選択でスタート以外を選択していたら
					else
					{
						//決定音の再生。
						g_gameSoundEngine->PlaySE(GameSoundList_SE_SelectScreen_Decision, 1.0f);
					}
				}
				//Bボタンを押したら
				else if (g_pad[0]->IsTrigger(enButtonB))
				{
					//タイトルへ遷移
					m_titleTransition = enTitleTransition_Title;

					//キャンセル音の再生。
					g_gameSoundEngine->PlaySE(GameSoundList_SE_SelectScreen_Cancel, 1.0f);
				}
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
				//画面遷移が終わった
				m_titleTransitionFlag = false;
			}
			break;
		case enTitleTransition_HowToPlay: //遊び方
			//Aボタンを押したら
			if (g_pad[0]->IsTrigger(enButtonA))
			{
				//モード選択へ遷移
				m_titleTransition = enTitleTransition_ModeSelect;
				//ボタンが押されていない
				m_pressButtonFlag = false;

				//決定音の再生。
				g_gameSoundEngine->PlaySE(GameSoundList_SE_SelectScreen_Decision, 1.0f);
			}
			break;
		default:
			break;
		}
	}
	//ゲーム開始フラグが立っているとき
	else
	{
		//右画面端に行ったら
		if (m_playerModelPosition.x > RIGHT_SCREEN_EDGE_POSITION)
		{
			//フェードをフェードアウトに切り替える
			m_fade->FadeTransition(enFadeState_FadeOut);

			if (m_titleBGMVolume > 0.0f)
			{
				//タイトル画面BGMの音量を下げる。
				m_titleBGMVolume -= 0.03f;
				g_gameSoundEngine->SetVolume(GameSoundList_BGM_Title, m_titleBGMVolume);
			}
			else
			{
				//タイトル画面BGMの音量を0に固定する。
				m_titleBGMVolume = 0.0f;
				g_gameSoundEngine->SetVolume(GameSoundList_BGM_Title, m_titleBGMVolume);
			}

			//2.5秒経過したらシーンを遷移する
			if (m_sceneTransitionFlag != true)
			{
				if (g_gameTime->StopWatch(2.5f))
				{
					//シーン遷移
					m_sceneTransitionFlag = true;
					return;
				}
			}

			//ゲームロードフラグが立ったらゲームクラスを生成する
			if (m_gameLoadFlag == true)
			{
				//タイトル画面BGMを削除。
				DeleteGO(g_gameSoundEngine->GetSoundInstance(GameSoundList_BGM_Title));
				NewGO<Game>(0, "game");
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
		if (m_titleBackGroundFadeInFinishFlag != true)
		{
			//時間が経過したら不透明にする
			m_alpha += g_gameTime->GetFrameDeltaTime();

			//タイトル背景の乗算カラーの更新
			m_titleBackGround.SetMulColor(Vector4(1.0f, 1.0f, 1.0f, m_alpha));
			m_titleBackGround.Update();

			//透明度が1.0fになったら処理しない
			if (m_alpha > 1.0f)
			{
				m_alpha = 0.0f;
				//タイトル背景が表示できた
				m_titleBackGroundFadeInFinishFlag = true;
			}
			return;
		}

		//Aボタンが押されたらボタンを押したときの演出が流れる
		if (m_pressButtonFlag == true)
		{
			//ボタンを押したときの動作をしていないとき
			if (m_pressButtonActionFlag != true)
			{
				//Aボタンを押すUIのカラーを黒にする
				m_pressAButtonUI.SetMulColor(Vector4(0.0f, 0.0f, 0.0f, 1.0f));
				m_pressAButtonUI.Update();
				//0.1秒経過したら次の演出に移る
				if (g_gameTime->StopWatch(0.1f) == true)
				{
					//ボタンを押したとき動作をする
					m_pressButtonActionFlag = true;
				}
				return;
			}
			//ボタンを押したときの動作をしたとき
			else
			{
				//画面遷移していないとき
				if (m_titleTransitionFlag != true)
				{
					//Aボタンを押すUIのカラーを白にする
					m_pressAButtonUI.SetMulColor(Vector4(1.0f, 1.0f, 1.0f, 1.0f));
					m_pressAButtonUI.Update();
					//0.1秒経過したらモード選択に移る
					if (g_gameTime->StopWatch(0.1f) == true)
					{
						//画面遷移をする
						m_titleTransitionFlag = true;
						m_alpha = 0.0f;
						//ボタンを押したときの動作をしない
						m_pressButtonActionFlag = false;
					}
					return;
				}
			}
		}

		//Aボタンを押すUIを透明にしたり元に戻したりする
		m_alpha += g_gameTime->GetFrameDeltaTime();
		//Aボタンを押すUIの乗算カラーの更新
		m_pressAButtonUI.SetMulColor(Vector4(1.0f, 1.0f, 1.0f, fabsf(sinf(m_alpha))));
		m_pressAButtonUI.Update();
		break;
	case enTitleTransition_ModeSelect: //モード選択
		//Aボタンが押されたらボタンを押したときの演出が流れる
		if (m_pressButtonFlag == true)
		{
			//ボタンを押したときの動作をしていないとき
			if (m_pressButtonActionFlag != true)
			{
				//モード選択
				switch (m_modeSelect)
				{
				case enModeSelect_Start: //スタート
					//モードUIのスタートのカラーを黒にする
					m_modeUI[enModeSelect_Start].SetMulColor(Vector4(0.0f, 0.0f, 0.0f, 1.0f));
					m_modeUI[enModeSelect_Start].Update();
					break;
				case enModeSelect_HowToPlay: //遊び方
					//モードUIの遊び方のカラーを黒にする
					m_modeUI[enModeSelect_HowToPlay].SetMulColor(Vector4(0.0f, 0.0f, 0.0f, 1.0f));
					m_modeUI[enModeSelect_HowToPlay].Update();
					break;
				case enModeSelect_Shutdown: //ゲーム終了
					//モードUIのゲーム終了のカラーを黒にする
					m_modeUI[enModeSelect_Shutdown].SetMulColor(Vector4(0.0f, 0.0f, 0.0f, 1.0f));
					m_modeUI[enModeSelect_Shutdown].Update();
					break;
				default:
					break;
				}
				//0.1秒経過したら次の演出に移る
				if (g_gameTime->StopWatch(0.1f) == true)
				{
					//ボタンを押したとき動作をする
					m_pressButtonActionFlag = true;
				}
				return;
			}
			//ボタンを押したときの動作をしたとき
			else
			{
				//画面遷移していないとき
				if (m_titleTransitionFlag != true)
				{
					//モード選択
					switch (m_modeSelect)
					{
					case enModeSelect_Start: //スタート
						//モードUIのスタートのカラーを白にする
						m_modeUI[enModeSelect_Start].SetMulColor(Vector4(1.0f, 1.0f, 1.0f, 1.0f));
						m_modeUI[enModeSelect_Start].Update();
						break;
					case enModeSelect_HowToPlay: //遊び方
						//モードUIの遊び方のカラーを白にする
						m_modeUI[enModeSelect_HowToPlay].SetMulColor(Vector4(1.0f, 1.0f, 1.0f, 1.0f));
						m_modeUI[enModeSelect_HowToPlay].Update();
						break;
					case enModeSelect_Shutdown: //ゲーム終了
						//モードUIのゲーム終了のカラーを白にする
						m_modeUI[enModeSelect_Shutdown].SetMulColor(Vector4(1.0f, 1.0f, 1.0f, 1.0f));
						m_modeUI[enModeSelect_Shutdown].Update();
						break;
					default:
						break;
					}
					//0.1秒経過したら各モードを選択した演出に移る
					if (g_gameTime->StopWatch(0.1f) == true)
					{
						//画面遷移をする
						m_titleTransitionFlag = true;
						//ボタンを押したときの動作をしない
						m_pressButtonActionFlag = false;
					}
					return;
				}
			}
		}

		//現在の選択がスタートだったらモード選択UIをスタート以外黒にする
		if (m_modeSelect == enModeSelect_Start)
		{
			//モード選択UIの乗算カラーの更新
			//モードUIのスタート以外のカラーは黒にする
			m_modeUI[enModeSelect_Start].SetMulColor(m_modeUIColor[enModeSelect_Start]);
			m_modeUI[enModeSelect_HowToPlay].SetMulColor(Vector4(0.0f, 0.0f, 0.0f, 1.0f));
			m_modeUI[enModeSelect_Shutdown].SetMulColor(Vector4(0.0f, 0.0f, 0.0f, 1.0f));
		}
		//現在の選択が遊び方だったらモード選択UIを遊び方以外黒にする
		else if (m_modeSelect == enModeSelect_HowToPlay)
		{
			//モード選択UIの乗算カラーの更新
			//モードUIの遊び方以外のカラーは黒にする
			m_modeUI[enModeSelect_Start].SetMulColor(Vector4(0.0f, 0.0f, 0.0f, 1.0f));
			m_modeUI[enModeSelect_HowToPlay].SetMulColor(m_modeUIColor[enModeSelect_HowToPlay]);
			m_modeUI[enModeSelect_Shutdown].SetMulColor(Vector4(0.0f, 0.0f, 0.0f, 1.0f));
		}
		//現在の選択がゲーム終了だったらモード選択UIをゲーム終了以外黒にする
		else if (m_modeSelect == enModeSelect_Shutdown)
		{
			//モード選択UIの乗算カラーの更新
			//モードUIのゲーム終了以外のカラーは黒にする
			m_modeUI[enModeSelect_Start].SetMulColor(Vector4(0.0f, 0.0f, 0.0f, 1.0f));
			m_modeUI[enModeSelect_HowToPlay].SetMulColor(Vector4(0.0f, 0.0f, 0.0f, 1.0f));
			m_modeUI[enModeSelect_Shutdown].SetMulColor(m_modeUIColor[enModeSelect_HowToPlay]);
		}

		//ゲームパッド(Aボタン)の更新
		m_gamePadUI[enGamePad_AButton].SetPosition(Vector3(325.0f, -345.0f, 0.0f));
		m_gamePadUI[enGamePad_AButton].Update();

		//戻るUIの更新
		m_returnUI.SetPosition(Vector3(600.0f, -345.0f, 0.0f));
		m_returnUI.Update();
		break;
	case enTitleTransition_HowToPlay: //遊び方
		//ゲームパッド(Aボタン)の更新
		m_gamePadUI[enGamePad_AButton].SetPosition(Vector3(575.0f, -345.0f, 0.0f));
		m_gamePadUI[enGamePad_AButton].Update();

		//戻るUIの更新
		m_returnUI.SetPosition(Vector3(650.0f, -345.0f, 0.0f));
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

	//スカイキューブ
	//0 スカイキューブの初期化
	m_skyCube->SetLuminance(1.0f);
	//0.1 スカイキューブのテクスチャを設定
	m_skyCube->SetType((EnSkyCubeType)m_skyCubeType);
	//0.2 スカイキューブの座標の設定
	m_skyCube->SetPosition(Vector3(0.0f, -1000.0f, 0.0f));
	//0.3 スカイキューブの大きさの設定
	m_skyCube->SetScale(Vector3(750.0f, 750.0f, 750.0f));
	//0.4 スカイキューブの更新
	m_skyCube->Update();
}

//アニメーションの初期化
void Title::InitAnimation()
{
	//各アニメーションの初期設定
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
	//各モデルの初期設定
	//ステージ
	//0 ステージの初期化
	m_backGroundModel[enBackGroundModel_Base].Init("Assets/title/background_base.tkm"); //土台
	m_backGroundModel[enBackGroundModel_Grass].Init("Assets/title/background_grass.tkm", 0,
		0, enModelUpAxisZ, false, true); //草原

	//0.1 ステージの大きさを設定
	m_backGroundModel[enBackGroundModel_Base].SetScale(Vector3(10.0f, 10.0f, 10.0f)); //土台
	m_backGroundModel[enBackGroundModel_Base].Update();

	m_backGroundModel[enBackGroundModel_Grass].SetScale(Vector3(10.0f, 10.0f, 10.0f)); //草原
	m_backGroundModel[enBackGroundModel_Grass].Update();

	//0.2 ステージのスクロール速度を設定
	m_backGroundModel[enBackGroundModel_Base].SetScrollSpeed(-1.0f); //土台
	m_backGroundModel[enBackGroundModel_Grass].SetScrollSpeed(1.0f); //草原

	//プレイヤーモデル
	//1 プレイヤーモデルの初期化
	m_playerModel.Init("Assets/modelData/player/player.tkm", m_animationClip,
		enAnimationClip_num, enModelUpAxisZ, true);

	//1.1 プレイヤーモデルの位置を設定
	m_playerModel.SetPosition(m_playerModelPosition);

	//1.2 プレイヤーモデルの回転を設定
	m_playerModelRotation.SetRotationDegY(90.0f);
	m_playerModel.SetRotation(m_playerModelRotation);

	//1.3 プレイヤーモデルの大きさを設定
	m_playerModel.SetScale(m_playerModelScale);
	m_playerModel.Update();
}

//スプライトの初期化
void Title::InitSprite()
{
	//各スプライトの初期設定
	//タイトル背景
	//0 タイトル背景の初期化
	m_titleBackGround.Init("Assets/title/title.dds", 1024, 1024);
	//0.1 タイトル画面の座標の設定
	m_titleBackGround.SetPosition(Vector3(0.0f, 300.0f, 0.0f));
	//0.2 タイトル画面の大きさの設定
	m_titleBackGround.SetScale(Vector3(0.65f, 0.65f, 0.65f));
	//0.3 タイトル画面の乗算カラーの設定
	m_titleBackGround.SetMulColor(Vector4(1.0f, 1.0f, 1.0f, m_alpha));
	//0.4 タイトル画面の更新
	m_titleBackGround.Update();

	//Aボタンを押すUI
	//1 Aボタンを押すUIの初期化
	m_pressAButtonUI.Init("Assets/title/text/pressabutton.dds", 1024, 128);
	//1.1 Aボタンを押すUIの座標の設定
	m_pressAButtonUI.SetPosition(Vector3(0.0f, -150.0f, 0.0f));
	//1.2 Aボタンを押すUIの大きさの設定
	m_pressAButtonUI.SetScale(Vector3(0.75f, 0.75f, 0.75f));
	//1.3 Aボタンを押すUIの乗算カラーの設定
	m_pressAButtonUI.SetMulColor(Vector4(1.0f, 1.0f, 1.0f, m_alpha));
	//1.4 Aボタンを押すUIの更新
	m_pressAButtonUI.Update();

	//モード選択UI(スタート)
	//2 モード選択UI(スタート)
	m_modeUI[enModeSelect_Start].Init("Assets/title/text/start.dds", 1024, 128);
	//2.1 モード選択UI(スタート)の座標の設定
	m_modeUI[enModeSelect_Start].SetPosition(Vector3(0.0f, 0.0f, 0.0f));
	//2.2 モード選択UI(スタート)の大きさの設定
	m_modeUI[enModeSelect_Start].SetScale(Vector3(0.5f,0.5f,0.5f));
	//2.3 モード選択UI(スタート)の乗算カラーの設定
	m_modeUI[enModeSelect_Start].SetMulColor(Vector4(1.0f, 1.0f, 1.0f, 1.0f));
	//2.4 モード選択UI(スタート)の更新
	m_modeUI[enModeSelect_Start].Update();
	//2.5 モード選択UI(スタート)の乗算カラーの取得
	m_modeUIColor[enModeSelect_Start] = m_modeUI[enModeSelect_Start].GetMulColor();

	//モード選択UI(遊び方)
	//3 モード選択UI(遊び方)
	m_modeUI[enModeSelect_HowToPlay].Init("Assets/title/text/howtoplay.dds", 1024, 128);
	//3.1 
	m_modeUI[enModeSelect_HowToPlay].SetPosition(Vector3(0.0f, -75.0f, 0.0f));
	//3.2 
	m_modeUI[enModeSelect_HowToPlay].SetScale(Vector3(0.5f,0.5f,0.5f));
	//3.3 
	m_modeUI[enModeSelect_HowToPlay].SetMulColor(Vector4(1.0f, 1.0f, 1.0f, 1.0f));
	//3.4 
	m_modeUI[enModeSelect_HowToPlay].Update();
	//3.5
	m_modeUIColor[enModeSelect_HowToPlay] = m_modeUI[enModeSelect_HowToPlay].GetMulColor();

	//モード選択UI(ゲーム終了)
	//4 モード選択UI(ゲーム終了)の初期化
	m_modeUI[enModeSelect_Shutdown].Init("Assets/title/text/shutdown.dds", 1024, 128);
	//4.1 モード選択UI(ゲーム終了)の座標の設定
	m_modeUI[enModeSelect_Shutdown].SetPosition(Vector3(0.0f, -150.0f, 0.0f));
	//4.2 モード選択UI(ゲーム終了)の大きさの設定
	m_modeUI[enModeSelect_Shutdown].SetScale(Vector3(0.5f, 0.5f, 0.5f));
	//4.3 モード選択UI(ゲーム終了)の乗算カラーの設定
	m_modeUI[enModeSelect_Shutdown].SetMulColor(Vector4(1.0f, 1.0f, 1.0f, 1.0f));
	//4.4 モード選択UI(ゲーム終了)の更新
	m_modeUI[enModeSelect_Shutdown].Update();
	//4.5 モード選択UI(ゲーム終了)の乗算カラーの取得
	m_modeUIColor[enModeSelect_Shutdown] = m_modeUI[enModeSelect_Shutdown].GetMulColor();

	//遊び方UI
	//5 遊び方UIの初期化
	m_howToPlayUI.Init("Assets/title/screen/howtoplay.dds", 1500, 800);

	//ゲームパッド(Aボタン)UI
	//6 ゲームパッド(Aボタン)UIの初期化
	m_gamePadUI[enGamePad_AButton].Init("Assets/title/gamepad/abutton.dds", 512, 512);
	//6.1 ゲームパッド(Aボタン)UIの座標の設定
	m_gamePadUI[enGamePad_AButton].SetPosition(Vector3(325.0f, -345.0f, 0.0f));
	//6.2 ゲームパッド(Aボタン)UIの大きさの設定
	m_gamePadUI[enGamePad_AButton].SetScale(Vector3(0.1f, 0.1f, 0.1f));
	//6.3 ゲームパッド(Aボタン)UIの更新
	m_gamePadUI[enGamePad_AButton].Update();

	//ゲームパッド(Bボタン)UI
	//7 ゲームパッド(Bボタン)UIの初期化
	m_gamePadUI[enGamePad_BButton].Init("Assets/title/gamepad/bbutton.dds", 512, 512);
	//7.1 ゲームパッド(Bボタン)UIの座標の設定
	m_gamePadUI[enGamePad_BButton].SetPosition(Vector3(525.0f, -345.0f, 0.0f));
	//7.2 ゲームパッド(Bボタン)UIの大きさの設定
	m_gamePadUI[enGamePad_BButton].SetScale(Vector3(0.1f, 0.1f, 0.1f));
	//7.3 ゲームパッド(Bボタン)UIの更新
	m_gamePadUI[enGamePad_BButton].Update();

	//ゲームパッド(Xボタン)UI
	//8 ゲームパッド(Xボタン)UIの初期化
	m_gamePadUI[enGamePad_XButton].Init("Assets/title/gamepad/xbutton.dds", 512, 512);

	//ゲームパッド(Yボタン)UI
	//9 ゲームパッド(Yボタン)UIの初期化
	m_gamePadUI[enGamePad_YButton].Init("Assets/title/gamepad/ybutton.dds", 512, 512);

	//ゲームパッド(Lスティック)UI
	//10 ゲームパッド(Lスティック)UIの初期化
	m_gamePadUI[enGamePad_LStick].Init("Assets/title/gamepad/lstick.dds", 512, 512);

	//ゲームパッド(Rスティック)UI
	//11 ゲームパッド(Rスティック)UIの初期化
	m_gamePadUI[enGamePad_RStick].Init("Assets/title/gamepad/rstick.dds", 512, 512);

	//ゲームパッド(十字キー)UI
	//12 ゲームパッド(十字キー)UIの初期化
	m_gamePadUI[enGamePad_DPad].Init("Assets/title/gamepad/dpad.dds", 512, 512);
	//12.1 ゲームパッド(十字キー)UIの座標の設定
	m_gamePadUI[enGamePad_DPad].SetPosition(Vector3(125.0f, -345.0f, 0.0f));
	//12.2 ゲームパッド(十字キー)UIの大きさの設定
	m_gamePadUI[enGamePad_DPad].SetScale(Vector3(0.1f, 0.1f, 0.1f));
	//12.3 ゲームパッド(十字キー)UIの更新
	m_gamePadUI[enGamePad_DPad].Update();

	//選択UI
	//13 選択UIの初期化
	m_selectUI.Init("Assets/title/text/select.dds", 1024, 128);
	//13.1 選択UIの座標の設定
	m_selectUI.SetPosition(Vector3(200.0f, -345.0f, 0.0f));
	//13.2 選択UIの大きさの設定
	m_selectUI.SetScale(Vector3(0.3f, 0.3f, 0.3f));
	//13.3 選択UIの更新
	m_selectUI.Update();

	//決定UI
	//14 決定UIの初期化
	m_decisionUI.Init("Assets/title/text/decision.dds", 1024, 128);
	//14.1 決定UIの座標の設定
	m_decisionUI.SetPosition(Vector3(400.0f, -345.0f, 0.0f));
	//14.2 決定UIの大きさの設定
	m_decisionUI.SetScale(Vector3(0.3f, 0.3f, 0.3f));
	//14.3 決定UIの更新
	m_decisionUI.Update();

	//戻るUI
	//15 戻るUIの初期化
	m_returnUI.Init("Assets/title/text/return.dds", 1024, 128);
	//15.1 戻るUIの座標の設定
	m_returnUI.SetPosition(Vector3(600.0f, -345.0f, 0.0f));
	//15.2 戻るUIの大きさの設定
	m_returnUI.SetScale(Vector3(0.3f, 0.3f, 0.3f));
	//15.3 戻るUIの更新
	m_returnUI.Update();
}

//カメラの初期化
void Title::InitCamera()
{
	//カメラの近平面と遠平面の初期設定
	g_camera3D->SetNear(1.0f);
	g_camera3D->SetFar(15000.0f);
}

//ステージモデルの動作
void Title::BackGroundModelMove()
{
	//遊び方用の画面に遷移していたら
	if (m_titleTransition == enTitleTransition_HowToPlay)
	{
		//ステージモデルの動きを止める
		m_backGroundModel[enBackGroundModel_Base].SetScrollSpeed(0.0f);  //土台
		m_backGroundModel[enBackGroundModel_Grass].SetScrollSpeed(0.0f); //草原
	}
	else
	{
		//ステージモデルを動き続ける
		m_backGroundModel[enBackGroundModel_Base].SetScrollSpeed(-1.0f); //土台
		m_backGroundModel[enBackGroundModel_Grass].SetScrollSpeed(1.0f); //草原
	}
}

//プレイヤーモデルの動作
void Title::PlayerModelMove()
{
	//モード選択でスタートを選択していたらモデルを右に移動する
	m_playerModelPosition.x += 7.5f;
	m_playerModel.SetPosition(m_playerModelPosition);
}

//カメラの更新
void Title::UpdateCamera()
{
	//ゲームスタートフラグが立っていないとき
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
	//ゲーム開始フラグが立っているときは走るアニメーションを再生する
	if (m_gameStartFlag == true)
	{
		//走るアニメーション
		m_playerModelAnimationState = enPlayerModelAnimationState_run;
	}
	//ゲーム開始フラグが立っていないときは歩きアニメーションを再生する
	else
	{
		//歩きアニメーション
		m_playerModelAnimationState = enPlayerModelAnimationState_walk;
	}
}

//プレイヤーモデルのアニメーション再生
void Title::PlayerModelPlayAnimation()
{
	//プレイヤーモデルアニメーションステート
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