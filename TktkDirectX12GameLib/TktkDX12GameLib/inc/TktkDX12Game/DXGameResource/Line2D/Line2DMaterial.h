#ifndef LINE_2D_H_
#define LINE_2D_H_

#include <TktkContainer/HeapArray/HeapArray.h>
#include <TktkDX12Wrapper/Resource/GraphicsPipeLine/PipeLineState/PipeLineStateInitParam.h>
#include "Line2DMaterialData.h"

namespace tktk
{
	// 「Line2DMaterialData」を管理するクラス
	class Line2DMaterial
	{
	public:

		Line2DMaterial(const ShaderFilePaths& shaderFilePaths, unsigned int line2DMaterialNum);
		~Line2DMaterial() = default;

	public:

		// ２Ｄラインを作る
		void create(unsigned int id, const Line2DMaterialDataInitParam& initParam);

		// 指定の２Ｄラインを描画する
		void drawLine(unsigned int id, const Line2DMaterialDrawFuncArgs& drawFuncArgs) const;

	private:

		// ２Ｄライン描画用のルートシグネチャを作る
		void createBasicDescriptorHeap() const;

		// ２Ｄライン描画用のルートシグネチャを作る
		void createRootSignature() const;

		// ２Ｄライン描画用のパイプラインステートを作る
		void createGraphicsPipeLineState(const ShaderFilePaths& shaderFilePaths) const;

	private:

		tktkContainer::HeapArray<Line2DMaterialData> m_line2DMaterialArray;
	};
}
#endif // !LINE_2D_H_