#pragma once
/// <summary>
/// フェード
/// </summary>
class Fade : public IGameObject
{
public:
	bool Start();	//開始処理
	void Update();	//更新処理
	void Render(RenderContext& rc);  //描画処理

	/// <summary>
	/// ローディングの動作
	/// </summary>
	void LoadingMove();

	/// <summary>
	/// フェードを切り替える
	/// </summary>
	void FadeTransition(EnFadeState enFadeState)
	{
		//フェードステートが異なっているときはフェードステートを切りえる
		if (m_fadeState != enFadeState)
		{
			//フェードステートの切り替え
			m_fadeState = enFadeState;
			m_fade.SetFadeTransition(enFadeState);
			//ローディングをしない
			m_fadeTransitionFlag = false;
		}

		//フェードステートがフェードアウトのとき
		if (m_fadeState == enFadeState_FadeOut)
		{
			//ローディングフラグが立っていないとき
			if (m_loadingFlag != true)
			{
				//2.0秒経過したらローディング画面に遷移する
				if (g_gameTime->StopWatch(2.0f))
				{
					//ローディングをする
					m_loadingFlag = true;
				}
			}
			else
			{
				//フェードステートをローディングに切り替える
				m_fadeState = enFadeState_Loading;
				m_fade.SetFadeTransition(enFadeState_Loading);
			}
		}
	}

	/// <summary>
	/// フェードステートの取得。
	/// </summary>
	/// <returns>フェードステート</returns>
	int GetFadeState() const
	{
		return m_fadeState;
	}

	/// <summary>
	/// フェード用のスプライトの取得。
	/// </summary>
	/// <returns>フェード用スプライト</returns>
	SpriteRender& GetFadeSprite()
	{
		return m_fade;
	}

private:

	//点
	enum EnPoint
	{
		enPoint_Left,		//左
		enPoint_Center,		//真ん中
		enPoint_Right,		//右
		enPoint_Num			//点の数
	};

	SpriteRender m_fade;							//フェード
	SpriteRender m_loading;							//ローディング
	SpriteRender m_point[enPoint_Num];				//点
	Vector3 m_pointInitPosition[enPoint_Num];		//点の初期位置
	Vector3 m_pointPosition[enPoint_Num];			//点の現在位置
	EnFadeState m_fadeState = enFadeState_FadeIn;	//フェードステート
	int m_pointMove = enPoint_Left;					//点動作
	bool m_loadingFlag = false;						//ローディングフラグ
	bool m_pointFallFlag = false;					//点落下フラグ
	bool m_fadeTransitionFlag = false;				//フェードが切り替わったか?
};

