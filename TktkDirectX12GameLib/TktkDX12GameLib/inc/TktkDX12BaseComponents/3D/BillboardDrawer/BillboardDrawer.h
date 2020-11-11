#ifndef BILLBOARD_DRAWER_H_
#define BILLBOARD_DRAWER_H_

/* base class */
#include "../../../TktkDX12Game/DXGameResource/GameObjectResouse/Component/ComponentBase.h"

/* funcUseType */
#include "TktkDX12Game/UtilityProcessManager/ResourceHandleGetter/ResourceIdConverter/ResourceIdCarrier.h"

/* class member */
#include <TktkMath/Structs/Color.h>
#include <TktkMath/Structs/Vector2.h>


namespace tktk
{
	/* class member */
	class Transform3D;

	// ビルボード描画コンポーネント
	// 【必須コンポーネント：Transform3D（回転はｚ軸、スケールはｘｙ軸のみ参照します）】
	class BillboardDrawer
		: public ComponentBase
	{
	public:

		BillboardDrawer(float drawPriority, size_t billboardMaterialHandle, size_t useRtvDescriptorHeapHandle, size_t cameraHandle, const tktkMath::Vector2& centerRate, const tktkMath::Color& blendRate);

	public:

		void start();
		void onDestroy();
		void draw() const;

	public:

		// ビルボードマテリアルハンドルを再設定する
		void setBillboardMaterialHandle(size_t handle);

		// ビルボードマテリアルIDを再設定する（列挙型を含む整数型のidが渡された場合のみビルド可）
		// ※内部で対応するリソースハンドルに変換される
		void setBillboardMaterialId(ResourceIdCarrier id);

		// ビルボードの中心位置の割合を設定する
		void setCenterRate(const tktkMath::Vector2& centerRate);

	private:

		size_t						m_createUploadTransformCbufferHandle{ 0U };
		size_t						m_useRtvDescriptorHeapHandle;
		size_t						m_cameraHandle;
		size_t						m_billboardMaterialHandle;
		tktkMath::Vector2			m_centerRate;
		tktkMath::Color				m_blendRate;
		ComponentPtr<Transform3D>	m_transform;
	};
}
#endif // !BILLBOARD_DRAWER_H_