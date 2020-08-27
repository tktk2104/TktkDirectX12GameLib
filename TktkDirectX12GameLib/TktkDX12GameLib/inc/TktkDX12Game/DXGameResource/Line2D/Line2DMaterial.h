#ifndef LINE_2D_H_
#define LINE_2D_H_

#include <TktkContainer/ResourceContainer/ResourceContainer.h>
#include <TktkDX12Wrapper/Resource/GraphicsPipeLine/PipeLineState/PipeLineStateInitParam.h>
#include "Line2DMaterialData.h"

namespace tktk
{
	// 「Line2DMaterialData」を管理するクラス
	class Line2DMaterial
	{
	public:

		Line2DMaterial(const ShaderFilePaths& shaderFilePaths, const tktkContainer::ResourceContainerInitParam& initParam);
		~Line2DMaterial() = default;

	public:

		// ２Ｄラインを作り、そのリソースのハンドルを返す
		unsigned int create();

		// 指定の２Ｄラインを描画する
		// ※前フレームで作った頂点バッファを削除し、内部でライン描画用の頂点バッファを作り、そのリソースハンドルを保持する処理の為、非const関数
		void drawLine(unsigned int handle, const Line2DMaterialDrawFuncArgs& drawFuncArgs);

	private:

		// ２Ｄライン描画用のルートシグネチャを作る
		void createBasicDescriptorHeap() const;

		// ２Ｄライン描画用のルートシグネチャを作る
		void createRootSignature() const;

		// ２Ｄライン描画用のパイプラインステートを作る
		void createGraphicsPipeLineState(const ShaderFilePaths& shaderFilePaths) const;

	private:

		tktkContainer::ResourceContainer<Line2DMaterialData> m_line2DMaterialArray;
	};
}
#endif // !LINE_2D_H_