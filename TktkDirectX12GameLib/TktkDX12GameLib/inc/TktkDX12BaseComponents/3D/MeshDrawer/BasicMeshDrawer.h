#ifndef BASIC_MESH_DRAWER_H_
#define BASIC_MESH_DRAWER_H_

#include <TktkTemplateMetaLib/TypeCheck/isIdType.h>
#include "../../../TktkDX12Game/Component/ComponentBase.h"
#include "BasicMeshDrawerUseResourceHandles.h"
#include "../Transform3D/Transform3D.h"
#include "../MeshAnimator/MeshAnimator.h"

namespace tktk
{
	// �ʏ탁�b�V���`��R���|�[�l���g
	// �y�K�{�R���|�[�l���g�FTransform3D�z
	class BasicMeshDrawer
		: public ComponentBase
	{
	public:

		BasicMeshDrawer(float drawPriority, const tktkMath::Vector3& baseScale, const tktkMath::Quaternion& baseRotation, const BasicMeshDrawerUseResourceHandles& useResourceHandles);

	public:

		void start();
		void onDestroy();
		void draw() const;

	private:

		// ���W�ϊ��p�̒萔�o�b�t�@�̍X�V
		void updateTransformCbuffer() const;

		// �V���h�E�}�b�v�p�̒萔�o�b�t�@�̍X�V
		void updateShadowMapCbuffer() const;

	private:

		unsigned int m_createCopyTransformCbufferHandle				{ 0U };
		unsigned int m_createCopyShadowMapCbufferHandle				{ 0U };
		unsigned int m_createCopyBoneMatrixCbufferHandle			{ 0U };
		tktkMath::Vector3					m_baseScale				{ tktkMath::Vector3_v::one };
		tktkMath::Quaternion				m_baseRotation			{ tktkMath::Quaternion_v::identity };
		BasicMeshDrawerUseResourceHandles	m_useResourceHandles	{ };
		ComponentPtr<Transform3D>			m_transform				{ };
		ComponentPtr<MeshAnimator>			m_animator				{ };
	};
}
#endif // !BASIC_MESH_DRAWER_H_