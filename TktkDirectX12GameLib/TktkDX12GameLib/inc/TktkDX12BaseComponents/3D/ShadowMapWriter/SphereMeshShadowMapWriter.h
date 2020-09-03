#ifndef SPHERE_MESH_SHADOW_MAP_WRITER_H_
#define SPHERE_MESH_SHADOW_MAP_WRITER_H_

#include <TktkTemplateMetaLib/TypeCheck/isIdType.h>
#include "../../../TktkDX12Game/Component/ComponentBase.h"
#include "../Transform3D/Transform3D.h"

namespace tktk
{
	// 球体メッシュのシャドウマップ書き込みコンポーネント
	// 【必須コンポーネント：Transform3D】
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

		// 座標変換用の定数バッファの更新
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