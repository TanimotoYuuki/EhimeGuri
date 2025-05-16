#pragma once
using namespace std;

class Player;
class StageClear;
class Config;
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

	int clearCount = 0;
	bool m_stageClearFlag = false;
};

