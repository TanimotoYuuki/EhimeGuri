#pragma once
#include "Game.h"

/// <summary>
/// タイトル
/// </summary>
class Player;
class Game;
class GameOver;
class Fade;
class Title : public IGameObject
{
public:
	~Title(); //デストラクタ。
	bool Start();  //開始処理。
	void Update();  //更新処理。
	void Render(RenderContext& rc);  //描画処理。

	bool m_sceneTransitionFlag = false;		//シーン遷移フラグ。
	bool m_gameLoadFlag = false;			//ゲームロードフラグ。
private:
	//スカイキューブの初期化。
	void InitSky();
	//アニメーションの初期化。
	void InitAnimation();
	//モデルの初期化。
	void InitModel();
	//スプライトの初期化。
	void InitSprite();
	//カメラの初期化。
	void InitCamera();
	//プレイヤー側の操作。
	void Action();
	//スプライトの動作。
	void SpriteMove();
	//カメラの更新処理。
	void UpdateCamera();
	//ステージモデルの動作。
	void BackGroundModelMove();
	//プレイヤーモデルの動作。
	void PlayerModelMove();
	//アニメーション管理。
	void AnimationManage();
	//アニメーション再生。
	void PlayAnimation();
	//プレイヤーモデルのアニメーション管理。
	void PlayerModelAnimationManage();
	//プレイヤーモデルのアニメーション再生。
	void PlayerModelPlayAnimation();


	//アニメーションクリップ。
	enum EnAnimationClip {
		enAnimationClip_walk,
		enAnimationClip_run,
		enAnimationClip_num
	};

	//プレイヤーモデルアニメーションステート。
	enum EnPlayerModelAnimationState
	{
		enPlayerModelAnimationState_walk,
		enPlayerModelAnimationState_run,
		enPlayerModelAnimationState_num
	};

	//モード選択。
	enum EnModeSelect
	{
		enModeSelect_Start,				//スタート。
		enModeSelect_HowToPlay,			//遊び方。
		enModeSelect_Shutdown,			//ゲーム終了。
		enModeSelect_Num				//モード選択数。
	};

	//ゲームパッド。
	enum EnGamePad
	{
		enGamePad_AButton,				//Aボタン。
		enGamePad_BButton,				//Bボタン。
		enGamePad_XButton,				//Xボタン。
		enGamePad_YButton,				//Yボタン。
		enGamePad_LStick,				//Lボタン。
		enGamePad_RStick,				//Rボタン。
		enGamePad_DPad,					//十字キー。
		enGamePad_Num,					//ゲームパッド数。
	};

	//タイトル画面用遷移。
	enum EnTitleTransition
	{
		enTitleTransition_Title,		//タイトル。
		enTitleTransition_ModeSelect,	//モード選択。
		enTitleTransition_HowToPlay,	//遊び方。
		enTitleTransition_Num			//遷移数。
	};

	//ステージモデル。
	enum EnBackGroundModel
	{
		enBackGroundModel_Base,			//土台。
		enBackGroundModel_Grass,		//草原。
		enBackGroundModel_Num			//ステージモデル数。
	};

	AnimationClip m_animationClip[enAnimationClip_num];								//アニメーションクリップ。
	ModelRender m_backGroundModel[enBackGroundModel_Num];							//ステージモデル。
	ModelRender m_playerModel;														//プレイヤーモデル。
	Vector3 m_playerModelPosition=Vector3::Zero;									//プレイヤーモデルの位置。
	Quaternion m_playerModelRotation = Quaternion::Identity;						//プレイヤーモデルの回転。
	Vector3 m_playerModelScale = Vector3( 0.5f,0.5f,0.5f );							//プレイヤーモデルの大きさ。
	int m_playerModelAnimationState = enPlayerModelAnimationState_walk;				//プレイヤーモデルアニメーションステート。
	int m_modeSelect = enModeSelect_Start;											//モード選択。
	int m_titleTransition = enTitleTransition_Title;								//タイトル画面用遷移。
	Vector4 m_modeUIColor[enModeSelect_Num];										//モード選択UIのカラー。
	float m_alpha = 0.0f;															//透明度。
	float m_titleBGMVolume = 0.0f;													//タイトルBGMの音量。
	SpriteRender m_titleBackGround;													//タイトル背景。
	SpriteRender m_pressAButtonUI;													//Aボタンを押すUI。
	SpriteRender m_modeUI[enModeSelect_Num];										//モードUI。
	SpriteRender m_howToPlayUI;														//遊び方UI。
	SpriteRender m_gamePadUI[enGamePad_Num];										//ゲームパッドUI。
	SpriteRender m_decisionUI;														//決定UI。
	SpriteRender m_selectUI;														//選択UI。
	SpriteRender m_returnUI;														//戻るUI。
	bool m_fadeInFinishFlag = false;												//フェードインが終わったか?
	bool m_titleBackGroundFadeInFinishFlag = false;									//タイトル背景のフェードインが終わったか?
	bool m_gameStartFlag = false;													//ゲームスタートフラグ。
	bool m_pressButtonFlag = false;													//ボタンを押したか?
	bool m_pressButtonActionFlag = false;											//ボタンを押したときの動作をしたか?
	bool m_titleTransitionFlag = false;												//タイトル画面遷移フラグ。
	bool m_getTitleBGMVolumeFlag = false;											//タイトルBGMの音量を取得したか?
	Fade* m_fade = nullptr;															//フェード用インスタンス。
	SkyCube* m_skyCube = nullptr;													//スカイキューブ用のインスタンス。
	int m_skyCubeType = enSkyCubeType_Day;											//スカイキューブの背景。

	/// ファイルパス定数化メソッド。/////////

	/// <summary>
	/// アニメーションの初期化。
	/// </summary>
	const string GetFullPath_InitAnimation(EnAnimationClip enAnimationClip, const std::string& name, bool flag);

	////////////////////////////////////////	

	/// <summary>
	/// アニメーションデータのディレクトリパスを表す定数文字列。
	/// </summary>
	const char* TITLE_ANIMATION = "Assets/animData/";
	const char* RETURN_UI = "Assets/title/text/";
	const char* GAMEPAD = "Assets/title/gamepad/";
	const char* SCREEN = "Assets/title/screen/";
	const char* TEXT = "Assets/title/text/";
	const char* TITLE_STAGE = "Assets/title/";
	const char* TITLE_TKA = ".tka";
	const char* TITLE_TKM = ".tkm";

};

