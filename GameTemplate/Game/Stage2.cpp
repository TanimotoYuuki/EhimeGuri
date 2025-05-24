#include "stdafx.h"
#include "Stage2.h"
#include "Config.h"
#include "FallingFloor.h"
#include "MovingNeedle.h"
#include "RotationFloor.h"
#include "level3DRender.h"
#include <string>
using namespace std;

namespace
{
	const Vector3 SCALE{ 10.0f, 10.0f, 10.0f };// モデルの大きさ。
	const Vector3 COLLISION_HEIGHT(0.0f, 250.0f, 0.0f);// コリジョンの高さ。
	const Vector3 COLLISION_SIZE(500.0f, 3.0f, 225.0f);// コリジョンの大きさ。
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

// レベルの処理。
// → playerのLevel処理を書く際、必要な部分のみコメントアウトを解除してください。　
//bool Stage2::LevelRender()
//{
//	// Levelを構築する。
//	m_level3DRender.Init("stage2.tkl", [&](LevelObjectData& objData)
//	{
//			///////////////////////////////
//			///if分でplayerのLevelを追加///
//			///////////////////////////////
//
//
//			// 名前が「FallingFloor」だったら
//			else if (objData.EqualObjectName(L"FallingFloor") == true)
//			{
//				// 落下床オブジェクトの作成。
//				m_fallingFloor = NewGO<FallingFloor>(0,"FallingFloor");
//				//座標を設定する。
//				m_fallingFloor->SetPosition(m_position);
//				return true;
//			}
//
//			// 名前が「movingNeedle」だったら
//			else if (objData.EqualObjectName(L"movingNeedle") == true)
//			{
//				// 針オブジェクトの作成。
//				m_movingNeedle = NewGO<MovingNeedle>(0, "movingneedle");
//				// 座標を設定する。
//				m_movingNeedle->SetPosition(m_position);
//				return true;
//			}
//
//			// 名前が「RotationFloor」だったら
//			else if (objData.EqualObjectName(L"RotationFloor") == true)
//			{
//				// 回転する床オブジェクトの作成。
//				m_rotationFloor = NewGO<RotationFloor>(0, "rotationfloor");
//				// 座標を設定する。
//				m_rotationFloor->SetPosition(m_position);
//				return true;
//			}
//			return true;
//	});
//}

// 描画処理。
void Stage2::Render(RenderContext& rc)
{
	m_level3DRender.Draw(rc);// レベルの描画。
	m_modelRender.Draw(rc);// モデルの描画。
}