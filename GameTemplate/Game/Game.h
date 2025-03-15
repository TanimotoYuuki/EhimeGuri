#pragma once
class Player;
class BackGround;
class MovingFloor;
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
	GameCamera  * m_gameCamera;
	MovingFloor * m_movingFloor;
	ModelRender   m_backGroundRender;
	ModelRender	  m_modelRender;
	Vector3		  m_position;
	FontRender m_fontRender;

	enum Sutaminastate {
		SutaminaMax,
		Sutamina0
	};

	Sutaminastate m_PlayerSutaminaSutate = SutaminaMax;
	SpriteRender SutaminaMaxrender;
	SpriteRender Sutamina0render;
	Vector3 m_scale = Vector3::One;
};

