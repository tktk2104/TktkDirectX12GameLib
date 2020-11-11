#ifndef BILLBOARD_CLIPPING_DRAWER_H_
#define BILLBOARD_CLIPPING_DRAWER_H_

/* base class */
#include "../../../TktkDX12Game/DXGameResource/GameObjectResouse/Component/ComponentBase.h"

/* funcUseType */
#include "TktkDX12Game/UtilityProcessManager/ResourceHandleGetter/ResourceIdConverter/ResourceIdCarrier.h"

/* class member */
#include <TktkMath/Structs/Color.h>
#include <TktkMath/Structs/Vector2.h>
#include "TktkDX12Game/DXGameResource/DXGameShaderResouse/Billboard/BillboardClippingParam.h"

namespace tktk
{
	/* class member */
	class Transform3D;

	// ビルボード切り抜き描画コンポーネント
	// 【必須コンポーネント：Transform3D（回転はｚ軸、スケールはｘｙ軸のみ参照します）】
	class BillboardClippingDrawer
		: public ComponentBase
	{
	public:

		BillboardClippingDrawer(float drawPriority, size_t billboardMaterialHandle, size_t useRtvDescriptorHeapHandle, size_t cameraHandle, const tktkMath::Vector2& centerRate, const tktkMath::Color& blendRate, const BillboardClippingParam& clippingParam);

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

		// 切り取る範囲のテクスチャ座標での左上座標を設定する（テクセル）
		void setClippingLeftTopPos(const tktkMath::Vector2& leftTopPos);

		// 切り取る範囲の大きさを設定する（テクセル）
		void setClippingSize(const tktkMath::Vector2& size);

	private:

		size_t						m_createUploadTransformCbufferHandle{ 0U };
		size_t						m_useRtvDescriptorHeapHandle;
		size_t						m_cameraHandle;
		size_t						m_billboardMaterialHandle;
		tktkMath::Vector2			m_centerRate;
		tktkMath::Color				m_blendRate;
		BillboardClippingParam		m_clippingParam;
		ComponentPtr<Transform3D>	m_transform;
	};
}
#endif // !BILLBOARD_CLIPPING_DRAWER_H_
