#pragma once

namespace nsK2EngineLow
{
	class IRenderer : public Noncopyable
	{
	public:
		/// <summary>
		/// モデルの描画
		/// </summary>
		/// <param name="rc"></param>
		virtual void OnRenderModel(RenderContext& rc)
		{

		}

		/// <summary>
		/// シャドウマップの描画
		/// </summary>
		/// <param name="rc"></param>
		/// <param name="ca"></param>
		virtual void OnRenderShadowMap(RenderContext& rc, Camera& ca)
		{

		}

		/// <summary>
		/// 2Dの描画
		/// </summary>
		/// <param name="rc"></param>
		virtual void OnRender2D(RenderContext& rc)
		{

		}
	};
}

