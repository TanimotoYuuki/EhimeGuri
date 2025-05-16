#pragma once
using namespace std;

class Player;
class Config;
class Checpoint:public IGameObject
{
public:
	bool Start();
	void Update();
	void Render(RenderContext& rc);

	Player* m_player;
	ModelRender m_modelRender;
	Vector3	position;
	Config* m_config;

	
};

