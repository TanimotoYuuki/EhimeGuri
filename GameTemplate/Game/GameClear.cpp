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

	// リザルト用の定数。
	const float RESULT_WIDHT = 1600;
	const float RESULT_HEIGHT = 900;

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
}

// リザルト用。
std::string GameClear::GetFullPath_RESULT(const std::string& name, const float w, const float h)  
{  
    string GameClear = RESULT + name + dds_EXTENSION;  

    m_result.Init(GameClear.c_str(), w, h);  
    return GameClear;  
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

//開始処理。
bool GameClear::Start()
{
	//スプライトの初期化。
	InitSprite();

	//インスタンス。
	//0 フェード。
	m_fade = FindGO<Fade>("fade");
	m_fade->FadeTransition(enFadeState_FadeIn);

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
	//リザルト画面。
	m_result.Draw(rc);

	//ゲーム結果UI。
	m_gameResultUI.Draw(rc);

	//アイテム取得リストUI。
	m_itemGetListUI.Draw(rc);

	//アイテム取得リストのテキストUI。
	m_itemGetListTextUI.Draw(rc);

	//ゲームクリア演出が終わったら描画する。
	if (m_gameClearDirectionFlag == true)
	{
		//アイテム選択UI。
		m_itemSelectUI[m_itemSelect].Draw(rc);

		//アイテムコレクションUI。
		m_itemCollectionUI[m_itemSelect].Draw(rc);

		//LスティックUI。
		m_lStickUI.Draw(rc);

		//十字キーUI。
		m_dPadUI.Draw(rc);

		//AボタンUI。
		m_aButtonUI.Draw(rc);

		//選択UI。
		m_selectUI.Draw(rc);

		//タイトルへ戻るUI。
		m_returnTitleUI.Draw(rc);
	}

	//アイテム関連UI。
	for (int i = 0; i < enItem_Num; i++)
	{
		//アイテムを取得していないときのUI。
		m_noItemGetUI[i].Draw(rc);

		//アイテムを取得していたら描画する。
		if (m_itemGetFlag[i] == true)
		{
			//アイテムを取得しているときのUI。
			m_itemGetUI[i].Draw(rc);
		}
	}
}

//スプライトの初期化。
void GameClear::InitSprite()
{
	//各スプライトの初期設定。
	//リザルト画面。
	//0 リザルト画面の初期化。
	GetFullPath_RESULT("resultbackground", RESULT_WIDHT, RESULT_HEIGHT);

	//ゲーム結果UI。
	//1 ゲーム結果UIの初期化。
	m_gameResultUI.Init("Assets/result/text/gameresult.dds", 1024, 128);
	//1.1 ゲーム結果UIの座標の設定。
	m_gameResultUI.SetPosition(Vector3(0.0f, 380.0f, 0.0f));
	//1.2 ゲーム結果UIの大きさの設定。
	m_gameResultUI.SetScale(Vector3(0.8f, 0.8f, 0.8f));
	//1.3 ゲーム結果UIの更新。
	m_gameResultUI.Update();

	//アイテム取得リストUI。
	//2 アイテム取得リストUIの初期化。
	m_itemGetListUI.Init("Assets/result/item/itemgetlist.dds", 800, 900);
	//2.1 アイテム取得リストUIの座標の設定。
	m_itemGetListUI.SetPosition(Vector3(0.0f,0.0f,0.0f));
	//2.2 アイテム取得リストUIの大きさの設定。
	m_itemGetListUI.SetScale(Vector3(0.7f, 0.45f, 0.5f));
	//2.3 アイテム取得リストUIの更新。
	m_itemGetListUI.Update();

	//アイテム取得リストテキストUI。
	//2 アイテム取得リストテキストUIの初期化。
	m_itemGetListTextUI.Init("Assets/result/text/itemgetlist.dds", 1024, 128);
	//2.1 アイテム取得リストテキストUIの座標の設定。
	m_itemGetListTextUI.SetPosition(Vector3(0.0f, 150.0f, 0.0f));
	//2.2 アイテム取得リストテキストUIの大きさの設定。
	m_itemGetListTextUI.SetScale(Vector3(0.5f, 0.5f, 0.5f));
	//2.3 アイテム取得リストテキストUIの更新。
	m_itemGetListTextUI.Update();

	//アイテムUI
	for (int i = 0; i < enItem_Num; i++)
	{
		//アイテムUI関連のスプライトの情報を取得。
		GetItemUISpriteData(i);
		
		//アイテムを取得していないときのUI。
		//3  アイテムを取得していないときのUIの初期化。
		m_noItemGetUI[i].Init(m_noItemGetUISpriteFilePath, 100, 100);
		//3.1 アイテムを取得していないときのUIの座標の設定。
		m_noItemGetUI[i].SetPosition(m_itemUIPosition);
		//3.2 アイテムを取得していないときのUIの大きさの設定。
		m_noItemGetUI[i].SetScale(m_noItemGetUIScale);
		//3.3 アイテムを取得していないときのUIの更新。
		m_noItemGetUI[i].Update();

		//アイテムを取得しているときのUI。
		//4 アイテムを取得しているときのUIの初期化
		m_itemGetUI[i].Init(m_itemGetUISpriteFilePath, 100, 100);
		//4.1 アイテムを取得しているときのUIの座標の設定。
		m_itemGetUI[i].SetPosition(m_itemUIPosition);
		//4.2 アイテムを取得しているときのUIの大きさの設定。
		m_itemGetUI[i].SetScale(m_itemGetUIScale);
		//4.3 アイテムを取得しているときのUIの乗算カラーの設定。
		m_itemGetUI[i].SetMulColor(Vector4(1.0f, 1.0f, 1.0f, 0.0f));
		//4.4 アイテムを取得しているときのUIの更新。
		m_itemGetUI[i].Update();

		//アイテムを選択しているときのUI。
		//5 アイテムを選択しているときのUIの初期化。
		m_itemSelectUI[i].Init(m_itemSelectUISpriteFilePath, 100, 100);
		//5.1 アイテムを選択しているときのUIの座標の設定。
		m_itemSelectUI[i].SetPosition(m_itemUIPosition);
		//5.2 アイテムを選択しているときのUIの大きさの設定。
		m_itemSelectUI[i].SetScale(m_itemSelectUIScale);
		//5.3 アイテムを選択しているときのUIの更新。
		m_itemSelectUI[i].Update();

		//アイテムコレクションUI
		//6 アイテムコレクションUIの初期化。
		m_itemCollectionUI[i].Init(m_itemCollectionUISpriteFilePath, 800, 900);
		//6.1 アイテムコレクションUIの座標の設定。
		m_itemCollectionUI[i].SetPosition(Vector3(-350.0f, 0.0f, 0.0f));
		//6.2 アイテムコレクションUIの大きさの設定。
		m_itemCollectionUI[i].SetScale(Vector3(0.7f, 0.7f, 0.7f));
		//6.3 アイテムコレクションUIの更新。
		m_itemCollectionUI[i].Update();
	}

	//LスティックUI
	//7 LスティックUIの初期化。
	m_lStickUI.Init("Assets/result/gamepad/lstick.dds", 512, 512);
	//7.1 LスティックUIの座標の設定。
	m_lStickUI.SetPosition(Vector3(225.0f, -400.0f, 0.0f));
	//7.2 LスティックUIの大きさの設定。
	m_lStickUI.SetScale(Vector3(0.1f, 0.1f, 0.1f));
	//7.3 LスティックUIの更新。
	m_lStickUI.Update();

	//十字キーUI
	//8 十字キーUIの初期化。
	m_dPadUI.Init("Assets/result/gamepad/dpad.dds", 512, 512);
	//8.1 十字キーUIの座標の設定。
	m_dPadUI.SetPosition(Vector3(275.0f, -400.0f, 0.0f));
	//8.2 十字キーUIの大きさの設定。
	m_dPadUI.SetScale(Vector3(0.1f, 0.1f, 0.1f));
	//8.3 十字キーUIの更新。
	m_dPadUI.Update();

	//AボタンUI。
	//9 AボタンUIの初期化。
	GetFullPaht_BUTTONUI("abutton", ABUTTON_WIDHT, ABUTTON_HEIGHT);
	//9.1 AボタンUIの座標の設定。
	m_aButtonUI.SetPosition(ABUTTON_UI);
	//9.2 AボタンUIの大きさの設定。
	m_aButtonUI.SetScale(ABUTTON_SCALE);
	//9.3 Aボタンの更新。
	m_aButtonUI.Update();

	//選択UI
	//10 選択UIの初期化。
	m_selectUI.Init("Assets/result/text/select.dds", 1024, 128);
	//10.1 選択UIの座標の設定。
	m_selectUI.SetPosition(Vector3(350.0f, -400.0f, 0.0f));
	//10.2 選択UIの大きさの設定。
	m_selectUI.SetScale(Vector3(0.3f, 0.3f, 0.3f));
	//10.3 選択UIの更新。
	m_selectUI.Update();

	//タイトルへ戻るUI。
	//11 タイトルへ戻るUIの初期化。
	GetFullPath_RETURNUI("returntitle", RETURNBUTTON_WIDHT, RETURNBUTTON_HEIGHT);
	//11.1 タイトルへ戻るUIの座標の設定。
	m_returnTitleUI.SetPosition(RETURNBUTTON_POSITION);
	//11.2 タイトルへ戻るUIの大きさの設定。
	m_returnTitleUI.SetScale(RETURNBUTTON_SCALE);
	//11.3 タイトルへ戻るUIの更新。
	m_returnTitleUI.Update();
}

//スプライトの動作。
void GameClear::SpriteMove()
{
	//ゲームクリア演出ステート。
	switch (m_gameClearDirectionState)
	{
	case enGameClearDirection_ItemGet:	//アイテム取得の演出。
		//現在のアイテムを取得しているときのUIのイージングステートでそのアイテムが取得していないとき
		if (m_itemGetFlag[m_itemGetUIEasingState] == false)
		{
			//アイテムを取得しているときのUIのイージングステートがタオル以外のとき
			if (m_itemGetUIEasingState != enItem_Taoru)
			{
				//次のアイテムに移る。
				m_itemGetUIEasingState++;
			}
			//アイテムを取得しているときのUIのイージングステートがタオルのとき
			else
			{
				//次の演出に移る。
				m_gameClearDirectionState = enGameClearDirection_ItemUIMove;
			}
			return;
		}

		//アイテムを取得しているときのUIのイージング開始フラグが立っていないとき
		if (m_itemGetUIEasingStartFlag[m_itemGetUIEasingState] != true)
		{
			//アイテムを取得しているときのUIのイージング設定。
			SetItemGetUIEasing(m_itemGetUIEasingState);
		}
		//アイテムを取得しているときのUIのイージング開始フラグが立っているとき
		else
		{
			//アイテムを取得しているときのUIのイージング更新処理。
			UpdateItemGetUIEasing(m_itemGetUIEasingState);
		}
		break;
	case enGameClearDirection_ItemUIMove:	//アイテムUIの動作の演出。
		//アイテムUI関連のイージング開始フラグが立っていないとき
		if (m_itemUIEasingStartFlag != true)
		{
			//アイテムUI関連のイージング設定。
			SetItemUIEasing();
		}
		//アイテムUI関連のイージング開始フラグが立っているとき
		else
		{
			//アイテムUI関連のイージング更新処理。
			UpdateItemUIEasing();
		}
		break;
	default:
		break;
	}
}

//アイテムを取得しているときのUIのイージング設定。
void GameClear::SetItemGetUIEasing(int item)
{
	//アイテムを取得しているときのUIの透明度。
	m_itemGetUIBeforeEasingAlpha[item] = m_itemGetUI[item].GetMulColor();
	m_itemGetUIAfterEasingAlpha[item] = Vector4(1.0f, 1.0f, 1.0f, 1.0f);
	m_itemGetUIEasingAlpha[item] = m_itemGetUI[item].GetMulColor();

	//アイテムを取得しているときのUIの大きさ。
	m_itemGetUIBeforeEasingScale[item] = m_itemGetUI[item].GetScale();
	m_itemGetUIAfterEasingScale[item] = m_noItemGetUI[item].GetScale();
	m_itemGetUIEasingScale[item] = m_itemGetUI[item].GetScale();

	//アイテム取得UIのイージングを開始する。
	m_itemGetUIEasingStartFlag[item] = true;
}

//アイテムを取得しているときのUIのイージング更新処理。
void GameClear::UpdateItemGetUIEasing(int item)
{
	//アイテムを取得しているときのUIの透明度。
	m_itemGetUIEasingAlphaTime[item] += 2.0f * g_gameTime->GetFrameDeltaTime();

	//アイテムを取得しているときのUIの透明度用の割合が1.0fになったら
	if (m_itemGetUIEasingAlphaTime[item] > 1.0f)
	{
		//固定する。
		m_itemGetUIEasingAlphaTime[item] = 1.0f;
	}

	m_itemGetUIEasingAlpha[item].Lerp(m_itemGetUIEasingAlphaTime[item], m_itemGetUIBeforeEasingAlpha[item], m_itemGetUIAfterEasingAlpha[item]);
	m_itemGetUI[item].SetMulColor(m_itemGetUIEasingAlpha[item]);
	m_itemGetUI[item].Update();

	//アイテムを取得しているときのUIの大きさ。
	m_itemGetUIEasingScaleTime[item] += g_gameTime->GetFrameDeltaTime();

	//アイテムを取得しているときのUIの大きさ用の割合が1.0fになったら
	if (m_itemGetUIEasingScaleTime[item] > 1.0f)
	{
		m_itemGetUIEasingScaleTime[item] = 1.0f;

		//リザルト画面でアイテムを表示した時の音の再生。
		g_gameSoundEngine->PlaySE(GameSoundList_SE_Result_ViewItemGet, 1.0f);

		//アイテムを取得しているときのUIのイージングステートがタオル以外のとき
		if (m_itemGetUIEasingState != enItem_Taoru)
		{
			//次のアイテムに移る。
			m_itemGetUIEasingState++;
		}
		//アイテムを取得しているときのUIのイージングステートがタオルのとき
		else
		{
			//次の演出に移る。
			m_gameClearDirectionState = enGameClearDirection_ItemUIMove;
		}
	}

	m_itemGetUIEasingScale[item].Lerp(m_itemGetUIEasingScaleTime[item], m_itemGetUIBeforeEasingScale[item], m_itemGetUIAfterEasingScale[item]);
	m_itemGetUI[item].SetScale(m_itemGetUIEasingScale[item]);
	m_itemGetUI[item].Update();
}

//アイテムUI関連のイージング設定。
void GameClear::SetItemUIEasing()
{
	//アイテム取得リスト。
	m_itemGetListUIBeforeEasingPosition = m_itemGetListUI.GetPosition();
	m_itemGetListUIAfterEasingPosition = Vector3(350.0f, 0.0f, 0.0f);
	m_itemGetListUIEasingPosition = m_itemGetListUI.GetPosition();

	//アイテム取得リストテキスト。
	m_itemGetListTextUIBeforeEasingPosition = m_itemGetListTextUI.GetPosition();
	m_itemGetListTextUIAfterEasingPosition = Vector3(350.0f, 150.0f, 0.0f);
	m_itemGetListTextUIEasingPosition = m_itemGetListTextUI.GetPosition();

	//アイテムUI。
	for (int i = 0; i < enItem_Num; i++)
	{
		m_itemUIBeforeEasingPosition[i] = m_noItemGetUI[i].GetPosition();
		m_itemUIAfterEasingPosition[i] = Vector3(m_noItemGetUI[i].GetPosition().x + 350.0f, m_noItemGetUI[i].GetPosition().y, 0.0f);
		m_itemUIEasingPosition[i] = m_noItemGetUI[i].GetPosition();
	}

	//割合。
	m_itemUIEasingTime = 0.0f;

	//アイテム関連UIのスプライトのイージングを開始する。
	m_itemUIEasingStartFlag = true;
}

//アイテムUI関連のイージング更新処理
void GameClear::UpdateItemUIEasing()
{
	m_itemUIEasingTime += 3.5f * g_gameTime->GetFrameDeltaTime();

	//割合が1.0fになったらゲームクリア演出を終了する
	if (m_itemUIEasingTime > 1.0f)
	{
		m_itemUIEasingTime = 1.0f;
		m_gameClearDirectionFlag = true;
	}

	//アイテム取得リスト。
	m_itemGetListUIEasingPosition.Lerp(m_itemUIEasingTime, m_itemGetListUIBeforeEasingPosition, m_itemGetListUIAfterEasingPosition);
	m_itemGetListUI.SetPosition(m_itemGetListUIEasingPosition);
	m_itemGetListUI.Update();

	//アイテム取得リストテキスト。
	m_itemGetListTextUIEasingPosition.Lerp(m_itemUIEasingTime, m_itemGetListTextUIBeforeEasingPosition, m_itemGetListTextUIAfterEasingPosition);
	m_itemGetListTextUI.SetPosition(m_itemGetListTextUIEasingPosition);
	m_itemGetListTextUI.Update();

	//アイテムUI。
	for (int i = 0; i < enItem_Num; i++)
	{
		//アイテムを取得していないときのUI。
		m_itemUIEasingPosition[i].Lerp(m_itemUIEasingTime, m_itemUIBeforeEasingPosition[i], m_itemUIAfterEasingPosition[i]);
		m_noItemGetUI[i].SetPosition(m_itemUIEasingPosition[i]);
		m_noItemGetUI[i].Update();

		//アイテムを取得しているときのUI。
		m_itemGetUI[i].SetPosition(m_itemUIEasingPosition[i]);
		m_itemGetUI[i].Update();

		//アイテムを選択しているときのUI。
		m_itemSelectUI[i].SetPosition(m_itemUIEasingPosition[i]);
		m_itemSelectUI[i].Update();
	}
}

//プレイヤー側の操作。
void GameClear::Action()
{
	//ゲームクリア演出が終わっていないとき。
	if (m_gameClearDirectionFlag != true)
	{
		//Aボタンを押したらゲームクリア演出ステートに応じて演出をスキップする。
		if (g_pad[0]->IsTrigger(enButtonA))
		{
			//ゲームクリア演出ステート。
			switch (m_gameClearDirectionState)
			{
			case enGameClearDirection_ItemGet:
				m_itemGetUIEasingAlphaTime[m_itemGetUIEasingState] = 1.0f;
				m_itemGetUIEasingScaleTime[m_itemGetUIEasingState] = 1.0f;
				break;
			case enGameClearDirection_ItemUIMove:
				m_itemUIEasingTime = 1.0f;
				break;
			default:
				break;
			}
		}
		return;
	}

	//タイトル画面遷移フラグが立っていないとき。
	if (m_titleScreenTransitionFlag != true)
	{
		//アイテム選択のときのプレイヤー側の操作。
		ItemSelectAction();

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

//アイテム選択のときのプレイヤー側の操作。
void GameClear::ItemSelectAction()
{
	//十字キーを上に倒す または
	//左スティックを上に倒したとき
	if (g_pad[0]->IsTrigger(enButtonUp) || g_pad[0]->IsTriggerLStickUp())
	{
		//選択音の再生。
		g_gameSoundEngine->PlaySE(GameSoundList_SE_SelectScreen_Select, 1.0f);

		//現在の選択がじゃこ天だったら
		if (m_itemSelect == enItem_Jako)
		{
			//砥部焼を選択する。
			m_itemSelect = enItem_Tobeyaki;
			return;
		}
		//現在の選択がみかんだったら
		else if (m_itemSelect == enItem_Mikan)
		{
			//タルトを選択する。
			m_itemSelect = enItem_Taruto;
			return;
		}
		//現在の選択が真珠だったら
		else if (m_itemSelect == enItem_Sinju)
		{
			//タオルを選択する。
			m_itemSelect = enItem_Taoru;
			return;
		}

		//選択が上に上がる。
		m_itemSelect -= 3;
	}
	//十字キーを下に倒す または
	//左スティックを下に倒したとき
	else if (g_pad[0]->IsTrigger(enButtonDown) || g_pad[0]->IsTriggerLStickDown())
	{
		//選択音の再生。
		g_gameSoundEngine->PlaySE(GameSoundList_SE_SelectScreen_Select, 1.0f);

		//現在の選択が砥部焼だったら
		if (m_itemSelect == enItem_Tobeyaki)
		{
			//じゃこ天を選択する。
			m_itemSelect = enItem_Jako;
			return;
		}
		//現在の選択がタルトだったら
		else if (m_itemSelect == enItem_Taruto)
		{
			//みかんを選択する。
			m_itemSelect = enItem_Mikan;
			return;
		}
		//現在の選択がタオルだったら
		else if (m_itemSelect == enItem_Taoru)
		{
			//真珠を選択する。
			m_itemSelect = enItem_Sinju;
			return;
		}

		//選択が下に下がる。
		m_itemSelect += 3;
	}
	//十字キーを左に倒す または
	//左スティックを左に倒したとき
	else if (g_pad[0]->IsTrigger(enButtonLeft) || g_pad[0]->IsTriggerLStickLeft())
	{
		//選択音の再生。
		g_gameSoundEngine->PlaySE(GameSoundList_SE_SelectScreen_Select, 1.0f);

		//現在の選択がじゃこ天だったら
		if (m_itemSelect == enItem_Jako)
		{
			//真珠を選択する。
			m_itemSelect = enItem_Sinju;
			return;
		}
		//現在の選択が砥部焼だったら
		else if (m_itemSelect == enItem_Tobeyaki)
		{
			//タオルを選択する。
			m_itemSelect = enItem_Taoru;
			return;
		}

		//選択が左にいく。
		m_itemSelect -= 1;
	}
	//十字キーを右に倒す または
	//左スティックを右に倒したとき
	else if (g_pad[0]->IsTrigger(enButtonRight) || g_pad[0]->IsTriggerLStickRight())
	{
		//選択音の再生。
		g_gameSoundEngine->PlaySE(GameSoundList_SE_SelectScreen_Select, 1.0f);

		//現在の選択が真珠だったら
		if (m_itemSelect == enItem_Sinju)
		{
			//じゃこ天を選択する。
			m_itemSelect = enItem_Jako;
			return;
		}
		//現在の選択がタオルだったら
		else if (m_itemSelect == enItem_Taoru)
		{
			//砥部焼を選択する。
			m_itemSelect = enItem_Tobeyaki;
			return;
		}

		//選択が下に行く。
		m_itemSelect += 1;
	}
}