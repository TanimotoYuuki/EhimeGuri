#pragma once
class Player;
class BackGround;
class Needle;
class MovingFloor;
class GameOver;
class GameCamera;
class Game : public IGameObject
{
public:
	Game() {}
	~Game() {}
	bool Start();
	void Update();
	void Render(RenderContext& rc);

	
private:
	BackGround  * m_backGround;
	Player		* m_player;
	Game		* m_game;
	GameOver	* m_gameOver;
	GameCamera  * m_gameCamera;
	Needle		* m_needle;
	MovingFloor * m_movingFloor;
	ModelRender   m_backGroundRender;
	ModelRender	  m_modelRender;
	Vector3		  m_position;
	FontRender    m_fontRender;
	PhysicsStaticObject	m_physicsStaticObject;
	enum Sutaminastate {
		SutaminaMax,
		Sutamina0
	};

	Sutaminastate m_PlayerSutaminaSutate = SutaminaMax;
	SpriteRender m_sutaminaMaxrender;
	SpriteRender m_sutamina0render;
	FontRender m_timerRender;
	Vector3 m_scale = Vector3::One;
	float m_timer = 10.0f;
};

