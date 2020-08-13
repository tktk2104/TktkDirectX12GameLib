#ifndef BASIC_MESH_SHADOW_MAP_WRITER_H_
#define BASIC_MESH_SHADOW_MAP_WRITER_H_

#include <TktkTemplateMetaLib/TypeCheck/isIdType.h>
#include "../../../TktkDX12Game/Component/ComponentBase.h"
#include "../Transform3D/Transform3D.h"

namespace tktk
{
	// 通常メッシュのシャドウマップ書き込みコンポーネント
	// 【必須コンポーネント：Transform3D】
	class BasicMeshShadowMapWriter
		: public ComponentBase
	{
	public:

		BasicMeshShadowMapWriter(float drawPriority, unsigned int meshId, unsigned int skeletonId, unsigned int cameraId);

	public:

		void start();
		void draw() const;

	private:

		unsigned int				m_meshId;
		unsigned int				m_skeletonId;
		unsigned int				m_cameraId;
		ComponentPtr<Transform3D>	m_transform{ };
	};
}
#endif // !BASIC_MESH_SHADOW_MAP_WRITER_H_