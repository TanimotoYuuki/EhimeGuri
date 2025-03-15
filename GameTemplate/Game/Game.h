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
};

