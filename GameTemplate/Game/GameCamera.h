#pragma once
class Player;
class GameCamera :public IGameObject
{
public:
	GameCamera();
	~GameCamera();
	bool Start();
	void Update();

	void SetTarget(Player* player) { m_player = player; }

	Player* m_player;
	Vector3 m_toCameraPos;
};

