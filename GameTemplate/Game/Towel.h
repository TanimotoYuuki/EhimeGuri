#pragma once
class Player;
class Towel : public IGameObject
{
public:
	
	/// <summary>
	/// タオル … アイテムのひとつ。
	/// </summary>
	Towel() {};
	~Towel() {};

	bool Start();
	void Update();// 更新作業。
	void Rotation();// 回転処理。
	void Render(RenderContext& rc);// 描画処理。

	/// <summary>
	/// 座標の設定。
	/// </summary>
	void SetPosition(const Vector3 position)
	{
		m_position = position;
	}
		
	ModelRender m_modelRender;
	Vector3 m_position;
	Vector3 m_firstposition;
	Quaternion m_Rot;
	Player* m_player;
};

