#pragma once
#include "FallingFloor.h"

#include <string>
#include "Config.h"
#include "Level3DRender.h"

using namespace std;

class Config;
class Tower;
class FallingFloor;
class Player;
class MovingNeedle;
class RotationFloor;
class StairsInTheForest;
class FallingRocks;
class Lever;
class Stage2 : public IGameObject
{
public:
	/// <summary>
	/// 2ステージ目
	/// </summary>
	Stage2() {};
	~Stage2() {};

	bool Start();
	void Update();// 更新処理。
//	bool LevelRender();// レベルの処理。
	void Render(RenderContext& rc);// 描画処理。
	

	/// <summary>
	/// LevelObject。
	/// </summary>
private:
	Stage2* m_stage2 = nullptr;// ステージ2
	Player* m_player = nullptr;
	Config* m_filePathConfig = nullptr;// ファイルパス。
	FallingRocks* m_fallingRocks = nullptr;
	FallingFloor* m_fallingFloor = nullptr;// 落下する床。
	MovingNeedle* m_movingNeedle = nullptr;// 動く針。
	RotationFloor* m_rotationFloor = nullptr;// 回転する床
	StairsInTheForest* m_StairsInTheForest;
	Tower* m_Tower = nullptr;


	ModelRender m_modelRender;// モデルの描画。
	PhysicsStaticObject m_physicsStaticObject;// 静的物理オブジェクト。
	CollisionObject* m_collisionObject = nullptr;// コリジョンオブジェクト。
	Vector3 m_position;// 座標。
	Vector3 m_firstposition;
     
	Level3DRender m_level3DRender;// レベル3Dレンダー。
};

