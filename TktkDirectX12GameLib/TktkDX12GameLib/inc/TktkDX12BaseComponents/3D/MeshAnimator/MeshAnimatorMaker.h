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

		// �X�e�[�g���w�肵�A�쐬���J�n����
		// ���u{ MOVE_STATE, WALK_STATE, BEGIN_MOVE_STATE }�v�Łu�gMOVE_STATE�h���́gWALK_STATE�h���́gBEGIN_MOVE_STATE�h�ɒǉ��v�ƂȂ�
		template <class StateIdType>
		static MeshAnimatorMaker& makeStart(std::initializer_list<StateIdType> targetState, GameObjectPtr user);

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

		// �P�b�Ԃɉ��t���[�����̃A�j���[�V�������Đ����邩��ݒ肷��
		MeshAnimatorMaker& animFramePerSec(float value);

	private: /* �e��id�w��n�̊֐��̎��� */

		MeshAnimatorMaker& initMotionIdImpl(int value);

	private: /* ���g�̃C���X�^���X�͐ÓI�ȑ��݂Ƃ��Ĉ��� */

		static MeshAnimatorMaker m_self;

	private: /* �ϐ��B */

		GameObjectPtr		m_user				{  };
		std::vector<int>	m_targetState		{  };
		unsigned int		m_isLoop			{ true };
		unsigned int		m_initMotionHandle	{ 0U };
		float				m_animFramePerSec	{ 60.0f };

	public: /* �s���Ȍ^�̈������n���ꂻ���ɂȂ������ɃR���p�C���G���[�ɂ���ׂ̎d�g�� */

		template<class IdType, std::enable_if_t<!is_idType_v<IdType>>* = nullptr>
		MeshAnimatorMaker& initMotionId(IdType value) { static_assert(false, "MotionId Fraud Type"); }
	};
//������������������������������������������������������������������������������������������������������������������������������������������������������������������
//���������牺�͊֐��̎���
//������������������������������������������������������������������������������������������������������������������������������������������������������������������

	// �X�e�[�g���w�肵�A�쐬���J�n����
	// ���u{ MOVE_STATE, WALK_STATE, BEGIN_MOVE_STATE }�v�Łu�gMOVE_STATE�h���́gWALK_STATE�h���́gBEGIN_MOVE_STATE�h�ɒǉ��v�ƂȂ�
	template<class StateIdType>
	inline MeshAnimatorMaker& MeshAnimatorMaker::makeStart(std::initializer_list<StateIdType> targetState, GameObjectPtr user)
	{
		// �쐬�J�n�������s��
		auto& result = makeStart(user);

		// �������q���X�g��z��ɕϊ�
		auto targetStateArray = std::vector<StateIdType>(targetState);

		// �Ώۂ̃X�e�[�g�̊K�w�����̃��������m��
		result.m_targetState.reserve(targetStateArray.size());

		// �Ώۂ̃X�e�[�g�̊K�w��ݒ肷��
		for (const auto& node : targetStateArray) result.m_targetState.push_back(static_cast<int>(node));

		// ���g�̎Q�Ƃ�Ԃ�
		return result;
	}

	// �g�p���鏉�����[�V����ID��ݒ肷��i�񋓌^���܂ސ����^��id���n���ꂽ�ꍇ�̂݃r���h�j
	template<class IdType, is_idType<IdType>>
	inline MeshAnimatorMaker& MeshAnimatorMaker::initMotionId(IdType value)
	{
		return initMotionIdImpl(static_cast<int>(value));
	}
}
#endif // !MESH_ANIMATOR_MAKER_H_
