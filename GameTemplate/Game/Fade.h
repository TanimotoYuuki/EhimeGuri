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
			//フェードを切り替えたか判定するフラグをfalseにする
			m_fadeTransitionFlag = false;
		}

		//フェードステートがフェードインのとき
		if (m_fadeState == enFadeState_FadeIn)
		{
			//ローディングをしない
			m_loadingFlag = false;
		}
		//フェードステートがフェードアウトのとき
		else if (m_fadeState == enFadeState_FadeOut)
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

	/// <summary>
	/// フェードインが終わったかどうか?
	/// </summary>
	/// <returns>trueならフェードインが終わった</returns>
	bool IsFadeInFinish() const
	{
		return m_isFadeInFinish;
	}
	Sprite m_sprite;								//スプライト

private:

	//点
	enum EnPoint
	{
		enPoint_Left,		//左
		enPoint_Center,		//真ん中
		enPoint_Right,		//右
		enPoint_Num			//点の数
	};

	/// <summary>
	/// ローディングの動作用の初期化
	/// </summary>
	void InitLoadingMove()
	{
		//点の現在位置を初期位置に戻す
		for (int i = 0; i < enPoint_Num; i++)
		{
			m_pointPosition[i] = m_pointInitPosition[i];
			m_point[i].SetPosition(m_pointPosition[i]);
			m_point[i].Update();
		}

		//点動作を左にする
		m_pointMove = enPoint_Left;

		//点落下をしない
		m_pointFallFlag = false;
	}

	SpriteRender m_spriteRender;
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
	bool m_isFadeInFinish = false;					//フェードインが終わったか?

	const char* GetFilePath(const std::string spriteName);


};

