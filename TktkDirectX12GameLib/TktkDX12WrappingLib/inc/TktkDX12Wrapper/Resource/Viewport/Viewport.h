#ifndef VIEWPORT_H_
#define VIEWPORT_H_

#include <TktkContainer/HeapArray/HeapArray.h>
#include "ViewportData.h"

namespace tktk
{
	// 「ViewportData」を管理するクラス
	class Viewport
	{
	public:

		Viewport(unsigned int viewportNum);

	public:

		// 「ViewportData」のインスタンスを作る
		void create(unsigned int id, const std::vector<ViewportInitParam>& initParamArray);

		// 指定のビューポートをコマンドリストに登録する
		void set(unsigned int id, ID3D12GraphicsCommandList* commandList) const;

	private:

		HeapArray<ViewportData> m_viewportDataArray;
	};
}
#endif // !VIEWPORT_H_