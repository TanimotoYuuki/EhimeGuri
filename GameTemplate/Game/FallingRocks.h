#pragma once
using namespace std;

class Config;
class FallingRocks : public IGameObject
{
public:
	/// <summary>
	/// 落石。
	/// 第2ステージ専用モデル 兼 LevelObject。 
	/// </summary>
	FallingRocks() {};
	~FallingRocks() {};

	bool Start();
	void Update();
	void Move();
	void Render(RenderContext& rc);

	/// <summary>
	/// ファイルパス。
	/// </summary>
	Config* m_config = nullptr;

	/// <summary>
	/// モデル。
	/// </summary>
	ModelRender m_modelRender;

	/// <summary>
    /// 座標のセット。
    /// </summary>
	void SetPosition(const Vector3 position)
	{
		m_position = position;
	}
	/// <summary>
	/// 座標を取得。
	/// </summary>
	const Vector3& GetPosition()const
	{
		return m_position;
	}
	
	Vector3 m_position;


private:
	Vector3 position;// 現在位置。
	Vector3 velocity;// 現在速度。
	Vector3 gravity; // 重力加速度。
};

