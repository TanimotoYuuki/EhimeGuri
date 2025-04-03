#pragma once
#include "Game.h"

class Player;
class Game;
class GameOver;
class Title : public IGameObject
{
public:
	Title();
	~Title();

	void Update();
	void Render(RenderContext& rc);


private:
	//スカイキューブの初期化
	void InitSky();
	//アニメーションの初期化
	void InitAnimation();
	//モデルの初期化
	void InitModel();
	//スプライトの初期化
	void InitSprite();
	//カメラの初期化
	void InitCamera();
	//プレイヤー側の操作
	void Action();
	//スプライトの動作
	void SpriteMove();
	//カメラの更新処理
	void UpdateCamera();
	//プレイヤーモデルの動作
	void PlayerModelMove();
	//アニメーション管理
	void AnimationManage();
	//アニメーション再生
	void PlayAnimation();
	//プレイヤーモデルのアニメーション管理
	void PlayerModelAnimationManage();
	//プレイヤーモデルのアニメーション再生
	void PlayerModelPlayAnimation();

	//アニメーションクリップ
	enum EnAnimationClip {
		enAnimationClip_walk,
		enAnimationClip_run,
		enAnimationClip_num
	};

	//プレイヤーモデルアニメーションステート
	enum EnPlayerModelAnimationState
	{
		enPlayerModelAnimationState_walk,
		enPlayerModelAnimationState_run,
		enPlayerModelAnimationState_num
	};

	//モード選択
	enum EnModeSelect
	{
		enModeSelect_Start,				//スタート
		enModeSelect_HowToPlay,			//遊び方
		enModeSelect_Shutdown,			//ゲーム終了
		enModeSelect_Num				//モード選択数
	};

	//ゲームパッド
	enum EnGamePad
	{
		enGamePad_AButton,				//Aボタン
		enGamePad_BButton,				//Bボタン
		enGamePad_XButton,				//Xボタン
		enGamePad_YButton,				//Yボタン
		enGamePad_LStick,				//Lボタン
		enGamePad_RStick,				//Rボタン
		enGamePad_DPad,					//十字キー
		enGamePad_Num,					//ゲームパッド数
	};

	//タイトル画面用遷移
	enum EnTitleTransition
	{
		enTitleTransition_Title,		//タイトル
		enTitleTransition_ModeSelect,	//モード選択
		enTitleTransition_HowToPlay,	//遊び方
		enTitleTransition_Num			//遷移数
	};

	AnimationClip		m_animationClip[enAnimationClip_num];										//アニメションクリップ
	ModelRender			m_playerModel;																//プレイヤーモデル
	ModelRender         m_backGroundModel;															//ステージモデル
	Vector3				m_playerModelPosition=Vector3::Zero;										//プレイヤーモデルの位置
	Quaternion          m_playerModelRotation = Quaternion::Identity;								//プレイヤーモデルの回転
	Vector3             m_playerModelScale = Vector3( 0.5f,0.5f,0.5f );								//プレイヤーモデルの大きさ
	int 				m_playerModelAnimationState = enPlayerModelAnimationState_walk;				//プレイヤーモデルアニメーションステート
	int                 m_modeSelect = enModeSelect_Start;											//モード選択
	int					m_titleTransition = enTitleTransition_Title;								//タイトル画面用遷移
	Vector4             m_modeUIColor[enModeSelect_Num];											//モード選択UIのカラー
	float				m_alpha = 0.0f;																//透明度
	SpriteRender        m_fade;																		//フェード
	SpriteRender		m_titleBackGround;															//タイトル背景
	SpriteRender		m_titleName[2];																//タイトル名
	SpriteRender        m_pressAButtonUI;															//Aボタンを押すUI
	SpriteRender        m_modeUI[enModeSelect_Num];													//モードUI
	SpriteRender        m_howToPlayUI;																//遊び方UI
	SpriteRender        m_gamePadUI[enGamePad_Num];													//ゲームパッドUI
	SpriteRender		m_decisionUI;																//決定UI
	SpriteRender        m_selectUI;																	//選択UI
	SpriteRender		m_returnUI;																	//戻るUI
	bool                m_startFadeFinishFlag = false;												//スタート用フェードが終わったか?
	bool				m_gameStartFlag = false;													//ゲームスタートフラグ
	SkyCube* m_skyCube = nullptr;
	int m_skyCubeType = enSkyCubeType_Day;
};

