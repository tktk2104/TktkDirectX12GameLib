#ifndef SPRITE_CLIPPING_DRAWER_H_
#define SPRITE_CLIPPING_DRAWER_H_

#include <TktkTemplateMetaLib/TypeCheck/isIdType.h>
#include <TktkMath/Structs/Color.h>
#include <TktkMath/Structs/Vector2.h>
#include "../../../TktkDX12Game/Component/ComponentBase.h"
#include "../Transform2D/Transform2D.h"
#include "../../../TktkDX12Game/DXGameResource/Sprite/SpriteClippingParam.h"

namespace tktk
{
	// スプライト切り抜き描画コンポーネント
	// 【必須コンポーネント：Transform2D】
	class SpriteClippingDrawer
		: public ComponentBase
	{
	public:

		SpriteClippingDrawer(float drawPriority, unsigned int spriteMaterialHandle, unsigned int useRtvDescriptorHeapHandle, const tktkMath::Vector2& centerRate, const SpriteClippingParam& clippingParam);

	public:

		void start();
		void onDestroy();
		void draw() const;

	public:

		// スプライトマテリアルハンドルを再設定する
		void setSpriteMaterialHandle(unsigned int handle);

		// スプライトマテリアルIDを再設定する（列挙型を含む整数型のidが渡された場合のみビルド可）
		// ※内部で対応するリソースハンドルに変換される
		template <class IdType, is_idType<IdType> = nullptr>
		void setSpriteMaterialId(IdType id) { setSpriteMaterialIdImpl(static_cast<unsigned int>(id)); }
		
		// スプライトの中心位置の割合を設定する
		void setCenterRate(const tktkMath::Vector2& centerRate);

		// 切り取る範囲のテクスチャ座標での左上座標を設定する（テクセル）
		void setClippingLeftTopPos(const tktkMath::Vector2& leftTopPos);

		// 切り取る範囲の大きさを設定する（テクセル）
		void setClippingSize(const tktkMath::Vector2& size);

	private:

		// 各種id指定系の関数の実装
		void setSpriteMaterialIdImpl(int id);

	private:

		unsigned int				m_createCopyTransformCbufferHandle{ 0U };
		unsigned int				m_useRtvDescriptorHeapHandle;
		unsigned int				m_spriteMaterialHandle;
		tktkMath::Vector2			m_spriteCenterRate;
		SpriteClippingParam			m_clippingParam;
		ComponentPtr<Transform2D>	m_transform;

	public:

		template <class IdType, is_not_idType<IdType> = nullptr>
		void setSpriteMaterialId(IdType id) { static_assert(false, "SpriteMaterialId Fraud Type"); }
	};
}
#endif // !SPRITE_CLIPPING_DRAWER_H_