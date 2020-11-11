#ifndef SPHERE_MESH_SHADOW_MAP_WRITER_H_
#define SPHERE_MESH_SHADOW_MAP_WRITER_H_

/* base class */
#include "../../../TktkDX12Game/DXGameResource/GameObjectResouse/Component/ComponentBase.h"

/* class member */
#include <TktkMath/Structs/Vector3.h>

namespace tktk
{
	/* class member */
	class Transform3D;

	// 球体メッシュのシャドウマップ書き込みコンポーネント
	// 【必須コンポーネント：Transform3D】
	class SphereMeshShadowMapWriter
		: public ComponentBase
	{
	public:

		SphereMeshShadowMapWriter(float drawPriority, float radius, const tktkMath::Vector3& localPosition, size_t cameraHandle);

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
		size_t				m_createUploadTransformCbufferHandle{ 0U };
		size_t				m_cameraHandle;
		ComponentPtr<Transform3D>	m_transform{ };
	};
}
#endif // !SPHERE_MESH_SHADOW_MAP_WRITER_H_