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
class Signboard;					//看板
class StageClear;
class GameOver;						//ゲームオーバー
class GameCamera;					//カメラ
class HS_FallingBlock;				//落下速度の速い床
class TransparentBlock;				//透明ブロック
class Towel;                        //タオル
class Fade;							//フェード
class Game : public IGameObject
{
public:
	Game() {}
	~Game() {}
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
	void Signboard_NewGO();
	void Scaffold_NewGO();
	void HS_fallingBlock_NewGO();
	void Fade_NewGO();
	

//	void InitSky();
	
private:
	Block             * m_block;
	BackGround		  * m_backGround;
	ClearPoint        * m_clearPoint;
	Enemy			  * m_enemyList[4];
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
	Signboard         * m_signboard;
	StageClear        * m_stageClear;
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

	ModelRender         m_backGroundRender;
	ModelRender	        m_modelRender;
	Vector3		        m_position;
	Vector3             m_scale = Vector3::One;

	PhysicsStaticObject m_physicsStaticObject;
	

	enum Sutaminastate {
		SutaminaMax,
		Sutamina0
	};

	Sutaminastate       m_PlayerSutaminaSutate = SutaminaMax;
	SpriteRender        m_sutaminaMaxrender;
	SpriteRender        m_sutamina0render;
	SpriteRender        m_mappuRender;
	SpriteRender        m_gennzaitiRender;
	SpriteRender        m_taorutoriRender;
	SpriteRender        m_taorukuroRender;
	//	SkyCube* m_SkyCube = nullptr; //背景
	//	int m_skycubeType = enSkyCubeType_NightToon;
	float               m_timer = 180.0f;
	bool                drawFlag = true;
};

