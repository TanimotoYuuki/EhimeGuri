#include "stdafx.h"
#include "GameClear.h"
#include "GameOver.h"
#include "Title.h"
#include "Config.h"
#include "Fade.h"

namespace
{
	// WIDHT … 横。
	// HEIGHT … 縦。

	// カメラ用の定数。
	const Vector3 CAMERA_POSITION(0.0f, 100.0f, -200.0f);
	const Vector3 CAMERA_TARGET(0.0f, 50.0f, 0.0f);

	// リザルト用の定数。
	const float RESULT_WIDHT = 1600;
	const float RESULT_HEIGHT = 900;

	// 収集率用の定数。
	const float PERCENT_WIDHT = 1024;
	const float PERCENT_HEIGHT = 128;
	const Vector3 UI_POSITION(675.0f, 149.0f, 0.0f);

	// 背景用の定数。
	const int PLACE_WIDHT = 1024;
	const int PLACE_HEIGHT = 128;
	const Vector3 PLACE_POSITION(672.5f, 10.0f, 0.0f);

	// Aボタン。
	const float ABUTTON_WIDHT = 512;
	const float ABUTTON_HEIGHT = 512;
	const Vector3 ABUTTON_UI(475.0f, -400.0f, 0.0f);
	const Vector3 ABUTTON_SCALE(0.1f, 0.1f, 0.1f);

	// タイトルへ戻るUI
	const float RETURNBUTTON_WIDHT = 1024;
	const float RETURNBUTTON_HEIGHT = 128;
	const Vector3 RETURNBUTTON_POSITION(615.0f, -400.0f, 0.0f);
	const Vector3 RETURNBUTTON_SCALE(0.3f, 0.3f, 0.3f);

	// 収集率 - 100の位-
	const Vector3 COLLECTIONRATE_100(320.0f, 157.5f, 0.0f);
	const float COLLECTIONRATE_WIDHT = 1024;
	const float COLLECTIONRATE_HEIGHT = 128;
	const Vector4 MULTIPLY_COLOR(1.0f, 1.0f, 1.0f, 0.0f);

	// 収集率 - 10の位 -
	const Vector3 COLLECTIONRATE_10(400.0f, 157.5f, 0.0f);

	// 収集率 - 1の位 -
	const Vector3 COLLECTIONRATE_1(480.0f, 157.5f, 0.0f);

	// ランクUI
	const float RANK_UI_WIDHT = 1024;
	const float RANK_UI_HEIGHT = 128;
	const Vector3 RANK_UI_POSITION(400.0f, -119.5, 0.0f);

	// ステージ背景用。
	const float GAME_BACKGD_WIDHT = 1600;
	const float GAME_BACKGD_HEIGHT = 900;
}

// リザルト用。
std::string GameClear::GetFullPath_RESULT(const std::string& name, const float w, const float h)  
{  
    string GameClear = RESULT + name + dds_EXTENSION;  

    m_result.Init(GameClear.c_str(), w, h);  
    return GameClear;  
}

// パーセント用。
std::string GameClear::GetFullPath_PERCENT(const std::string& name, const float w, const float h)
{
	string Percent = RESULT + name + dds_EXTENSION;


	m_percentUI.Init(Percent.c_str(), w, h);
	return Percent;
}

// Aボタン用。
std::string GameClear::GetFullPaht_BUTTONUI(const std::string& name, const float w, const float h)
{
	string Abutton = ABUTTHON + name + dds_EXTENSION;

	m_aButtonUI.Init(Abutton.c_str(), w, h);
	return Abutton;
}

// タイトルへ戻るUI
std::string GameClear::GetFullPath_RETURNUI(const std::string& name, const float w, const float h)
{
	string RETURNUI = RETURNBUTTON + name + dds_EXTENSION;

	m_returnTitleUI.Init(RETURNUI.c_str(), w, h);
	return RETURNUI;

}

// ステージ背景用。
std::string GameClear::GetFullPath_BACKGROUND(const std::string& name, const float w, const float h)
{
	string BACKGROUND = GROUND + name + dds_EXTENSION;

	m_gameBackground.Init(BACKGROUND.c_str(), w, h);
	return BACKGROUND;

}

// リザルトアニメーションメソッド。
std::string GameClear::GetFullPath_ResultAnimation(EnAnimationClip enAnimationClip, const std::string& animationName, bool flag)
{
	std::string ResultAnimation = RESULT_ANIMATION + animationName + ANIMATION_FILE_EXTENSION;

	// アニメーションをロードをする。
	m_animationClip[enAnimationClip].Load(ResultAnimation.c_str());
	m_animationClip[enAnimationClip].SetLoopFlag(flag);

	return ResultAnimation;
};

// Playerモデルをセットする。
std::string GameClear::GetFullPath_ResultPlayer(const std::string& modelName, AnimationClip* animationClip, EnAnimationClip enAnimationClip, EnModelUpAxis enModelUpAxis)
{
	// モデルをロード(tkmファイル名を打ち込む)。
	std::string  ResultPlayer = RESULT_PLAYER + modelName + TKM;

	m_animationClip[enAnimationClip].Load(ResultPlayer.c_str());

	return ResultPlayer;
}

//デストラクタ。
GameClear::~GameClear()
{
	DeleteGO(m_fade);
}

//開始処理。
bool GameClear::Start()
{
	//カメラの初期化。
	InitCamera();

	//スプライトの初期化。
	InitSprite();

	//モデルの初期化。
	InitModel();

	//ライトカメラの注視点の設定。
	g_renderingEngine->SetLightCameraTarget(m_playerModelPosition);

	//インスタンス。
	//0 フェード。
	NewGO<Fade>(0, "fade");
	m_fade = FindGO<Fade>("fade");

	return true;
}

//更新処理。
void GameClear::Update()
{
	//プレイヤー側の操作。
	Action();

	//ゲームクリア演出が終わっていないとき。
	if (m_gameClearDirectionFlag != true)
	{
		//フェードインが終わったら処理する
		if (m_fade->IsFadeInFinish())
		{
			//スプライトの動作。
			SpriteMove();
		}
	}
	//ゲームクリア演出が終わったとき
	else
	{
		//ランク用の音の再生。
		RankSEPlay();
	}

	//プレイヤーモデルのアニメーション管理。
	PlayerModelAnimationManage();

	//プレイヤーモデルのアニメーション再生。
	PlayerModelPlayAnimation();

	//モデルの更新。
	m_playerModel.Update();

	//ライトカメラの更新。
	g_renderingEngine->SetLightCameraTarget(m_playerModelPosition);

	//このクラスが削除していないとき処理する。
	if (!this->IsDead())
	{
		//リザルト画面BGMの再生
		g_gameSoundEngine->PlayBGM(GameSoundList_BGM_Result, 1.0f);

		//リザルト画面BGMの音量を取得していなかったら
		if (m_getResultBGMVolumeFlag != true)
		{
			//タイトル画面BGMの音量を取得。
			m_resultBGMVolume = g_gameSoundEngine->GetVolume(GameSoundList_BGM_Result);
			m_getResultBGMVolumeFlag = true;
		}
	}
}

//描画処理。
void GameClear::Render(RenderContext& rc)
{	
	
	//ゲーム背景の描画。
	m_gameBackground.Draw(rc);

	//リザルト画面。
	m_result.Draw(rc);

	//パーセントUI。
	m_percentUI.Draw(rc);

	//ランクUI。
	m_rankUI[m_rankState].Draw(rc);

	//ゲームクリア演出が終わったら描画する。
	if (m_gameClearDirectionFlag == true)
	{
		//AボタンUI。
		m_aButtonUI.Draw(rc);

		//タイトルへ戻るUI。
		m_returnTitleUI.Draw(rc);
	}

	//収集率が100%のとき描画する。
	if (m_gatheringRate >= 100)
	{
		//100%～。
		//収集率用数字UI(百の位)。
		m_gatheringRateNumberHundredPlaceUI[m_hundredPlace].Draw(rc);
	}

	//収集率が10%以上のとき描画する。
	if (m_gatheringRate >= 10)
	{
		//10%～。
		//収集率用数字UI(十の位)。
		m_gatheringRateNumberTenPlaceUI[m_tenPlace].Draw(rc);
	}

	//0%～。
	//収集率用数字UI(一の位)。
	m_gatheringRateNumberOnePlaceUI[m_onePlace].Draw(rc);

	//プレイヤーモデル。
	m_playerModel.Draw(rc);
}

//カメラの初期化。
void GameClear::InitCamera()
{
	//カメラの位置と注視点の初期設定。
	g_camera3D->SetPosition(CAMERA_POSITION);
	g_camera3D->SetTarget(CAMERA_TARGET);
}

//スプライトの初期化。
void GameClear::InitSprite()
{
	//各スプライトの初期設定。
	//リザルト画面。
	//0 リザルト画面の初期化。
	GetFullPath_RESULT("result", RESULT_WIDHT, RESULT_HEIGHT);

	//パーセントUI。
	//1 パーセントUIの初期化。
	GetFullPath_PERCENT("percent", PERCENT_WIDHT, PERCENT_HEIGHT);
	//1.1 パーセントUIの座標の設定。
	m_percentUI.SetPosition(UI_POSITION);
	//1.2 パーセントUIの更新。
	m_percentUI.Update();

	//AボタンUI。
	//4 AボタンUIの初期化。
	GetFullPaht_BUTTONUI("abutton", ABUTTON_WIDHT, ABUTTON_HEIGHT);
	//4.1 AボタンUIの座標の設定。
	m_aButtonUI.SetPosition(ABUTTON_UI);
	//4.2 AボタンUIの大きさの設定。
	m_aButtonUI.SetScale(ABUTTON_SCALE);
	//4.3 Aボタンの更新。
	m_aButtonUI.Update();

	//タイトルへ戻るUI。
	//5 タイトルへ戻るUIの初期化。
	GetFullPath_RETURNUI("returntitle", RETURNBUTTON_WIDHT, RETURNBUTTON_HEIGHT);
	//5.1 タイトルへ戻るUIの座標の設定。
	m_returnTitleUI.SetPosition(RETURNBUTTON_POSITION);
	//5.2 タイトルへ戻るUIの大きさの設定。
	m_returnTitleUI.SetScale(RETURNBUTTON_SCALE);
	//5.3 タイトルへ戻るUIの更新。
	m_returnTitleUI.Update();

	//収集率の計算。
	GatheringRate(m_gatheringItemNum, m_totalItemNum);

	//収集率用数字UI(百の位)。
	//6 収集率用数字UI(百の位)用のファイルパスを取得。
	GetNumberUISpriteFilePath(m_hundredPlace);
	//6.1 収集率用数字UI(百の位)の初期化。
	m_gatheringRateNumberHundredPlaceUI[m_hundredPlace].Init(m_numberUISpriteFilePath, COLLECTIONRATE_WIDHT, COLLECTIONRATE_HEIGHT);
	//6.2 収集率用数字UI(百の位)の座標の設定。
	m_gatheringRateNumberHundredPlaceUI[m_hundredPlace].SetPosition(COLLECTIONRATE_100);
	//6.3 収集率用数字UI(百の位)の乗算カラーの設定。
	m_gatheringRateNumberHundredPlaceUI[m_hundredPlace].SetMulColor(MULTIPLY_COLOR);
	//6.4 収集率用数字UI(百の位)の更新。
	m_gatheringRateNumberHundredPlaceUI[m_hundredPlace].Update();

	//収集率用数字UI(十の位)。
	//7 収集率用数字UI(十の位)用のファイルパスを取得。
	GetNumberUISpriteFilePath(m_tenPlace);
	//7.1 収集率用数字UI(十の位)の初期化。
	m_gatheringRateNumberTenPlaceUI[m_tenPlace].Init(m_numberUISpriteFilePath, COLLECTIONRATE_WIDHT, COLLECTIONRATE_HEIGHT);
	//7.2 収集率用数字UI(十の位)の座標の設定。
	m_gatheringRateNumberTenPlaceUI[m_tenPlace].SetPosition(COLLECTIONRATE_10);
	//7.3 収集率用数字UI(十の位)の乗算カラーの設定。
	m_gatheringRateNumberTenPlaceUI[m_tenPlace].SetMulColor(MULTIPLY_COLOR);
	//7.4 収集率用数字UI(十の位)の更新。
	m_gatheringRateNumberTenPlaceUI[m_tenPlace].Update();

	//収集率用数字UI(一の位)。
	//8 収集率用数字UI(一の位)用のファイルパスを取得。
	GetNumberUISpriteFilePath(m_onePlace);
	//8.1 収集率用数字UI(一の位)の初期化。
	m_gatheringRateNumberOnePlaceUI[m_onePlace].Init(m_numberUISpriteFilePath, COLLECTIONRATE_WIDHT, COLLECTIONRATE_HEIGHT);
	//8.2 収集率用数字UI(一の位)の座標の設定。
	m_gatheringRateNumberOnePlaceUI[m_onePlace].SetPosition(COLLECTIONRATE_1);
	//8.3 収集率用数字UI(一の位)の乗算カラーの設定。
	m_gatheringRateNumberOnePlaceUI[m_onePlace].SetMulColor(MULTIPLY_COLOR);
	//8.4 収集率用数字UI(一の位)の更新。
	m_gatheringRateNumberOnePlaceUI[m_onePlace].Update();

	//ランクを設定する。
	SetRank();

	//ランクUI。
	//9 ランクUIの初期化。
	m_rankUI[m_rankState].Init(m_rankUISpriteFilePath, RANK_UI_WIDHT, RANK_UI_HEIGHT);
	//9.1 ランクUIの座標の設定。
	m_rankUI[m_rankState].SetPosition(RANK_UI_POSITION);
	//9.2 ランクUIの乗算カラーの設定。
	m_rankUI[m_rankState].SetMulColor(m_rankUISpriteColor);
	//9.3 ランクUIの更新。
	m_rankUI[m_rankState].Update();

	//ゲーム背景。
	//10 ゲーム背景の初期化。
	GetFullPath_BACKGROUND("yellow", GAME_BACKGD_WIDHT, GAME_BACKGD_HEIGHT);
	//10.1 ゲーム背景の更新。
	m_gameBackground.Update();
}

//モデルの初期化。
void GameClear::InitModel()
{
	// アニメーションを再生する。
	SetPlayAnimation();

	//モデルの初期化。
	//0 プレイヤーモデルの初期化。
	m_playerModel.Init("Assets/modelData/player/player.tkm", m_animationClip, enAnimationClip_Num, enModelUpAxisZ);

	//0.1 位置の設定。
	m_playerModel.SetPosition(m_playerModelPosition);

	//0.2 回転の設定。
	m_playerModelRotation.SetRotationDegY(180.0f);
	m_playerModel.SetRotation(m_playerModelRotation);

	//0.3 大きさの設定。
	m_playerModel.SetScale(m_playerModelScale);

	//0.4 モデルの更新処理。
	m_playerModel.Update();
}

//収集率の計算。
void GameClear::GatheringRate(int gatheringItemNum, int totalItemNum)
{
	//収集率を求める。
	m_gatheringRate = ((gatheringItemNum * 100) + (totalItemNum / 2)) / totalItemNum;

	//UIを表示するための計算。
	//百の位。
	m_hundredPlace = m_gatheringRate / 100;

	//十の位。
	m_tenPlace = (m_gatheringRate % 100) / 10;

	//一の位。
	m_onePlace = m_gatheringRate % 10;
}

//プレイヤーモデルのアニメーション管理。
void GameClear::PlayerModelAnimationManage()
{
	//ゲームクリア演出が終わったらランクごとのアニメーションを再生する。
	if (m_gameClearDirectionFlag == true)
	{
		//収集率が100%なら(Sランク)。
		if (m_gatheringRate >= 100)
		{
			m_animationState = enAnimationState_Victory;	//嬉しい。
		}
		//収集率が40%以上なら(A～Bランク)。
		else if (m_gatheringRate >= 40)
		{
			m_animationState = enAnimationState_FistPump;	//ガッツ。
		}
		//収集率が40%未満なら(Cランク)。
		else
		{
			m_animationState = enAnimationState_Defeat;		//悔しい。
		}
	}
	//ゲームクリア演出が終わっていなかったら待機アニメーションを再生する。
	else
	{
		m_animationState = enAnimationClip_Idle;	//待機。
	}
}

//スプライトの動作。
void GameClear::SpriteMove()
{
	//ゲームクリア演出ステート。
	switch (m_gameClearDirectionState)
	{
	case enGameClearDirection_GatheringRate:	//収集率。
		//時間が経過したら不透明にする。
		m_gatheringRateUIAlphaColor += g_gameTime->GetFrameDeltaTime() * 1.2f;

		//収集率UIが不透明になったら順位用の演出に移る。
		if (m_gatheringRateUIAlphaColor > 1.0f)
		{
			m_gatheringRateUIAlphaColor = 1.0f;

			//スコアを表示した時の音の再生。
			g_gameSoundEngine->PlaySE(GameSoundList_SE_Result_ViewScore, 1.0f);

			//順位用の演出に移る。
			m_gameClearDirectionState = enGameClearDirection_Rank;
		}

		//収集率用数字UIの乗算カラーの更新。
		m_gatheringRateNumberHundredPlaceUI[m_hundredPlace].SetMulColor(Vector4(1.0f, 1.0f, 1.0f, m_gatheringRateUIAlphaColor));
		m_gatheringRateNumberTenPlaceUI[m_tenPlace].SetMulColor(Vector4(1.0f, 1.0f, 1.0f, m_gatheringRateUIAlphaColor));
		m_gatheringRateNumberOnePlaceUI[m_onePlace].SetMulColor(Vector4(1.0f, 1.0f, 1.0f, m_gatheringRateUIAlphaColor));
		break;
	case enGameClearDirection_Rank:				//ランク。
		//時間が経過したら不透明にする。
		m_rankUIAlphaColor += g_gameTime->GetFrameDeltaTime() * 1.2f;

		//ランク用UIが不透明になったらゲームクリア演出を終了する。
		if (m_rankUIAlphaColor > 1.0f)
		{
			m_rankUIAlphaColor = 1.0f;

			//スコアを表示した時の音の再生をしていないとき
			if (m_isViewScoreSEPlaying != true)
			{
				//スコアを表示した時の音の再生。
				g_gameSoundEngine->PlaySE(GameSoundList_SE_Result_ViewScore, 1.0f);
				m_isViewScoreSEPlaying = true;
			}

			//ランク用UIの表示が終わってから0.75秒経過したらゲームクリア演出を終了する。
			if (g_gameTime->StopWatch(0.75f))
			{
				//ゲームクリア演出を終了する。
				m_gameClearDirectionFlag = true;
			}
			return;
		}

		//ランクUIの乗算カラーの更新。
		m_rankUI[m_rankState].SetMulColor(Vector4(m_rankUISpriteColor.x, m_rankUISpriteColor.y, m_rankUISpriteColor.z, m_rankUIAlphaColor));
		break;
	default:
		break;
	}
}

//プレイヤー側の操作。
void GameClear::Action()
{
	//ゲームクリア演出が終わっていないとき。
	if (m_gameClearDirectionFlag != true)
	{
		//Aボタンを押したら演出をスキップできる。
		if (g_pad[0]->IsTrigger(enButtonA))
		{
			//各スプライトの透明度を不透明にする。
			//収集率UI。
			m_gatheringRateNumberHundredPlaceUI[m_hundredPlace].SetMulColor(MULTIPLY_COLOR);
			m_gatheringRateNumberTenPlaceUI[m_tenPlace].SetMulColor(MULTIPLY_COLOR);
			m_gatheringRateNumberOnePlaceUI[m_onePlace].SetMulColor(MULTIPLY_COLOR);

			//ランクUI。
			m_rankUI[m_rankState].SetMulColor(Vector4(m_rankUISpriteColor.x, m_rankUISpriteColor.y, m_rankUISpriteColor.z, 1.0f));

			//ゲームクリア演出を終了する。
			m_gameClearDirectionFlag = true;
		}
		return;
	}

	//タイトル画面遷移フラグが立っていないとき。
	if (m_titleScreenTransitionFlag != true)
	{
		//Aボタンを押したらタイトルへ戻る。
		if (g_pad[0]->IsTrigger(enButtonA))
		{
			m_titleScreenTransitionFlag = true;

			//決定音(画面遷移用)の再生。
			g_gameSoundEngine->PlaySE(GameSoundList_SE_SelectScreen_Decision_ScreenTransition, 1.0f);

			//フェードをフェードアウトに切り替える。
			m_fade->FadeTransition(enFadeState_FadeOut);
		}
	}
	else
	{
		//リザルトBGMの音量が0ではないとき
		if (m_resultBGMVolume > 0.0f)
		{
			//リザルト画面BGMの音量を下げる。
			m_resultBGMVolume -= 0.03f;
			g_gameSoundEngine->SetVolume(GameSoundList_BGM_Result, m_resultBGMVolume);
		}
		//リザルトBGMの音量が0のとき
		else
		{
			//リザルト画面BGMの音量を0に固定する。
			m_resultBGMVolume = 0.0f;
			g_gameSoundEngine->SetVolume(GameSoundList_BGM_Result, m_resultBGMVolume);
		}

		//2.0秒経過したらタイトルへ戻る。
		if (g_gameTime->StopWatch(2.0f))
		{
			//リザルト画面BGMを削除。
			DeleteGO(g_gameSoundEngine->GetSoundInstance(GameSoundList_BGM_Result));

			// SceneManagerを経由してゲームクリア画面への遷移を要求。
			Scene_Manager::GetInstance()->SetRequest(SceneID::S_Title);
		}
	}
}

//プレイヤーモデルのアニメーション再生。
void GameClear::PlayerModelPlayAnimation()
{
	//アニメーションステート。
	switch (m_animationState)
	{
	case enAnimationState_Idle:			//待機。
		m_playerModel.PlayAnimation(enAnimationClip_Idle);
		break;
	case enAnimationState_Defeat:		//悔しい。
		m_playerModel.PlayAnimation(enAnimationClip_Defeat);
		break;
	case enAnimationState_FistPump:		//ガッツ。
		m_playerModel.PlayAnimation(enAnimationClip_FistPump);
		break;
	case enAnimationState_Victory:		//嬉しい。
		m_playerModel.PlayAnimation(enAnimationClip_Victory);
		break;
	default:
		break;
	}
}

//ランク用の音の再生。
void GameClear::RankSEPlay()
{
	//ランク用の音の再生をしていないとき
	if (m_isRankSEPlaying != true)
	{
		//ランクステート
		switch (m_rankState)
		{
		case enRank_S: //Sランク
			//Sランク用の音の再生。
			g_gameSoundEngine->PlaySE(GameSoundList_SE_Result_SRank, 1.5f);
			break;
		case enRank_A: //Aランク
			//Aランク用の音の再生。
			g_gameSoundEngine->PlaySE(GameSoundList_SE_Result_ARank, 1.5f);
			break;
		case enRank_B: //Bランク
			//Bランク用の音の再生。
			g_gameSoundEngine->PlaySE(GameSoundList_SE_Result_BRank, 3.0f);
			break;
		case enRank_C: //Cランク
			//Cランク用の音の再生。
			g_gameSoundEngine->PlaySE(GameSoundList_SE_Result_CRank, 3.0f);
			break;
		default:
			break;
		}
		m_isRankSEPlaying = true;
	}
}

// アニメーションを再生する。
void GameClear::SetPlayAnimation()
{
	//各アニメーションの初期化。
	//0.待機アニメーション。
	GetFullPath_ResultAnimation(enAnimationClip_Idle, "playeridle", true);

	//1.悔しいアニメーション。
	GetFullPath_ResultAnimation(enAnimationClip_Defeat, "defeat", true);

	//2.ガッツアニメーション。
	GetFullPath_ResultAnimation(enAnimationClip_FistPump, "fistpump", true);

	//3.嬉しいアニメーション。
	GetFullPath_ResultAnimation(enAnimationClip_Victory, "victory", true);
}