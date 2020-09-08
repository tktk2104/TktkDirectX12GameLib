#ifndef BILLBOARD_CLIPPING_DRAWER_H_
#define BILLBOARD_CLIPPING_DRAWER_H_

#include <TktkTemplateMetaLib/TypeCheck/isIdType.h>
#include <TktkMath/Structs/Color.h>
#include <TktkMath/Structs/Vector2.h>
#include "../../../TktkDX12Game/Component/ComponentBase.h"
#include "../Transform3D/Transform3D.h"

namespace tktk
{
	// ビルボード切り抜き描画コンポーネント
	// 【必須コンポーネント：Transform3D（回転はｚ軸、スケールはｘｙ軸のみ参照します）】
	class BillboardClippingDrawer
		: public ComponentBase
	{
	public:

		BillboardClippingDrawer(float drawPriority, unsigned int billboardMaterialHandle, unsigned int useRtvDescriptorHeapHandle, unsigned int cameraHandle, const tktkMath::Vector2& centerRate, const tktkMath::Color& blendRate, const BillboardClippingParam& clippingParam);

	public:

		void start();
		void onDestroy();
		void draw() const;

	public:

		// ビルボードマテリアルハンドルを再設定する
		void setBillboardMaterialHandle(unsigned int handle);

		// ビルボードマテリアルIDを再設定する（列挙型を含む整数型のidが渡された場合のみビルド可）
		// ※内部で対応するリソースハンドルに変換される
		template <class IdType, is_idType<IdType> = nullptr>
		void setBillboardMaterialId(IdType id) { setBillboardMaterialIdImpl(static_cast<unsigned int>(id)); }

		// ビルボードの中心位置の割合を設定する
		void setCenterRate(const tktkMath::Vector2& centerRate);

		// 切り取る範囲のテクスチャ座標での左上座標を設定する（テクセル）
		void setClippingLeftTopPos(const tktkMath::Vector2& leftTopPos);

		// 切り取る範囲の大きさを設定する（テクセル）
		void setClippingSize(const tktkMath::Vector2& size);

	private:

		// 各種id指定系の関数の実装
		void setBillboardMaterialIdImpl(int id);

	private:

		unsigned int				m_createCopyTransformCbufferHandle{ 0U };
		unsigned int				m_useRtvDescriptorHeapHandle;
		unsigned int				m_cameraHandle;
		unsigned int				m_billboardMaterialHandle;
		tktkMath::Vector2			m_centerRate;
		tktkMath::Color				m_blendRate;
		BillboardClippingParam		m_clippingParam;
		ComponentPtr<Transform3D>	m_transform;

	public:

		template <class IdType, is_not_idType<IdType> = nullptr>
		void setBillboardMaterialId(IdType id) { static_assert(false, "BillboardMaterialId Fraud Type"); }
	};
}
#endif // !BILLBOARD_CLIPPING_DRAWER_H_
