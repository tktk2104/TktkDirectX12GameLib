#ifndef MESH_ANIMATOR_MAKER_H_
#define MESH_ANIMATOR_MAKER_H_

#include <TktkTemplateMetaLib/TypeCheck/isIdType.h>
#include "MeshAnimator.h"

namespace tktk
{
	// �uMeshAnimator�v�����w���p�[�N���X
	class MeshAnimatorMaker
	{
	private: /* �v���C�x�[�g�R���X�g���N�^�B */

		MeshAnimatorMaker() = default;
		MeshAnimatorMaker(const MeshAnimatorMaker& other) = default;
		MeshAnimatorMaker& operator = (const MeshAnimatorMaker& other) = default;

	public:

		// �쐬�J�n
		static MeshAnimatorMaker& makeStart(GameObjectPtr user);

	public:

		// �쐬����
		ComponentPtr<MeshAnimator> create();

	public:  /* �p�����[�^�ݒ�֐� */

		// ���[�V���������[�v�����邩��ݒ肷��
		MeshAnimatorMaker& isLoop(bool value);

		// �g�p���鏉�����[�V�����n���h����ݒ肷��
		MeshAnimatorMaker& initMotionHandle(unsigned int value);

		// �g�p���鏉�����[�V����ID��ݒ肷��i�񋓌^���܂ސ����^��id���n���ꂽ�ꍇ�̂݃r���h�j
		// �������őΉ����郊�\�[�X�n���h���ɕϊ������
		template<class IdType, is_idType<IdType> = nullptr>
		MeshAnimatorMaker& initMotionId(IdType value);

	private: /* �e��id�w��n�̊֐��̎��� */

		MeshAnimatorMaker& initMotionIdImpl(int value);

	private: /* ���g�̃C���X�^���X�͐ÓI�ȑ��݂Ƃ��Ĉ��� */

		static MeshAnimatorMaker m_self;

	private: /* �ϐ��B */

		GameObjectPtr	m_user				{  };
		unsigned int	m_isLoop			{ true };
		unsigned int	m_initMotionHandle	{ 0U };

	public: /* �s���Ȍ^�̈������n���ꂻ���ɂȂ������ɃR���p�C���G���[�ɂ���ׂ̎d�g�� */

		template<class IdType, std::enable_if_t<!is_idType_v<IdType>>* = nullptr>
		MeshAnimatorMaker& initMotionId(IdType value) { static_assert(false, "MotionId Fraud Type"); }
	};
//������������������������������������������������������������������������������������������������������������������������������������������������������������������
//���������牺�͊֐��̎���
//������������������������������������������������������������������������������������������������������������������������������������������������������������������

	// �g�p���鏉�����[�V����ID��ݒ肷��i�񋓌^���܂ސ����^��id���n���ꂽ�ꍇ�̂݃r���h�j
	template<class IdType, is_idType<IdType>>
	inline MeshAnimatorMaker& MeshAnimatorMaker::initMotionId(IdType value)
	{
		return initMotionIdImpl(static_cast<int>(value));
	}
}
#endif // !MESH_ANIMATOR_MAKER_H_
