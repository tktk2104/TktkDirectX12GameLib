#ifndef BOX_MESH_SHADOW_MAP_WRITER_H_
#define BOX_MESH_SHADOW_MAP_WRITER_H_

#include <TktkTemplateMetaLib/TypeCheck/isIdType.h>
#include "../../../TktkDX12Game/Component/ComponentBase.h"
#include "../Transform3D/Transform3D.h"

namespace tktk
{
	// �����̃��b�V���̃V���h�E�}�b�v�������݃R���|�[�l���g
	// �y�K�{�R���|�[�l���g�FTransform3D�z
	class BoxMeshShadowMapWriter
		: public ComponentBase
	{
	public:

		BoxMeshShadowMapWriter(float drawPriority, const tktkMath::Vector3& boxSize, const tktkMath::Vector3& localPosition, size_t cameraHandle);

	public:

		void start();
		void onDestroy();
		void draw() const;

	private:

		// ���W�ϊ��p�̒萔�o�b�t�@�̍X�V
		void updateTransformCbuffer() const;

	private:

		tktkMath::Vector3	m_boxSize;
		tktkMath::Vector3	m_localPosition;
		size_t				m_createUploadTransformCbufferHandle{ 0U };
		size_t				m_cameraHandle;
		ComponentPtr<Transform3D>	m_transform{ };
	};
}
#endif // !BOX_MESH_SHADOW_MAP_WRITER_H_