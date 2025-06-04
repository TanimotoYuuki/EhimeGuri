#pragma once
#include "Scene.h"
#include "GameClear.h"
using namespace std;


class Player;
class StageClear;
class Config;
class Stage1Scene;
class GameClear;
class ClearPoint : public IGameObject
{ 
public:
	/// <summary>
    /// クリアポイント
    /// </summary>

	ClearPoint();
	~ClearPoint() {};

	void Update();// 更新作業。
	void StageClear_NewGO();
	void Render(RenderContext& rc);// 描画処理。

	Config* m_config = nullptr;
	StageClear* m_stageClear;
	Player* m_player = nullptr;
	ModelRender m_modelRender;
	Vector3	position;
	Stage1Scene* m_stage1Scene = nullptr;
	GameClear* m_gameClear = nullptr;
	int clearCount = 0;


	// ゲームクリアフラグを取得
	void SetIsClrar(bool clear)
	{
		isClear = clear;
	}

	bool GetIsClear() const
	{
		return isClear;
	}
	bool isClear = false; // ゲームクリアフラグ


};

