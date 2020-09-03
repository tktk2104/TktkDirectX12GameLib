#ifndef COLLIDER_WIRE_FRAME_DRAWER_3D_MAKER_H_
#define COLLIDER_WIRE_FRAME_DRAWER_3D_MAKER_H_

#include <TktkTemplateMetaLib/TypeCheck/isIdType.h>
#include "ColliderWireFrameDrawer3D.h"

namespace tktk
{
	// �uColliderWireFrameDrawer3D�v�̃C���X�^���X���쐬����N���X
	class ColliderWireFrameDrawer3DMaker
	{
	private:  /* �v���C�x�[�g�R���X�g���N�^�B */

		ColliderWireFrameDrawer3DMaker() = default;
		ColliderWireFrameDrawer3DMaker(const ColliderWireFrameDrawer3DMaker& other) = default;
		ColliderWireFrameDrawer3DMaker& operator = (const ColliderWireFrameDrawer3DMaker& other) = default;

	public:

		// �쐬�J�n
		static ColliderWireFrameDrawer3DMaker& makeStart(GameObjectPtr user);

	public:

		// �쐬����
		ComponentPtr<ColliderWireFrameDrawer3D> create();

		// �`��D��x��ݒ肷��
		ColliderWireFrameDrawer3DMaker& drawPriority(float value);

		// �g�p���郌���_�[�^�[�Q�b�g�̃f�B�X�N���v�^�q�[�v�n���h����ݒ肷��
		ColliderWireFrameDrawer3DMaker& useRtvDescriptorHeapHandle(unsigned int value);

		// �g�p����J�����n���h����ݒ肷��
		// �������p�����[�^�̓f�t�H���g�ʏ�J����
		ColliderWireFrameDrawer3DMaker& cameraHandle(unsigned int value);

		// �g�p����J����ID��ݒ肷��i�񋓌^���܂ސ����^��id���n���ꂽ�ꍇ�̂݃r���h�ŁA�֐����őΉ����郊�\�[�X�n���h���ɕϊ������j
		// �������p�����[�^�̓f�t�H���g�ʏ�J����
		template<class IdType, is_idType<IdType> = nullptr>
		ColliderWireFrameDrawer3DMaker& cameraId(IdType value) { return cameraIdImpl(static_cast<int>(value)); }

		// �g�p����V���h�E�}�b�v�J�����n���h����ݒ肷��
		// �������p�����[�^�̓f�t�H���g�V���h�E�}�b�v�J����
		ColliderWireFrameDrawer3DMaker& shadowMapCameraHandle(unsigned int value);

		// �g�p����V���h�E�}�b�v�J����ID��ݒ肷��i�񋓌^���܂ސ����^��id���n���ꂽ�ꍇ�̂݃r���h�ŁA�֐����őΉ����郊�\�[�X�n���h���ɕϊ������j
		// �������p�����[�^�̓f�t�H���g�V���h�E�}�b�v�J����
		template<class IdType, is_idType<IdType> = nullptr>
		ColliderWireFrameDrawer3DMaker& shadowMapCameraId(IdType value) { return shadowMapCameraIdImpl(static_cast<int>(value)); }

		// �g�p���郉�C�g�n���h����ݒ肷��
		// �������p�����[�^�̓f�t�H���g���C�g
		ColliderWireFrameDrawer3DMaker& lightHandle(unsigned int value);

		// �g�p���郉�C�gID��ݒ肷��i�񋓌^���܂ސ����^��id���n���ꂽ�ꍇ�̂݃r���h�ŁA�֐����őΉ����郊�\�[�X�n���h���ɕϊ������j
		// �������p�����[�^�̓f�t�H���g���C�g
		template<class IdType, is_idType<IdType> = nullptr>
		ColliderWireFrameDrawer3DMaker& lightId(IdType value) { return lightIdImpl(static_cast<int>(value)); }

		// ���̐F��ݒ肷��
		ColliderWireFrameDrawer3DMaker& lineColor(const tktkMath::Color & value);

	private: /* �e��id�w��n�̊֐��̎��� */

		ColliderWireFrameDrawer3DMaker& cameraIdImpl(int value);
		ColliderWireFrameDrawer3DMaker& shadowMapCameraIdImpl(int value);
		ColliderWireFrameDrawer3DMaker& lightIdImpl(int value);

	private:

		static ColliderWireFrameDrawer3DMaker m_self;

	private:

		// �쐬�p�ϐ��B
		GameObjectPtr						m_user				{ };
		float								m_drawPriority		{ 0.0f };
		tktkMath::Color						m_lineColor			{ tktkMath::Color_v::white };
		SphereMeshDrawerUseResourceHandles	m_useResourceHandles{  }; // ���uRtvDescriptorHeap�v�̏����p�����[�^�̓o�b�N�o�b�t�@�[
	
	public: /* �s���Ȍ^�̈������n���ꂻ���ɂȂ������ɃR���p�C���G���[�ɂ���ׂ̎d�g�� */

		template<class IdType, is_not_idType<IdType> = nullptr>
		ColliderWireFrameDrawer3DMaker& cameraId(IdType value) { static_assert(false, "CameraId Fraud Type"); }

		template<class IdType, is_not_idType<IdType> = nullptr>
		ColliderWireFrameDrawer3DMaker& shadowMapCameraId(IdType value) { static_assert(false, "ShadowMapCameraId Fraud Type"); }

		template<class IdType, is_not_idType<IdType> = nullptr>
		ColliderWireFrameDrawer3DMaker& lightId(IdType value) { static_assert(false, "LightId Fraud Type"); }
	};
}

#endif // !COLLIDER_WIRE_FRAME_DRAWER_3D_MAKER_H_