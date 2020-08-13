#ifndef VIEWPORT_DATA_H_
#define VIEWPORT_DATA_H_

#include <vector>
#include "../../Includer/D3d12Includer.h"
#include "ViewportInitParam.h"

namespace tktk
{
	// ビューポートを管理するクラス
	class ViewportData
	{
	public:

		ViewportData(const std::vector<ViewportInitParam>& initParamArray);
		~ViewportData() = default;

	public:

		// 自身をコマンドリストに登録する
		void set(ID3D12GraphicsCommandList* commandList) const;
	
	private:

		std::vector<D3D12_VIEWPORT> m_viewportArray{};
	};
}
#endif // !VIEWPORT_DATA_H_