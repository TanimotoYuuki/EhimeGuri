#pragma once

class Player;						//プレイヤー
class Block;						//ブロック
class BackGround;					//ステージ		
class Enemy;						//エネミー
class ClearPoint;                   //クリアポイント
class FallingBlock;					//落ちる床
class Needle;						//針
class MovingFloor;					//移動する床
class Scaffold;						//足場
class ScaffoldBlock;				//T型の足場
class StageClear;					//ステージクリア
class S_MovingFloor;				//動く床(遅)
class GameOver;						//ゲームオーバー
class GameCamera;					//カメラ
class HS_FallingBlock;				//動く床(速)
class TransparentBlock;				//透明ブロック
class Towel;                        //タオル
class Fade;							//フェード
class ItemEnemy;
class Tobeyaki;
class sinju;
class Mikan;
class Jako;
class Taruto;

class Game : public IGameObject
{
public:
	Game() {}
	~Game();
	bool Start();
	void Update();
	void Render(RenderContext& rc);
		
	void Block_NewGO();
	void ClearPoint_NewGO();
	void TransparentBlock_NewGO();	
	void FallingBlock_NewGO();
	void MovingFloor_NewGO();
	void Needle_NewGO();
	void Item_NewGO();
	void ScaffoldBlock_NewGO();
	void Scaffold_NewGO();
	void S_MovingFloor_NewGO();
	void HS_fallingBlock_NewGO();
	void Fade_NewGO();

//	void InitSky();
	
private:
	/// <summary>
	/// 現在の愛媛県の場所を設定する
	/// </summary>
	/// <param name="nowPos">現在位置</param>
	void SetNowEhimePlace(const Vector3& pos);

	/// <summary>
	/// 愛媛県の場所のスプライトの情報を取得
	/// </summary>
	/// <param name="place">場所</param>
	void GetEhimePlaceSpriteData(int place)
	{
		//場所
		switch (place)
		{
		case enEhimePlace_Iyo:				//伊予市
			m_ehimePlaceFilePath = "Assets/Sprite/background/text/1stage/place/iyo.dds";
			m_ehimePlacePosition = Vector3(280.0f, 360.0f, 0.0f);
			break;
		case enEhimePlace_Ooze:				//大洲市
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
	/// <param name="place">名所</param>
	void GetEhimeFamousPlaceSpriteData(int famousplace)
	{
		//名所
		switch (famousplace)
		{
		case enEhimePlace_Iyo:				//伊予市
			m_ehimeFamousPlaceFilePath = "Assets/Sprite/background/text/1stage/famousplace/simonagi.dds";
			m_ehimeFamousPlacePosition = Vector3(400.0f, 360.0f, 0.0f);
			break;
		case enEhimePlace_Ooze:				//大洲市
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

	Block             * m_block;
	Block             * m_block1;
	Block             * m_block2;
	Block             * m_block3;
	Block             * m_block4;
	BackGround		  * m_backGround;
	ClearPoint        * m_clearPoint;
	Enemy			  * m_enemyList[5];
	FallingBlock	  * m_fallingBlock;
	FallingBlock      * m_fallingBlock1;
	FallingBlock      * m_fallingBlock2;
	FallingBlock      * m_fallingBlock3;

	Player			  * m_player;
	Game		      * m_game;
	GameOver          * m_gameOver;
	GameCamera        * m_gameCamera;
	HS_FallingBlock   * m_HS_FallingBlock;
	Needle		      * m_needle;
	Needle			  * m_needle1;
	Needle			  * m_needle2;
	Needle            * m_needle3;

	ScaffoldBlock     * m_scaffoldBlock;
	Scaffold		  * m_scaffold;
	Scaffold		  * m_scaffold1;
	StageClear        * m_stageClear;
	S_MovingFloor	  * m_s_MovingFloor;
	S_MovingFloor     * m_s_MovingFloor1;
	S_MovingFloor	  * m_s_MovingFloor2;
	S_MovingFloor	  * m_s_MovingFloor3;


	MovingFloor       * m_movingFloor;
	MovingFloor       * m_movingFloor1;
	MovingFloor       * m_movingFloor2;


	TransparentBlock  * m_transparentBlock;
	TransparentBlock  * m_transparentBlock1;
	TransparentBlock  * m_transparentBlock2;
	TransparentBlock  * m_transparentBlock3;
	TransparentBlock  * m_transparentBlock4;
	TransparentBlock  * m_transparentBlock5;
	TransparentBlock  * m_transparentBlock6;
	TransparentBlock  * m_transparentBlock7;
	TransparentBlock  * m_transparentBlock8;
	TransparentBlock  * m_transparentBlock9;
	TransparentBlock  * m_transparentBlock10;
	TransparentBlock  * m_transparentBlock11;
	Towel             * m_towel;
	Fade			  * m_fade;

	FontRender          m_timerRender;
	FontRender          m_fontRender;

	ItemEnemy*          m_itemenemy;
	Tobeyaki*           m_tobeyaki;
	sinju*              m_sinju;
	Mikan*              m_mikan;
	Jako*               m_jako;
	Taruto* m_taruto;
	ModelRender         m_backGroundRender;
	ModelRender	        m_modelRender;
	Vector3		        m_position;
	Vector3             m_scale = Vector3::One;

	PhysicsStaticObject m_physicsStaticObject;
	

	enum Sutaminastate {
		SutaminaMax,
		Sutamina0
	};

	//愛媛県の場所
	enum EnEhimePlace
	{
		enEhimePlace_Iyo,				//伊予市
		enEhimePlace_Ooze,				//大洲市
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

	Sutaminastate       m_PlayerSutaminaSutate = SutaminaMax;
	SpriteRender        m_sutaminaMaxrender;
	SpriteRender        m_sutamina0render;
	SpriteRender        m_mappuRender;
	SpriteRender        m_gennzaitiRender;
	SpriteRender        m_taorutoriRender;
	SpriteRender        m_taorukuroRender;
	SpriteRender        m_ehimePlace[enEhimePlace_Num];
	SpriteRender		m_ehimeFamousPlace[enEhimePlace_Num];
	BackGroundRender	m_stageBackGround;
	Vector3				m_ehimePlacePosition;
	Vector3				m_ehimeFamousPlacePosition;
	float               m_timer = 180.0f;
	bool                drawFlag = true;
	int					m_nowEhimePlace = enEhimePlace_Iyo;
	bool                m_gameOverFlag = false;
	const char* m_ehimePlaceFilePath = nullptr;
	const char* m_ehimeFamousPlaceFilePath = nullptr;
};

