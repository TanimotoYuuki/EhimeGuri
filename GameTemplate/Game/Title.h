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

	//タイトル遷移
	enum EnTitleTransition
	{
		enTitleTransition_Title,		//タイトル
		enTitleTransition_HowToPlay,	//遊び方
	};

	AnimationClip		m_animationClip[enAnimationClip_num];										//アニメションクリップ
	ModelRender			m_playerModel;																//プレイヤーモデル
	ModelRender         m_stageModel;																//ステージモデル
	Vector3				m_playerModelPosition=Vector3::Zero;										//プレイヤーモデルの位置
	Quaternion          m_playerModelRotation = Quaternion::Identity;								//プレイヤーモデルの回転
	Vector3             m_playerModelScale = Vector3( 0.5f,0.5f,0.5f );								//プレイヤーモデルの大きさ
	int 				m_playerModelAnimationState = enPlayerModelAnimationState_walk;				//プレイヤーモデルアニメーションステート
	SpriteRender        m_fade;																		//フェード
	SpriteRender		m_titleBackGround;															//タイトル背景
	SpriteRender		m_titleName[2];																//タイトル名
	Stopwatch			m_stopWatch;																//ストップウォッチ
	bool                m_startFadeFinishFlag = false;												//スタート用フェードが終わったか?
	bool				m_gameStartFlag = false;													//ゲームスタートフラグ
};

