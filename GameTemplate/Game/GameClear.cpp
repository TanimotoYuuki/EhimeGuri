#include "stdafx.h"
#include "GameClear.h"
#include "Title.h"
#include "Fade.h"

//デストラクタ
GameClear::~GameClear()
{
	DeleteGO(m_fade);
}

//開始処理
bool GameClear::Start()
{
	//カメラの初期化
	InitCamera();

	//スプライトの初期化
	InitSprite();

	//モデルの初期化
	InitModel();

	//ライトカメラの注視点の設定
	g_renderingEngine->SetLightCameraTarget(m_playerModelPosition);

	//インスタンス
	//0 フェード
	NewGO<Fade>(0, "fade");
	m_fade = FindGO<Fade>("fade");
	//フェードを描画しないようにする
	m_fade->FadeTransition(enFadeState_None);

	return true;
}

//更新処理
void GameClear::Update()
{
	//プレイヤー側の操作
	Action();

	//ゲームクリア演出がいないとき
	if (m_gameClearDirectionFlag != true)
	{
		//スプライトの動作
		SpriteMove();
	}

	//プレイヤーモデルのアニメーション管理
	PlayerModelAnimationManage();

	//プレイヤーモデルのアニメーション再生
	PlayerModelPlayAnimation();

	//モデルの更新
	m_playerModel.Update();

	//ライトカメラの更新
	g_renderingEngine->SetLightCameraTarget(m_playerModelPosition);
}

//描画処理
void GameClear::Render(RenderContext& rc)
{
	//ゲーム背景
	m_gameBackground.Draw(rc);

	//リザルト画面
	m_result.Draw(rc);

	//パーセントUI
	m_percentUI.Draw(rc);

	//位UI
	m_placeUI.Draw(rc);

	//ランクUI
	m_rankUI[m_rankState].Draw(rc);

	//ゲームクリア演出が終わったら描画する
	if (m_gameClearDirectionFlag == true)
	{
		//AボタンUI
		m_aButtonUI.Draw(rc);

		//タイトルへ戻るUI
		m_returnTitleUI.Draw(rc);
	}

	//収集率が100%のとき描画する
	if (m_hundredPlace[enNumberDraw_GatheringRate] >= 1.0f)
	{
		//100%～
		//収集率用数字UI(百の位)
		m_gatheringRateNumberHundredPlaceUI[m_hundredPlace[enNumberDraw_GatheringRate]].Draw(rc);
	}

	//収集率が10%以上のとき描画する
	if (m_tenPlace[enNumberDraw_GatheringRate] >= 1.0f)
	{
		//10%～
		//収集率用数字UI(十の位)
		m_gatheringRateNumberTenPlaceUI[m_tenPlace[enNumberDraw_GatheringRate]].Draw(rc);
	}

	//0%～
	//収集率用数字UI(一の位)
	m_gatheringRateNumberOnePlaceUI[m_onePlace[enNumberDraw_GatheringRate]].Draw(rc);

	//100位以上のとき描画する
	if (m_hundredPlace[enNumberDraw_Ranking] >= 1.0f)
	{
		//100位～
		//順位用数字UI(百の位)
		m_rankingNumberHundredPlaceUI[m_hundredPlace[enNumberDraw_Ranking]].Draw(rc);
	}

	//10位以上のとき描画する
	if (m_tenPlace[enNumberDraw_Ranking] >= 1.0f)
	{
		//10位～
		//順位用数字UI(十の位)
		m_rankingNumberTenPlaceUI[m_tenPlace[enNumberDraw_Ranking]].Draw(rc);
	}

	//1位～
	//順位用数字UI(一の位)
	m_rankingNumberOnePlaceUI[m_onePlace[enNumberDraw_Ranking]].Draw(rc);

	//プレイヤーモデル
	m_playerModel.Draw(rc);
}

//カメラの初期化
void GameClear::InitCamera()
{
	//カメラの位置と注視点の初期設定
	g_camera3D->SetPosition({ 0.0f, 100.0f, -200.0f });
	g_camera3D->SetTarget({ 0.0f, 50.0f, 0.0f });
}

//スプライトの初期化
void GameClear::InitSprite()
{
	//各スプライトの初期設定
	//リザルト画面
	//0 リザルト画面の初期化
	m_result.Init("Assets/result/screen/result.dds", 1600, 900);

	//パーセントUI
	//1 パーセントUIの初期化
	m_percentUI.Init("Assets/result/text/percent.dds", 1024, 128);
	//1.1 パーセントUIの座標の設定
	m_percentUI.SetPosition(Vector3(675.0f, 275.0f, 0.0f));
	//1.2 パーセントUIの更新
	m_percentUI.Update();

	//位UI
	//2 位UIの初期化
	m_placeUI.Init("Assets/result/text/place.dds", 1024, 128);
	//2.1 位UIの座標の設定
	m_placeUI.SetPosition(Vector3(672.5f, 10.0f, 0.0f));
	//2.2 位UIの更新
	m_placeUI.Update();

	//AボタンUI
	//3 AボタンUIの初期化
	m_aButtonUI.Init("Assets/result/gamepad/abutton.dds", 512, 512);
	//3.1 AボタンUIの座標の設定
	m_aButtonUI.SetPosition(Vector3(Vector3(475.0f, -400.0f, 0.0f)));
	//3.2 AボタンUIの大きさの設定
	m_aButtonUI.SetScale(Vector3(Vector3(0.1f, 0.1f, 0.1f)));
	//3.3 Aボタンの更新
	m_aButtonUI.Update();

	//タイトルへ戻るUI
	//4 タイトルへ戻るUIの初期化
	m_returnTitleUI.Init("Assets/result/text/returntitle.dds", 1024, 128);
	//4.1 タイトルへ戻るUIの座標の設定
	m_returnTitleUI.SetPosition(Vector3(615.0f, -400.0f, 0.0f));
	//4.2 タイトルへ戻るUIの大きさの設定
	m_returnTitleUI.SetScale(Vector3(0.3f,0.3f,0.3f));
	//4.3 タイトルへ戻るUIの更新
	m_returnTitleUI.Update();

	//収集率の計算
	GatheringRate(m_gatheringItemNum, m_totalItemNum);

	//収集率用数字UI(百の位)
	//5 収集率用数字UI(百の位)用のファイルパスを取得
	GetNumberUISpriteFilePath(m_hundredPlace[enNumberDraw_GatheringRate]);
	//5.1 収集率用数字UI(百の位)の初期化
	m_gatheringRateNumberHundredPlaceUI[m_hundredPlace[enNumberDraw_GatheringRate]].Init(m_numberUISpriteFilePath, 1024, 128);
	//5.2 収集率用数字UI(百の位)の座標の設定
	m_gatheringRateNumberHundredPlaceUI[m_hundredPlace[enNumberDraw_GatheringRate]].SetPosition(Vector3(400.0f, 283.5f, 0.0f));
	//5.3 収集率用数字UI(百の位)の乗算カラーの設定
	m_gatheringRateNumberHundredPlaceUI[m_hundredPlace[enNumberDraw_GatheringRate]].SetMulColor(Vector4(1.0f, 1.0f, 1.0f, 0.0f));
	//5.4 収集率用数字UI(百の位)の更新
	m_gatheringRateNumberHundredPlaceUI[m_hundredPlace[enNumberDraw_GatheringRate]].Update();

	//収集率用数字UI(十の位)
	//6 収集率用数字UI(十の位)用のファイルパスを取得
	GetNumberUISpriteFilePath(m_tenPlace[enNumberDraw_GatheringRate]);
	//6.1 収集率用数字UI(十の位)の初期化
	m_gatheringRateNumberTenPlaceUI[m_tenPlace[enNumberDraw_GatheringRate]].Init(m_numberUISpriteFilePath, 1024, 128);
	//6.2 収集率用数字UI(十の位)の座標の設定
	m_gatheringRateNumberTenPlaceUI[m_tenPlace[enNumberDraw_GatheringRate]].SetPosition(Vector3(480.0f, 283.5f, 0.0f));
	//6.3 収集率用数字UI(十の位)の乗算カラーの設定
	m_gatheringRateNumberTenPlaceUI[m_tenPlace[enNumberDraw_GatheringRate]].SetMulColor(Vector4(1.0f, 1.0f, 1.0f, 0.0f));
	//6.4 収集率用数字UI(十の位)の更新
	m_gatheringRateNumberTenPlaceUI[m_tenPlace[enNumberDraw_GatheringRate]].Update();

	//収集率用数字UI(一の位)
	//7 収集率用数字UI(一の位)用のファイルパスを取得
	GetNumberUISpriteFilePath(m_onePlace[enNumberDraw_GatheringRate]);
	//7.1 収集率用数字UI(一の位)の初期化
	m_gatheringRateNumberOnePlaceUI[m_onePlace[enNumberDraw_GatheringRate]].Init(m_numberUISpriteFilePath, 1024, 128);
	//7.2 収集率用数字UI(一の位)の座標の設定
	m_gatheringRateNumberOnePlaceUI[m_onePlace[enNumberDraw_GatheringRate]].SetPosition(Vector3(560.0f, 283.5f, 0.0f));
	//7.3 収集率用数字UI(一の位)の乗算カラーの設定
	m_gatheringRateNumberOnePlaceUI[m_onePlace[enNumberDraw_GatheringRate]].SetMulColor(Vector4(1.0f, 1.0f, 1.0f, 0.0f));
	//7.4 収集率用数字UI(一の位)の更新
	m_gatheringRateNumberOnePlaceUI[m_onePlace[enNumberDraw_GatheringRate]].Update();

	//順位を設定する
	SetRanking();

	//順位用数字UI(百の位)
	//8 順位用数字UI(百の位)用のファイルパスを取得
	GetNumberUISpriteFilePath(m_hundredPlace[enNumberDraw_Ranking]);
	//8.1 順位用数字UI(百の位)の初期化
	m_rankingNumberHundredPlaceUI[m_hundredPlace[enNumberDraw_Ranking]].Init(m_numberUISpriteFilePath, 1024, 128);
	//8.2 順位用数字UI(百の位)の座標の設定
	m_rankingNumberHundredPlaceUI[m_hundredPlace[enNumberDraw_Ranking]].SetPosition(Vector3(400.0f, 7.5f, 0.0f));
	//8.3 順位用数字UI(百の位)の乗算カラーの設定
	m_rankingNumberHundredPlaceUI[m_hundredPlace[enNumberDraw_Ranking]].SetMulColor(Vector4(1.0f,1.0f,1.0f,0.0f));
	//8.4 順位用数字UI(百の位)の更新
	m_rankingNumberHundredPlaceUI[m_hundredPlace[enNumberDraw_Ranking]].Update();

	//順位用数字UI(十の位)
	//9 順位用数字UI(十の位)用のファイルパスを取得
	GetNumberUISpriteFilePath(m_tenPlace[enNumberDraw_Ranking]);
	//9.1 順位用数字UI(十の位)の初期化
	m_rankingNumberTenPlaceUI[m_tenPlace[enNumberDraw_Ranking]].Init(m_numberUISpriteFilePath, 1024, 128);
	//9.2 順位用数字UI(十の位)の座標の設定
	m_rankingNumberTenPlaceUI[m_tenPlace[enNumberDraw_Ranking]].SetPosition(Vector3(480.0f, 7.5f, 0.0f));
	//9.3 順位用数字UI(十の位)の乗算カラーの設定
	m_rankingNumberTenPlaceUI[m_tenPlace[enNumberDraw_Ranking]].SetMulColor(Vector4(1.0f, 1.0f, 1.0f, 0.0f));
	//9.4 順位用数字UI(十の位)の更新
	m_rankingNumberTenPlaceUI[m_tenPlace[enNumberDraw_Ranking]].Update();

	//順位用数字UI(一の位)
	//10 順位用数字UI(一の位)用のファイルパスを取得
	GetNumberUISpriteFilePath(m_onePlace[enNumberDraw_Ranking]);
	//10.1 順位用数字UI(一の位)の初期化
	m_rankingNumberOnePlaceUI[m_onePlace[enNumberDraw_Ranking]].Init(m_numberUISpriteFilePath, 1024, 128);
	//10.2 順位用数字UI(一の位)の座標の設定
	m_rankingNumberOnePlaceUI[m_onePlace[enNumberDraw_Ranking]].SetPosition(Vector3(560.0f, 7.5f, 0.0f));
	//10.3 順位用数字UI(一の位)の乗算カラーの設定
	m_rankingNumberOnePlaceUI[m_onePlace[enNumberDraw_Ranking]].SetMulColor(Vector4(1.0f, 1.0f, 1.0f, 0.0f));
	//10.4 順位用数字UI(一の位)の更新
	m_rankingNumberOnePlaceUI[m_onePlace[enNumberDraw_Ranking]].Update();

	//ランクを設定する
	SetRank();

	//ランクUI
	//11 ランクUIの初期化
	m_rankUI[m_rankState].Init(m_rankUISpriteFilePath, 1024, 128);
	//11.1 ランクUIの座標の設定
	m_rankUI[m_rankState].SetPosition(Vector3(480.0f, -275.5f, 0.0f));
	//11.2 ランクUIの乗算カラーの設定
	m_rankUI[m_rankState].SetMulColor(m_rankUISpriteColor);
	//11.3 ランクUIの更新
	m_rankUI[m_rankState].Update();

	//ゲーム背景
	//12 ゲーム背景の初期化
	m_gameBackground.Init("Assets/Sprite/yellow.dds", 1600, 900);
	//12.1 ゲーム背景の更新
	m_gameBackground.Update();
}

//モデルの初期化
void GameClear::InitModel()
{
	//各アニメーションの初期化
	//0.待機アニメーション
	m_animationClip[enAnimationClip_Idle].Load("Assets/animData/playeridle.tka");
	m_animationClip[enAnimationClip_Idle].SetLoopFlag(true);
	//1.悔しいアニメーション
	m_animationClip[enAnimationClip_Defeat].Load("Assets/animData/defeat.tka");
	m_animationClip[enAnimationClip_Defeat].SetLoopFlag(true);
	//2.ガッツアニメーション
	m_animationClip[enAnimationClip_FistPump].Load("Assets/animData/fistpump.tka");
	m_animationClip[enAnimationClip_FistPump].SetLoopFlag(true);
	//3.嬉しいアニメーション
	m_animationClip[enAnimationClip_Victory].Load("Assets/animData/victory.tka");
	m_animationClip[enAnimationClip_Victory].SetLoopFlag(true);

	//モデルの初期化
	//0 プレイヤーモデルの初期化
	m_playerModel.Init("Assets/modelData/player/player.tkm", m_animationClip, enAnimationClip_Num, enModelUpAxisZ);

	//0.1 位置の設定
	m_playerModel.SetPosition(m_playerModelPosition);

	//0.2 回転の設定
	m_playerModelRotation.SetRotationDegY(180.0f);
	m_playerModel.SetRotation(m_playerModelRotation);

	//0.3 大きさの設定
	m_playerModel.SetScale(m_playerModelScale);

	//0.4 モデルの更新処理
	m_playerModel.Update();
}

//収集率の計算
void GameClear::GatheringRate(int gatheringItemNum, int totalItemNum)
{
	//収集率を求める
	m_gatheringRate = (double(gatheringItemNum) / double(totalItemNum)) * 100.0f;

	//UIを表示するための計算
	//百の位
	m_hundredPlace[enNumberDraw_GatheringRate] = m_gatheringRate / 100;

	//十の位
	m_tenPlace[enNumberDraw_GatheringRate] = m_gatheringRate / 10;

	//十の位を求める計算の結果が10.0f以上のとき
	if (m_tenPlace[enNumberDraw_GatheringRate] >= 10.0f)
	{
		//十の位が0を表示できるようにする
		m_tenPlace[enNumberDraw_GatheringRate] = enNumver_TenOver;
	}

	//一の位
	m_onePlace[enNumberDraw_GatheringRate] = m_gatheringRate % 10;
}

//プレイヤーモデルのアニメーション管理
void GameClear::PlayerModelAnimationManage()
{
	//ゲームクリア演出が終わったらランクごとのアニメーションを再生する
	if (m_gameClearDirectionFlag == true)
	{
		//収集率が80%以上なら(S～Aランク)
		if (m_gatheringRate >= 80)
		{
			m_animationState = enAnimationState_Victory;	//嬉しい
		}
		//収集率が40%以上なら(B～Cランク)
		else if (m_gatheringRate >= 40)
		{
			m_animationState = enAnimationState_FistPump;	//ガッツ
		}
		//収集率が40%未満なら(D～Eランク)
		else
		{
			m_animationState = enAnimationState_Defeat;		//悔しい
		}
	}
	//ゲームクリア演出が終わっていなかったら待機アニメーションを再生する
	else
	{
		m_animationState = enAnimationClip_Idle;	//待機
	}
}

//スプライトの動作
void GameClear::SpriteMove()
{
	//ゲームクリア演出ステート
	switch (m_gameClearDirectionState)
	{
	case enGameClearDirection_GatheringRate:	//収集率
		//時間が経過したら不透明にする
		m_gatheringRateUIAlphaColor += g_gameTime->GetFrameDeltaTime();

		//収集率UIが不透明になったら順位用の演出に移る
		if (m_gatheringRateUIAlphaColor > 1.0f)
		{
			m_gatheringRateUIAlphaColor = 1.0f;
			//順位用の演出に移る
			m_gameClearDirectionState = enGameClearDirection_Ranking;
		}

		//収集率用数字UIの乗算カラーの更新
		m_gatheringRateNumberHundredPlaceUI[m_hundredPlace[enNumberDraw_GatheringRate]].SetMulColor(Vector4(1.0f, 1.0f, 1.0f, m_gatheringRateUIAlphaColor));
		m_gatheringRateNumberTenPlaceUI[m_tenPlace[enNumberDraw_GatheringRate]].SetMulColor(Vector4(1.0f, 1.0f, 1.0f, m_gatheringRateUIAlphaColor));
		m_gatheringRateNumberOnePlaceUI[m_onePlace[enNumberDraw_GatheringRate]].SetMulColor(Vector4(1.0f, 1.0f, 1.0f, m_gatheringRateUIAlphaColor));
		break;
	case enGameClearDirection_Ranking:			//順位
		//時間が経過したら不透明にする
		m_rankingUIAlphaColor += g_gameTime->GetFrameDeltaTime();

		//順位用UIが不透明になったらランク用の演出に移る
		if (m_rankingUIAlphaColor > 1.0f)
		{
			m_rankingUIAlphaColor = 1.0f;
			//ランク用の演出に移る
			m_gameClearDirectionState = enGameClearDirection_Rank;
			return;
		}

		//順位用数字UIの乗算カラーの更新
		m_rankingNumberHundredPlaceUI[m_hundredPlace[enNumberDraw_Ranking]].SetMulColor(Vector4(1.0f, 1.0f, 1.0f, m_rankingUIAlphaColor));
		m_rankingNumberTenPlaceUI[m_tenPlace[enNumberDraw_Ranking]].SetMulColor(Vector4(1.0f, 1.0f, 1.0f, m_rankingUIAlphaColor));
		m_rankingNumberOnePlaceUI[m_onePlace[enNumberDraw_Ranking]].SetMulColor(Vector4(1.0f, 1.0f, 1.0f, m_rankingUIAlphaColor));
		break;
	case enGameClearDirection_Rank:				//ランク
		//時間が経過したら不透明にする
		m_rankUIAlphaColor += g_gameTime->GetFrameDeltaTime();

		//ランク用UIが不透明になったらゲームクリア演出を終了する
		if (m_rankUIAlphaColor > 1.0f)
		{
			m_rankUIAlphaColor = 1.0f;
			//ゲームクリア演出を終了する
			m_gameClearDirectionFlag = true;
			return;
		}

		//ランクUIの乗算カラーの更新
		m_rankUI[m_rankState].SetMulColor(Vector4(m_rankUISpriteColor.x, m_rankUISpriteColor.y, m_rankUISpriteColor.z, m_rankUIAlphaColor));
		break;
	default:
		break;
	}
}

//プレイヤー側の操作
void GameClear::Action()
{
	//ゲームクリア演出が終わっていないとき
	if (m_gameClearDirectionFlag != true)
	{
		//Aボタンを押したら演出をスキップできる
		if (g_pad[0]->IsTrigger(enButtonA))
		{
			//各スプライトの透明度を不透明にする
			//収集率UI
			m_gatheringRateNumberHundredPlaceUI[m_hundredPlace[enNumberDraw_GatheringRate]].SetMulColor(Vector4(1.0f, 1.0f, 1.0f, 1.0f));
			m_gatheringRateNumberTenPlaceUI[m_tenPlace[enNumberDraw_GatheringRate]].SetMulColor(Vector4(1.0f, 1.0f, 1.0f, 1.0f));
			m_gatheringRateNumberOnePlaceUI[m_onePlace[enNumberDraw_GatheringRate]].SetMulColor(Vector4(1.0f, 1.0f, 1.0f, 1.0f));

			//順位UI
			m_rankingNumberHundredPlaceUI[m_hundredPlace[enNumberDraw_Ranking]].SetMulColor(Vector4(1.0f, 1.0f, 1.0f, 1.0f));
			m_rankingNumberTenPlaceUI[m_tenPlace[enNumberDraw_Ranking]].SetMulColor(Vector4(1.0f, 1.0f, 1.0f, 1.0f));
			m_rankingNumberOnePlaceUI[m_onePlace[enNumberDraw_Ranking]].SetMulColor(Vector4(1.0f, 1.0f, 1.0f, 1.0f));

			//ランクUI
			m_rankUI[m_rankState].SetMulColor(Vector4(m_rankUISpriteColor.x, m_rankUISpriteColor.y, m_rankUISpriteColor.z, 1.0f));

			//ゲームクリア演出を終了する
			m_gameClearDirectionFlag = true;
		}
		return;
	}

	//タイトル画面遷移フラグが立っていないとき
	if (m_titleScreenTransitionFlag != true)
	{
		//Aボタンを押したらタイトルへ戻る
		if (g_pad[0]->IsTrigger(enButtonA))
		{
			m_titleScreenTransitionFlag = true;
			//フェードをフェードアウトに切り替える
			m_fade->FadeTransition(enFadeState_FadeOut);
		}
	}
	else
	{
		//2.0秒経過したらタイトルへ戻る
		if (g_gameTime->StopWatch(2.0f))
		{
			NewGO<Title>(0,"title");
			DeleteGO(this);
		}
	}
}

//プレイヤーモデルのアニメーション再生
void GameClear::PlayerModelPlayAnimation()
{
	//アニメーションステート
	switch (m_animationState)
	{
	case enAnimationState_Idle:			//待機
		m_playerModel.PlayAnimation(enAnimationClip_Idle);
		break;
	case enAnimationState_Defeat:		//悔しい
		m_playerModel.PlayAnimation(enAnimationClip_Defeat);
		break;
	case enAnimationState_FistPump:		//ガッツ
		m_playerModel.PlayAnimation(enAnimationClip_FistPump);
		break;
	case enAnimationState_Victory:		//嬉しい
		m_playerModel.PlayAnimation(enAnimationClip_Victory);
		break;
	default:
		break;
	}
}