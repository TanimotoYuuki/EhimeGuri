#include "k2EngineLowPreCompile.h"
#include "ModelRender.h"

namespace nsK2EngineLow
{
	void ModelRender::Init(const char* filePath,
		AnimationClip* animationClips,
		int numAnimationClips,
		EnModelUpAxis enModelUpAxis)
	{
		InitSkeleton(filePath);
		InitAnimation(animationClips, numAnimationClips, enModelUpAxis);
		InitModel(filePath, enModelUpAxis);
	}

	void ModelRender::InitSkeleton(const char* filePath)
	{
		std::string skeletonFilePath = filePath;
		int pos = (int)skeletonFilePath.find(".tkm");
		skeletonFilePath.replace(pos, 4, ".tks");
		m_skeleton.Init(skeletonFilePath.c_str());
	}

	void ModelRender::InitAnimation(AnimationClip* animationClips, int numAnimationClips, EnModelUpAxis enModelUpAxis)
	{
		m_animationClips = animationClips;
		m_numAnimationClips = numAnimationClips;
		if (m_animationClips != nullptr)
		{
			m_animation.Init(m_skeleton,
				m_animationClips,
				m_numAnimationClips);
		}
	}

	void ModelRender::InitModel(const char* filePath, EnModelUpAxis enModelUpAxis)
	{
		ModelInitData modelInitData;
		modelInitData.m_tkmFilePath = filePath;
		modelInitData.m_fxFilePath = "Assets/shader/model.fx";
		modelInitData.m_vsEntryPointFunc = "VSMain";

		if (m_animationClips != nullptr)
		{
			modelInitData.m_vsSkinEntryPointFunc = "VSSkinMain";
			modelInitData.m_skeleton = &m_skeleton;
		}

		modelInitData.m_modelUpAxis = enModelUpAxis;
		m_model.Init(modelInitData);
	}

	void ModelRender::Update()
	{
		//スケルトンを更新
		m_skeleton.Update(m_model.GetWorldMatrix());

		//モデルの更新
		m_model.UpdateWorldMatrix(m_position, m_rotation, m_scale);

		//アニメーションを進める
		m_animation.Progress(g_gameTime->GetFrameDeltaTime() * m_animationSpeed);
	}

	void ModelRender::Draw(RenderContext& rc)
	{
		m_model.Draw(rc);
	}
}