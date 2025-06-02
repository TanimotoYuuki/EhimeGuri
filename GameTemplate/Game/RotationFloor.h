#pragma once
class RotationFloor : public IGameObject
{
public:
	RotationFloor() {};
	~RotationFloor() {};

	bool Start();
	void Update();
	void Render(RenderContext& rc);
	void Rotation();
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
};

