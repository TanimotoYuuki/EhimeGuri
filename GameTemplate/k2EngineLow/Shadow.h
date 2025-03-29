#pragma once

namespace nsK2EngineLow
{
	class Shadow
	{
	public:
		/// <summary>
		/// 初期化
		/// </summary>
		void Init();

		/// <summary>
		/// 描画処理を実行
		/// </summary>
		/// <param name="rc"></param>
		/// <param name="roj"></param>
		void Execute(RenderContext& rc, std::vector<IRenderer*>& ro);

		/// <summary>
		/// シャドウマップを取得
		/// </summary>
		/// <returns></returns>
		RenderTarget& GetRenderTarget()
		{
			return m_shadowMap;
		}

	private:

		RenderTarget m_shadowMap;
	};
}

