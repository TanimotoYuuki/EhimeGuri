#pragma once
#include <string>
#include "FilePathConfig.h"
using namespace std;

class FilePathConfig;

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
	void Render(RenderContext& rc);// 描画処理。

	FilePathConfig* m_filePathConfig;
	ModelRender m_modelRender;// モデルの描画。
	PhysicsStaticObject m_physicsStaticObject;// 静的物理オブジェクト。
	CollisionObject* m_collisionObject = nullptr;// コリジョンオブジェクト。
	Vector3 m_position;// 座標。
	Vector3 m_firstposition;
     
};

