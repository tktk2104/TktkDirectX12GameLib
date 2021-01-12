#ifndef SPRITE_DRAWER_H_
#define SPRITE_DRAWER_H_

/* class member */
#include <TktkMath/Structs/Color.h>
#include <TktkMath/Structs/Vector2.h>

/* funcUseType */
#include "../../../TktkDX12Game/UtilityProcessManager/ResourceHandleGetter/ResourceIdConverter/ResourceIdCarrier.h"

/* base class */
#include "../../../TktkDX12Game/DXGameResource/GameObjectResouse/Component/ComponentBase.h"

namespace tktk
{
	/* class member */
	class Transform2D;

	// スプライト描画コンポーネント
	// 【必須コンポーネント：Transform2D】
	class SpriteDrawer
		: public ComponentBase
	{
	public:

		SpriteDrawer(
			float drawPriority,
			size_t spriteMaterialHandle,
			const tktkMath::Vector2& centerRate,
			const tktkMath::Color& blendRate,
			const tktkMath::Vector2& clippingLeftTopPos,
			const tktkMath::Vector2& clippingSize
		);

	public:

		void start();
		void afterCollide();

	public:

		// スプライトマテリアルハンドルを再設定する
		void setSpriteMaterialHandle(size_t handle);

		// スプライトマテリアルIDを再設定する（列挙型を含む整数型のidが渡された場合のみビルド可）
		// ※内部で対応するリソースハンドルに変換される
		void setSpriteMaterialId(ResourceIdCarrier id);
		
		// スプライトの中心位置の割合を設定する
		void setCenterRate(const tktkMath::Vector2& centerRate);

		// ブレンドレートを取得する
		const tktkMath::Color& getBlendRate() const;

		// ブレンドレートを設定する
		void setBlendRate(const tktkMath::Color& blendRate);

		// 切り取る範囲のテクスチャ座標での左上座標を設定する（テクセル）
		void setClippingLeftTopPos(const tktkMath::Vector2& leftTopPos);

		// 切り取る範囲の大きさを設定する（テクセル）
		void setClippingSize(const tktkMath::Vector2& size);

		// 切り取る範囲の左上座標を設定する（テクスチャサイズを（1, 1）とした時の割合）
		void setClippingLeftTopPosRate(const tktkMath::Vector2& leftTopPosRate);

		// 切り取る範囲の大きさを設定する（テクスチャサイズを（1, 1）とした時の割合）
		void setClippingSizeRate(const tktkMath::Vector2& sizeRate);

	private:

		size_t						m_spriteMaterialHandle;
		float						m_drawPriority;
		tktkMath::Vector2			m_centerRate;
		tktkMath::Color				m_blendRate;
		tktkMath::Vector2			m_clippingLeftTopPos;
		tktkMath::Vector2			m_clippingSize;
		ComponentPtr<Transform2D>	m_transform;
	};
}
#endif // !SPRITE_DRAWER_H_