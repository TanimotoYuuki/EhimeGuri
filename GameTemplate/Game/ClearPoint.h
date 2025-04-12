#pragma once
class Player;
class StageClear;
class ClearPoint : public IGameObject
{ 
public:
	ClearPoint();
	~ClearPoint();

	void Update();
	void Render(RenderContext& rc);

	StageClear* m_stageClear;
	Player* m_player;
	ModelRender m_modelRender;
	Vector3     position;

	int clearCount = 0;
};

