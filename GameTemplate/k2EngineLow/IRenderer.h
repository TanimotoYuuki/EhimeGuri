#pragma once

namespace nsK2EngineLow
{
	class IRenderer : public Noncopyable
	{
	public:
		/// <summary>
		/// ƒ‚ƒfƒ‹‚Ì•`‰æ
		/// </summary>
		/// <param name="rc"></param>
		virtual void OnRenderModel(RenderContext& rc)
		{

		}

		/// <summary>
		/// ƒVƒƒƒhƒEƒ}ƒbƒv‚Ì•`‰æ
		/// </summary>
		/// <param name="rc"></param>
		/// <param name="ca"></param>
		virtual void OnRenderShadowMap(RenderContext& rc, Camera& ca)
		{

		}

		/// <summary>
		/// 2D‚Ì•`‰æ
		/// </summary>
		/// <param name="rc"></param>
		virtual void OnRender2D(RenderContext& rc)
		{

		}

		/// <summary>
		/// ”wŒi‚Ì•`‰æ
		/// </summary>
		/// <param name="rc"></param>
		virtual void OnRenderBackGround(RenderContext& rc)
		{

		}
	};
}

