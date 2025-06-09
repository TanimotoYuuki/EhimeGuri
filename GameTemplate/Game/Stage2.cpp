#include "stdafx.h"
#include "Stage2.h"
#include "Config.h"
#include "FallingFloor.h"
#include "FallingRocks.h"
#include "MovingNeedle.h"
#include "RotationFloor.h"
#include "Tower.h"
#include "level3DRender.h"
#include "StairsInTheForest.h"
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
	//Configの初期化
	m_filePathConfig = NewGO<Config>(0, "config");

	//モデルの初期化
	m_modelRender.Init("Assets/level3D/Stage2.tkm");
	m_modelRender.SetScale(SCALE);// スケールのセット。

	//レベルオブジェクトのロード
	LevelRender();

	m_modelRender.Update();// モデルの更新。
	m_physicsStaticObject.CreateFromModel
	(
		m_modelRender.GetModel(),
		m_modelRender.GetModel().GetWorldMatrix()
	);

	return true;
}

// 更新処理。
void Stage2::Update()
{
	m_modelRender.Update();// モデルの更新。
}

//レベルの処理。
bool Stage2::LevelRender()
{
	// Levelを構築する。
	m_level3DRender.Init("Assets/level3D/stage2.tkl", [&](LevelObjectData& objData)
	{
		//オブジェクトの位置を設定
		m_position = objData.position;

		// 名前が「FallingFloor」だったら。
		if (objData.ForwardMatchName(L"FallingFloor") == true)
		{
			// 落下床オブジェクトの作成。
			m_fallingFloor = NewGO<FallingFloor>(0, "FallingFloor");
			//座標を設定する。
			m_fallingFloor->SetPosition(m_position);
			return true;
		}

		// 名前が「movingNeedle」だったら。
		else if (objData.EqualObjectName(L"MovingNeedle") == true)
		{
			// 針オブジェクトの作成。
			m_movingNeedle = NewGO<MovingNeedle>(0, "movingneedle");
			// 座標を設定する。
			m_movingNeedle->SetPosition(m_position);
			return true;
		}

		// 名前が「RotationFloor」だったら。
		else if (objData.EqualObjectName(L"RotationFloor") == true)
		{
			// 回転する床オブジェクトの作成。
			m_rotationFloor = NewGO<RotationFloor>(0, "rotationfloor");
			// 座標を設定する。
			m_rotationFloor->SetPosition(m_position);
			return true;
		}

		// 名前が「FallingRocks」だったら。
		else if (objData.ForwardMatchName(L"FallingRocks") == true)
		{
			// 落石のオブジェクト生成。
			m_fallingRocks = NewGO<FallingRocks>(0, "fallingRocks");
			// 座標の設定。
			m_fallingRocks->SetPosition(m_position);
			return true;
		}

		// 名前が「Tower」だったら
		else if (objData.EqualObjectName(L"Tower") == true)
		{
			// タワーのオブジェクト生成。
			m_Tower = NewGO<Tower>(0, "Tower");
			// 座標の設定。
			m_Tower->SetPosition(m_position);
			return true;
		}

		// 名前が「Stairs in the forest」だったら
		else if (objData.EqualObjectName(L"Stairs in the forest") == true)
		{
			m_StairsInTheForest = NewGO<StairsInTheForest>(0, "Stairsintheforest");
			// 座標の設定。
			m_StairsInTheForest->SetPosition(m_position);
			return true;
		}
		return false;
	});
	return true;
}

// 描画処理。
void Stage2::Render(RenderContext& rc)
{
	m_level3DRender.Draw(rc);// レベルの描画。
	m_modelRender.Draw(rc);// モデルの描画。
}