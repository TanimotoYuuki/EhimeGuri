#include "stdafx.h"
#include "StairsInTheForest.h"
#include "Config.h"

namespace
{
	const Vector3 SCALE{ 10.0f, 10.0f, 10.0f };// モデルの大きさ。
	const Vector3 COLLISION_HEIGHT(0.0f, 250.0f, 0.0f);// コリジョンの高さ。
	const Vector3 COLLISION_SIZE(500.0f, 3.0f, 225.0f);// コリジョンの大きさ。

}

// 初期化処理。
bool StairsInTheForest::Start()
{
	// LevelObjectのため、Objectごとにファイル分けをしています。
	// → 今まで、使っていた定数化を解除。
	m_modelRender.Init("Assets/modelData/StairsInTheForest/StairsInTheForest.tkm");


	m_modelRender.SetScale(SCALE);// スケールのセット。
	m_modelRender.Update();// モデルの更新。
	m_physicsStaticObject.CreateFromModel// 静的物理オブジェクトの作成。
	(
		m_modelRender.GetModel(),
		m_modelRender.GetModel().GetWorldMatrix()
	);
	m_collisionObject->CreateBox// コリジョンの作成。
	(
		m_position + COLLISION_HEIGHT,
		Quaternion::Identity,
		COLLISION_SIZE
	);
	m_collisionObject->SetIsEnableAutoDelete(false);// コリジョンの破棄。

	return true;
}

// 更新処理。
void StairsInTheForest::Update()
{
	m_modelRender.Update();
}

// 描画処理。	
void StairsInTheForest::Render(RenderContext& rc)
{
	m_modelRender.Draw(rc);
}