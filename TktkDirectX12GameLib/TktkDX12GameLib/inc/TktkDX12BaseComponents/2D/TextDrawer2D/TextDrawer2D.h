#ifndef TEXT_DRAWER_2D_H_
#define TEXT_DRAWER_2D_H_

/* class member */
#include <string>
#include <TktkMath/Structs/Color.h>
#include <TktkMath/Structs/Vector2.h>
#include "../../../TktkDX12Game/DXGameResource/DXGameShaderResouse/Sprite/Structs/SpriteClippingParam.h"

/* funcUseType */
#include "../../../TktkDX12Game/UtilityProcessManager/ResourceHandleGetter/ResourceIdConverter/ResourceIdCarrier.h"

/* base class */
#include "../../../TktkDX12Game/DXGameResource/GameObjectResouse/Component/ComponentBase.h"

namespace tktk
{
	/* class member */
	class Transform2D;

	// テキスト描画コンポーネント
	class TextDrawer2D
		: public ComponentBase
	{
	public:

		TextDrawer2D(
			float drawPriority,
			size_t fontHandle,
			const std::string& initText,
			size_t useRtvDescriptorHeapHandle,
			const tktkMath::Vector2& centerRate,
			const tktkMath::Color& blendRate
		);

	public:

		void start();
		void onDestroy();
		void afterCollide();
		void draw() const;

	private:

		size_t						m_createUploadTransformCbufferHandle{ 0U };
		size_t						m_createUploadTextureBufferHandle	{ 0U };
		size_t						m_useRtvDescriptorHeapHandle;
		size_t						m_fontHandle;
		std::string					m_tempText;
		tktkMath::Vector2			m_spriteCenterRate;
		tktkMath::Color				m_blendRate;
		SpriteClippingParam			m_clippingParam	{};
		ComponentPtr<Transform2D>	m_transform;
	};
}
#endif // !TEXT_DRAWER_2D_H_