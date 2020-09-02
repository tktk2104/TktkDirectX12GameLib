#ifndef BASIC_MESH_SHADOW_MAP_WRITER_H_
#define BASIC_MESH_SHADOW_MAP_WRITER_H_

#include <TktkTemplateMetaLib/TypeCheck/isIdType.h>
#include "../../../TktkDX12Game/Component/ComponentBase.h"
#include "../Transform3D/Transform3D.h"

namespace tktk
{
	// �ʏ탁�b�V���̃V���h�E�}�b�v�������݃R���|�[�l���g
	// �y�K�{�R���|�[�l���g�FTransform3D�z
	class BasicMeshShadowMapWriter
		: public ComponentBase
	{
	public:

		BasicMeshShadowMapWriter(float drawPriority, unsigned int meshHandle, unsigned int skeletonHandle, unsigned int cameraHandle);

	public:

		void start();
		void onDestroy();
		void draw() const;

	private:

		// ���W�ϊ��p�̒萔�o�b�t�@�̍X�V
		void updateTransformCbuffer() const;

	private:

		unsigned int				m_createCopyTransformCbufferHandle{ 0U };
		unsigned int				m_createCopyBoneMatrixCbufferHandle{ 0U };
		unsigned int				m_meshHandle;
		unsigned int				m_skeletonHandle;
		unsigned int				m_cameraHandle;
		ComponentPtr<Transform3D>	m_transform{ };
	};
}
#endif // !BASIC_MESH_SHADOW_MAP_WRITER_H_