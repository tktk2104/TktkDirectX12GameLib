#ifndef SPHERE_MESH_WIRE_FRAME_DRAWER_MAKER_H_
#define SPHERE_MESH_WIRE_FRAME_DRAWER_MAKER_H_

#include <TktkTemplateMetaLib/TypeCheck/isIdType.h>
#include "SphereMeshWireFrameDrawer.h"

namespace tktk
{
	// �uSphereMeshWireFrameDrawer�v�����w���p�[�N���X
	class SphereMeshWireFrameDrawerMaker
	{
	private: /* �v���C�x�[�g�R���X�g���N�^�B */

		SphereMeshWireFrameDrawerMaker() = default;
		SphereMeshWireFrameDrawerMaker(const SphereMeshWireFrameDrawerMaker& other) = default;
		SphereMeshWireFrameDrawerMaker& operator = (const SphereMeshWireFrameDrawerMaker& other) = default;

	public:

		// �쐬�J�n
		static SphereMeshWireFrameDrawerMaker& makeStart(GameObjectPtr user);

	public:

		// �쐬����
		ComponentPtr<SphereMeshWireFrameDrawer> create();

	public:  /* �p�����[�^�ݒ�֐� */

		// �`��D��x��ݒ肷��
		SphereMeshWireFrameDrawerMaker& drawPriority(float value);

		// ���a��ݒ肷��
		SphereMeshWireFrameDrawerMaker& radius(float value);

		// ���[�J�����W��ݒ肷��
		SphereMeshWireFrameDrawerMaker& localPosition(const tktkMath::Vector3& value);

		// �`��F��ݒ肷��
		SphereMeshWireFrameDrawerMaker& albedoColor(const tktkMath::Color & value);

		// �g�p���郌���_�[�^�[�Q�b�g�̃f�B�X�N���v�^�q�[�v�n���h����ݒ肷��
		// �������p�����[�^�̓o�b�N�o�b�t�@�[
		SphereMeshWireFrameDrawerMaker& useRtvDescriptorHeapHandle(unsigned int value);

		// �g�p����J�����n���h����ݒ肷��
		// �������p�����[�^�̓f�t�H���g�ʏ�J����
		SphereMeshWireFrameDrawerMaker& cameraHandle(unsigned int value);

		// �g�p����J����ID��ݒ肷��i�񋓌^���܂ސ����^��id���n���ꂽ�ꍇ�̂݃r���h�ŁA�֐����őΉ����郊�\�[�X�n���h���ɕϊ������j
		// �������p�����[�^�̓f�t�H���g�ʏ�J����
		template<class IdType, is_idType<IdType> = nullptr>
		SphereMeshWireFrameDrawerMaker& cameraId(IdType value) { return cameraIdImpl(static_cast<int>(value)); }

		// �g�p����V���h�E�}�b�v�J�����n���h����ݒ肷��
		// �������p�����[�^�̓f�t�H���g�V���h�E�}�b�v�J����
		SphereMeshWireFrameDrawerMaker& shadowMapCameraHandle(unsigned int value);

		// �g�p����V���h�E�}�b�v�J����ID��ݒ肷��i�񋓌^���܂ސ����^��id���n���ꂽ�ꍇ�̂݃r���h�ŁA�֐����őΉ����郊�\�[�X�n���h���ɕϊ������j
		// �������p�����[�^�̓f�t�H���g�V���h�E�}�b�v�J����
		template<class IdType, is_idType<IdType> = nullptr>
		SphereMeshWireFrameDrawerMaker& shadowMapCameraId(IdType value) { return shadowMapCameraIdImpl(static_cast<int>(value)); }

		// �g�p���郉�C�g�n���h����ݒ肷��
		SphereMeshWireFrameDrawerMaker& lightHandle(unsigned int value);

		// �g�p���郉�C�gID��ݒ肷��i�񋓌^���܂ސ����^��id���n���ꂽ�ꍇ�̂݃r���h�ŁA�֐����őΉ����郊�\�[�X�n���h���ɕϊ������j
		template<class IdType, is_idType<IdType> = nullptr>
		SphereMeshWireFrameDrawerMaker& lightId(IdType value) { return lightIdImpl(static_cast<int>(value)); }

	private: /* �e��id�w��n�̊֐��̎��� */

		SphereMeshWireFrameDrawerMaker& cameraIdImpl(int value);
		SphereMeshWireFrameDrawerMaker& shadowMapCameraIdImpl(int value);
		SphereMeshWireFrameDrawerMaker& lightIdImpl(int value);

	private: /* ���g�̃C���X�^���X�͐ÓI�ȑ��݂Ƃ��Ĉ��� */

		static SphereMeshWireFrameDrawerMaker m_self;

	private: /* �ϐ��B */

		GameObjectPtr						m_user				{  };
		float								m_drawPriority		{ 0.0f };
		float								m_radius			{ 0.5f };
		tktkMath::Vector3					m_localPosition		{ tktkMath::Vector3_v::zero };
		tktkMath::Color						m_albedoColor		{ tktkMath::Color_v::white };
		SphereMeshDrawerUseResourceHandles	m_useResourceHandles{  };

	public: /* �s���Ȍ^�̈������n���ꂻ���ɂȂ������ɃR���p�C���G���[�ɂ���ׂ̎d�g�� */

		template<class IdType, is_not_idType<IdType> = nullptr>
		SphereMeshWireFrameDrawerMaker& cameraId(IdType value) { static_assert(false, "CameraId Fraud Type"); }

		template<class IdType, is_not_idType<IdType> = nullptr>
		SphereMeshWireFrameDrawerMaker& shadowMapCameraId(IdType value) { static_assert(false, "ShadowMapCameraId Fraud Type"); }

		template<class IdType, is_not_idType<IdType> = nullptr>
		SphereMeshWireFrameDrawerMaker& lightId(IdType value) { static_assert(false, "LightId Fraud Type"); }
	};
}
#endif // !SPHERE_MESH_WIRE_FRAME_DRAWER_MAKER_H_