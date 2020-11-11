#ifndef SPHERE_MESH_DRAWER_MAKER_H_
#define SPHERE_MESH_DRAWER_MAKER_H_

#include "TktkDX12Game/UtilityProcessManager/ResourceHandleGetter/ResourceIdConverter/ResourceIdCarrier.h"
#include "SphereMeshDrawer.h"

namespace tktk
{
	// �uSphereMeshDrawer�v�����w���p�[�N���X
	class SphereMeshDrawerMaker
	{
	private: /* �v���C�x�[�g�R���X�g���N�^�B */

		SphereMeshDrawerMaker() = default;
		SphereMeshDrawerMaker(const SphereMeshDrawerMaker& other) = default;
		SphereMeshDrawerMaker& operator = (const SphereMeshDrawerMaker& other) = default;

	public:

		// �쐬�J�n
		static SphereMeshDrawerMaker& makeStart(GameObjectPtr user);

	public:

		// �쐬����
		ComponentPtr<SphereMeshDrawer> create();

	public:  /* �p�����[�^�ݒ�֐� */

		// �`��D��x��ݒ肷��
		SphereMeshDrawerMaker& drawPriority(float value);

		// ���a��ݒ肷��
		SphereMeshDrawerMaker& radius(float value);

		// ���[�J�����W��ݒ肷��
		SphereMeshDrawerMaker& localPosition(const tktkMath::Vector3& value);

		// �`��F��ݒ肷��
		SphereMeshDrawerMaker& albedoColor(const tktkMath::Color&  value);

		// �g�p���郌���_�[�^�[�Q�b�g�̃f�B�X�N���v�^�q�[�v�n���h����ݒ肷��
		// �������p�����[�^�̓o�b�N�o�b�t�@�[
		SphereMeshDrawerMaker& useRtvDescriptorHeapHandle(size_t value);

		// �g�p����J�����n���h����ݒ肷��
		// �������p�����[�^�̓f�t�H���g�ʏ�J����
		SphereMeshDrawerMaker& cameraHandle(size_t value);

		// �g�p����J����ID��ݒ肷��i�񋓌^���܂ސ����^��id���n���ꂽ�ꍇ�̂݃r���h�ŁA�֐����őΉ����郊�\�[�X�n���h���ɕϊ������j
		// �������p�����[�^�̓f�t�H���g�ʏ�J����
		SphereMeshDrawerMaker& cameraId(ResourceIdCarrier value);

		// �g�p����V���h�E�}�b�v�J�����n���h����ݒ肷��
		// �������p�����[�^�̓f�t�H���g�V���h�E�}�b�v�J����
		SphereMeshDrawerMaker& shadowMapCameraHandle(size_t value);

		// �g�p����V���h�E�}�b�v�J����ID��ݒ肷��i�񋓌^���܂ސ����^��id���n���ꂽ�ꍇ�̂݃r���h�ŁA�֐����őΉ����郊�\�[�X�n���h���ɕϊ������j
		// �������p�����[�^�̓f�t�H���g�V���h�E�}�b�v�J����
		SphereMeshDrawerMaker& shadowMapCameraId(ResourceIdCarrier value);

		// �g�p���郉�C�g�n���h����ݒ肷��
		// �������p�����[�^�̓f�t�H���g���C�g
		SphereMeshDrawerMaker& lightHandle(size_t value);

		// �g�p���郉�C�gID��ݒ肷��i�񋓌^���܂ސ����^��id���n���ꂽ�ꍇ�̂݃r���h�ŁA�֐����őΉ����郊�\�[�X�n���h���ɕϊ������j
		// �������p�����[�^�̓f�t�H���g���C�g
		SphereMeshDrawerMaker& lightId(ResourceIdCarrier value);

	private: /* ���g�̃C���X�^���X�͐ÓI�ȑ��݂Ƃ��Ĉ��� */

		static SphereMeshDrawerMaker m_self;

	private: /* �ϐ��B */

		GameObjectPtr						m_user				{  };
		float								m_drawPriority		{ 0.0f };
		float								m_radius			{ 0.5f };
		tktkMath::Vector3					m_localPosition		{ tktkMath::Vector3_v::zero };
		tktkMath::Color						m_albedoColor		{ tktkMath::Color_v::white };
		SphereMeshDrawerUseResourceHandles	m_useResourceHandles{  };
	};
}
#endif // !SPHERE_MESH_DRAWER_MAKER_H_