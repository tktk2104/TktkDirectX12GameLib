#ifndef BOX_MESH_DRAWER_H_
#define BOX_MESH_DRAWER_H_

#include <TktkMath/Structs/Color.h>
#include <TktkMath/Structs/Vector3.h>
#include "../../../TktkDX12Game/Component/ComponentBase.h"
#include "BoxMeshDrawerUseResourceHandles.h"
#include "../Transform3D/Transform3D.h"

namespace tktk
{
	// 立方体メッシュ描画コンポーネント
	class BoxMeshDrawer
		: public ComponentBase
	{
	public:

		BoxMeshDrawer(float drawPriority, const tktkMath::Vector3& boxSize, const tktkMath::Vector3& localPosition, const tktkMath::Color& albedoColor, const BoxMeshDrawerUseResourceHandles& useResourceHandles);

	public:

		void start();
		void onDestroy();
		void draw() const;

	public:

		const tktkMath::Color& getAlbedoColor() const;

		void setAlbedoColor(const tktkMath::Color& color);

	private:

		// 座標変換用の定数バッファの更新
		void updateTransformCbuffer() const;

		// シャドウマップ用の定数バッファの更新
		void updateShadowMapCbuffer() const;

	private:

		tktkMath::Vector3	m_boxSize;
		tktkMath::Vector3	m_localPosition;
		tktkMath::Color		m_albedoColor;
		size_t				m_createUploadTransformCbufferHandle{ 0U };
		size_t				m_createUploadShadowMapCbufferHandle{ 0U };
		size_t				m_createUploadMonoColorMeshCbufferHandle{ 0U };
		BoxMeshDrawerUseResourceHandles		m_useResourceHandles;
		ComponentPtr<Transform3D>			m_transform{ };
	};
}
#endif // !BOX_MESH_DRAWER_H_