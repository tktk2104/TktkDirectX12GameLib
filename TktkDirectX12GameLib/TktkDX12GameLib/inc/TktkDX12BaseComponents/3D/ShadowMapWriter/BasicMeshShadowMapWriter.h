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

		BasicMeshShadowMapWriter(float drawPriority, unsigned int meshHandle, unsigned int skeletonHandle, unsigned int cameraHandle);

	public:

		void start();
		void onDestroy();
		void draw() const;

	private:

		// 座標変換用の定数バッファの更新
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