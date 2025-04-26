#include "stdafx.h"
#include "GameClear.h"
#include "Title.h"
#include "Fade.h"

GameClear::~GameClear()
{
	DeleteGO(m_fade);
}

bool GameClear::Start()
{
	//カメラの初期化
	InitCamera();

	//スプライトの初期化
	InitSprite();

	//モデルの初期化
	InitModel();

	NewGO<Fade>(0, "fade");
	m_fade = FindGO<Fade>("fade");
	m_fade->FadeTransition(enFadeState_None);

	return true;
}

void GameClear::Update()
{
	//プレイヤー側の操作
	Action();

	//ゲームクリア演出が終わったか?
	if (m_gameClearDirectionFlag != true)
	{
		//スプライトの動作
		SpriteMove();
	}

	//プレイヤーモデルのアニメーション管理
	PlayerModelAnimationManage();

	//プレイヤーモデルのアニメーション再生
	PlayerModelPlayAnimation();

	m_playerModel.Update();
}

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

	//ゲームクリア演出が終わっているとき
	if (m_gameClearDirectionFlag == true)
	{
		//AボタンUI
		m_aButtonUI.Draw(rc);

		//タイトルへ戻るUI
		m_returnTitleUI.Draw(rc);
	}

	//100%
	if (m_hundredPlace[enNumberDraw_GatheringRate] >= 1.0f)
	{
		//収集率用数字UI(百の位)
		m_gatheringRateNumberHundredPlaceUI[m_hundredPlace[enNumberDraw_GatheringRate]].Draw(rc);
	}

	//10%～
	if (m_tenPlace[enNumberDraw_GatheringRate] >= 1.0f)
	{
		//収集率用数字UI(十の位)
		m_gatheringRateNumberTenPlaceUI[m_tenPlace[enNumberDraw_GatheringRate]].Draw(rc);
	}

	//0%～
	//収集率用数字UI(一の位)
	m_gatheringRateNumberOnePlaceUI[m_onePlace[enNumberDraw_GatheringRate]].Draw(rc);

	//100位
	if (m_hundredPlace[enNumberDraw_Ranking] >= 1.0f)
	{
		m_rankingNumberHundredPlaceUI[m_hundredPlace[enNumberDraw_Ranking]].Draw(rc);
	}

	//10位～
	if (m_tenPlace[enNumberDraw_Ranking] >= 1.0f)
	{
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
	g_camera3D->SetPosition({ 0.0f, 100.0f, -200.0f });
	g_camera3D->SetTarget({ 0.0f, 50.0f, 0.0f });
}

//スプライトの初期化
void GameClear::InitSprite()
{
	//リザルト画面
	m_result.Init("Assets/result/screen/result.dds", 1600, 900);

	//パーセントUI
	m_percentUI.Init("Assets/result/text/percent.dds", 1024, 128);
	m_percentUI.SetPosition(Vector3(675.0f, 275.0f, 0.0f));
	m_percentUI.Update();

	//位UI
	m_placeUI.Init("Assets/result/text/place.dds", 1024, 128);
	m_placeUI.SetPosition(Vector3(672.5f, 10.0f, 0.0f));
	m_placeUI.Update();

	//AボタンUI
	m_aButtonUI.Init("Assets/result/gamepad/abutton.dds", 512, 512);
	m_aButtonUI.SetPosition(Vector3(Vector3(475.0f, -400.0f, 0.0f)));
	m_aButtonUI.SetScale(Vector3(Vector3(0.1f, 0.1f, 0.1f)));
	m_aButtonUI.Update();

	//タイトルへ戻るUI
	m_returnTitleUI.Init("Assets/result/text/returntitle.dds", 1024, 128);
	m_returnTitleUI.SetPosition(Vector3(615.0f, -400.0f, 0.0f));
	m_returnTitleUI.SetScale(Vector3(0.3f,0.3f,0.3f));
	m_returnTitleUI.Update();

	//収集率の計算
	GatheringRate(m_gatheringItemNum, m_totalItemNum);

	//収集率用数字UI(百の位)
	GetNumberSpriteFilePaht(m_hundredPlace[enNumberDraw_GatheringRate]);
	m_gatheringRateNumberHundredPlaceUI[m_hundredPlace[enNumberDraw_GatheringRate]].Init(m_numberSpriteFilePath, 1024, 128);
	m_gatheringRateNumberHundredPlaceUI[m_hundredPlace[enNumberDraw_GatheringRate]].SetPosition(Vector3(400.0f, 283.5f, 0.0f));
	m_gatheringRateNumberHundredPlaceUI[m_hundredPlace[enNumberDraw_GatheringRate]].SetMulColor(Vector4(1.0f, 1.0f, 1.0f, 0.0f));
	m_gatheringRateNumberHundredPlaceUI[m_hundredPlace[enNumberDraw_GatheringRate]].Update();

	//収集率用数字UI(十の位)
	GetNumberSpriteFilePaht(m_tenPlace[enNumberDraw_GatheringRate]);
	m_gatheringRateNumberTenPlaceUI[m_tenPlace[enNumberDraw_GatheringRate]].Init(m_numberSpriteFilePath, 1024, 128);
	m_gatheringRateNumberTenPlaceUI[m_tenPlace[enNumberDraw_GatheringRate]].SetPosition(Vector3(480.0f, 283.5f, 0.0f));
	m_gatheringRateNumberTenPlaceUI[m_tenPlace[enNumberDraw_GatheringRate]].SetMulColor(Vector4(1.0f, 1.0f, 1.0f, 0.0f));
	m_gatheringRateNumberTenPlaceUI[m_tenPlace[enNumberDraw_GatheringRate]].Update();

	//収集率用数字UI(一の位)
	GetNumberSpriteFilePaht(m_onePlace[enNumberDraw_GatheringRate]);
	m_gatheringRateNumberOnePlaceUI[m_onePlace[enNumberDraw_GatheringRate]].Init(m_numberSpriteFilePath, 1024, 128);
	m_gatheringRateNumberOnePlaceUI[m_onePlace[enNumberDraw_GatheringRate]].SetPosition(Vector3(560.0f, 283.5f, 0.0f));
	m_gatheringRateNumberOnePlaceUI[m_onePlace[enNumberDraw_GatheringRate]].SetMulColor(Vector4(1.0f, 1.0f, 1.0f, 0.0f));
	m_gatheringRateNumberOnePlaceUI[m_onePlace[enNumberDraw_GatheringRate]].Update();

	//順位を設定する
	SetRanking();

	//順位用数字UI(十の位)
	GetNumberSpriteFilePaht(m_hundredPlace[enNumberDraw_Ranking]);
	m_rankingNumberHundredPlaceUI[m_hundredPlace[enNumberDraw_Ranking]].Init(m_numberSpriteFilePath, 1024, 128);
	m_rankingNumberHundredPlaceUI[m_hundredPlace[enNumberDraw_Ranking]].SetPosition(Vector3(400.0f, 7.5f, 0.0f));
	m_rankingNumberHundredPlaceUI[m_hundredPlace[enNumberDraw_Ranking]].SetMulColor(Vector4(1.0f,1.0f,1.0f,0.0f));
	m_rankingNumberHundredPlaceUI[m_hundredPlace[enNumberDraw_Ranking]].Update();

	//順位用数字UI(十の位)
	GetNumberSpriteFilePaht(m_tenPlace[enNumberDraw_Ranking]);
	m_rankingNumberTenPlaceUI[m_tenPlace[enNumberDraw_Ranking]].Init(m_numberSpriteFilePath, 1024, 128);
	m_rankingNumberTenPlaceUI[m_tenPlace[enNumberDraw_Ranking]].SetPosition(Vector3(480.0f, 7.5f, 0.0f));
	m_rankingNumberTenPlaceUI[m_tenPlace[enNumberDraw_Ranking]].SetMulColor(Vector4(1.0f, 1.0f, 1.0f, 0.0f));
	m_rankingNumberTenPlaceUI[m_tenPlace[enNumberDraw_Ranking]].Update();

	//順位用数字UI(一の位)
	GetNumberSpriteFilePaht(m_onePlace[enNumberDraw_Ranking]);
	m_rankingNumberOnePlaceUI[m_onePlace[enNumberDraw_Ranking]].Init(m_numberSpriteFilePath, 1024, 128);
	m_rankingNumberOnePlaceUI[m_onePlace[enNumberDraw_Ranking]].SetPosition(Vector3(560.0f, 7.5f, 0.0f));
	m_rankingNumberOnePlaceUI[m_onePlace[enNumberDraw_Ranking]].SetMulColor(Vector4(1.0f, 1.0f, 1.0f, 0.0f));
	m_rankingNumberOnePlaceUI[m_onePlace[enNumberDraw_Ranking]].Update();

	//ランクを設定する
	SetRank();

	//ランクUI
	m_rankUI[m_rankState].Init(m_rankSpriteFilePath, 1024, 128);
	m_rankUI[m_rankState].SetPosition(Vector3(480.0f, -275.5f, 0.0f));
	m_rankUI[m_rankState].SetMulColor(m_rankSpriteColor);
	m_rankUI[m_rankState].Update();

	//ゲーム背景
	m_gameBackground.Init("Assets/Sprite/yellow.dds");
	m_gameBackground.Update();
}

//モデルの初期化
void GameClear::InitModel()
{
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

	//プレイヤーモデル
	m_playerModel.Init("Assets/modelData/player/player.tkm", m_animationClip, enAnimationClip_Num, enModelUpAxisZ);

	//位置の設定
	m_playerModel.SetPosition(m_playerModelPosition);

	//回転の設定
	m_playerModelRotation.SetRotationDegY(180.0f);
	m_playerModel.SetRotation(m_playerModelRotation);

	//大きさの設定
	m_playerModel.SetScale(m_playerModelScale);

	m_playerModel.Update();
}

//収集率の計算
void GameClear::GatheringRate(int gatheringItemNum, int totalItemNum)
{
	//収集率
	m_gatheringRate = (double(gatheringItemNum) / double(totalItemNum)) * 100.0f;

	//UIを表示するための計算
	//百の位
	m_hundredPlace[enNumberDraw_GatheringRate] = m_gatheringRate / 100;

	//十の位
	m_tenPlace[enNumberDraw_GatheringRate] = m_gatheringRate / 10;
	if (m_tenPlace[enNumberDraw_GatheringRate] >= 10.0f)
	{
		m_tenPlace[enNumberDraw_GatheringRate] = enNumver_TenOver;
	}

	//一の位
	m_onePlace[enNumberDraw_GatheringRate] = m_gatheringRate % 10;
}

//プレイヤーモデルのアニメーション管理
void GameClear::PlayerModelAnimationManage()
{
	//ゲームクリア演出が終わったら
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
	//ゲームクリア演出が終わっていなかったら
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
		m_gatheringRateUIAlphaColor += g_gameTime->GetFrameDeltaTime();

		//収集率UIが不透明になったら
		if (m_gatheringRateUIAlphaColor > 1.0f)
		{
			m_gatheringRateUIAlphaColor = 1.0f;
			m_gameClearDirectionState = enGameClearDirection_Ranking;
		}

		//収集率用数字UI
		m_gatheringRateNumberHundredPlaceUI[m_hundredPlace[enNumberDraw_GatheringRate]].SetMulColor(Vector4(1.0f, 1.0f, 1.0f, m_gatheringRateUIAlphaColor));
		m_gatheringRateNumberTenPlaceUI[m_tenPlace[enNumberDraw_GatheringRate]].SetMulColor(Vector4(1.0f, 1.0f, 1.0f, m_gatheringRateUIAlphaColor));
		m_gatheringRateNumberOnePlaceUI[m_onePlace[enNumberDraw_GatheringRate]].SetMulColor(Vector4(1.0f, 1.0f, 1.0f, m_gatheringRateUIAlphaColor));
		break;
	case enGameClearDirection_Ranking:			//順位
		m_rankingUIAlphaColor += g_gameTime->GetFrameDeltaTime();

		//順位用UIが不透明になったら
		if (m_rankingUIAlphaColor > 1.0f)
		{
			m_rankingUIAlphaColor = 1.0f;
			m_gameClearDirectionState = enGameClearDirection_Rank;
			return;
		}

		//順位用数字UI
		m_rankingNumberHundredPlaceUI[m_hundredPlace[enNumberDraw_Ranking]].SetMulColor(Vector4(1.0f, 1.0f, 1.0f, m_rankingUIAlphaColor));
		m_rankingNumberTenPlaceUI[m_tenPlace[enNumberDraw_Ranking]].SetMulColor(Vector4(1.0f, 1.0f, 1.0f, m_rankingUIAlphaColor));
		m_rankingNumberOnePlaceUI[m_onePlace[enNumberDraw_Ranking]].SetMulColor(Vector4(1.0f, 1.0f, 1.0f, m_rankingUIAlphaColor));
		break;
	case enGameClearDirection_Rank:				//ランク
		m_rankUIAlphaColor += g_gameTime->GetFrameDeltaTime();

		//ランク用UIが不透明になったら
		if (m_rankUIAlphaColor > 1.0f)
		{
			m_rankUIAlphaColor = 1.0f;
			m_gameClearDirectionFlag = true;
			return;
		}

		//ランクUI
		m_rankUI[m_rankState].SetMulColor(Vector4(m_rankSpriteColor.x, m_rankSpriteColor.y, m_rankSpriteColor.z, m_rankUIAlphaColor));
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
			//収集率UI
			m_gatheringRateNumberHundredPlaceUI[m_hundredPlace[enNumberDraw_GatheringRate]].SetMulColor(Vector4(1.0f, 1.0f, 1.0f, 1.0f));
			m_gatheringRateNumberTenPlaceUI[m_tenPlace[enNumberDraw_GatheringRate]].SetMulColor(Vector4(1.0f, 1.0f, 1.0f, 1.0f));
			m_gatheringRateNumberOnePlaceUI[m_onePlace[enNumberDraw_GatheringRate]].SetMulColor(Vector4(1.0f, 1.0f, 1.0f, 1.0f));

			//順位UI
			m_rankingNumberHundredPlaceUI[m_hundredPlace[enNumberDraw_Ranking]].SetMulColor(Vector4(1.0f, 1.0f, 1.0f, 1.0f));
			m_rankingNumberTenPlaceUI[m_tenPlace[enNumberDraw_Ranking]].SetMulColor(Vector4(1.0f, 1.0f, 1.0f, 1.0f));
			m_rankingNumberOnePlaceUI[m_onePlace[enNumberDraw_Ranking]].SetMulColor(Vector4(1.0f, 1.0f, 1.0f, 1.0f));

			//ランクUI
			m_rankUI[m_rankState].SetMulColor(Vector4(m_rankSpriteColor.x, m_rankSpriteColor.y, m_rankSpriteColor.z, 1.0f));

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
			m_fade->FadeTransition(enFadeState_FadeOut);
		}
	}
	else
	{
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