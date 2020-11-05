#ifndef BOX_MESH_SHADOW_MAP_WRITER_H_
#define BOX_MESH_SHADOW_MAP_WRITER_H_

#include <TktkTemplateMetaLib/TypeCheck/isIdType.h>
#include "../../../TktkDX12Game/Component/ComponentBase.h"
#include "../Transform3D/Transform3D.h"

namespace tktk
{
	// 立方体メッシュのシャドウマップ書き込みコンポーネント
	// 【必須コンポーネント：Transform3D】
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

		// 座標変換用の定数バッファの更新
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