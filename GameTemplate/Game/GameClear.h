#pragma once
#include "GameClear.h"
#include "GameOver.h"
#include "ClearPoint.h"


class Fade;
class GameClear : public IGameObject
{
	/// <summary>
	/// ゲームクリア。
	/// </summary>

public:
	~GameClear() {};  //デストラクタ。
	bool Start();	//開始処理。
	void Update();  //更新処理。
	void Render(RenderContext& rc);  //描画処理。

	/// <summary>
	/// 取得したアイテムを設定する。
	/// </summary>
	/// <param name="jako">じゃこ天</param>
	/// <param name="mikan">みかん</param>
	/// <param name="sinju">真珠</param>
	/// <param name="tobeyaki">砥部焼</param>
	/// <param name="taruto">タルト</param>
	/// <param name="taoru">タオル</param>
	void SetItemGet(int item[])
	{
		for (int i = 0; i < enItem_Num; i++)
		{
			if (item[i] == 1)
			{
				m_itemGetFlag[i] = true;
			}
		}
	}

	bool isClear = false;  //ゲームクリアフラグ
	// ゲームクリアを設定する。
	void SetIsClrar(bool clear)
	{
		isClear = clear;
	}

	// ゲームクリアを返す。
	bool GetIsClear() const
	{
		return isClear;
	}

	SpriteRender m_result;															//リザルト画面。


private:
	/// <summary>
	/// スプライトの初期化。
	/// </summary>
	void InitSprite();

	/// <summary>
	/// アイテムUI関連のスプライトの情報を取得。
	/// </summary>
	/// <param name="item">アイテム</param>
	void GetItemUISpriteData(int item)
	{
		//アイテム
		switch (item)
		{
		case enItem_Jako:		//じゃこ天
			m_noItemGetUISpriteFilePath = "Assets/result/item/item/jako.dds";
			m_itemGetUISpriteFilePath = "Assets/result/item/item/jakoget.dds";
			m_itemSelectUISpriteFilePath = "Assets/result/item/item/jakoselect.dds";

			//じゃこ天を取得していたら
			if (m_itemGetFlag[enItem_Jako] == true)
			{
				m_itemCollectionUISpriteFilePath = "Assets/result/item/collection/jako.dds";
			}
			//じゃこ天を取得していなかったら
			else
			{
				m_itemCollectionUISpriteFilePath = "Assets/result/item/collection/noitemget.dds";
			}

			m_itemUIPosition = Vector3(-150.0f, 25.0f, 0.0f);
			m_noItemGetUIScale = Vector3(1.0f, 1.0f, 1.0f);
			m_itemGetUIScale = Vector3(1.4f, 1.4f, 1.4f);
			m_itemSelectUIScale = Vector3(1.1f, 1.1f, 1.1f);
			break;
		case enItem_Mikan:		//みかん
			m_noItemGetUISpriteFilePath = "Assets/result/item/item/mikan.dds";
			m_itemGetUISpriteFilePath = "Assets/result/item/item/mikanget.dds";
			m_itemSelectUISpriteFilePath = "Assets/result/item/item/mikanselect.dds";

			//みかんを取得していたら
			if (m_itemGetFlag[enItem_Mikan] == true)
			{
				m_itemCollectionUISpriteFilePath = "Assets/result/item/collection/mikan.dds";
			}
			//みかんを取得していなかったら
			else
			{
				m_itemCollectionUISpriteFilePath = "Assets/result/item/collection/noitemget.dds";
			}

			m_itemUIPosition = Vector3(0.0f, 25.0f, 0.0f);
			m_noItemGetUIScale = Vector3(1.0f, 1.0f, 1.0f);
			m_itemGetUIScale = Vector3(1.4f, 1.4f, 1.4f);
			m_itemSelectUIScale = Vector3(1.07f, 1.1f, 1.07f);
			break;
		case enItem_Sinju:		//真珠
			m_noItemGetUISpriteFilePath = "Assets/result/item/item/sinju.dds";
			m_itemGetUISpriteFilePath = "Assets/result/item/item/sinjuget.dds";
			m_itemSelectUISpriteFilePath = "Assets/result/item/item/sinjuselect.dds";

			//真珠を取得していたら
			if (m_itemGetFlag[enItem_Sinju] == true)
			{
				m_itemCollectionUISpriteFilePath = "Assets/result/item/collection/sinju.dds";
			}
			//真珠を取得していなかったら
			else
			{
				m_itemCollectionUISpriteFilePath = "Assets/result/item/collection/noitemget.dds";
			}

			m_itemUIPosition = Vector3(150.0f, 25.0f, 0.0f);
			m_noItemGetUIScale = Vector3(1.0f, 1.0f, 1.0f);
			m_itemGetUIScale = Vector3(1.4f, 1.4f, 1.4f);
			m_itemSelectUIScale = Vector3(1.07f, 1.07f, 1.07f);
			break;
		case enItem_Tobeyaki:	//砥部焼
			m_noItemGetUISpriteFilePath = "Assets/result/item/item/tobeyaki.dds";
			m_itemGetUISpriteFilePath = "Assets/result/item/item/tobeyakiget.dds";
			m_itemSelectUISpriteFilePath = "Assets/result/item/item/tobeyakiselect.dds";
			
			//砥部焼を取得していたら
			if (m_itemGetFlag[enItem_Tobeyaki] == true)
			{
				m_itemCollectionUISpriteFilePath = "Assets/result/item/collection/tobeyaki.dds";
			}
			//砥部焼を取得していなかったら
			else
			{
				m_itemCollectionUISpriteFilePath = "Assets/result/item/collection/noitemget.dds";
			}

			m_itemUIPosition = Vector3(-150.0f, -100.0f, 0.0f);
			m_noItemGetUIScale = Vector3(1.0f, 1.0f, 1.0f);
			m_itemGetUIScale = Vector3(1.4f, 1.4f, 1.4f);
			m_itemSelectUIScale = Vector3(1.1f, 1.1f, 1.1f);
			break;
		case enItem_Taruto:		//タルト
			m_noItemGetUISpriteFilePath = "Assets/result/item/item/taruto.dds";
			m_itemGetUISpriteFilePath = "Assets/result/item/item/tarutoget.dds";
			m_itemSelectUISpriteFilePath = "Assets/result/item/item/tarutoselect.dds";

			//タルトを取得していたら
			if (m_itemGetFlag[enItem_Taruto] == true)
			{
				m_itemCollectionUISpriteFilePath = "Assets/result/item/collection/taruto.dds";
			}
			//タルトを取得していなかったら
			else
			{
				m_itemCollectionUISpriteFilePath = "Assets/result/item/collection/noitemget.dds";
			}

			m_itemUIPosition = Vector3(0.0f, -100.0f, 0.0f);
			m_noItemGetUIScale = Vector3(1.0f, 1.0f, 1.0f);
			m_itemGetUIScale = Vector3(1.4f, 1.4f, 1.4f);
			m_itemSelectUIScale = Vector3(1.1f, 1.1f, 1.1f);
			break;
		case enItem_Taoru:		//タオル
			m_noItemGetUISpriteFilePath = "Assets/result/item/item/taorukuro.dds";
			m_itemGetUISpriteFilePath = "Assets/result/item/item/taorutori.dds";
			m_itemSelectUISpriteFilePath = "Assets/result/item/item/taoruselect.dds";

			//タオルを取得していたら
			if (m_itemGetFlag[enItem_Taoru] == true)
			{
				m_itemCollectionUISpriteFilePath = "Assets/result/item/collection/taoru.dds";
			}
			//タオルを取得していなかったら
			else
			{
				m_itemCollectionUISpriteFilePath = "Assets/result/item/collection/noitemget.dds";
			}

			m_itemUIPosition = Vector3(150.0f, -100.0f, 0.0f);
			m_noItemGetUIScale = Vector3(1.3f, 1.3f, 1.3f);
			m_itemGetUIScale = Vector3(1.7f, 1.7f, 1.7f);
			m_itemSelectUIScale = Vector3(1.45f, 1.35f, 1.45f);
			break;
		default:
			break;
		}
	}

	/// <summary>
	/// スプライトの動作。
	/// </summary>
	void SpriteMove();

	/// <summary>
	/// アイテムUI関連のイージング設定。
	/// </summary>
	void SetItemUIEasing();

	/// <summary>
	/// アイテムUI関連のイージング更新処理。
	/// </summary>
	void UpdateItemUIEasing();

	/// <summary>
	/// アイテムを取得しているときのUIのイージング設定。
	/// </summary>
	/// <param name="item">アイテム</param>
	void SetItemGetUIEasing(int item);

	/// <summary>
	/// アイテムを取得しているときのUIのイージング更新処理。
	/// </summary>
	/// <param name="item">アイテム</param>
	void UpdateItemGetUIEasing(int item);

	/// <summary>
	/// プレイヤー側の操作。
	/// </summary>
	void Action();

	/// <summary>
	/// アイテム選択のときのプレイヤー側の操作。
	/// </summary>
	void ItemSelectAction();

	//アイテム
	enum EnItem
	{
		enItem_Jako,		//じゃこ天
		enItem_Mikan,		//みかん
		enItem_Sinju,		//真珠
		enItem_Tobeyaki,	//砥部焼
		enItem_Taruto,		//タルト
		enItem_Taoru,		//タオル
		enItem_Num,			//アイテム数
	};

	//ゲームクリア演出。
	enum EnGameClearDirection
	{
		enGameClearDirection_ItemGet,		//アイテム取得の演出。
		enGameClearDirection_ItemUIMove,	//アイテムUIの動作の演出。
		enGameClearDirection_Num			//ゲームクリア演出数。
	};

	SpriteRender m_gameResultUI;													//ゲーム結果UI
	SpriteRender m_itemGetListUI;													//アイテム取得リストUI。
	SpriteRender m_itemGetListTextUI;												//アイテム取得リストのテキストUI。
	SpriteRender m_noItemGetUI[enItem_Num];											//アイテムを取得していないときのUI。
	SpriteRender m_itemGetUI[enItem_Num];											//アイテムを取得しているときのUI。
	SpriteRender m_itemSelectUI[enItem_Num];										//アイテムを選択しているときのUI。
	SpriteRender m_itemCollectionUI[enItem_Num];									//アイテムコレクションUI。	
	SpriteRender m_lStickUI;														//LスティックUI。
	SpriteRender m_dPadUI;															//十字キーUI。
	SpriteRender m_aButtonUI;														//AボタンUI。
	SpriteRender m_selectUI;														//選択UI。
	SpriteRender m_returnTitleUI;													//タイトルへ戻るUI。
	Vector3 m_itemUIPosition = Vector3::Zero;										//アイテムUIの位置。
	Vector3 m_noItemGetUIScale = Vector3::One;										//アイテムを取得していないときのUIの大きさ
	Vector3 m_itemGetUIScale = Vector3::One;										//アイテムを取得しているときのUIの大きさ
	Vector3 m_itemSelectUIScale = Vector3::One;										//アイテムを選択しているときのUIの大きさ
	Vector3 m_itemGetListUIBeforeEasingPosition = Vector3::Zero;					//アイテム取得リストUI用のイージング前の位置。
	Vector3 m_itemGetListUIAfterEasingPosition = Vector3::Zero;						//アイテム取得リストUI用のイージング後の位置。
	Vector3 m_itemGetListUIEasingPosition = Vector3::Zero;							//アイテム取得リストUI用のイージング中の位置。
	Vector3 m_itemGetListTextUIBeforeEasingPosition = Vector3::Zero;				//アイテム取得リストテキストUI用のイージング前の位置。
	Vector3 m_itemGetListTextUIAfterEasingPosition = Vector3::Zero;					//アイテム取得リストテキストUI用のイージング後の位置。
	Vector3 m_itemGetListTextUIEasingPosition = Vector3::Zero;						//アイテム取得リストテキストUI用のイージング中の位置。
	Vector3 m_itemUIBeforeEasingPosition[enItem_Num];								//アイテムUIイージング前の位置。
	Vector3 m_itemUIAfterEasingPosition[enItem_Num];								//アイテムUIイージング後の位置。
	Vector3 m_itemUIEasingPosition[enItem_Num];										//アイテムUIイージング中の位置。
	Vector4 m_itemGetUIBeforeEasingAlpha[enItem_Num];								//アイテムを取得しているときのUIのイージング前の透明度。
	Vector4 m_itemGetUIAfterEasingAlpha[enItem_Num];								//アイテムを取得しているときのUIのイージング後の透明度。
	Vector4 m_itemGetUIEasingAlpha[enItem_Num];										//アイテムを取得しているときのUIのイージング中の透明度。
	Vector3 m_itemGetUIBeforeEasingScale[enItem_Num];								//アイテムを取得しているときのUIのイージング前の大きさ。
	Vector3 m_itemGetUIAfterEasingScale[enItem_Num];								//アイテムを取得しているときのUIのイージング後の大きさ。
	Vector3 m_itemGetUIEasingScale[enItem_Num];										//アイテムを取得しているときのUIのイージング中の大きさ。
	int m_itemGetUIEasingState = enItem_Jako;										//アイテムを取得しているときのUIのイージングステート
	int m_itemSelect = enItem_Jako;													//アイテム選択。
	int m_gameClearDirectionState = enGameClearDirection_ItemGet;					//ゲームクリア演出ステート。
	float m_itemUIEasingTime = 0.0f;												//アイテムUI関連用の割合。
	float m_itemGetUIEasingAlphaTime[enItem_Num] = { 0.0f };						//アイテムを取得しているときのUIの透明度用の割合。
	float m_itemGetUIEasingScaleTime[enItem_Num] = { 0.0f };						//アイテムを取得しているときのUIの大きさ用の割合。
	float m_resultBGMVolume = 0.0f;													//リザルト画面BGMの音量。
	bool m_gameClearDirectionFlag = false;											//ゲームクリア演出フラグ。
	bool m_titleScreenTransitionFlag = false;										//タイトル画面遷移フラグ。
	bool m_getResultBGMVolumeFlag = false;											//リザルト画面BGMの音量を取得したか?
	bool m_itemGetFlag[enItem_Num] = {false};										//アイテム取得フラグ
	bool m_itemUIEasingStartFlag = false;											//アイテム関連UIのイージング開始フラグ
	bool m_itemGetUIEasingStartFlag[enItem_Num] = { false };						//アイテムを取得しているときのUIのイージング開始フラグ
	const char* m_noItemGetUISpriteFilePath = nullptr;								//アイテムを取得していないときのUIのファイルパス。						
	const char* m_itemGetUISpriteFilePath = nullptr;								//アイテムを取得しているときのUIのファイルパス。
	const char* m_itemSelectUISpriteFilePath = nullptr;								//アイテムを選択しているときのUIファイルパス。
	const char* m_itemCollectionUISpriteFilePath = nullptr;							//アイテムコレクションUIのファイルパス。
	Fade* m_fade = nullptr;															//フェード用インスタンス。


	Config* m_config = nullptr;
	static constexpr const char* RESULT = "Assets/result/screen/";
	static constexpr const char* ABUTTHON = "Assets/result/gamepad/";
	static constexpr const char* RETURNBUTTON = "Assets/result/text/";

	static constexpr const char* dds_EXTENSION = ".dds"; // 画像用の拡張子。
	static constexpr const char* DDS_EXTENSION = ".DDS";


	/// <summary>
	/// リザルト用。
	/// </summary>
	string GetFullPath_RESULT(const std::string& name, const float w, const float h);

	/// <summary>
	/// Aボタン。
	/// </summary>
	string GetFullPaht_BUTTONUI(const std::string& name, const float w, const float h);

	/// <summary>
	/// タイトルへ戻る用。
	/// </summary>
	string GetFullPath_RETURNUI(const std::string& name, const float w, const float h);
};		

