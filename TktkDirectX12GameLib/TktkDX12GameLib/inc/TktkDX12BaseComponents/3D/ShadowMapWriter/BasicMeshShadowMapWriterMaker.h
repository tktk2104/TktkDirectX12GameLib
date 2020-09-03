#ifndef BASIC_MESH_SHADOW_MAP_WRITER_MAKER_H_
#define BASIC_MESH_SHADOW_MAP_WRITER_MAKER_H_

#include <TktkTemplateMetaLib/TypeCheck/isIdType.h>
#include "BasicMeshShadowMapWriter.h"

namespace tktk
{
	// �uBasicMeshShadowMapWriter�v�����w���p�[�N���X
	class BasicMeshShadowMapWriterMaker
	{
	private: /* �v���C�x�[�g�R���X�g���N�^�B */

		BasicMeshShadowMapWriterMaker() = default;
		BasicMeshShadowMapWriterMaker(const BasicMeshShadowMapWriterMaker& other) = default;
		BasicMeshShadowMapWriterMaker& operator = (const BasicMeshShadowMapWriterMaker& other) = default;

	public:

		// �쐬�J�n
		static BasicMeshShadowMapWriterMaker& makeStart(GameObjectPtr user);

	public:

		// �쐬����
		ComponentPtr<BasicMeshShadowMapWriter> create();

	public:  /* �p�����[�^�ݒ�֐� */

		// �`��D��x��ݒ肷��
		BasicMeshShadowMapWriterMaker& drawPriority(float value);

		// �g�p���郁�b�V��ID��ݒ肷��i�񋓌^���܂ސ����^��id���n���ꂽ�ꍇ�̂݃r���h�ŁA�֐����őΉ����郊�\�[�X�n���h���ɕϊ������j
		template<class IdType, is_idType<IdType> = nullptr>
		BasicMeshShadowMapWriterMaker& meshId(IdType value) { return meshIdImpl(static_cast<int>(value)); }

		// �g�p����X�P���g��ID��ݒ肷��i�񋓌^���܂ސ����^��id���n���ꂽ�ꍇ�̂݃r���h�ŁA�֐����őΉ����郊�\�[�X�n���h���ɕϊ������j
		template<class IdType, is_idType<IdType> = nullptr>
		BasicMeshShadowMapWriterMaker& skeletonId(IdType value) { return skeletonIdImpl(static_cast<int>(value)); }

		// �g�p����J����ID��ݒ肷��i�񋓌^���܂ސ����^��id���n���ꂽ�ꍇ�̂݃r���h�ŁA�֐����őΉ����郊�\�[�X�n���h���ɕϊ������j
		// �������p�����[�^�̓f�t�H���g�V���h�E�}�b�v�J����
		template<class IdType, is_idType<IdType> = nullptr>
		BasicMeshShadowMapWriterMaker& cameraId(IdType value) { return cameraIdImpl(static_cast<int>(value)); }

	private: /* �e��id�w��n�̊֐��̎��� */

		BasicMeshShadowMapWriterMaker& meshIdImpl(int value);
		BasicMeshShadowMapWriterMaker& skeletonIdImpl(int value);
		BasicMeshShadowMapWriterMaker& cameraIdImpl(int value);

	private: /* ���g�̃C���X�^���X�͐ÓI�ȑ��݂Ƃ��Ĉ��� */

		static BasicMeshShadowMapWriterMaker m_self;

	private: /* �ϐ��B */

		GameObjectPtr	m_user			{  };
		float			m_drawPriority	{ 0.0f };
		unsigned int	m_meshHandle	{ 0U };
		unsigned int	m_skeletonHandle{ 0U };
		unsigned int	m_cameraHandle	{ 0U };

	public: /* �s���Ȍ^�̈������n���ꂻ���ɂȂ������ɃR���p�C���G���[�ɂ���ׂ̎d�g�� */

		template<class IdType, is_not_idType<IdType> = nullptr>
		BasicMeshShadowMapWriterMaker& meshId(IdType value) { static_assert(false, "MeshId Fraud Type"); }

		template<class IdType, is_not_idType<IdType> = nullptr>
		BasicMeshShadowMapWriterMaker& skeletonId(IdType value) { static_assert(false, "SkeletonId Fraud Type"); }
	
		template<class IdType, is_not_idType<IdType> = nullptr>
		BasicMeshShadowMapWriterMaker& cameraId(IdType value) { static_assert(false, "CameraId Fraud Type"); }
	};
}
#endif // !BASIC_MESH_SHADOW_MAP_WRITER_MAKER_H_
