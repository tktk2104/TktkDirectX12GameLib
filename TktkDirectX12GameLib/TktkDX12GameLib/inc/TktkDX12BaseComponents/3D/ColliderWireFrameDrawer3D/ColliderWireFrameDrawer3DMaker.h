#ifndef COLLIDER_WIRE_FRAME_DRAWER_3D_MAKER_H_
#define COLLIDER_WIRE_FRAME_DRAWER_3D_MAKER_H_

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

		// ���̐F��ݒ肷��
		ColliderWireFrameDrawer3DMaker& lineColor(const tktkMath::Color & value);

	private:

		static ColliderWireFrameDrawer3DMaker m_self;

	private:

		// �쐬�p�ϐ��B
		GameObjectPtr						m_user				{ };
		tktkMath::Color						m_lineColor			{ tktkMath::Color_v::white };
	};
}
#endif // !COLLIDER_WIRE_FRAME_DRAWER_3D_MAKER_H_