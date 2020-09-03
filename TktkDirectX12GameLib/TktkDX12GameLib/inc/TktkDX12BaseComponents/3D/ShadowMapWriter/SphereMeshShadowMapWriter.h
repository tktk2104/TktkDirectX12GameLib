#ifndef SPHERE_MESH_SHADOW_MAP_WRITER_H_
#define SPHERE_MESH_SHADOW_MAP_WRITER_H_

#include <TktkTemplateMetaLib/TypeCheck/isIdType.h>
#include "../../../TktkDX12Game/Component/ComponentBase.h"
#include "../Transform3D/Transform3D.h"

namespace tktk
{
	// ���̃��b�V���̃V���h�E�}�b�v�������݃R���|�[�l���g
	// �y�K�{�R���|�[�l���g�FTransform3D�z
	class SphereMeshShadowMapWriter
		: public ComponentBase
	{
	public:

		SphereMeshShadowMapWriter(float drawPriority, float radius, const tktkMath::Vector3& localPosition, unsigned int cameraHandle);

	public:

		void start();
		void onDestroy();
		void draw() const;

	private:

		// ���W�ϊ��p�̒萔�o�b�t�@�̍X�V
		void updateTransformCbuffer() const;

	private:

		float				m_radius;
		tktkMath::Vector3	m_localPosition;
		unsigned int		m_createCopyTransformCbufferHandle{ 0U };
		unsigned int		m_cameraHandle;
		ComponentPtr<Transform3D>	m_transform{ };
	};
}
#endif // !SPHERE_MESH_SHADOW_MAP_WRITER_H_