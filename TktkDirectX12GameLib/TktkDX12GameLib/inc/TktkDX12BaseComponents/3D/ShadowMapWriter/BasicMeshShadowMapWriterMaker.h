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

		// �X�e�[�g���w�肵�A�쐬���J�n����
		static BasicMeshShadowMapWriterMaker& makeStart(const StateTypeHierarchy& targetState, GameObjectPtr user);

	public:

		// �쐬����
		ComponentPtr<BasicMeshShadowMapWriter> create();

	public:  /* �p�����[�^�ݒ�֐� */

		// �`��D��x��ݒ肷��
		BasicMeshShadowMapWriterMaker& drawPriority(float value);

		// ��{�̃X�P�[����ݒ肷��
		BasicMeshShadowMapWriterMaker& baseScale(const tktkMath::Vector3& value);

		// ��{�̉�]��ݒ肷��
		BasicMeshShadowMapWriterMaker& baseRotation(const tktkMath::Quaternion& value);

		// �g�p���郁�b�V��ID��ݒ肷��i�񋓌^���܂ސ����^��id���n���ꂽ�ꍇ�̂݃r���h�ŁA�֐����őΉ����郊�\�[�X�n���h���ɕϊ������j
		BasicMeshShadowMapWriterMaker& meshId(ResourceIdCarrier value);

		// �g�p����X�P���g��ID��ݒ肷��i�񋓌^���܂ސ����^��id���n���ꂽ�ꍇ�̂݃r���h�ŁA�֐����őΉ����郊�\�[�X�n���h���ɕϊ������j
		BasicMeshShadowMapWriterMaker& skeletonId(ResourceIdCarrier value);

		// �g�p����J����ID��ݒ肷��i�񋓌^���܂ސ����^��id���n���ꂽ�ꍇ�̂݃r���h�ŁA�֐����őΉ����郊�\�[�X�n���h���ɕϊ������j
		// �������p�����[�^�̓f�t�H���g�V���h�E�}�b�v�J����
		BasicMeshShadowMapWriterMaker& cameraId(ResourceIdCarrier value);

	private: /* ���g�̃C���X�^���X�͐ÓI�ȑ��݂Ƃ��Ĉ��� */

		static BasicMeshShadowMapWriterMaker m_self;

	private: /* �ϐ��B */

		GameObjectPtr			m_user			{  };
		StateTypeHierarchy		m_targetState	{  };
		float					m_drawPriority	{ 0.0f };
		tktkMath::Vector3		m_baseScale{ tktkMath::Vector3_v::one };
		tktkMath::Quaternion	m_baseRotation{ tktkMath::Quaternion_v::identity };
		size_t					m_meshHandle	{ 0U };
		size_t					m_skeletonHandle{ 0U };
		size_t					m_cameraHandle	{ 0U };
	};
}
#endif // !BASIC_MESH_SHADOW_MAP_WRITER_MAKER_H_
