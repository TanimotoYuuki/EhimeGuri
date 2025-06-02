#pragma once
class Config;
class FallingFloor : public IGameObject
{
public:
	/// <summary>
	/// 落下する床。
	/// 第2ステージ専用モデル 兼 LevelObject。 
	/// </summary>
	FallingFloor() {};
	~FallingFloor() {};


	bool Start();
	void Update();// 更新処理。
	void Floor();// 落下処理。
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
private:
	Config* m_filePathConfig = nullptr;
	ModelRender m_modelRender;// モデル。
	Vector3 m_position;

};

