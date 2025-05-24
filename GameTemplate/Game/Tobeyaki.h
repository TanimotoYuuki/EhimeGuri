#pragma once
using namespace std;

class Player;
class Config;
class Tobeyaki:public IGameObject
{
public:
	/// <summary>
	/// 砥部焼。
	/// 第2ステージ専用モデル 兼 LevelObject。
	/// </summary>
	bool Start();
	void Update();
	void Rotation();
	void Render(RenderContext& rc);

	void SetPosition(const Vector3 position)
	{
		m_position = position;
	}
	Config* m_config;
	ModelRender m_modelRender;
	Vector3 m_position;
	Vector3 m_firstposition;
	Quaternion m_rotation;
	Player* m_player;
};

