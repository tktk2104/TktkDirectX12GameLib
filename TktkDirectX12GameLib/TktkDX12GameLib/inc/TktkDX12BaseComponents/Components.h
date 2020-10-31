#ifndef COMPONENTS_H_
#define COMPONENTS_H_

#include "2D/Transform2D/Transform2DMaker.h"
#include "2D/InertialMovement2D/InertialMovement2DMaker.h"
#include "2D/InertialRotatement2D/InertialRotatement2DMaker.h"
#include "2D/CircleCollider/CircleColliderMaker.h"
#include "2D/Polygon2dCollider/Polygon2dColliderMaker.h"
#include "2D/RectCollider/RectColliderMaker.h"
#include "2D/ColliderWireFrameDrawer2D/ColliderWireFrameDrawer2DMaker.h"
#include "2D/Line2dDrawer/Line2DDrawerMaker.h"
#include "2D/SpriteDrawer/SpriteDrawerMaker.h"
#include "2D/SpriteDrawer/SpriteClippingDrawerMaker.h"
#include "2D/PostEffectDrawer/PostEffectDrawerMaker.h"

#include "3D/Transform3D/Transform3DMaker.h"
#include "3D/InertialMovement3D/InertialMovement3DMaker.h"
#include "3D/SphereCollider/SphereColliderMaker.h"
#include "3D/BoxCollider/BoxColliderMaker.h"
#include "3D/ColliderWireFrameDrawer3D/ColliderWireFrameDrawer3DMaker.h"
#include "3D/Light/PointLightControllerMaker.h"
#include "3D/Light/DirectionalLightControllerMaker.h"
#include "3D/Camera/BasicCameraControllerMaker.h"
#include "3D/Camera/OrthographicCameraControllerMaker.h"
#include "3D/Camera/FirstPersonModuleMaker.h"
#include "3D/BillboardDrawer/BillboardDrawerMaker.h"
#include "3D/BillboardDrawer/BillboardClippingDrawerMaker.h"
#include "3D/MeshDrawer/BasicMeshDrawerMaker.h"
#include "3D/MeshDrawer/SphereMeshDrawerMaker.h"
#include "3D/MeshDrawer/SphereMeshWireFrameDrawerMaker.h"
#include "3D/MeshDrawer/BoxMeshDrawerMaker.h"
#include "3D/MeshDrawer/BoxMeshWireFrameDrawerMaker.h"
#include "3D/MeshAnimator/MeshAnimatorMaker.h"
#include "3D/MeshAnimator/MotionChangerMaker.h"
#include "3D/ShadowMapWriter/BasicMeshShadowMapWriterMaker.h"
#include "3D/ShadowMapWriter/SphereMeshShadowMapWriterMaker.h"
#include "3D/ShadowMapWriter/BoxMeshShadowMapWriterMaker.h"

#include "Other/ReceiveMessageToSelfDestroyer/ReceiveMessageToSelfDestroyerMaker.h"
#include "Other/Sound/SoundPlayerMaker.h"

class TktkManual;

// ���̍s�̃R�����g�A�E�g���O���ƁgF12�h�őΉ�����N���X�ɔ�ׂ܂�
//#define SAMPLE

#ifdef SAMPLE
namespace tktk
{
	/* �Q�����R���|�[�l���g�B */
	//<
		// �Q�������W�A�X�P�[���A��]�R���|�[�l���g
		using C01 = Transform2D;

		// �ȈՊ����Q�����ړ��R���|�[�l���g
		using C02 = InertialMovement2D;

		// �ȈՊ����Q������]�R���|�[�l���g
		using C03 = InertialRotatement2D;

		// �~�̓����蔻��R���|�[�l���g
		using C04 = CircleCollider;

		// �Q�����|���S�������蔻��R���|�[�l���g
		using C05 = Polygon2dCollider;

		// �l�p�`�̓����蔻��R���|�[�l���g
		using C06 = RectCollider;

		// �Q�����Փ˔���̋��E����`�悷��R���|�[�l���g
		using C08 = ColliderWireFrameDrawer2D;

		// �Q�����Ő��`�悷��R���|�[�l���g
		using C09 = Line2DDrawer;

		// �X�v���C�g�`��R���|�[�l���g
		using C10 = SpriteDrawer;

		// �X�v���C�g�؂蔲���`��R���|�[�l���g
		using C11 = SpriteClippingDrawer;

		// �|�X�g�G�t�F�N�g�`��R���|�[�l���g
		using C12 = PostEffectDrawer;
	//>



	/* �R�����R���|�[�l���g�B */
	//<
		// �R�������W�A�X�P�[���A��]�R���|�[�l���g
		using C30 = Transform3D;

		// �ȈՊ����R�����ړ��R���|�[�l���g
		using C31 = InertialMovement3D;

		// ���̓����蔻��R���|�[�l���g
		using C32 = SphereCollider;

		// AABB�̓����蔻��R���|�[�l���g
		using C33 = BoxCollider;

		// �Q�����Փ˔���̋��E����`�悷��R���|�[�l���g
		using C34 = ColliderWireFrameDrawer3D;

		// �|�C���g���C�g�̐���R���|�[�l���g
		using C35 = PointLightController;

		// �f�B���N�V���i�����C�g�̐���R���|�[�l���g
		using C36 = DirectionalLightController;

		// �ʏ�J�����̐���R���|�[�l���g
		using C37 = BasicCameraController;

		// ���s���e�J�����̐���R���|�[�l���g
		using C38 = OrthographicCameraController;

		// �P�l�̈ړ��R���|�[�l���g
		using C39 = FirstPersonModule;

		// �r���{�[�h�`��R���|�[�l���g
		using C40 = BillboardDrawer;

		// �r���{�[�h�؂蔲���`��R���|�[�l���g
		using C41 = FirstPersonModule;

		// ���b�V���̕`��R���|�[�l���g
		using C42 = BasicMeshDrawer;

		// ���̃��b�V���̕`��R���|�[�l���g
		using C43 = SphereMeshDrawer;

		// ���̃��b�V�����C���[�t���[���̕`��R���|�[�l���g
		using C44 = SphereMeshWireFrameDrawer;

		// �����̃��b�V���̕`��R���|�[�l���g
		using C45 = BoxMeshDrawer;

		// �����̃��b�V�����C���[�t���[���̕`��R���|�[�l���g
		using C46 = BoxMeshWireFrameDrawer;

		// ���b�V���̃A�j���[�V�����R���|�[�l���g
		using C47 = MeshAnimator;

		// ���[�V�����ύX�R���|�[�l���g
		using C48 = MotionChanger;

		// ���b�V���̃V���h�E�}�b�v�`��R���|�[�l���g
		using C49 = BasicMeshShadowMapWriter;

		// ���̃��b�V���̃V���h�E�}�b�v�`��R���|�[�l���g
		using C50 = SphereMeshShadowMapWriter;

		// �����̃��b�V���̃V���h�E�}�b�v�`��R���|�[�l���g
		using C51 = BoxMeshShadowMapWriter;
	//>



	/* ���̑��̃R���|�[�l���g�B */
	//<
		// ����̃��b�Z�[�W���󂯎�������Ɏ��g������GameObject���E���R���|�[�l���g
		using C60 = ReceiveMessageToSelfDestroyer;

		// �T�E���h�Đ��R���|�[�l���g
		using C61 = SoundPlayer;
	//>
}
#endif // !SAMPLE

#endif // !COMPONENTS_H_