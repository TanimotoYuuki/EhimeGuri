#pragma once

namespace nsK2EngineLow
{
	class BackGroundRender : public IRenderer
	{
	public:
		/// <summary>
		/// 初期化
		/// </summary>
		/// <param name="filePath">ファイルパス</param>
		/// <param name="w">画像の横幅</param>
		/// <param name="h">画像の縦幅</param>
		void Init(const char* filePath);

		/// <summary>
		/// 更新処理
		/// </summary>
		void Update();

		/// <summary>
		/// 描画処理
		/// </summary>
		/// <param name="rc">レンダーコンテキスト</param>
		void Draw(RenderContext& rc);


	private:

		/// <summary>
		/// 背景の描画
		/// </summary>
		/// <param name="rc"></param>
		void OnRenderBackGround(RenderContext& rc) override
		{
			m_sprite.Draw(rc);
		}

		Sprite			m_sprite;	//スプライト
	};
}

