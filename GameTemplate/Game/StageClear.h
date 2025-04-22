#pragma once
class Player;

class StageClear : public IGameObject
{
public:
	bool Start();
	void Update();

	void Render(RenderContext& rc);
private:
	/// <summary>
	/// ステージクリアスプライト用のイージングを設定
	/// </summary>
	void SetStageClearSpriteEasing();
	/// <summary>
	/// ステージクリアスプライト用のイージングの更新処理
	/// </summary>
	void UpdateStageClearSpriteEasing();

	SpriteRender		m_stageClearUI;												//ステージクリアUI
	Vector3				m_position = Vector3(-1100.0f, 275.0f, 0.0f);				//位置
	Vector3				m_beforeEasingPosition;										//イージング前の位置
	Vector3				m_afterEasingPosition;										//イージング後の位置
	float               m_easingTime = 0.0f;										//割合
	bool                m_gameClearRenditionFinishFlag = false;						//ゲームクリア演出終了フラグ
	Player*				m_player;													//プレイヤー用のインスタンス
};

