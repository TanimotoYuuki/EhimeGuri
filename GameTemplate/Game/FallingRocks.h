#pragma once
class Config;
class FallingRocks : public IGameObject
{
public:
	/// <summary>
	/// 落石。
	/// </summary>
	FallingRocks();
	~FallingRocks() {};

	bool Start();
	void Update();
	void Move();
	void Render(RenderContext& rc);

	/// <summary>
	/// ファイルパス。
	/// </summary>
	Config* m_filePathConfig;

	/// <summary>
	/// モデル。
	/// </summary>
	ModelRender m_modelRender;

private:
	Vector3 position;// 現在位置。
	Vector3 velocity;// 現在速度。
	Vector3 gravity; // 重力加速度。
};

