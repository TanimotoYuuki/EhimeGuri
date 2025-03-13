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
	BackGround  * background;
	Player		* player;
	GameCamera  * gamecamera;
	
	ModelRender   backGroundRender;
};

