#pragma once
namespace nsK2EngineLow
{
	class SpriteRender
	{
	public:
		/// <summary>
		/// ������
		/// </summary>
		/// <param name="filePath">�t�@�C���p�X</param>
		/// <param name="w">�摜�̉���</param>
		/// <param name="h">�摜�̏c��</param>
		void Init(const char* filePath, const float w, const float h, AlphaBlendMode alphaBlendMode = AlphaBlendMode_Trans);

		/// <summary>
		/// ���W��ݒ�B
		/// </summary>
		/// <param name="pos">���W�B</param>
		void SetPosition(const Vector3& pos)
		{
			m_position = pos;
		}
		/// <summary>
		/// ���W���擾�B
		/// </summary>
		/// <returns>���W�B</returns>
		const Vector3& GetPosition() const
		{
			return m_position;
		}
		/// <summary>
		/// �傫����ݒ�B
		/// </summary>
		/// <param name="scale">�傫���B</param>
		void SetScale(const Vector3& scale)
		{
			m_scale = scale;
		}
		/// <summary>
		/// �傫�����擾�B
		/// </summary>
		/// <returns>�傫���B</returns>
		const Vector3& GetScale() const
		{
			return m_scale;
		}
		/// <summary>
		/// ��]��ݒ�B
		/// </summary>
		/// <param name="rot">��]�B</param>
		void SetRotation(const Quaternion& rot)
		{
			m_rotation = rot;
		}
		/// <summary>
		/// ��]���擾�B
		/// </summary>
		/// <returns>��]�B</returns>
		const Quaternion& GetRotation() const
		{
			return m_rotation;
		}
		/// <summary>
		/// �s�{�b�g��ݒ�B
		/// </summary>
		/// <param name="pivot">�s�{�b�g�B</param>
		void SetPivot(const Vector2& pivot)
		{
			m_pivot = pivot;
		}
		/// <summary>
		/// �s�{�b�g���擾�B
		/// </summary>
		/// <returns>�s�{�b�g�B</returns>
		const Vector2& GetPivot() const
		{
			return m_pivot;
		}

		/// <summary>
		/// �X�V����
		/// </summary>
		void Update();
		
		/// <summary>
		/// �`�揈��
		/// </summary>
		/// <param name="rc">�����_�[�R���e�L�X�g</param>
		void Draw(RenderContext& rc);

	private:
		Sprite m_sprite;
		Vector3 m_position = Vector3::Zero;
		Quaternion m_rotation = Quaternion::Identity;
		Vector3 m_scale = Vector3::One;
		Vector2 m_pivot = Sprite::DEFAULT_PIVOT;
	};
}

