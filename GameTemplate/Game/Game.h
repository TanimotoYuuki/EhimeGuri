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
class ScaffoldBlock;// T型の足場。
class StageClear;// ステージクリア。
class S_MovingFloor;// 動く床(遅)。
class GameOver;// ゲームオーバー。
class GameCamera;// カメラ。
class HS_FallingBlock;	//動く床(速)。
class TransparentBlock;// 透明ブロック。
class Towel;// タオル。
class Fade;// フェード。
class ItemEnemy;// 敵のアイテム。
class Tobeyaki;// 砥部焼。
class sinju;// 真珠。
class Mikan;// みかん。
class Jako;// じゃこ天。
class Taruto;// タルト。
class Checpoint;// 中間地点。

class Game : public IGameObject
{
public:
	Game() {}
	~Game();
	bool Start();
	void Update();// 更新処理。
	void Render(RenderContext& rc);// 描画処理。
		
	void Block_NewGO();// ブロックのNewGO。
	void ClearPoint_NewGO();// クリアポイントのNewGO。
	void TransparentBlock_NewGO();// 透明ブロックのNewGO。
	void FallingBlock_NewGO();// 落ちるブロックのNewGO。
	void MovingFloor_NewGO();// 動く床のNewGO 。
	void Item_NewGO();// アイテムのNewGO。
	void ScaffoldBlock_NewGO();// T字ブロックのNewGO。
	void Scaffold_NewGO();// 足場ブロックのNewGO。
	void S_MovingFloor_NewGO();// 落下速度の遅い床のNewGO。
	void HS_fallingBlock_NewGO();// 落下速度の速い床のNewGO。
	void Fade_NewGO();// FadeのNewGO。

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
	Block* m_block;
	Block* m_block1;
	Block* m_block2;
	Block* m_block3;
	Block* m_block4;
	/// <summary>
	/// 第1ステージ。
	/// </summary>
	Stage1* m_stage1;
	/// <summary>
	/// クリアポイント。
	/// </summary>
	ClearPoint* m_clearPoint;
	Config* m_config;
	/// <summary>
	/// エネミー。
	/// </summary>
	Enemy* m_enemyList[5];
	/// <summary>
	/// 落ちる床。
	/// </summary>
	FallingBlock* m_fallingBlock;
	FallingBlock* m_fallingBlock1;
	FallingBlock* m_fallingBlock2;
	FallingBlock* m_fallingBlock3;
	/// <summary>
	/// プレイヤー。
	/// </summary>
	Player			  * m_player;
	/// <summary>
	/// ゲーム。
	/// </summary>
	Game* m_game;
	/// <summary>
	/// ゲームーバー。
	/// </summary>
	GameOver* m_gameOver;
	/// <summary>
	/// ステージクリア。
	/// </summary>
	StageClear* m_stageClear;
	/// <summary>
	/// ゲームカメラ。
	/// </summary>
	GameCamera* m_gameCamera;
	/// <summary>
	/// 落下速度の速い床。
	/// </summary>
	HS_FallingBlock* m_HS_FallingBlock;
	/// <summary>
	/// 針。
	/// </summary>
	movingNeedle* m_needle;
	/// <summary>
	/// 足場ブロック。
	/// </summary>
	ScaffoldBlock* m_scaffoldBlock;
	Scaffold* m_scaffold;
	Scaffold* m_scaffold1;
	/// <summary>
	/// 落下速度の遅い床。
	/// </summary>
	S_MovingFloor* m_s_MovingFloor;
	S_MovingFloor* m_s_MovingFloor1;
	S_MovingFloor* m_s_MovingFloor2;
	S_MovingFloor* m_s_MovingFloor3;
	/// <summary>
	/// 動く床。
	/// </summary>
	MovingFloor* m_movingFloor;
	MovingFloor* m_movingFloor1;
	MovingFloor* m_movingFloor2;
	/// <summary>
	/// 透明ブロック。
	/// </summary>
	TransparentBlock* m_transparentBlock;
	TransparentBlock* m_transparentBlock1;
	TransparentBlock* m_transparentBlock2;
	TransparentBlock* m_transparentBlock3;
	TransparentBlock* m_transparentBlock4;
	TransparentBlock* m_transparentBlock5;
	TransparentBlock* m_transparentBlock6;
	TransparentBlock* m_transparentBlock7;
	TransparentBlock* m_transparentBlock8;
	TransparentBlock* m_transparentBlock9;
	TransparentBlock* m_transparentBlock10;
	TransparentBlock* m_transparentBlock11;
	/// <summary>
	/// タオル。
	/// </summary>
	Towel* m_towel;
	/// <summary>
	/// フェード。
	/// </summary>
	Fade* m_fade;
	/// <summary>
	/// アイテム類。
	/// </summary>
	ItemEnemy* m_itemenemy;// 敵のアイテム。
	Tobeyaki* m_tobeyaki;// 砥部焼。
	sinju* m_sinju;// 真珠。
	Mikan* m_mikan;// みかん。
	Jako* m_jako;// じゃこ天。
	Taruto* m_taruto;// タルト。
	/// <summary>
	/// チェックポイント。
	/// </summary>
	Checpoint* m_checpoint;
	
	/// <summary>
	/// フォントレンダー。
	/// </summary>
	FontRender m_timerRender;
	FontRender m_fontRender;

	ModelRender         m_backGroundRender;
	ModelRender	        m_modelRender;

	PhysicsStaticObject m_physicsStaticObject;
	
	enum Sutaminastate {
		SutaminaMax,
		Sutamina0
	};

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
	Sutaminastate       m_PlayerSutaminaSutate = SutaminaMax;
	/// <summary>
	/// スプライトレンダー。
	/// </summary>
	SpriteRender        m_sutaminaMaxrender;
	SpriteRender        m_sutamina0render;
	SpriteRender        m_mappuRender;
	SpriteRender        m_gennzaitiRender;
	SpriteRender        m_taorutoriRender;
	SpriteRender        m_taorukuroRender;
	SpriteRender        m_ehimePlace[enEhimePlace_Num];//愛媛県の場所
	SpriteRender		m_ehimeFamousPlace[enEhimePlace_Num];//愛媛県の名所
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

	float m_timer = 180.0f;// タイマー。
	float m_stageBackGroundTransitionAlpha = 1.0f;//遷移用のステージ背景の透明度
	float m_stageBackGroundTransitionFlag = false;//ステージ背景を遷移するか？
	bool drawFlag = true;// 描画フラグ。
	int	m_nowEhimePlace = enEhimePlace_Iyo;//愛媛県での現在位置
	int	m_previousEhimePlace = enEhimePlace_Iyo;//愛媛県での前の位置
	int m_ehimePlaceDrawingUI = enEhimePlace_Iyo;//UI描画用愛媛県の場所
	int m_ehimeFamousPlaceDrawingUI = enEhimePlace_Iyo;//UI描画用愛媛県の名所
	bool m_gameOverFlag = false;// ゲームオーバーフラグ。
	const char* m_stageBackGroundFilePath = nullptr;// ステージ背景用ファイルパス
	const char* m_ehimePlaceFilePath = nullptr;//愛媛県の場所用ファイルパス
	const char* m_ehimeFamousPlaceFilePath = nullptr;//愛媛県の名所用ファイルパス
};

