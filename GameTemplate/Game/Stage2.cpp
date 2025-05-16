#include "stdafx.h"
#include "Stage2.h"
#include "Config.h"
#include <string>
using namespace std;

namespace
{
	Vector3 SCALE = Vector3{ 10.0f, 10.0f, 10.0f };// モデルの大きさ。
	Vector3 COLLISION_HEIGHT = Vector3(0.0f, 250.0f, 0.0f);// コリジョンの高さ。
	Vector3 COLLISION_SIZE = Vector3(500.0f, 3.0f, 225.0f);// コリジョンの大きさ。
}

bool Stage2::Start()
{ 
	string modelPath = m_filePathConfig->GetFullPath_3DModel("Stage2");// ファイルパスを読み込む。
	m_modelRender.Init(modelPath.c_str());// モデルをセットする。


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
	m_firstposition = m_position;
	return true;
}

// 更新処理。
void Stage2::Update()
{
	m_modelRender.Update();// モデルの更新。
	m_physicsStaticObject.SetPosition(m_position);
	m_collisionObject->SetPosition(m_position + COLLISION_HEIGHT);
}

// 描画処理。
void Stage2::Render(RenderContext& rc)
{
	m_modelRender.Draw(rc);// モデルの描画。
}