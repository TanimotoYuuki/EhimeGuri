#pragma once
namespace nsK2EngineLow
{
	/// <summary>
	/// �t�H���g�����_�[
	/// </summary>
	class FontRender
	{
	public:
		/// <summary>
		/// �\�����镶����ݒ�
		/// </summary>
		/// <param name="text">�\�����镶��</param>
		void SetText(const wchar_t* text)
		{
			swprintf(m_text, text);
		}

		/// <summary>
		/// �\�����镶�����擾
		/// </summary>
		/// <returns>�\�����镶��</returns>
		const wchar_t* GetText() const
		{
			return m_text;
		}

		/// <summary>
		/// ���W��ݒ�
		/// </summary>
		/// <param name="position">���W</param>
		void SetPosition(const Vector3& position)
		{
			m_position = position;
		}
		/// <summary>
		/// ���W���擾
		/// </summary>
		/// <returns>���W</returns>
		const Vector3& GetPosition() const
		{
			return m_position;
		}
		/// <summary>
		/// �傫����ݒ�
		/// </summary>
		/// <param name="scale">�傫��</param>
		void SetScale(const float scale)
		{
			m_scale = scale;
		}
		/// <summary>
		/// �傫�����擾
		/// </summary>
		/// <returns>�傫��</returns>
		const float GetScale() const
		{
			return m_scale;
		}
		/// <summary>
		/// �F��ݒ�
		/// </summary>
		/// <param name="color">�F</param>
		void SetColor(const Vector4& color)
		{
			m_color = color;
		}
		/// <summary>
		/// �F���擾
		/// </summary>
		/// <returns>�F</returns>
		const Vector4& GetColor() const
		{
			return m_color;
		}
		/// <summary>
		/// ��]��ݒ�
		/// </summary>
		/// <param name="rotation">��]</param>
		void SetRotation(const float rotation)
		{
			m_rotation = rotation;
		}
		/// <summary>
		/// ��]���擾
		/// </summary>
		/// <returns>��]</returns>
		const float GetRotation() const
		{
			return m_rotation;
		}
		/// <summary>
		/// �s�{�b�g��ݒ�
		/// </summary>
		/// <param name="pivot">�s�{�b�g</param>
		void SetPivot(const Vector2& pivot)
		{
			m_pivot = pivot;
		}
		/// <summary>
		/// �s�{�b�g���擾
		/// </summary>
		/// <returns>�s�{�b�g</returns>
		const Vector2& GetPivot() const
		{
			return m_pivot;
		}

		/// <summary>
		/// �`�揈��
		/// </summary>
		/// <param name="rc">�����_�\�R���e�L�X�g</param>
		void Draw(RenderContext& rc);

		/// <summary>
		/// �e�̃p�����[�^��ݒ�
		/// </summary>
		/// <param name="isDrawShadow">�e��`�悷��H</param>
		/// <param name="shadowOffset">�e��`�悷��Ƃ��̃s�N�Z���̃I�t�Z�b�g��</param>
		/// <param name="shadowColor">�e�̐F</param>
		void SetShadowParam(bool isDrawShadow, float shadowOffset, const Vector4& shadowColor)
		{
			m_font.SetShadowParam(isDrawShadow, shadowOffset, shadowColor);
		}
	private:
		Vector3 m_position = Vector3::Zero; //���W
		float m_scale = 1.0f; //�����̑傫��
		Vector4 m_color = g_vec4White; //�����̐F
		float m_rotation = 0.0f; //��]
		Vector2 m_pivot = Sprite::DEFAULT_PIVOT; //�s�{�b�g
		wchar_t m_text[256]; //����
		Font m_font; //�t�H���g
	};
}

