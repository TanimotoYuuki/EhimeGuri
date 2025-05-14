#pragma once
class Player;
class FilePathConfig;
class Checpoint:public IGameObject
{
public:
	bool Start();
	void Update();
	void Render(RenderContext& rc);

	Player* m_player;
	ModelRender m_modelRender;
	Vector3	position;
	FilePathConfig* m_filePathConfig;

	
};

