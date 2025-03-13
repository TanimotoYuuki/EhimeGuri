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
	BackGround  * m_background;
	Player		* m_player;
	GameCamera  * m_gamecamera;
	
	ModelRender   m_backGroundRender;
};

