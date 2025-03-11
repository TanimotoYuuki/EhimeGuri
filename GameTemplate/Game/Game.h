#pragma once
class Player;
class BackGround;
class Game : public IGameObject
{
public:
	Game() {}
	~Game() {}
	bool Start();
	void Update();

private:
	BackGround* background;
	Player* player;
};

