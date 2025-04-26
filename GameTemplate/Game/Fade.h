#pragma once
class Fade : public IGameObject
{
public:
	bool Start();
	void Update();
	void Render(RenderContext& rc);

	/// <summary>
	/// ローディングの動作
	/// </summary>
	void LoadingMove();

	/// <summary>
	/// フェードを切り替える
	/// </summary>
	void FadeTransition(EnFadeState enFadeState)
	{
		//フェードステートが異なっているとき
		if (m_fadeState != enFadeState)
		{
			m_fadeState = enFadeState;
			m_fade.SetFadeTransition(enFadeState);
			m_fadeTransitionFlag = false;
		}

		if (m_fadeState == enFadeState_FadeOut)
		{
			if (m_loadingFlag != true)
			{
				if (g_gameTime->StopWatch(2.0f))
				{
					m_loadingFlag = true;
				}
			}
			else
			{
				m_fadeState = enFadeState_Loading;
				m_fade.SetFadeTransition(enFadeState_Loading);
			}
		}
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

	SpriteRender m_fade;						//フェード
	SpriteRender m_loading;						//ローディング
	SpriteRender m_point[enPoint_Num];			//点
	Vector3 m_pointInitPosition[enPoint_Num];	//点の初期位置
	Vector3 m_pointPosition[enPoint_Num];		//点の現在位置
	int m_fadeState = enFadeState_FadeIn;		//フェードステート
	int m_pointMove = enPoint_Left;				//点動作
	bool m_loadingFlag = false;					//ローディングフラグ
	bool m_pointFallFlag = false;				//点落下フラグ
	bool m_fadeTransitionFlag = false;			//フェードが切り替わったか?
};

