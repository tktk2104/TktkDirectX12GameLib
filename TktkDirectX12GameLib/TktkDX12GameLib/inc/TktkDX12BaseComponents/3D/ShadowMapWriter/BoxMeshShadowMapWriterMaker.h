#ifndef BOX_MESH_SHADOW_MAP_WRITER_MAKER_H_
#define BOX_MESH_SHADOW_MAP_WRITER_MAKER_H_

#include <TktkTemplateMetaLib/TypeCheck/isIdType.h>
#include "BoxMeshShadowMapWriter.h"

namespace tktk
{
	// �uBoxMeshShadowMapWriter�v�����w���p�[�N���X
	class BoxMeshShadowMapWriterMaker
	{
	private: /* �v���C�x�[�g�R���X�g���N�^�B */

		BoxMeshShadowMapWriterMaker() = default;
		BoxMeshShadowMapWriterMaker(const BoxMeshShadowMapWriterMaker& other) = default;
		BoxMeshShadowMapWriterMaker& operator = (const BoxMeshShadowMapWriterMaker& other) = default;

	public:

		// �쐬�J�n
		static BoxMeshShadowMapWriterMaker& makeStart(GameObjectPtr user);

		// �X�e�[�g���w�肵�A�쐬���J�n����
		// ���u{ MOVE_STATE, WALK_STATE, BEGIN_MOVE_STATE }�v�Łu�gMOVE_STATE�h���́gWALK_STATE�h���́gBEGIN_MOVE_STATE�h�ɒǉ��v�ƂȂ�
		template <class StateIdType>
		static BoxMeshShadowMapWriterMaker& makeStart(std::initializer_list<StateIdType> targetState, GameObjectPtr user);

	public:

		// �쐬����
		ComponentPtr<BoxMeshShadowMapWriter> create();

	public:  /* �p�����[�^�ݒ�֐� */

		// �`��D��x��ݒ肷��
		BoxMeshShadowMapWriterMaker& drawPriority(float value);

		// �����̂̑傫����ݒ肷��
		BoxMeshShadowMapWriterMaker& boxSize(const tktkMath::Vector3& value);

		// ���[�J�����W��ݒ肷��
		BoxMeshShadowMapWriterMaker& localPosition(const tktkMath::Vector3 & value);

		// �g�p����J����ID��ݒ肷��i�񋓌^���܂ސ����^��id���n���ꂽ�ꍇ�̂݃r���h�ŁA�֐����őΉ����郊�\�[�X�n���h���ɕϊ������j
		// �������p�����[�^�̓f�t�H���g�V���h�E�}�b�v�J����
		template<class IdType, is_idType<IdType> = nullptr>
		BoxMeshShadowMapWriterMaker& cameraId(IdType value) { return cameraIdImpl(static_cast<int>(value)); }

	private: /* �e��id�w��n�̊֐��̎��� */

		BoxMeshShadowMapWriterMaker& cameraIdImpl(int value);

	private: /* ���g�̃C���X�^���X�͐ÓI�ȑ��݂Ƃ��Ĉ��� */

		static BoxMeshShadowMapWriterMaker m_self;

	private: /* �ϐ��B */

		GameObjectPtr		m_user			{  };
		std::vector<int>	m_targetState	{  };
		float				m_drawPriority	{ 0.0f };
		tktkMath::Vector3	m_boxSize		{ tktkMath::Vector3_v::zero };
		tktkMath::Vector3	m_localPosition	{ tktkMath::Vector3_v::zero };
		unsigned int		m_cameraHandle	{ 0U };

	public: /* �s���Ȍ^�̈������n���ꂻ���ɂȂ������ɃR���p�C���G���[�ɂ���ׂ̎d�g�� */

		template<class IdType, is_not_idType<IdType> = nullptr>
		BoxMeshShadowMapWriterMaker& cameraId(IdType value) { static_assert(false, "CameraId Fraud Type"); }
	};
//������������������������������������������������������������������������������������������������������������������������������������������������������������������
//���������牺�͊֐��̎���
//������������������������������������������������������������������������������������������������������������������������������������������������������������������

	// �X�e�[�g���w�肵�A�쐬���J�n����
	// ���u{ MOVE_STATE, WALK_STATE, BEGIN_MOVE_STATE }�v�Łu�gMOVE_STATE�h���́gWALK_STATE�h���́gBEGIN_MOVE_STATE�h�ɒǉ��v�ƂȂ�
	template<class StateIdType>
	inline BoxMeshShadowMapWriterMaker& BoxMeshShadowMapWriterMaker::makeStart(std::initializer_list<StateIdType> targetState, GameObjectPtr user)
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
}
#endif // !BOX_MESH_SHADOW_MAP_WRITER_MAKER_H_