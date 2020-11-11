#ifndef SPHERE_MESH_SHADOW_MAP_WRITER_MAKER_H_
#define SPHERE_MESH_SHADOW_MAP_WRITER_MAKER_H_

#include "TktkDX12Game/UtilityProcessManager/ResourceHandleGetter/ResourceIdConverter/ResourceIdCarrier.h"
#include "SphereMeshShadowMapWriter.h"

namespace tktk
{
	// �uSphereMeshShadowMapWriter�v�����w���p�[�N���X
	class SphereMeshShadowMapWriterMaker
	{
	private: /* �v���C�x�[�g�R���X�g���N�^�B */

		SphereMeshShadowMapWriterMaker() = default;
		SphereMeshShadowMapWriterMaker(const SphereMeshShadowMapWriterMaker& other) = default;
		SphereMeshShadowMapWriterMaker& operator = (const SphereMeshShadowMapWriterMaker& other) = default;

	public:

		// �쐬�J�n
		static SphereMeshShadowMapWriterMaker& makeStart(GameObjectPtr user);

	public:

		// �쐬����
		ComponentPtr<SphereMeshShadowMapWriter> create();

	public:  /* �p�����[�^�ݒ�֐� */

		// �`��D��x��ݒ肷��
		SphereMeshShadowMapWriterMaker& drawPriority(float value);

		// ���a��ݒ肷��
		SphereMeshShadowMapWriterMaker& radius(float value);

		// ���[�J�����W��ݒ肷��
		SphereMeshShadowMapWriterMaker& localPosition(const tktkMath::Vector3& value);

		// �g�p����J����ID��ݒ肷��i�񋓌^���܂ސ����^��id���n���ꂽ�ꍇ�̂݃r���h�ŁA�֐����őΉ����郊�\�[�X�n���h���ɕϊ������j
		// �������p�����[�^�̓f�t�H���g�V���h�E�}�b�v�J����
		SphereMeshShadowMapWriterMaker& cameraId(ResourceIdCarrier value);

	private: /* ���g�̃C���X�^���X�͐ÓI�ȑ��݂Ƃ��Ĉ��� */

		static SphereMeshShadowMapWriterMaker m_self;

	private: /* �ϐ��B */

		GameObjectPtr		m_user			{  };
		float				m_drawPriority	{ 0.0f };
		float				m_radius		{ 0.5f };
		tktkMath::Vector3	m_localPosition	{ tktkMath::Vector3_v::zero };
		size_t				m_cameraHandle	{ 0U };
	};
}
#endif // !SPHERE_MESH_SHADOW_MAP_WRITER_MAKER_H_