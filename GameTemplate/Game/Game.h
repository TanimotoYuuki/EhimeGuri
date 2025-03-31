#pragma once
class Player;
class Block;
class BackGround;
class ClearBlock;
class Enemy;
class FallingBlock;
class Needle;
class MovingFloor;
class ScaffoldBlock;
class GameOver;
class GameCamera;
class Enemy;
class TransparentBlock;
class Game : public IGameObject
{
public:
	Game() {}
	~Game() {}
	bool Start();
	void Update();
	void Render(RenderContext& rc);
		
	void TransparentBlock_NewGO();	
	void FallingBlock_NewGO();
	void ScaffoldBlock_NewGO();
	void Needle_NewGO();
	void MovingFloor_NewGO();
	void Block_NewGo();
private:
	Block             * m_block;
	BackGround		  * m_backGround;
	ClearBlock		  * m_clearBlock;
	Enemy			  * m_enemyList[1];
	FallingBlock	  * m_fallingBlock;
	FallingBlock      * m_fallingBlock1;
	FallingBlock      * m_fallingBlock2;
	Player			  * m_player;
	Game		      * m_game;
	GameOver          * m_gameOver;
	GameCamera        * m_gameCamera;
	Needle		      * m_needle;
	ScaffoldBlock     * m_scaffoldBlock;
	MovingFloor       * m_movingFloor;
	TransparentBlock  * m_transparentBlock;
	TransparentBlock  * m_transparentBlock1;

	ModelRender         m_backGroundRender;
	ModelRender	        m_modelRender;
	Vector3		        m_position;
	FontRender          m_fontRender;
	PhysicsStaticObject m_physicsStaticObject;
	

	enum Sutaminastate {
		SutaminaMax,
		Sutamina0
	};

	Sutaminastate       m_PlayerSutaminaSutate = SutaminaMax;
	SpriteRender        m_sutaminaMaxrender;
	SpriteRender        m_sutamina0render;
	FontRender          m_timerRender;
	Vector3             m_scale = Vector3::One;
	float               m_timer = 180.0f;
	bool                drawFlag = true;
};

