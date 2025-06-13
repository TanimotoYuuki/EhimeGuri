#pragma once
#include "Stage1.h"

#include "level3D/TklFile.h"

using namespace std;

class Player;// プレイヤー。
class Block;// ブロック。
class Stage1;// ステージ1。		
class Enemy;// エネミー。
class ClearPoint;// クリアポイント。
class Config;// ファイルパス統合クラス。
class FallingBlock;// 落ちる床。
class movingNeedle;// 針。
class MovingFloor;// 移動する床。
class Scaffold;// 足場。
class StageClear;// ステージクリア。
class S_MovingFloor;// 動く床(遅)。
class GameOver;// ゲームオーバー。
class GameCamera;// カメラ。
class GameTimer;// ゲームタイマー。
class HS_FallingBlock;	//動く床(速)。
class TransparentBlock;// 透明ブロック。
class TransparentWall;
class Towel;// タオル。
class Tower;// タワー。
class Fade;// フェード。
class ItemEnemy;// 敵のアイテム。
class Tobeyaki;// 砥部焼。
class sinju;// 真珠。
class Mikan;// みかん。
class Jako;// じゃこ天。
class Taruto;// タルト。
class Checpoint;// 中間地点。
class RotationFloor;

class Game : public IGameObject
{
public:
	Game() {}
	~Game();
	bool Start();
	void Update();// 更新処理。
	void Render(RenderContext& rc);// 描画処理。
		
	void GameTimer_NewGO();// ゲームタイマーのNewGO。
	void Block_NewGO();// ブロックのNewGO。
	void Stage1Goal_NewGO();// ステージ1のゴールポイント。
	void State2Goal_NewGO();// ステージ2のゴールポイント。

	void TransparentBlock_NewGO();// 透明ブロックのNewGO。
	void FallingBlock_NewGO();// 落ちるブロックのNewGO。
	void MovingFloor_NewGO();// 動く床のNewGO 。
	void Item_NewGO();// アイテムのNewGO。
	void Scaffold_NewGO();// 足場ブロックのNewGO。
	void S_MovingFloor_NewGO();// 落下速度の遅い床のNewGO。
	void Fade_NewGO();// FadeのNewGO。
	void RotationFloor_NewGO();// 回転床のNewGO。
	void Tower_NewGO();// タワーのNewGO。
	
	void Stage1ObjectDelete();//ステージ1オブジェクトの削除。
	void Stage2ObjectDelete();//ステージ2オブジェクトの削除。
	//ステージステート
	enum enStageState
	{
		enStageState_Stage1,			//ステージ1
		enStageState_Stage2,			//ステージ2
		enStageState_Num				//ステージ数
	};

	/// <summary>
	/// ステージステートの設定
	/// </summary>
	/// <param name="enStageStage">ステージステート</param>
	void SetStageState(enStageState enStageStage)
	{
		m_stageState = enStageStage;
	}

	/// <summary>
	/// ステージステートの取得
	/// </summary>
	/// <returns>ステージステート</returns>
	enStageState GetStageState() const
	{
		return m_stageState;
	}



	int	m_nowEhimePlace = enEhimePlace_Iyo;//愛媛県での現在位置
	int	m_previousEhimePlace = enEhimePlace_Iyo;//愛媛県での前の位置
	int m_ehimePlaceDrawingUI = enEhimePlace_Iyo;//UI描画用愛媛県の場所
	int m_ehimeFamousPlaceDrawingUI = enEhimePlace_Iyo;//UI描画用愛媛県の名所

	/// <summary>
	/// チェックポイント。
	/// </summary>
	Checpoint* m_checpoint = nullptr;

	//愛媛県の場所
	enum EnEhimePlace
	{
		enEhimePlace_Iyo,				//伊予市
		enEhimePlace_Oozu,				//大洲市
		enEhimePlace_Yawatahama,		//八幡浜市
		enEhimePlace_Uwajima,			//宇和島市
		enEhimePlace_Onihoku,			//鬼北町
		enEhimePlace_Kumakougen,		//久万高原町
		enEhimePlace_Sikokutyuou,		//四国中央市
		enEhimePlace_Niihama,			//新居浜市
		enEhimePlace_Imabari,			//今治市
		enEhimePlace_Matuyama,			//松山市
		enEhimePlace_Num				//場所数
	};

	/// <summary>
    /// ステージ2で使うオブジェクト。
    /// </summary>
	RotationFloor* m_RotationFloor = nullptr;



private:
	/// <summary>
	/// ステージ背景用の初期位置の更新
	/// </summary>
	void UpdateStageBackGroundCurrentPosition();

	/// <summary>
	/// ステージ背景用のゴール位置の更新
	/// </summary>
	void UpdateStageBackGroundGolePosition();

	/// <summary>
	///	ステージ背景の情報を取得
	/// </summary>
	/// <param name="place">愛媛県の場所</param>
	void GetStageBackGroundData(int place);

	/// <summary>
	/// 現在の愛媛県の場所の設定
	/// </summary>
	/// <param name="nowPos">現在位置</param>
	void SetNowEhimePlace(const Vector3& pos);

	/// <summary>
	/// 愛媛県の場所のスプライトの情報を取得
	/// </summary>
	/// <param name="place">愛媛県の場所</param>
	void GetEhimePlaceSpriteData(int place)
	{
		//愛媛県の場所
		switch (place)
		{
		case enEhimePlace_Iyo:				//伊予市
			m_ehimePlaceFilePath = "Assets/Sprite/background/text/1stage/place/iyo.dds";
			m_ehimePlacePosition = Vector3(280.0f, 360.0f, 0.0f);
			break;
		case enEhimePlace_Oozu:				//大洲市
			m_ehimePlaceFilePath = "Assets/Sprite/background/text/1stage/place/oozu.dds";
			m_ehimePlacePosition = Vector3(280.0f, 360.0f, 0.0f);
			break;
		case enEhimePlace_Yawatahama:		//八幡浜市
			m_ehimePlaceFilePath = "Assets/Sprite/background/text/1stage/place/yawatahama.dds";
			m_ehimePlacePosition = Vector3(300.0f, 360.0f, 0.0f);
			break;
		case enEhimePlace_Uwajima:			//宇和島市
			m_ehimePlaceFilePath = "Assets/Sprite/background/text/1stage/place/uwajima.dds";
			m_ehimePlacePosition = Vector3(300.0f, 360.0f, 0.0f);
			break;
		case enEhimePlace_Onihoku:			//鬼北町
			m_ehimePlaceFilePath = "Assets/Sprite/background/text/1stage/place/onihoku.dds";
			m_ehimePlacePosition = Vector3(280.0f, 360.0f, 0.0f);
			break;
		case enEhimePlace_Kumakougen:		//久万高原町
			m_ehimePlaceFilePath = "Assets/Sprite/background/text/2stage/place/kumakougen.dds";
			m_ehimePlacePosition = Vector3(320.0f, 360.0f, 0.0f);
			break;
		case enEhimePlace_Sikokutyuou:		//四国中央市
			m_ehimePlaceFilePath = "Assets/Sprite/background/text/2stage/place/sikokutyuou.dds";
			m_ehimePlacePosition = Vector3(320.0f, 360.0f, 0.0f);
			break;
		case enEhimePlace_Niihama:			//新居浜市
			m_ehimePlaceFilePath = "Assets/Sprite/background/text/2stage/place/niihama.dds";
			m_ehimePlacePosition = Vector3(300.0f, 360.0f, 0.0f);
			break;
		case enEhimePlace_Imabari:			//今治市
			m_ehimePlaceFilePath = "Assets/Sprite/background/text/2stage/place/imabari.dds";
			m_ehimePlacePosition = Vector3(280.0f, 360.0f, 0.0f);
			break;
		case enEhimePlace_Matuyama:			//松山市
			m_ehimePlaceFilePath = "Assets/Sprite/background/text/2stage/place/matuyama.dds";
			m_ehimePlacePosition = Vector3(280.0f, 360.0f, 0.0f);
			break;
		default:
			break;
		}
	}

	/// <summary>
	/// 愛媛県の名所のスプライトの情報を取得
	/// </summary>
	/// <param name="place">愛媛県の名所</param>
	void GetEhimeFamousPlaceSpriteData(int famousplace)
	{
		//愛媛県の名所
		switch (famousplace)
		{
		case enEhimePlace_Iyo:				//伊予市
			m_ehimeFamousPlaceFilePath = "Assets/Sprite/background/text/1stage/famousplace/simonagi.dds";
			m_ehimeFamousPlacePosition = Vector3(400.0f, 360.0f, 0.0f);
			break;
		case enEhimePlace_Oozu:				//大洲市
			m_ehimeFamousPlaceFilePath = "Assets/Sprite/background/text/1stage/famousplace/oozujyou.dds";
			m_ehimeFamousPlacePosition = Vector3(400.0f, 360.0f, 0.0f);
			break;
		case enEhimePlace_Yawatahama:		//八幡浜市
			m_ehimeFamousPlaceFilePath = "Assets/Sprite/background/text/1stage/famousplace/mikanbatake.dds";
			m_ehimeFamousPlacePosition = Vector3(455.0f, 360.0f, 0.0f);
			break;
		case enEhimePlace_Uwajima:			//宇和島市
			m_ehimeFamousPlaceFilePath = "Assets/Sprite/background/text/1stage/famousplace/uwajimajyou.dds";
			m_ehimeFamousPlacePosition = Vector3(455.0f, 360.0f, 0.0f);
			break;
		case enEhimePlace_Onihoku:			//鬼北町
			m_ehimeFamousPlaceFilePath = "Assets/Sprite/background/text/1stage/famousplace/mitinoeki.dds";
			m_ehimeFamousPlacePosition = Vector3(520.0f, 357.5f, 0.0f);
			break;
		case enEhimePlace_Kumakougen:		//久万高原町
			m_ehimeFamousPlaceFilePath = "Assets/Sprite/background/text/2stage/famousplace/sikokukarusuto.dds";
			m_ehimeFamousPlacePosition = Vector3(520.0f, 360.0f, 0.0f);
			break;
		case enEhimePlace_Sikokutyuou:		//四国中央市
			m_ehimeFamousPlaceFilePath = "Assets/Sprite/background/text/2stage/famousplace/suihakougen.dds";
			m_ehimeFamousPlacePosition = Vector3(490.0f, 360.0f, 0.0f);
			break;
		case enEhimePlace_Niihama:			//新居浜市
			m_ehimeFamousPlaceFilePath = "Assets/Sprite/background/text/2stage/famousplace/bessidousan.dds";
			m_ehimeFamousPlacePosition = Vector3(460.0f, 360.0f, 0.0f);
			break;
		case enEhimePlace_Imabari:			//今治市
			m_ehimeFamousPlaceFilePath = "Assets/Sprite/background/text/2stage/famousplace/simanamikaidou.dds";
			m_ehimeFamousPlacePosition = Vector3(450.0f, 360.0f, 0.0f);
			break;
		case enEhimePlace_Matuyama:			//松山市
			m_ehimeFamousPlaceFilePath = "Assets/Sprite/background/text/2stage/famousplace/dougoonnsen.dds";
			m_ehimeFamousPlacePosition = Vector3(420.0f, 360.0f, 0.0f);
			break;
		default:
			break;
		}
	}



	/// <summary>
	/// ブロック。
	/// </summary>
	Block* m_block = nullptr;
	Block* m_block1 = nullptr;
	Block* m_block2 = nullptr;
	Block* m_block3 = nullptr;
	Block* m_block4 = nullptr;


	/// <summary>
	/// 第1ステージ。
	/// </summary>
	Stage1* m_stage1 = nullptr;
	/// <summary>
	/// クリアポイント。
	/// </summary>
	ClearPoint* m_Stage1Goal = nullptr;
	ClearPoint* m_Stage2Goal = nullptr;
	Config* m_config = nullptr;
	/// <summary>
	/// エネミー。
	/// </summary>
	Enemy* m_enemyList[5];
	/// <summary>
	/// 落ちる床。
	/// </summary>
	FallingBlock* m_fallingBlock= nullptr;
	/// <summary>
	/// プレイヤー。
	/// </summary>
	Player* m_player = nullptr;
	/// <summary>
	/// ゲーム。
	/// </summary>
	Game* m_game = nullptr;
	/// <summary>
	/// ゲームーバー。
	/// </summary>
	GameOver* m_gameOver = nullptr;
	/// <summary>
	/// ステージクリア。
	/// </summary>
	StageClear* m_stageClear = nullptr;
	/// <summary>
	/// ゲームカメラ。
	/// </summary>
	GameCamera* m_gameCamera = nullptr;
	/// <summary>
	/// ゲームタイマー
	/// </summary>
	GameTimer* m_gameTimer = nullptr;
	/// <summary>
	/// 落下速度の速い床。
	/// </summary>
	HS_FallingBlock* m_HS_FallingBlock = nullptr;
	/// <summary>
	/// 針。
	/// </summary>
	movingNeedle* m_needle = nullptr;
	/// <summary>
	/// 足場ブロック。
	/// </summary>
	Scaffold* m_scaffold = nullptr;
	Scaffold* m_scaffold1 = nullptr;
	/// <summary>
	/// 落下速度の遅い床。
	/// </summary>
	S_MovingFloor* m_s_MovingFloor = nullptr;
	S_MovingFloor* m_s_MovingFloor1 = nullptr;
	S_MovingFloor* m_s_MovingFloor2 = nullptr;
	S_MovingFloor* m_s_MovingFloor3 = nullptr;
	/// <summary>
	/// 動く床。
	/// </summary>
	MovingFloor* m_movingFloor = nullptr;
	MovingFloor* m_movingFloor1 = nullptr;
	MovingFloor* m_movingFloor2 = nullptr;
	/// <summary>
	/// 透明ブロック。
	/// </summary>
	TransparentBlock* m_transparentBlock = nullptr;
	TransparentBlock* m_transparentBlock1 = nullptr;
	TransparentBlock* m_transparentBlock2 = nullptr;
	TransparentBlock* m_transparentBlock3 = nullptr;
	TransparentBlock* m_transparentBlock4 = nullptr;
	TransparentBlock* m_transparentBlock5 = nullptr;
	TransparentBlock* m_transparentBlock6 = nullptr;
	TransparentBlock* m_transparentBlock7 = nullptr;
	TransparentBlock* m_transparentBlock8 = nullptr;
	TransparentBlock* m_transparentBlock9 = nullptr;
	TransparentBlock* m_transparentBlock10 = nullptr;
	TransparentBlock* m_transparentBlock11 = nullptr;
	TransparentWall* m_transparentWall;
	/// <summary>
	/// タオル。
	/// </summary>
	Towel* m_towel = nullptr;
	/// <summary>
	/// タワー。
	/// </summary>
	Tower* m_tower = nullptr;
	/// <summary>
	/// フェード。
	/// </summary>
	Fade* m_fade= nullptr;
	/// <summary>
	/// アイテム類。
	/// </summary>
	ItemEnemy* m_itemenemy = nullptr;// 敵のアイテム。
	Tobeyaki* m_tobeyaki = nullptr;// 砥部焼。
	sinju* m_sinju = nullptr;// 真珠。
	Mikan* m_mikan = nullptr;// みかん。
	Jako* m_jako = nullptr;// じゃこ天。
	Taruto* m_taruto = nullptr;// タルト。
		
	/// <summary>
	/// フォントレンダー。
	/// </summary>
	FontRender m_fontRender;
	ModelRender	m_modelRender;

	PhysicsStaticObject m_physicsStaticObject;
	
	enum Sutaminastate {
		SutaminaMax,
		Sutamina0
	};

	
	/// <summary>
	/// 愛媛県での現在位置を切り替える
	/// </summary>
	/// <param name="enEhimePlace">愛媛県の場所</param>
	void NowEhimePlaceTransition(EnEhimePlace enEhimePlace);
	/// <summary>
	/// ステージ背景の遷移
	/// </summary>
	/// <param name="enEhimePlace">愛媛県の場所</param>
	void StageBackGoundTransition(EnEhimePlace enEhimePlace);
	/// <summary>
	/// スタミナ。
	/// </summary>
	Sutaminastate m_PlayerSutaminaSutate = SutaminaMax;
	/// <summary>
	/// スプライトレンダー。
	/// </summary>
	SpriteRender m_sutaminaMaxrender;
	SpriteRender m_sutamina0render;
	SpriteRender m_mappuRender;
	SpriteRender m_gennzaitiRender;
	SpriteRender m_taorutoriRender;
	SpriteRender m_taorukuroRender;
	SpriteRender m_jakorender;
	SpriteRender m_jakogetrender;
	SpriteRender m_mikanRender;
	SpriteRender m_mikangetRender;
	SpriteRender m_sinjuRender;
	SpriteRender m_sinjugetRender;
	SpriteRender m_ehimePlace[enEhimePlace_Num];//愛媛県の場所
	SpriteRender m_ehimeFamousPlace[enEhimePlace_Num];//愛媛県の名所
	/// <summary>
	/// バックグラウンドレンダー。
	/// </summary>
	BackGroundRender	m_stageBackGround[enEhimePlace_Num];//ステージ背景
	BackGroundRender    m_stageBackGroundTransition[enEhimePlace_Num];//遷移用のステージ背景
	/// <summary>
	/// 座標。
	/// </summary>
	Vector3 m_stageBackGroundTransitionPosition[enEhimePlace_Num];//ステージ背景用の遷移位置
	Vector3 m_stageBackGroundInitPosition;//ステージ背景用の初期位置
	Vector3 m_stageBackGroundCurrentPosition;//ステージ背景用の現在位置
	Vector3 m_stageBackGroundCurrentPositionMemory[enEhimePlace_Num];//各ステージ背景用の現在位置の値を保存する配列
	Vector3 m_stageBackGroundGolePosition;//ステージ背景用のゴール位置
	Vector3 m_stageBackGroundGolePositionMemory[enEhimePlace_Num];//各ステージ背景用のゴール位置の値を保存する配列
	Vector3	m_ehimePlacePosition;//愛媛県の場所の座標
	Vector3	m_ehimeFamousPlacePosition;//愛媛県の名所の座標
	Vector3 m_position;
	Vector3 m_scale = Vector3::One;

	float m_stageBackGroundTransitionAlpha = 1.0f;//遷移用のステージ背景の透明度
	float m_stageBackGroundTransitionFlag = false;//ステージ背景を遷移するか？
	bool drawFlag = true;// 描画フラグ。
	bool m_gameOverFlag = false;// ゲームオーバーフラグ。
	enStageState m_stageState = enStageState_Stage1;//ステージステート

	const char* m_stageBackGroundFilePath = nullptr;// ステージ背景用ファイルパス
	const char* m_ehimePlaceFilePath = nullptr;//愛媛県の場所用ファイルパス
	const char* m_ehimeFamousPlaceFilePath = nullptr;//愛媛県の名所用ファイルパス
};

