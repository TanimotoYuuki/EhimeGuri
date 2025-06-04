#pragma once
class Config;
class StairsInTheForest : public IGameObject
{
public:
	StairsInTheForest() {};
	~StairsInTheForest() {};

	bool Start();// 初期化処理。
	void Update();// 更新処理。
	void Render(RenderContext& rc);// 描画処理。

	/// <summary>
    /// 座標のセット 
    /// </summary>
	void SetPosition(const Vector3 position)
	{
		m_position = position;
	}

	/// <summary>
	/// 座標を取得
	/// </summary>
	const Vector3& GetPosition()const
	{
		return m_position;
	}

	Vector3 m_position;

	Config* m_filePathConfig = nullptr;
	CollisionObject* m_collisionObject = nullptr;
private:
	ModelRender m_modelRender;
	PhysicsStaticObject m_physicsStaticObject;
	
};

