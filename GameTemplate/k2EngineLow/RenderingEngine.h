#pragma once

#include "SceneLight.h"
#include "IRenderer.h"

namespace nsK2EngineLow
{
	class RenderingEngine : public Noncopyable
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
		void Execute(RenderContext& rc);

		void AddRenderObject(IRenderer* renderObject)
		{
			m_renderObjects.push_back(renderObject);
		}

		/// <summary>
		/// ライトを取得
		/// </summary>
		/// <returns></returns>
		Light& GetLight()
		{
			return m_sceneLight.GetLight();
		}

	private:

		/// <summary>
		/// メインレンダリングターゲットを初期化
		/// </summary>
		void InitMainRenderTarget();

		/// <summary>
		/// 2D(フォントとスプライト)の初期化
		/// </summary>
		void Init2DSprite();

		/// <summary>
		/// モノクロ用のレンダリングターゲットを初期化
		/// </summary>
		void InitMonochromeRenderTarget();

		/// <summary>
		/// メインレンダリングターゲットのカラーバッファの内容を
		/// フレームバッファにコピーするためのスプライトを初期化する
		/// </summary>
		void InitCopyMainRenderTargetToFrameBuffer();

		/// <summary>
		/// モデルの描画
		/// </summary>
		/// <param name="rc"></param>
		void ModelDraw(RenderContext& rc);

		/// <summary>
		/// 2D(フォントとスプライト)の描画
		/// </summary>
		/// <param name="rc"></param>
		void SpriteFontDraw(RenderContext& rc);

		/// <summary>
		/// モノクロの描画
		/// </summary>
		/// <param name="rc"></param>
		void OnMonochromeRendering(RenderContext& rc);

		/// <summary>
		/// メインレンダリングターゲットの内容をフレームバッファにコピーする
		/// </summary>
		/// <param name="rc"></param>
		void CopyMainRenderTargetToFrameBuffer(RenderContext& rc);

		SceneLight m_sceneLight;
		RenderTarget m_mainRenderTarget;
		RenderTarget m_2DRenderTarget;
		RenderTarget m_monochromeRenderTarget;
		Sprite m_2DSprite;
		Sprite m_mainSprite;
		Sprite m_monochromeSprite;
		Sprite m_copyToFrameBufferSprite;
		std::vector< IRenderer* > m_renderObjects;
	};
}

