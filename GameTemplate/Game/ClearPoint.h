#pragma once
#include "Scene.h"
using namespace std;


class Player;
class StageClear;
class Config;
class Stage1Scene;
class ClearPoint : public IGameObject
{ 
public:
	/// <summary>
    /// クリアポイント
    /// </summary>

	ClearPoint();
	~ClearPoint() {};

	void Update();// 更新作業。
	void Render(RenderContext& rc);// 描画処理。

	Config* m_config;
	StageClear* m_stageClear;
	Player* m_player;
	ModelRender m_modelRender;
	Vector3	position;
	Stage1Scene* m_stage1Scene;

	int clearCount = 0;
};

