#ifndef BOX_MESH_WIRE_FRAME_DRAWER_MAKER_H_
#define BOX_MESH_WIRE_FRAME_DRAWER_MAKER_H_

#include <TktkTemplateMetaLib/TypeCheck/isIdType.h>
#include "BoxMeshWireFrameDrawer.h"

namespace tktk
{
	// �uBoxMeshWireFrameDrawer�v�����w���p�[�N���X
	class BoxMeshWireFrameDrawerMaker
	{
	private: /* �v���C�x�[�g�R���X�g���N�^�B */

		BoxMeshWireFrameDrawerMaker() = default;
		BoxMeshWireFrameDrawerMaker(const BoxMeshWireFrameDrawerMaker& other) = default;
		BoxMeshWireFrameDrawerMaker& operator = (const BoxMeshWireFrameDrawerMaker& other) = default;

	public:

		// �쐬�J�n
		static BoxMeshWireFrameDrawerMaker& makeStart(GameObjectPtr user);

		// �X�e�[�g���w�肵�A�쐬���J�n����
		// ���u{ MOVE_STATE, WALK_STATE, BEGIN_MOVE_STATE }�v�Łu�gMOVE_STATE�h���́gWALK_STATE�h���́gBEGIN_MOVE_STATE�h�ɒǉ��v�ƂȂ�
		template <class StateIdType>
		static BoxMeshWireFrameDrawerMaker& makeStart(std::initializer_list<StateIdType> targetState, GameObjectPtr user);

	public:

		// �쐬����
		ComponentPtr<BoxMeshWireFrameDrawer> create();

	public:  /* �p�����[�^�ݒ�֐� */

		// �`��D��x��ݒ肷��
		BoxMeshWireFrameDrawerMaker& drawPriority(float value);

		// �����̂̑傫����ݒ肷��
		BoxMeshWireFrameDrawerMaker& boxSize(const tktkMath::Vector3 & value);

		// ���[�J�����W��ݒ肷��
		BoxMeshWireFrameDrawerMaker& localPosition(const tktkMath::Vector3 & value);

		// �`��F��ݒ肷��
		BoxMeshWireFrameDrawerMaker& albedoColor(const tktkMath::Color & value);

		// �g�p���郌���_�[�^�[�Q�b�g�̃f�B�X�N���v�^�q�[�v�n���h����ݒ肷��
		// �������p�����[�^�̓o�b�N�o�b�t�@�[
		BoxMeshWireFrameDrawerMaker& useRtvDescriptorHeapHandle(unsigned int value);

		// �g�p����J�����n���h����ݒ肷��
		// �������p�����[�^�̓f�t�H���g�ʏ�J����
		BoxMeshWireFrameDrawerMaker& cameraHandle(unsigned int value);

		// �g�p����J����ID��ݒ肷��i�񋓌^���܂ސ����^��id���n���ꂽ�ꍇ�̂݃r���h�ŁA�֐����őΉ����郊�\�[�X�n���h���ɕϊ������j
		// �������p�����[�^�̓f�t�H���g�ʏ�J����
		template<class IdType, is_idType<IdType> = nullptr>
		BoxMeshWireFrameDrawerMaker& cameraId(IdType value) { return cameraIdImpl(static_cast<int>(value)); }

		// �g�p����V���h�E�}�b�v�J�����n���h����ݒ肷��
		// �������p�����[�^�̓f�t�H���g�V���h�E�}�b�v�J����
		BoxMeshWireFrameDrawerMaker& shadowMapCameraHandle(unsigned int value);

		// �g�p����V���h�E�}�b�v�J����ID��ݒ肷��i�񋓌^���܂ސ����^��id���n���ꂽ�ꍇ�̂݃r���h�ŁA�֐����őΉ����郊�\�[�X�n���h���ɕϊ������j
		// �������p�����[�^�̓f�t�H���g�V���h�E�}�b�v�J����
		template<class IdType, is_idType<IdType> = nullptr>
		BoxMeshWireFrameDrawerMaker& shadowMapCameraId(IdType value) { return shadowMapCameraIdImpl(static_cast<int>(value)); }

		// �g�p���郉�C�g�n���h����ݒ肷��
		// �������p�����[�^�̓f�t�H���g���C�g
		BoxMeshWireFrameDrawerMaker& lightHandle(unsigned int value);

		// �g�p���郉�C�gID��ݒ肷��i�񋓌^���܂ސ����^��id���n���ꂽ�ꍇ�̂݃r���h�ŁA�֐����őΉ����郊�\�[�X�n���h���ɕϊ������j
		// �������p�����[�^�̓f�t�H���g���C�g
		template<class IdType, is_idType<IdType> = nullptr>
		BoxMeshWireFrameDrawerMaker& lightId(IdType value) { return lightIdImpl(static_cast<int>(value)); }

	private: /* �e��id�w��n�̊֐��̎��� */

		BoxMeshWireFrameDrawerMaker& cameraIdImpl(int value);
		BoxMeshWireFrameDrawerMaker& shadowMapCameraIdImpl(int value);
		BoxMeshWireFrameDrawerMaker& lightIdImpl(int value);

	private: /* ���g�̃C���X�^���X�͐ÓI�ȑ��݂Ƃ��Ĉ��� */

		static BoxMeshWireFrameDrawerMaker m_self;

	private: /* �ϐ��B */

		GameObjectPtr						m_user				{  };
		std::vector<int>					m_targetState		{  };
		float								m_drawPriority		{ 0.0f };
		tktkMath::Vector3					m_boxSize			{ tktkMath::Vector3_v::one };
		tktkMath::Vector3					m_localPosition		{ tktkMath::Vector3_v::zero };
		tktkMath::Color						m_albedoColor		{ tktkMath::Color_v::white };
		BoxMeshDrawerUseResourceHandles		m_useResourceHandles{  };

	public: /* �s���Ȍ^�̈������n���ꂻ���ɂȂ������ɃR���p�C���G���[�ɂ���ׂ̎d�g�� */

		template<class IdType, std::enable_if_t<!is_idType_v<IdType>>* = nullptr>
		BoxMeshWireFrameDrawerMaker& cameraId(IdType value) { static_assert(false, "CameraId Fraud Type"); }

		template<class IdType, std::enable_if_t<!is_idType_v<IdType>>* = nullptr>
		BoxMeshWireFrameDrawerMaker& shadowMapCameraId(IdType value) { static_assert(false, "ShadowMapCameraId Fraud Type"); }

		template<class IdType, std::enable_if_t<!is_idType_v<IdType>>* = nullptr>
		BoxMeshWireFrameDrawerMaker& lightId(IdType value) { static_assert(false, "LightId Fraud Type"); }
	};
//������������������������������������������������������������������������������������������������������������������������������������������������������������������
//���������牺�͊֐��̎���
//������������������������������������������������������������������������������������������������������������������������������������������������������������������

	// �X�e�[�g���w�肵�A�쐬���J�n����
	// ���u{ MOVE_STATE, WALK_STATE, BEGIN_MOVE_STATE }�v�Łu�gMOVE_STATE�h���́gWALK_STATE�h���́gBEGIN_MOVE_STATE�h�ɒǉ��v�ƂȂ�
	template<class StateIdType>
	inline BoxMeshWireFrameDrawerMaker& BoxMeshWireFrameDrawerMaker::makeStart(std::initializer_list<StateIdType> targetState, GameObjectPtr user)
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
#endif // !BOX_MESH_WIRE_FRAME_DRAWER_MAKER_H_