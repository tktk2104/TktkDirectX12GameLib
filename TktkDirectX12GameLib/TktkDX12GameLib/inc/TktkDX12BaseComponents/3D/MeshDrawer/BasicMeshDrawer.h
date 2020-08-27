#ifndef BASIC_MESH_DRAWER_H_
#define BASIC_MESH_DRAWER_H_

#include <TktkTemplateMetaLib/TypeCheck/isIdType.h>
#include "../../../TktkDX12Game/Component/ComponentBase.h"
#include "../Transform3D/Transform3D.h"
#include "../MeshAnimator/MeshAnimator.h"

namespace tktk
{
	// 通常メッシュ描画コンポーネント
	// 【必須コンポーネント：Transform3D】
	class BasicMeshDrawer
		: public ComponentBase
	{
	public:

		BasicMeshDrawer(float drawPriority, unsigned int meshHandle, unsigned int skeletonHandle, unsigned int cameraHandle, unsigned int shadowMapCameraHandle, unsigned int lightHandle, unsigned int useRtvDescriptorHeapHandle);

	public:

		void start();
		void draw() const;

	private:

		unsigned int				m_useRtvDescriptorHeapHandle;
		unsigned int				m_meshHandle;
		unsigned int				m_skeletonHandle;
		unsigned int				m_cameraHandle;
		unsigned int				m_shadowMapCameraHandle;
		unsigned int				m_lightHandle;
		ComponentPtr<Transform3D>	m_transform{ };
		ComponentPtr<MeshAnimator>	m_animator{ };
	};
}
#endif // !BASIC_MESH_DRAWER_H_