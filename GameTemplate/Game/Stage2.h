#pragma once
#include "FallingFloor.h"

#include <string>
#include "Config.h"
#include "Level3DRender.h"

using namespace std;

class Config;
class FallingFloor;
class MovingNeedle;
class RotationFloor;
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
	Stage2* m_stage2 = nullptr;// ステージ2
	Config* m_filePathConfig = nullptr;// ファイルパス。
	FallingFloor* m_fallingFloor = nullptr;// 落下する床。
	MovingNeedle* m_movingNeedle = nullptr;// 動く針。
	RotationFloor* m_rotationFloor = nullptr;// 回転する床

private:
	ModelRender m_modelRender;// モデルの描画。
	PhysicsStaticObject m_physicsStaticObject;// 静的物理オブジェクト。
	CollisionObject* m_collisionObject = nullptr;// コリジョンオブジェクト。
	Vector3 m_position;// 座標。
	Vector3 m_firstposition;
     
	Level3DRender m_level3DRender;// レベル3Dレンダー。
};

