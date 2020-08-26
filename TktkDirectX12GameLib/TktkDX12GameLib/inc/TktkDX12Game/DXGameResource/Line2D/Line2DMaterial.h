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
		void create(unsigned int id);

		// 指定の２Ｄラインを描画する
		// ※前フレームで作った頂点バッファを削除し、内部でライン描画用の頂点バッファを作り、そのリソースハンドルを保持する処理の為、非const関数
		void drawLine(unsigned int id, const Line2DMaterialDrawFuncArgs& drawFuncArgs);

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