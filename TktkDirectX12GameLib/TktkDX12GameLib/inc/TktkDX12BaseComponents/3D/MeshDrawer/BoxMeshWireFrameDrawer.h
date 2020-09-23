#ifndef BOX_MESH_WIRE_FRAME_DRAWER_H_
#define BOX_MESH_WIRE_FRAME_DRAWER_H_

#include <TktkMath/Structs/Color.h>
#include <TktkMath/Structs/Vector3.h>
#include "../../../TktkDX12Game/Component/ComponentBase.h"
#include "BoxMeshDrawerUseResourceHandles.h"
#include "../Transform3D/Transform3D.h"

namespace tktk
{
	// 立方体メッシュワイヤーフレーム描画コンポーネント
	class BoxMeshWireFrameDrawer
		: public ComponentBase
	{
	public:

		BoxMeshWireFrameDrawer(float drawPriority, const tktkMath::Vector3& boxSize, const tktkMath::Vector3& localPosition, const tktkMath::Color& albedoColor, const BoxMeshDrawerUseResourceHandles& useResourceHandles);

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
		unsigned int		m_createCopyTransformCbufferHandle{ 0U };
		unsigned int		m_createCopyShadowMapCbufferHandle{ 0U };
		unsigned int		m_createCopyMonoColorMeshCbufferHandle{ 0U };
		BoxMeshDrawerUseResourceHandles	m_useResourceHandles;
		ComponentPtr<Transform3D>		m_transform{ };
	};
}
#endif // !BOX_MESH_WIRE_FRAME_DRAWER_H_