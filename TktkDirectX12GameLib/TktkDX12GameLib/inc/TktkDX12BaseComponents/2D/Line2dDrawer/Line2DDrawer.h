#ifndef LINE_2D_DRAWER_H_
#define LINE_2D_DRAWER_H_

#include <vector>
#include <TktkTemplateMetaLib/TypeCheck/isIdType.h>
#include <TktkMath/Structs/Color.h>
#include <TktkMath/Structs/Vector2.h>
#include "../../../TktkDX12Game/Component/ComponentBase.h"
#include "../Transform2D/Transform2D.h"

namespace tktk
{
	// 2次元線分描画コンポーネント
	// 【必須コンポーネント：Transform2D】
	class Line2DDrawer
		: public ComponentBase
	{
	public:

		Line2DDrawer(
			float drawPriority,
			unsigned int useLine2DMaterialId,
			const std::vector<tktkMath::Vector2>& lineVertexArray,
			const tktkMath::Color& lineColor,
			const tktkMath::Color& blendRate,
			unsigned int useRtvDescriptorHeapId
		);

	public:

		void start();
		void draw() const;

	public:

		// 線分を構成する頂点座標の配列を取得する
		const std::vector<tktkMath::Vector2>& getLineVertexArray() const;

		// 線分を構成する頂点座標の配列を設定する
		void setLineVertexArray(const std::vector<tktkMath::Vector2>& vertexArray);

		// 線の色を取得する
		const tktkMath::Color& getLineColor() const;

		// 線の色を設定する
		void setLineColor(const tktkMath::Color& color);

		// ブレンドレートを再設定する
		void setBlendRate(const tktkMath::Color& blendRate);

	private:

		unsigned int					m_useLine2DMaterialId;
		unsigned int					m_useRtvDescriptorHeapId;
		std::vector<tktkMath::Vector2>	m_lineVertexArray;
		tktkMath::Color					m_lineColor{ tktkMath::colorWhite };
		tktkMath::Color					m_blendRate{ 1.0f, 1.0f, 1.0f, 1.0f };
		
		ComponentPtr<Transform2D> m_transform{  };
	};
}
#endif // !LINE_2D_DRAWER_H_