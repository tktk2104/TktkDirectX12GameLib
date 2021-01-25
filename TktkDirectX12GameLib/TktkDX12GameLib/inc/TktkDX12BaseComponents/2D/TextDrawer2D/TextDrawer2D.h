#ifndef TEXT_DRAWER_2D_H_
#define TEXT_DRAWER_2D_H_

/* class member */
#include <string>
#include <vector>
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

	// テキスト描画コンポーネント
	class TextDrawer2D
		: public ComponentBase
	{
	public:

		TextDrawer2D(
			float drawPriority,
			size_t fontHandle,
			const std::string& initText,
			const tktkMath::Vector2& localPosition,
			const tktkMath::Vector2& localScale,
			const tktkMath::Vector2& centerRate,
			const tktkMath::Color& blendRate
		);

	public:

		void start();
		void afterCollide();

	public:

		// 使用するフォントIDを再設定する
		void setFontId(ResourceIdCarrier fontId);

		// 描画するテキストを更新する
		void updateText(const std::string& text);

		// テキストのローカル座標を再設定する
		void setLocalPosition(const tktkMath::Vector2& localPosition);

		// テキストのローカルスケールを再設定する
		void setLocalScale(const tktkMath::Vector2& localScale);

		// テキストの中心位置の割合を再設定する
		void setCenterRate(const tktkMath::Vector2& centerRate);

		// ブレンドレートを再設定する
		void setBlendRate(const tktkMath::Color& blendRate);

	private:

		float						m_drawPriority;
		size_t						m_fontHandle;
		std::string					m_tempText;
		std::vector<unsigned char>	m_textureData;
		float						m_useTextureDataWidth{ 0.0f };
		tktkMath::Vector2			m_localPosition;
		tktkMath::Vector2			m_localScale;
		tktkMath::Vector2			m_centerRate;
		tktkMath::Color				m_blendRate;
		ComponentPtr<Transform2D>	m_transform;
	};
}
#endif // !TEXT_DRAWER_2D_H_